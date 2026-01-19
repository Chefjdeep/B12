# app.py - Main Flask App with Ghidra + Heuristic Enhancement + Security Analysis
from flask import Flask, request, jsonify, render_template, session
from flask_cors import CORS
from enhance import HeuristicEnhancer
import requests
import os
import subprocess
import tempfile
import shutil
import datetime
import time
import re
import json

# ==============================================================
# GHIDRA CONFIGURATION
# ==============================================================
GHIDRA_PATH = "ghidra/ghidra_11.0.3_PUBLIC/support/analyzeHeadless"
GHIDRA_SCRIPT = "ghidra/decompile.py"
PROJECT_NAME = "tmp_ghidra_proj"
TEMP_SAVE_DIR = "temp_saves"
OUTPUT_DIR = "Ghidra_decompiled"
ENHANCED_OUTPUT_DIR = "Enhanced_Decompiled"
TIMEOUT = 120

# ==============================================================
# SECURITY ANALYSIS CONFIGURATION
# ==============================================================
SECURITY_API_URL = "http://127.0.0.1:5500/analyze"  # Your security analysis API

# ==============================================================
# SECURITY CATEGORIES FOR RADAR CHART
# ==============================================================
SECURITY_CATEGORIES = [
    "DATA_EXFILTRATION",
    "PERSISTENCE", 
    "PRIVILEGE_ESCALATION",
    "SURVEILLANCE",
    "DESTRUCTIVE",
    "EVASION",
    "DENIAL_OF_SERVICE",
    "CREDENTIAL_THEFT"
]

# Create directories
os.makedirs(TEMP_SAVE_DIR, exist_ok=True)
os.makedirs(OUTPUT_DIR, exist_ok=True)
os.makedirs(ENHANCED_OUTPUT_DIR, exist_ok=True)

# Global variable for current Ghidra file
current_ghidra_file = None

# Initialize the enhancer globally
enhancer = HeuristicEnhancer()

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
# FLASK APP INITIALIZATION
# ==============================================================
app = Flask(__name__, template_folder="templates")
app.secret_key = os.urandom(24)  # For session management
CORS(app)

# ==============================================================
# ROUTES
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
        "ghidra_available": ghidra_status is None,
        "ghidra_error": ghidra_status,
        "security_api_configured": SECURITY_API_URL is not None,
        "security_api_url": SECURITY_API_URL,
        "categories": SECURITY_CATEGORIES
    })

# ==============================================================
# GHIDRA DECOMPILATION ROUTES
# ==============================================================

@app.route("/ghidra_decompile", methods=["POST"])
def ghidra_decompile():
    """Ghidra decompilation ONLY (no enhancement)"""
    return run_ghidra_analysis(enhance=False)

@app.route("/ghidra_enhance", methods=["POST"])
def ghidra_enhance():
    """Ghidra decompilation WITH heuristic enhancement"""
    return run_ghidra_analysis(enhance=True)

