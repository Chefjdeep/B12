# app.py - Main Flask App with Ghidra + Enhancement
from flask import Flask, request, jsonify, render_template
from flask_cors import CORS
from enhance import LLM4DecompileEnhancer
import requests
import torch
import os
import subprocess
import tempfile
import shutil
import datetime
import time
import re

# ==============================================================
# 🧠 MODEL CONFIGURATION
# ==============================================================
MODEL_PATH = "LLM4Binary/llm4decompile-1.3b-v1.5"
DEVICE = "cuda" if torch.cuda.is_available() else "mps"

# ==============================================================
# ⚙️ GHIDRA CONFIGURATION
# ==============================================================
GHIDRA_PATH = "LLM4Decompile/ghidra/ghidra_11.0.3_PUBLIC/support/analyzeHeadless"
GHIDRA_SCRIPT = "LLM4Decompile/ghidra/decompile.py"
PROJECT_NAME = "tmp_ghidra_proj"
TEMP_SAVE_DIR = "LLM4Decompile/temp_saves"
OUTPUT_DIR = "Ghidra_decompiled"
ENHANCED_OUTPUT_DIR = "Enhanced_Decompiled"
TIMEOUT = 120

# Create directories
os.makedirs(TEMP_SAVE_DIR, exist_ok=True)
os.makedirs(OUTPUT_DIR, exist_ok=True)
os.makedirs(ENHANCED_OUTPUT_DIR, exist_ok=True)

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
# 🌐 FLASK APP INITIALIZATION
# ==============================================================
app = Flask(__name__, template_folder="templates")
CORS(app)

# ===============================
# CONFIG: Enhancement Mode
# ===============================
# Choose one: "colab" or "local"
ENHANCEMENT_MODE = "colab"  # Change to "local" if you want local model

# Colab URL (for colab mode)
COLAB_NGROK_URL = "https://joetta-colorimetric-audra.ngrok-free.dev/llm4decompile"

# Initialize enhancer - THIS IS YOUR ENHANCER INSTANCE
enhancer = LLM4DecompileEnhancer(
    use_local_model=(ENHANCEMENT_MODE == "local"),
    colab_url=COLAB_NGROK_URL if ENHANCEMENT_MODE == "colab" else None
)

print(f"\n🔧 Enhancement Mode: {ENHANCEMENT_MODE.upper()}")
print(f"🔗 Colab URL: {COLAB_NGROK_URL if ENHANCEMENT_MODE == 'colab' else 'Not used'}\n")

# ==============================================================
# 🏠 ROUTES
# ==============================================================

@app.route("/")
def home():
    return render_template("index.html")

@app.route("/status")
def status():
    """Check server status"""
    ghidra_status = check_ghidra_environment()
    return jsonify({
        "status": "running",
        "enhancement_mode": ENHANCEMENT_MODE,
        "ghidra_available": ghidra_status is None,
        "ghidra_error": ghidra_status,
        "colab_url": COLAB_NGROK_URL if ENHANCEMENT_MODE == "colab" else None,
        "local_model": ENHANCEMENT_MODE == "local"
    })

# ==============================================================
# 🧠 LLM DECOMPILATION ROUTE
# ==============================================================

