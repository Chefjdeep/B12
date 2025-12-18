from flask import Flask, request, jsonify, render_template
from flask_cors import CORS
# from transformers import AutoTokenizer, AutoModelForCausalLM  # Original model imports (commented)
import requests  # NEW: used to forward requests to Colab/ngrok
import torch, os, subprocess, tempfile, shutil, datetime

# ==============================================================
# 🧠 MODEL SETUP (LLM Decompiler)
# ==============================================================
MODEL_PATH = "LLM4Binary/llm4decompile-1.3b-v1.5"   # Change if needed
DEVICE = "cuda" if torch.cuda.is_available() else "mps"

print("🚀 (Info) Model config prepared...")
# --------------------------
# ORIGINAL LOCAL MODEL USAGE (COMMENTED OUT)
# --------------------------
# The lines below show how your local model would be loaded.
# They are intentionally commented out — keep them as reference / fallback.
#
# print("🚀 Loading model...")
# tokenizer = AutoTokenizer.from_pretrained(MODEL_PATH)
# model = AutoModelForCausalLM.from_pretrained(
#     MODEL_PATH,
#     torch_dtype=torch.float32 if DEVICE == "cuda" else torch.float32,
#     device_map="auto" if DEVICE == "cuda" else None
# )
# model.to(DEVICE)
# model.eval()
# print(f"✅ Model loaded on {DEVICE.upper()}!")
#
# --------------------------
print(f"✅ Model config set (no local model loaded). Device hint: {DEVICE.upper()}")

# ==============================================================
# ⚙️ Ghidra Setup
# ==============================================================
GHIDRA_PATH = "LLM4Decompile/ghidra/ghidra_11.0.3_PUBLIC/support/analyzeHeadless"
GHIDRA_SCRIPT = "LLM4Decompile/ghidra/decompile.py"
PROJECT_NAME = "tmp_ghidra_proj"
TEMP_SAVE_DIR = "LLM4Decompile/temp_saves"
OUTPUT_DIR = "Ghidra_decompiled"
TIMEOUT = 120

os.makedirs(TEMP_SAVE_DIR, exist_ok=True)
os.makedirs(OUTPUT_DIR, exist_ok=True)

def check_ghidra_environment():
    """Ensure Ghidra and Java are available"""
    if not os.path.exists(GHIDRA_PATH):
        return f"Ghidra not found at {GHIDRA_PATH}"
    if not os.path.exists(GHIDRA_SCRIPT):
        return f"Ghidra script not found at {GHIDRA_SCRIPT}"
    if shutil.which("java") is None:
        return "Java runtime not found. Please install Java (OpenJDK 17+)."
    return None


# ==============================================================
# 🌐 Flask App
# ==============================================================
app = Flask(__name__, template_folder="templates")
CORS(app)

# ===============================
# CONFIG: Colab/ngrok forwarding
# ===============================
# Option A: set the ngrok Colab URL here:
COLAB_NGROK_URL = "https://xavi-sawdusty-reciprocatively.ngrok-free.dev/llm4decompile"
# Example: "https://abcd1234.ngrok.io/llm4decompile"
#
# If COLAB_NGROK_URL is non-empty, the /decompile route will forward
# the uploaded file to that URL and return the Colab response.
#
# If empty, the route will fall back to local (commented) model behavior
# or use a minimal local severity heuristic.
USE_COLAB = bool(COLAB_NGROK_URL)

@app.route("/")
def home():
    return render_template("ghidra.html")


# ==============================================================
# 🔁 Helper: forward file to Colab/ngrok endpoint
# ==============================================================
def forward_to_colab(file_bytes, filename):
    """
    Send uploaded file bytes to Colab/ngrok endpoint for LLM4Decompile inference.
    Returns parsed JSON response or raises an exception on failure.
    """
    if not COLAB_NGROK_URL:
        raise RuntimeError("COLAB_NGROK_URL not configured")

    try:
        files = {"file": (filename, file_bytes)}
        # You may want to set headers/auth if your Colab endpoint requires it
        resp = requests.post(COLAB_NGROK_URL, files=files, timeout=120)
        resp.raise_for_status()
        return resp.json()
    except Exception as e:
        # Bubble up a clear error
        raise RuntimeError(f"Forwarding to Colab failed: {e}")