def run_ghidra_analysis(enhance=False):
    """Run Ghidra analysis with optional enhancement"""
    global current_ghidra_file
    
    env_error = check_ghidra_environment()
    if env_error:
        return jsonify({"error": env_error}), 500

    if "file" not in request.files:
        return jsonify({"error": "No file uploaded"}), 400

    upload_file = request.files["file"]
    filename = upload_file.filename

    supported_extensions = {'.o', '.elf', '.exe', '.so', '.dll', '.dylib', '.bin', '.rom', '.img', '.c'}
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

    print(f"📦 Running Ghidra {'with heuristic enhancement' if enhance else ''} on: {filename}")

    try:
        binary_path = os.path.join(save_dir, filename)
        upload_file.save(binary_path)

        output_path = os.path.join(save_dir, f"{os.path.splitext(filename)[0]}_decompiled.c")

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

        if not os.path.exists(output_path):
            print("Ghidra stderr:", result.stderr[:500])
            return jsonify({
                "error": "Ghidra did not produce output.",
                "stderr": result.stderr[:500]
            }), 500

        with open(output_path, "r", encoding="utf-8", errors="ignore") as f:
            ghidra_code = f.read()

        original_ghidra_code = ghidra_code
        enhancement_time = 0
        enhancement_status = "not_requested"
        
        if enhance:
            print("✨ Applying heuristic enhancement...")
            enhancement_start = time.time()
            try:
                enhanced_code = enhancer.enhance_code_new(ghidra_code, filename)
                enhancement_time = time.time() - enhancement_start
                
                if enhanced_code and enhanced_code != original_ghidra_code:
                    enhancement_status = "success"
                    ghidra_code = enhanced_code
                    print(f"Heuristic enhancement completed in {enhancement_time:.2f}s")
                else:
                    enhancement_status = "no_improvement"
                    print("No significant improvement from heuristic enhancement")
            except Exception as e:
                enhancement_status = "failed"
                print(f"❌ Heuristic enhancement failed: {e}")
    
        # Store the current Ghidra file path for security analysis
        ghidra_filename = f"{os.path.splitext(filename)[0]}_{timestamp}_ghidra.c"
        current_ghidra_file = ghidra_filename
        session['current_ghidra_file'] = current_ghidra_file
        
        ghidra_path = os.path.join(OUTPUT_DIR, ghidra_filename)
        with open(ghidra_path, "w", encoding="utf-8") as out_file:
            out_file.write(original_ghidra_code)

        enhanced_path = None
        if enhancement_status == "success":
            enhanced_filename = f"{os.path.splitext(filename)[0]}_{timestamp}_enhanced.c"
            enhanced_path = os.path.join(ENHANCED_OUTPUT_DIR, enhanced_filename)
            with open(enhanced_path, "w", encoding="utf-8") as out_file:
                out_file.write(ghidra_code)

        # Get enhancement statistics
        enhancement_info = enhancer.get_enhancement_info(
            len(original_ghidra_code), 
            len(ghidra_code)
        )

        print(f"Analysis complete!")
        print(f"   - Ghidra time: {ghidra_time:.2f}s")
        if enhancement_time > 0:
            print(f"   - Enhancement time: {enhancement_time:.2f}s")

        return jsonify({
            "decompiled_code": ghidra_code,
            "severity_score": 0,
            "severity_label": "Unknown",
            "method": "ghidra_heuristic_enhanced" if enhance else "ghidra_only",
            "enhancement_status": enhancement_status,
            "ghidra_time": round(ghidra_time, 2),
            "enhancement_time": round(enhancement_time, 2) if enhancement_time > 0 else 0,
            "enhancement_info": enhancement_info,
            "saved_files": {
                "original": ghidra_path,
                "enhanced": enhanced_path
            },
            "current_ghidra_file": current_ghidra_file
        })

    except subprocess.TimeoutExpired:
        return jsonify({"error": f"Ghidra decompilation timed out after {TIMEOUT}s"}), 504
    except Exception as e:
        print("Error:", str(e))
        return jsonify({"error": str(e)}), 500

# ==============================================================
# SECURITY ANALYSIS ROUTE
# ==============================================================

