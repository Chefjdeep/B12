# B12 – Intelligent Decompilation and Malware Analysis using LLMs

[![Python 3.10+](https://img.shields.io/badge/python-3.10+-blue.svg)](https://www.python.org/downloads/)
[![Flask](https://img.shields.io/badge/Flask-API-green.svg)](https://flask.palletsprojects.com/)
[![Ghidra](https://img.shields.io/badge/Ghidra-Reverse_Engineering-orange.svg)](https://ghidra-sre.org/)
[![LLM4Decompile](https://img.shields.io/badge/LLM4Decompile-AI_Decompilation-purple.svg)](https://github.com/albertan017/LLM4Decompile)
[![Research Use](https://img.shields.io/badge/Use-Research-yellow.svg)](#disclaimer)
# **B12 - Intelligent Binary Analysis Platform**

## 📋 **Project Overview**
**B12** is an advanced binary analysis system that combines **Ghidra decompilation** with **heuristic enhancement** and **ML-based security analysis** into a unified web interface. The platform automates reverse engineering workflows from binary upload to threat visualization.

## ⚠️ **DISCLAIMER**
**WARNING**: This project is for **educational and research purposes only**. Never execute decompiled or generated code on production systems. Use isolated environments exclusively.

---

## ✨ **Core Features**

### **🔧 Multi-Function Enhancement**
- **Intelligent function extraction**: Processes all user-defined functions individually
- **Library filtering**: Automatically skips standard library functions (printf, malloc, etc.)
- **Context-aware naming**: Preserves original function names with intelligent restoration
- **Non-destructive output**: Enhanced functions appended below original for easy comparison

### **🔒 Enhanced Security Analysis**
- **8 Threat Categories**: DATA_EXFILTRATION, PERSISTENCE, PRIVILEGE_ESCALATION, SURVEILLANCE, DESTRUCTIVE, EVASION, DENIAL_OF_SERVICE, CREDENTIAL_THEFT
- **Real-time Radar Charts**: Interactive threat visualization
- **Behavior Mapping**: Converts ML behaviors to security categories
- **Comprehensive Reporting**: Detailed function-by-function analysis

### **📊 Advanced Analytics**
- **Per-function statistics**: Character-level improvement tracking
- **Performance metrics**: Processing time and enhancement percentage tracking
- **Threat scoring**: Severity assessment with pattern recognition
- **Language classification**: Automated detection of source programming language

---

## 🚀 **Quick Start**

### **Prerequisites**
```bash
Python 3.8+
Java 17+ (for Ghidra)
Ghidra 11.0.3+ (Public/Enterprise)
```

### **Installation**

1. **Clone and setup**
```bash
# Create virtual environment
python3 -m venv .venv
source .venv/bin/activate  # On Windows: .venv\Scripts\activate

# Install dependencies
pip install -r requirements.txt
```

2. **Configure Ghidra**
- Set `GHIDRA_PATH` in `app.py` to your Ghidra installation
- Example: `"ghidra/ghidra_11.0.3_PUBLIC/support/analyzeHeadless"`

3. **Configure Security API**
- Set `SECURITY_API_URL` in `app.py` to your ML analysis endpoint
- Example: `"http://10.208.53.33:5000/analyze"`

4. **Start the server**
```bash
python app.py
```
Access: `http://localhost:5000`

---

## 🏗️ **Project Structure**
```
B12/
├── app.py                    # Main Flask application
├── enhance.py               # Heuristic enhancement module
├── classifier/              # Language classification
│   └── predict_xgb.py  
│   └── feature_extractor.py    # XGBoost classifier
├── templates/
│   └── index.html          # Web interface
├── Ghidra_decompiled/      # Original Ghidra outputs
├── Enhanced_Decompiled/    # Heuristic enhanced outputs
├── temp_saves/             # Temporary workspaces
├── ghidra/                 # Ghidra installation
├── samples/                # Test binaries
├── security_api.py         # Security analysis API template
├── requirements.txt
└── README.md
```

---

## 🌐 **API Endpoints**

### **Analysis Endpoints**
| Endpoint | Method | Description |
|----------|--------|-------------|
| `/ghidra_decompile` | POST | Ghidra-only decompilation |
| `/ghidra_enhance` | POST | Ghidra + heuristic enhancement |
| `/security_analyze` | POST | Security analysis (sends enhanced files) |
| `/classify` | POST | Language classification |
| `/enhance_code` | POST | Enhance existing decompiled code |

### **Utility Endpoints**
| Endpoint | Method | Description |
|----------|--------|-------------|
| `/status` | GET | Server health check |
| `/get_current_file` | GET | Get current analysis file |
| `/` | GET | Web interface |

---

## 🔍 **Usage Workflow**

### **Step 1: Upload Binary**
- Supported formats: `.o`, `.elf`, `.exe`, `.so`, `.dll`, `.bin`, `.rom`, `.img`, `.c`
- Drag-and-drop or click to upload

### **Step 2: Run Analysis**
1. **Ghidra Tab** → Click ▶️ for decompilation
2. **Heuristic Enhanced Tab** → Click ▶️ for improved code
3. **Security Tab** → Click ▶️ for threat analysis (requires Ghidra first)

### **Step 3: View Results**
- **Raw View**: Original binary/object file content
- **Ghidra Output**: Decompiled C code
- **Enhanced Code**: Heuristically improved with readability enhancements
- **Security Analysis**: Threat radar, malicious function detection, behavior analysis

---

## ⚙️ **Configuration**

### **Key Settings (`app.py`)**
```python
GHIDRA_PATH = "ghidra/ghidra_11.0.3_PUBLIC/support/analyzeHeadless"
GHIDRA_SCRIPT = "ghidra/decompile.py"
SECURITY_API_URL = "http://10.208.53.33:5000/analyze"
PROJECT_NAME = "tmp_ghidra_proj"
TIMEOUT = 120  # Ghidra timeout in seconds
```

### **Security Categories**
```python
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
```

---

## 📊 **Security Analysis Integration**

### **Expected API Response Format**
Your ML endpoint should return:
```json
{
  "functions": [
    {
      "function": "function_name",
      "classification": {
        "malicious": true,
        "confidence": 0.85,
        "behavioral_actions": [
          {"behavior": "file_access", "apis": ["fwrite"], "reason": "..."}
        ],
        "explanation": "Detected DATA_EXFILTRATION..."
      },
      "signals": {
        "triggers": [
          {"type": "api_category", "category": "file_access", "count": 1}
        ],
        "raw_counts": {"total_api_calls": 6}
      }
    }
  ]
}
```

### **Behavior to Category Mapping**
- `file_access` → DATA_EXFILTRATION
- `memory` → EVASION  
- `network` → DATA_EXFILTRATION
- `process` → PRIVILEGE_ESCALATION
- `registry` → PERSISTENCE
- `antidebug` → EVASION
- `destructive` → DESTRUCTIVE
- `crypto` → CREDENTIAL_THEFT

---

## 🛠️ **Troubleshooting**

### **Common Issues**
1. **Ghidra not found**: Check `GHIDRA_PATH` in `app.py`
2. **Java runtime missing**: Install OpenJDK 17+
3. **Security analysis API unavailable**: Verify `SECURITY_API_URL` connectivity
4. **Timeout during decompilation**: Increase `TIMEOUT` value for large binaries

### **Debug Mode**
```python
# Enable debug prints
print(f"🔍 [DEBUG] Message here")
```

---

## 📈 **Performance Notes**
- **Ghidra decompilation**: 30-120 seconds depending on binary size
- **Heuristic enhancement**: 1-5 seconds per function
- **Security analysis**: Depends on remote API response time
- **Memory usage**: Moderate (200-500MB for large binaries)

---

## 🔒 **Security Best Practices**
1. **Isolated Execution**: Always use VMs or containers
2. **Network Isolation**: Disable internet during malware analysis  
3. **Sample Sources**: Use only from trusted research repositories
4. **Legal Compliance**: Ensure proper authorization for all binaries
5. **Data Protection**: Never upload sensitive/proprietary code

---

## 📄 **License**
This project is for educational and research purposes.

---