@app.route("/decompile", methods=["POST"])
def decompile_llm():
    """LLM-based decompilation for assembly files"""
    if "file" not in request.files:
        return jsonify({"error": "No file uploaded"}), 400

    asm_file = request.files["file"]
    filename = asm_file.filename
    file_bytes = asm_file.read()
    
    try:
        asm_text = file_bytes.decode("utf-8", errors="ignore").strip()
    except Exception:
        asm_text = ""

    if not file_bytes:
        return jsonify({"error": "File is empty"}), 400

    print(f"📜 LLM decompilation: {filename}")

    # Create prompt for LLM4Decompile
    prompt = f"# This is the assembly code:\n{asm_text}\n# What is the source code?\n"
    
    # Convert to bytes for API
    file_bytes = prompt.encode('utf-8')
    
    try:
        # Send to Colab API
        files = {"file": (filename, file_bytes)}
        response = requests.post(COLAB_NGROK_URL, files=files, timeout=120)
        
        if response.status_code == 200:
            result = response.json()
            decompiled_code = result.get("decompiled_code", "")
            severity_score = result.get("severity", 0)
        else:
            decompiled_code = f"// API Error: {response.status_code}"
            severity_score = 0
    except Exception as e:
        decompiled_code = f"// Error: {str(e)}"
        severity_score = 0
    
    # Calculate severity if not provided
    if severity_score == 0:
        severity_score, severity_label = calculate_severity_score(decompiled_code)
    else:
        _, severity_label = calculate_severity_score(decompiled_code)
    
    return jsonify({
        "decompiled_code": decompiled_code,
        "severity_score": severity_score,
        "severity_label": severity_label,
        "method": "llm_colab"
    })

# ==============================================================
# ⚙️ GHIDRA DECOMPILATION ROUTES
# ==============================================================

@app.route("/ghidra_decompile", methods=["POST"])
def ghidra_decompile():
    """Ghidra decompilation ONLY (no enhancement)"""
    return run_ghidra_analysis(enhance=False)

@app.route("/ghidra_enhance", methods=["POST"])
def ghidra_enhance():
    """Ghidra decompilation WITH LLM enhancement"""
    return run_ghidra_analysis(enhance=True)

def run_ghidra_analysis(enhance=False):
    """Run Ghidra analysis with optional enhancement"""
    # Check Ghidra environment
    env_error = check_ghidra_environment()
    if env_error:
        return jsonify({"error": env_error}), 500

    if "file" not in request.files:
        return jsonify({"error": "No file uploaded"}), 400

    upload_file = request.files["file"]
    filename = upload_file.filename

        # Accept actual binary formats that Ghidra can handle
    supported_extensions = {'.o', '.elf', '.exe', '.so', '.dll', '.dylib', '.bin', '.rom', '.img'}
    file_ext = os.path.splitext(filename)[1]
    
    if file_ext not in supported_extensions:
        return jsonify({
            "error": f"File type {file_ext} not supported by Ghidra",
            "supported_formats": list(supported_extensions)
        }), 400

    timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
    run_id = f"ghidra_{'enhance' if enhance else 'decompile'}_{os.getpid()}_{timestamp}"
    save_dir = os.path.join(TEMP_SAVE_DIR, run_id)
    os.makedirs(save_dir, exist_ok=True)

    print(f"📦 Running Ghidra {'with enhancement' if enhance else ''} on: {filename}")

    try:
        # Save uploaded file
        binary_path = os.path.join(save_dir, filename)
        upload_file.save(binary_path)

        # Output path for Ghidra
        output_path = os.path.join(save_dir, f"{os.path.splitext(filename)[0]}_decompiled.c")

        # Run Ghidra command
        command = [
            GHIDRA_PATH,
            save_dir,
            PROJECT_NAME,
            "-import", binary_path,
            "-postScript", GHIDRA_SCRIPT, output_path,
            "-deleteProject"
        ]

        print("▶️ Running Ghidra...")
        start_time = time.time()
        result = subprocess.run(command, text=True, capture_output=True, timeout=TIMEOUT)
        ghidra_time = time.time() - start_time

        # Check output
        if not os.path.exists(output_path):
            print("⚠️ Ghidra stderr:", result.stderr[:500])
            return jsonify({
                "error": "Ghidra did not produce output.",
                "stderr": result.stderr[:500]
            }), 500

        # Read Ghidra output
        with open(output_path, "r", encoding="utf-8", errors="ignore") as f:
            ghidra_code = f.read()

        original_ghidra_code = ghidra_code
        enhancement_time = 0
        enhancement_status = "not_requested"
        
        # Apply enhancement if requested
        if enhance:
            print("✨ Applying LLM4Decompile enhancement...")
            enhancement_start = time.time()
            try:
                enhanced_code = enhancer.enhance_code(ghidra_code, filename)
                enhancement_time = time.time() - enhancement_start
                
                if enhanced_code and enhanced_code != ghidra_code:
                    ghidra_code = enhanced_code
                    enhancement_status = "success"
                    print(f"✅ Enhancement completed in {enhancement_time:.2f}s")
                else:
                    enhancement_status = "no_improvement"
                    print("⚠️ No significant improvement")
            except Exception as e:
                enhancement_status = "failed"
                print(f"❌ Enhancement failed: {e}")

        # Save outputs
        ghidra_path = os.path.join(OUTPUT_DIR, f"{os.path.splitext(filename)[0]}_{timestamp}_ghidra.c")
        with open(ghidra_path, "w", encoding="utf-8") as out_file:
            out_file.write(original_ghidra_code)

        if enhancement_status == "success":
            enhanced_path = os.path.join(ENHANCED_OUTPUT_DIR, f"{os.path.splitext(filename)[0]}_{timestamp}_enhanced.c")
            with open(enhanced_path, "w", encoding="utf-8") as out_file:
                out_file.write(ghidra_code)

        # Calculate severity
        severity_score, severity_label = calculate_severity_score(ghidra_code)
        
        # Get enhancement stats
        enhancement_info = enhancer.get_enhancement_info(
            len(original_ghidra_code), 
            len(ghidra_code)
        )

        print(f"✅ Analysis complete!")
        print(f"   - Ghidra time: {ghidra_time:.2f}s")
        if enhancement_time > 0:
            print(f"   - Enhancement time: {enhancement_time:.2f}s")
        print(f"   - Severity: {severity_label} ({severity_score}%)")

        return jsonify({
            "decompiled_code": ghidra_code,
            "severity_score": severity_score,
            "severity_label": severity_label,
            "method": "ghidra_enhanced" if enhance else "ghidra_only",
            "enhancement_status": enhancement_status,
            "ghidra_time": round(ghidra_time, 2),
            "enhancement_time": round(enhancement_time, 2) if enhancement_time > 0 else 0,
            "enhancement_info": enhancement_info,
            "saved_files": {
                "original": ghidra_path,
                "enhanced": enhanced_path if enhancement_status == "success" else None
            }
        })

    except subprocess.TimeoutExpired:
        return jsonify({"error": f"Ghidra decompilation timed out after {TIMEOUT}s"}), 504
    except Exception as e:
        print("❌ Error:", str(e))
        return jsonify({"error": str(e)}), 500