@app.route("/security_analyze", methods=["POST"])
def security_analyze():
    """Run security analysis using remote Flask API - SENDS ENHANCED VERSION"""
    global current_ghidra_file
    
    if not current_ghidra_file:
        current_ghidra_file = session.get('current_ghidra_file')
    
    if not current_ghidra_file:
        return jsonify({"error": "No Ghidra file available. Run Ghidra analysis first."}), 400
    
    # MODIFIED: Look for enhanced file instead of original Ghidra file
    # Get base filename without timestamp
    base_name = current_ghidra_file.replace("_ghidra.c", "")
    
    # Look for enhanced file in Enhanced_Decompiled directory
    enhanced_dir = "Enhanced_Decompiled"
    enhanced_file = None
    
    print(f" [DEBUG] Looking for enhanced files matching: {base_name}*_enhanced.c")
    
    # List all enhanced files
    if os.path.exists(enhanced_dir):
        all_files = os.listdir(enhanced_dir)
        print(f" Files in {enhanced_dir}: {all_files}")
        
        # Find enhanced file matching the current Ghidra file
        for f in all_files:
            if f.startswith(base_name) and f.endswith("_enhanced.c"):
                enhanced_file = f
                break
    
    if enhanced_file:
        file_path = os.path.join(enhanced_dir, enhanced_file)
        print(f" Found enhanced file: {enhanced_file}")
    else:
        # Fallback to original Ghidra file if no enhanced version exists
        file_path = os.path.join("Ghidra_decompiled", current_ghidra_file)
        print(f" No enhanced file found, using original: {current_ghidra_file}")
    
    print(f" File being sent: {os.path.basename(file_path)}")
    print(f" Path: {file_path}")
    print(f" File exists: {os.path.exists(file_path)}")
    
    if not os.path.exists(file_path):
        return jsonify({"error": f"C file not found: {file_path}"}), 404
    
    if not SECURITY_API_URL:
        return jsonify({"error": "Security analysis API not configured."}), 500
    
    print(f"Sending ENHANCED file to security API: {SECURITY_API_URL}")
    print(f"File: {os.path.basename(file_path)}")
    
    try:
        with open(file_path, 'rb') as f:
            files = {'file': (os.path.basename(file_path), f, 'text/plain')}
            
            response = requests.post(
                SECURITY_API_URL,
                files=files,
                timeout=180
            )
        
        print(f"API Response Status: {response.status_code}")
        
        if response.status_code == 200:
            try:
                result = response.json()
                security_metrics = process_security_data(result)
                
                return jsonify({
                    "terminal_output": f"Security analysis completed via remote API",
                    "json_report": result,
                    "security_metrics": security_metrics,
                    "method": "remote_flask_api",
                    "success": True,
                    "file_analyzed": os.path.basename(file_path),  # Show which file was sent
                    "is_enhanced": enhanced_file is not None,  # Flag if enhanced or original
                    "api_endpoint": SECURITY_API_URL
                })
            except ValueError:
                return jsonify({
                    "terminal_output": response.text,
                    "json_report": {"raw_response": response.text},
                    "method": "remote_flask_api",
                    "success": True,
                    "file_analyzed": os.path.basename(file_path),
                    "is_enhanced": enhanced_file is not None,
                    "api_endpoint": SECURITY_API_URL
                })
        else:
            error_msg = f"API returned error {response.status_code}"
            try:
                error_data = response.json()
                error_msg = error_data.get('error', error_msg)
            except:
                error_msg = response.text[:500] if response.text else error_msg
            
            print(f"API Error: {error_msg}")
            return jsonify({
                "error": f"Security analysis API failed: {error_msg}",
                "status_code": response.status_code,
                "api_endpoint": SECURITY_API_URL,
                "success": False
            }), 502
            
    except requests.exceptions.Timeout:
        print("API timeout after 180 seconds")
        return jsonify({
            "error": "Security analysis API timeout after 180 seconds",
            "api_endpoint": SECURITY_API_URL
        }), 504
    except requests.exceptions.ConnectionError as ce:
        print(f"🔌 Connection error: {ce}")
        return jsonify({
            "error": f"Could not connect to security analysis API at {SECURITY_API_URL}",
            "details": str(ce),
            "suggestion": "Check if the remote Flask app is running on port 5000"
        }), 503
    except Exception as e:
        print(f"❌ Unexpected error: {e}")
        import traceback
        traceback.print_exc()
        return jsonify({
            "error": f"Security analysis failed: {str(e)}",
            "api_endpoint": SECURITY_API_URL
        }), 500