# ==============================================================
# 🧠 LLM Decompiler Route (now forwards to Colab if configured)
# ==============================================================
@app.route("/decompile", methods=["POST"])
def decompile_llm():
    """LLM-based decompilation for uploaded ASM text.
    If COLAB_NGROK_URL is set, this will forward the file to the Colab endpoint
    and return the endpoint's JSON. Otherwise, it uses a local fallback heuristic.
    """
    if "file" not in request.files:
        return jsonify({"error": "No file uploaded"}), 400

    asm_file = request.files["file"]
    filename = asm_file.filename

    # Read bytes once (we'll decode for local fallback and forward bytes to Colab)
    file_bytes = asm_file.read()
    try:
        asm_text = file_bytes.decode("utf-8", errors="ignore").strip()
    except Exception:
        asm_text = ""

    if not file_bytes:
        return jsonify({"error": "File is empty"}), 400

    print(f"📜 Received file for decompilation: {filename}  (size: {len(file_bytes)} bytes)")

    # --------------------------
    # If configured, forward to Colab/ngrok endpoint
    # --------------------------
    if USE_COLAB:
        try:
            print(f"🌐 Forwarding to Colab/ngrok URL: {COLAB_NGROK_URL}")
            colab_result = forward_to_colab(file_bytes, filename)

            # Expecting JSON like: { "decompiled_code": "...", "severity": 42, ... }
            # Normalize field names for frontend compatibility
            decompiled_code = colab_result.get("decompiled_code") or colab_result.get("decompiled") or ""
            severity_score = colab_result.get("severity") or colab_result.get("severity_score") or None
            severity_label = colab_result.get("severity_label") or None

            # If severity not provided by Colab, compute a simple local heuristic (below)
            if severity_score is None:
                # Minimal heuristic: compute locally from the decompiled_code or asm_text
                text_source = (decompiled_code or asm_text).lower()
                severity_calc = 0
                if any(x in text_source for x in ["shell", "exec", "payload", "socket", "system(", "download", "encrypt"]):
                    severity_calc += 70
                if "printf" in text_source or "cout" in text_source:
                    severity_calc += 10
                if "main" in text_source:
                    severity_calc += 5
                severity_score = min(100, severity_calc)
                severity_label = ("Low" if severity_score < 30 else "Medium" if severity_score < 70 else "High")

            return jsonify({
                "decompiled_code": decompiled_code,
                "severity_score": severity_score,
                "severity_label": severity_label,
                "colab_raw": colab_result  # optional: for debugging, remove in production
            })

        except Exception as e:
            # If forwarding fails, return informative error (and also attempt local fallback)
            print("❌ Error forwarding to Colab:", e)
            # Fall through to local fallback below (so UI still gets something)
            # You may prefer to return an error instead; adjust as needed.
            # return jsonify({"error": str(e)}), 500

    # --------------------------
    # FALLBACK: Local behaviour (commented-out real model + light heuristic)
    # --------------------------
    try:
        # --------------------------
        # ORIGINAL MODEL INFERENCE (COMMENTED OUT)
        # --------------------------
        # The following shows how you would run the local LLM if it were enabled.
        # Keep commented unless you have the model available locally.
        #
        # inputs = tokenizer(asm_text, return_tensors="pt").to(model.device)
        # with torch.no_grad():
        #     outputs = model.generate(
        #         **inputs,
        #         max_new_tokens=2048,
        #         temperature=0.7,
        #         do_sample=True,
        #         top_p=0.95,
        #         pad_token_id=tokenizer.eos_token_id,
        #     )
        # decoded = tokenizer.decode(
        #     outputs[0][len(inputs["input_ids"][0]):],
        #     skip_special_tokens=True
        # ).strip()

        # --------------------------
        # SIMPLE LOCAL HEURISTIC (fallback) — NOT the LLM
        # --------------------------
        decoded = asm_text if asm_text else "// Binary data — no text representation available\n"

        # compute a basic severity score from decoded text
        lower_code = decoded.lower()
        severity_score = 0
        if any(x in lower_code for x in ["shell", "exec", "payload", "socket", "system(", "download", "encrypt"]):
            severity_score += 70
        if "printf" in lower_code or "cout" in lower_code:
            severity_score += 10
        if "main" in lower_code:
            severity_score += 5
        severity_score = min(severity_score, 100)
        severity_label = ("Low" if severity_score < 30 else "Medium" if severity_score < 70 else "High")

        return jsonify({
            "decompiled_code": decoded,
            "severity_score": severity_score,
            "severity_label": severity_label
        })

    except Exception as e:
        print("❌ LLM/Fallback Error:", str(e))
        return jsonify({"error": str(e)}), 500


