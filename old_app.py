from flask import Flask, request, jsonify, render_template
from flask_cors import CORS
from transformers import AutoTokenizer, AutoModelForCausalLM
import torch, os, subprocess, tempfile, shutil, datetime

# ==============================================================
# 🧠 MODEL SETUP (LLM Decompiler)
# ==============================================================
MODEL_PATH = "LLM4Binary/llm4decompile-1.3b-v1.5"   # Change if needed
DEVICE = "cuda" if torch.cuda.is_available() else "mps"

print("🚀 Loading model...")
# tokenizer = AutoTokenizer.from_pretrained(MODEL_PATH)
# model = AutoModelForCausalLM.from_pretrained(
#     MODEL_PATH,
#     torch_dtype=torch.float32 if DEVICE == "cuda" else torch.float32,
#     device_map="auto" if DEVICE == "cuda" else None
# )
# model.to("mps")
# model.eval()
print(f"✅ Model loaded on {DEVICE.upper()}!")

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

@app.route("/")
def home():
    return render_template("ghidra.html")


# ==============================================================
# 🧠 LLM Decompiler Route
# ==============================================================
@app.route("/decompile", methods=["POST"])
def decompile_llm():
    """LLM-based decompilation for uploaded ASM text"""
    if "file" not in request.files:
        return jsonify({"error": "No file uploaded"}), 400

    asm_file = request.files["file"]
    asm_text = asm_file.read().decode("utf-8").strip()

    if not asm_text:
        return jsonify({"error": "File is empty"}), 400

    print(f"📜 Received ASM file: {asm_file.filename}")

    try:
        # Tokenize + generate
        inputs = tokenizer(asm_text, return_tensors="pt").to(model.device)
        with torch.no_grad():
            outputs = model.generate(
                **inputs,
                max_new_tokens=2048,
                temperature=0.7,
                do_sample=True,
                top_p=0.95,
                pad_token_id=tokenizer.eos_token_id,
            )

        decoded = tokenizer.decode(
            outputs[0][len(inputs["input_ids"][0]):],
            skip_special_tokens=True
        ).strip()

        return jsonify({"decompiled_code": decoded})

    except Exception as e:
        print("❌ LLM Error:", str(e))
        return jsonify({"error": str(e)}), 500


# ==============================================================
# ⚙️ Ghidra Decompiler Route
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
# 🖥️ Run the Server
# ==============================================================
if __name__ == "__main__":
    port = int(os.environ.get("PORT", 5000))
    print(f"🌍 Server running on http://0.0.0.0:{port}")
    app.run(host="0.0.0.0", port=port, debug=False)