def process_security_data(security_result):
    """Process security analysis results for radar chart and metrics"""
    try:
        functions = security_result.get('functions', [])
        
        # Map behavior categories to security categories
        BEHAVIOR_TO_CATEGORY = {
    'file_access': 'DATA_EXFILTRATION',
    'memory': 'EVASION',
    
    'network': 'DATA_EXFILTRATION',
    'process': 'PRIVILEGE_ESCALATION',
    'persistence': 'PERSISTENCE',
    'privilege': 'PRIVILEGE_ESCALATION',
    'surveillance': 'SURVEILLANCE',
    'evasion': 'EVASION',
    'destructive': 'DESTRUCTIVE',
    'dos': 'DENIAL_OF_SERVICE',
    'credential': 'CREDENTIAL_THEFT',
    
    # From his sensitive_apis categories
    'file_access': 'DATA_EXFILTRATION',          
    'network': 'DATA_EXFILTRATION',              
    'process': 'PRIVILEGE_ESCALATION',           
    'memory': 'EVASION',                         
    'persistence': 'PERSISTENCE',                
    'privilege': 'PRIVILEGE_ESCALATION',         
    'surveillance': 'SURVEILLANCE',              
    'evasion': 'EVASION',                        
    
    # From malicious_actions indicators 
    'file_access': 'DATA_EXFILTRATION',          
    'network_communication': 'DATA_EXFILTRATION',
    'sensitive_data_access': 'DATA_EXFILTRATION',
    
    'startup_modification': 'PERSISTENCE',
    'cron_job_addition': 'PERSISTENCE',
    'service_installation': 'PERSISTENCE',
    
    'setuid_misuse': 'PRIVILEGE_ESCALATION',
    'passwd_modification': 'PRIVILEGE_ESCALATION',
    'sudo_exploitation': 'PRIVILEGE_ESCALATION',
    
    'keylogging': 'SURVEILLANCE',
    'screenshot_capture': 'SURVEILLANCE',
    'process_enumeration': 'SURVEILLANCE',
    'network_service': 'SURVEILLANCE',
    
    'recursive_deletion': 'DESTRUCTIVE',
    'disk_wiping': 'DESTRUCTIVE',
    'fork_bomb': 'DESTRUCTIVE',
    
    'anti_debugging': 'EVASION',
    'vm_detection': 'EVASION',
    'code_obfuscation': 'EVASION',
    
    'uncontrolled_execution': 'DENIAL_OF_SERVICE',
    'dangerous_api_combination': 'DENIAL_OF_SERVICE',
    
    'shadow_read': 'CREDENTIAL_THEFT',
    'password': 'CREDENTIAL_THEFT',
    'keylog': 'CREDENTIAL_THEFT'
}
        
        malicious_count = len([f for f in functions if f.get('classification', {}).get('malicious', False)])
        total_functions = len(functions)
        
        category_scores = {}
        for category in SECURITY_CATEGORIES:
            category_scores[category] = 0
        
        # Process each function
        for func in functions:
            if func.get('classification', {}).get('malicious', False):
                confidence = func.get('classification', {}).get('confidence', 0.5)
                
                # Extract security categories from behavioral_actions
                behavioral_actions = func.get('classification', {}).get('behavioral_actions', [])
                for action in behavioral_actions:
                    behavior = action.get('behavior', '')
                    if behavior in BEHAVIOR_TO_CATEGORY:
                        category = BEHAVIOR_TO_CATEGORY[behavior]
                        if category in category_scores:
                            category_scores[category] += confidence * 100
                
                # Also check triggers
                triggers = func.get('signals', {}).get('triggers', [])
                for trigger in triggers:
                    if trigger.get('type') == 'api_category':
                        behavior = trigger.get('category', '')
                        if behavior in BEHAVIOR_TO_CATEGORY:
                            category = BEHAVIOR_TO_CATEGORY[behavior]
                            if category in category_scores:
                                count = trigger.get('count', 1)
                                category_scores[category] += confidence * 20 * count
        
        # Normalize scores
        normalized_scores = []
        for category in SECURITY_CATEGORIES:
            score = min(100, category_scores[category])
            normalized_scores.append(score)
        
        # Calculate threat level
        avg_score = sum(normalized_scores) / len(normalized_scores) if normalized_scores else 0
        if avg_score > 70:
            threat_level = "high"
        elif avg_score > 30:
            threat_level = "medium"
        else:
            threat_level = "low"
        
        # Calculate complexity
        total_api_calls = sum(f.get('signals', {}).get('raw_counts', {}).get('total_api_calls', 0) for f in functions)
        avg_api_calls = total_api_calls / total_functions if total_functions > 0 else 0
        
        if avg_api_calls > 10:
            complexity = "High"
        elif avg_api_calls > 5:
            complexity = "Medium"
        else:
            complexity = "Low"
        
        return {
            "radar_data": {
                "labels": SECURITY_CATEGORIES,
                "data": normalized_scores,
                "threat_level": threat_level,
                "avg_score": avg_score
            },
            "metrics": {
                "malicious_functions": malicious_count,
                "total_functions": total_functions,
                "threat_percentage": round((malicious_count / total_functions * 100) if total_functions > 0 else 0),
                "complexity": complexity,
                "avg_api_calls": round(avg_api_calls, 1)
            }
        }
        
    except Exception as e:
        print(f"Error processing security data: {e}")
        import traceback
        traceback.print_exc()
        return {
            "radar_data": {
                "labels": SECURITY_CATEGORIES,
                "data": [0, 0, 0, 0, 0, 0, 0, 0],
                "threat_level": "unknown",
                "avg_score": 0
            },
            "metrics": {
                "malicious_functions": 0,
                "total_functions": 0,
                "threat_percentage": 0,
                "complexity": "Unknown",
                "avg_api_calls": 0
            }
        }