# ==============================================================
# 🛠️ HELPER FUNCTIONS
# ==============================================================

def calculate_severity_score(code):
    """Calculate threat severity score"""
    if not code:
        return 0, "Low"
    
    lower_code = code.lower()
    score = 0
    
    # Threat patterns
    patterns = [
        (["shell", "exec", "system(", "popen", "CreateProcess"], 40),
        (["socket", "bind", "listen", "connect", "send", "recv"], 30),
        (["malloc", "calloc", "realloc", "free", "VirtualAlloc"], 20),
        (["strcpy", "strcat", "sprintf", "memcpy"], 25),
        (["download", "wget", "curl", "upload"], 40),
        (["encrypt", "decrypt", "crypt", "xor"], 35),
        (["LoadLibrary", "GetProcAddress", "dlopen", "dlsym"], 30),
    ]
    
    for keywords, weight in patterns:
        if any(keyword in lower_code for keyword in keywords):
            score += weight
    
    # Reduce score for safe patterns
    if "printf" in lower_code or "cout" in lower_code:
        score = max(0, score - 10)
    if "main(" in lower_code:
        score = max(0, score - 5)
    
    score = min(100, score)
    
    if score < 30:
        label = "Low"
    elif score < 70:
        label = "Medium"
    else:
        label = "High"
    
    return score, label

# ==============================================================
# 🆕 DIRECT ENHANCEMENT ROUTE
# ==============================================================