# ==============================================================
# ⚙️ Ghidra Decompiler Route (UNCHANGED)
# ==============================================================
@app.route("/ghidra_decompile", methods=["POST"])
def ghidra_decompile():
    """Run Ghidra decompilation on uploaded .o or .asm file"""
    env_error = check_ghidra_environment()
    if env_error:
        return jsonify({"error": env_error}), 500

    if "file" not in request.files:
        return jsonify({"error": "No file uploaded"}), 400

    upload_file = request.files["file"]
    filename = upload_file.filename

    if not (filename.endswith(".o") or filename.endswith(".asm")):
        return jsonify({"error": "Only .o or .asm files are supported"}), 400

    timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
    run_id = f"ghidra_run_{os.getpid()}_{timestamp}"
    save_dir = os.path.join(TEMP_SAVE_DIR, run_id)
    os.makedirs(save_dir, exist_ok=True)

    print(f"📦 Running Ghidra on: {filename}")
    print(f"📂 Saving temp data to: {save_dir}")

    try:
        # Save uploaded file to temp dir
        binary_path = os.path.join(save_dir, filename)
        upload_file.save(binary_path)

        # Output path for Ghidra
        output_path = os.path.join(save_dir, f"{os.path.splitext(filename)[0]}_decompiled.c")

        # Run Ghidra
        command = [
            GHIDRA_PATH,
            save_dir,
            PROJECT_NAME,
            "-import", binary_path,
            "-postScript", GHIDRA_SCRIPT, output_path,
            "-deleteProject"
        ]

        print("▶️ Running:", " ".join(command))
        result = subprocess.run(command, text=True, capture_output=True, timeout=TIMEOUT)

        # Check output
        if not os.path.exists(output_path):
            print("⚠️ Ghidra stderr:", result.stderr)
            return jsonify({
                "error": "Ghidra did not produce output.",
                "stderr": result.stderr,
                "stdout": result.stdout
            }), 500

        # Read Ghidra output
        with open(output_path, "r", encoding="utf-8", errors="ignore") as f:
            c_code = f.read()

        # Save final pseudo file
        final_path = os.path.join(OUTPUT_DIR, f"{os.path.splitext(filename)[0]}_{timestamp}.pseudo")
        with open(final_path, "w", encoding="utf-8") as out_file:
            out_file.write(c_code)

        print(f"✅ Ghidra decompilation complete!")
        print(f"📝 Saved final output to: {final_path}")

        return jsonify({
            "decompiled_code": c_code,
            "stderr": result.stderr,
            "stdout": result.stdout,
            "saved_path": final_path
        })

    except subprocess.TimeoutExpired:
        return jsonify({"error": f"Ghidra decompilation timed out after {TIMEOUT}s"}), 504
    except Exception as e:
        print("❌ Error:", str(e))
        return jsonify({"error": str(e)}), 500


# ==============================================================
# Optional: Automatically start ngrok tunnel locally (COMMENTED / OPTIONAL)
# ==============================================================
# If you want the Flask app itself to start an ngrok tunnel (for
# exposing the app, not required to forward to Colab), you can
# uncomment the following block and install pyngrok.
#
# try:
#     from pyngrok import ngrok
#     port = int(os.environ.get("PORT", 5000))
#     public_url = ngrok.connect(port).public_url
#     print(f"🌍 Public Ngrok URL for this Flask server: {public_url}")
# except Exception as e:
#     print("⚠️ Ngrok not available (optional):", e)


# ==============================================================
# 🖥️ Run the Server
# ==============================================================
if __name__ == "__main__":
    port = int(os.environ.get("PORT", 5000))
    print(f"🌍 Server running on http://0.0.0.0:{port}")
    app.run(host="0.0.0.0", port=port, debug=False)