# ==============================================================
# DIRECT ENHANCEMENT ROUTE
# ==============================================================

@app.route("/enhance_code", methods=["POST"])
def enhance_existing_code():
    """Enhance already decompiled code"""
    data = request.get_json()
    if not data or "code" not in data:
        return jsonify({"error": "No code provided"}), 400
    
    code = data["code"]
    filename = data.get("filename", "unknown.c")
    mode = data.get("mode", "all")
    
    try:
        print(f"✨ Enhancing existing code: {filename}")
        enhanced_code = enhancer.enhance_code(code, filename, mode=mode)
        
        enhancement_info = enhancer.get_enhancement_info(len(code), len(enhanced_code))
        
        return jsonify({
            "enhanced_code": enhanced_code,
            "severity_score": 0,
            "severity_label": "Unknown",
            "enhancement_info": enhancement_info,
            "improved": enhanced_code != code
        })
        
    except Exception as e:
        print(f"Enhancement failed: {e}")
        return jsonify({"error": str(e)}), 500

# ==============================================================
# CLASSIFICATION ROUTE
# ==============================================================

@app.route("/classify", methods=["POST"])
def classify():
    if "file" not in request.files:
        print("No file uploaded")
        return jsonify({"error": "No file uploaded"}), 400

    file = request.files["file"]
    tmp_path = None

    try:
        # Save uploaded binary temporarily
        with tempfile.NamedTemporaryFile(delete=False, suffix=".o") as tmp:
            file.save(tmp.name)
            tmp_path = tmp.name

        # Path to the classifier script
        classifier_dir = os.path.join(os.path.dirname(__file__), "classifier")
        script_path = os.path.join(classifier_dir, "predict_xgb.py")

        # Execute classifier as a subprocess
        result = subprocess.run(
            ["python3", script_path, tmp_path],
            capture_output=True,
            text=True,
            timeout=15
        )

        if result.returncode != 0:
            print(result.stderr)
            return jsonify({
                "error": "Classifier execution failed",
                "details": result.stderr
            }), 500

        # Parse JSON output from predict_xgb.py
        output = json.loads(result.stdout.strip())

        return jsonify({
            "language": output.get("language", "Unknown"),
            "confidence": output.get("confidence", 0.0),
            "method": "subprocess"
        })

    except subprocess.TimeoutExpired:
        print("Classification timed out")
        return jsonify({"error": "Classification timed out"}), 500

    except Exception as e:
        print(f"Classification failed: {e}")
        return jsonify({"error": str(e)}), 500

    finally:
        if tmp_path and os.path.exists(tmp_path):
            os.unlink(tmp_path)


# ==============================================================
# UTILITY ROUTES
# ==============================================================

@app.route("/get_current_file", methods=["GET"])
def get_current_file():
    """Get the current Ghidra file being analyzed"""
    global current_ghidra_file
    return jsonify({
        "current_file": current_ghidra_file,
        "exists": os.path.exists(os.path.join("Ghidra_decompiled", current_ghidra_file)) if current_ghidra_file else False
    })

# ==============================================================
# RUN SERVER
# ==============================================================

if __name__ == "__main__":
    port = int(os.environ.get("PORT", 5000))
    
    print("\n" + "="*60)
    print("DECOMPILER SERVER (Ghidra + Heuristic Enhancement)")
    print("="*60)
    print(f"Server: http://0.0.0.0:{port}")
    
    ghidra_status = check_ghidra_environment()
    print(f"Ghidra: {'Available' if ghidra_status is None else 'Not Available'}")
    if ghidra_status:
        print(f"   Error: {ghidra_status}")
    
    print(f"Security Analysis: {'Configured' if SECURITY_API_URL else 'Not Configured'}")
    if SECURITY_API_URL:
        print(f"   Endpoint: {SECURITY_API_URL}")
    
    print("="*60)
    print("\nAvailable Endpoints:")
    print("  - POST /ghidra_decompile → Ghidra only decompilation")
    print("  - POST /ghidra_enhance   → Ghidra + heuristic enhancement")
    print("  - POST /security_analyze → Security Analysis with remote API")
    print("  - POST /enhance_code     → Enhance existing code")
    print("  - POST /classify         → Language Classification")
    print("  - GET  /status           → Server status")
    print("  - GET  /get_current_file → Get current analyzed file")
    print("="*60)
    
    app.run(host="0.0.0.0", port=port, debug=False)