@app.route("/enhance_code", methods=["POST"])
def enhance_existing_code():
    """Enhance already decompiled code"""
    data = request.get_json()
    if not data or "code" not in data:
        return jsonify({"error": "No code provided"}), 400
    
    code = data["code"]
    filename = data.get("filename", "unknown.c")
    mode = data.get("mode", "all")  # Optional: "all", "single", "func:NAME"
    
    try:
        print(f"✨ Enhancing existing code: {filename}")
        # Use the enhancer instance defined at line 85 in your app.py
        enhanced_code = enhancer.enhance_code(code, filename, mode=mode)
        score, label = calculate_severity_score(enhanced_code)
        
        # Get enhancement info
        enhancement_info = enhancer.get_enhancement_info(len(code), len(enhanced_code))
        
        return jsonify({
            "enhanced_code": enhanced_code,
            "severity_score": score,
            "severity_label": label,
            "enhancement_info": enhancement_info,
            "improved": enhanced_code != code
        })
        
    except Exception as e:
        print(f"❌ Enhancement failed: {e}")
        return jsonify({"error": str(e)}), 500
# ==============================================================
# Classification ROUTE
# ==============================================================
# In app.py - Simple classification endpoint
@app.route("/classify", methods=["POST"])
def classify_binary():
    """Classify binary by importing classifier directly"""
    if "file" not in request.files:
        return jsonify({"error": "No file uploaded"}), 400
    
    file = request.files["file"]
    try:
        import tempfile
        import os
        import sys
        
        # Add classifier to path
        classifier_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), "classifier")
        sys.path.append(classifier_dir)
        
        # Import directly
        from classifier.pipeline.language_inferencer import LanguageInferencer
        
        # Save file
        with tempfile.NamedTemporaryFile(delete=False, suffix='.o') as tmp:
            file.save(tmp.name)
            temp_path = tmp.name
        
        # Run classification
        model_path = os.path.join(classifier_dir, "models", "language_classifier.pkl")
        inferencer = LanguageInferencer(model_path)
        result = inferencer.analyze_binary(temp_path)
        
        # Clean up
        os.unlink(temp_path)
        
        # Format response
        c_prob = result.get('C', 0.5)
        cpp_prob = result.get('C++', 0.5)
        confidence = result.get('confidence', max(c_prob, cpp_prob))
        language = "C++" if cpp_prob > c_prob else "C"
        
        return jsonify({
            "language": language,
            "confidence": confidence,
            "c_prob": c_prob,
            "cpp_prob": cpp_prob,
            "method": "direct_import"
        })
        
    except Exception as e:
        print(f"Direct classification error: {e}")
        return jsonify({
            "error": str(e),
            "language": "Unknown",
            "confidence": 0.5,
            "c_prob": 0.5,
            "cpp_prob": 0.5
        }), 500
# ==============================================================
# 🖥️ RUN SERVER
# ==============================================================

if __name__ == "__main__":
    port = int(os.environ.get("PORT", 5000))
    
    print("\n" + "="*60)
    print("🚀 ML DECOMPILER SERVER")
    print("="*60)
    print(f"🌍 Server: http://0.0.0.0:{port}")
    print(f"⚙️  Ghidra: {'Available' if check_ghidra_environment() is None else 'Not Available'}")
    print(f"🧠 Enhancement: {ENHANCEMENT_MODE.upper()} mode")
    print(f"📡 Colab URL: {COLAB_NGROK_URL if ENHANCEMENT_MODE == 'colab' else 'Not used'}")
    print("="*60)
    print("\n📋 Available Endpoints:")
    print("  - POST /decompile        → LLM decompilation (Colab)")
    print("  - POST /ghidra_decompile → Ghidra only")
    print("  - POST /ghidra_enhance   → Ghidra + LLM enhancement")
    print("  - POST /enhance_code     → Enhance existing code")
    print("  - GET  /status           → Server status")
    print("  - POST /classify         → Language Classification")
    print("="*60)
    
    app.run(host="0.0.0.0", port=port, debug=False)