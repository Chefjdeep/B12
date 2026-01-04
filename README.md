Here's the updated README with the latest information about your enhancements and fixes:

```markdown
# B12 – Intelligent Decompilation and Malware Analysis using LLMs

[![Python 3.10+](https://img.shields.io/badge/python-3.10+-blue.svg)](https://www.python.org/downloads/)
[![Flask](https://img.shields.io/badge/Flask-API-green.svg)](https://flask.palletsprojects.com/)
[![Ghidra](https://img.shields.io/badge/Ghidra-Reverse_Engineering-orange.svg)](https://ghidra-sre.org/)
[![LLM4Decompile](https://img.shields.io/badge/LLM4Decompile-AI_Decompilation-purple.svg)](https://github.com/albertan017/LLM4Decompile)
[![Research Use](https://img.shields.io/badge/Use-Research-yellow.svg)](#disclaimer)

**B12** is an advanced decompilation system that integrates **Ghidra-based binary analysis** with **LLM-powered enhancement** to produce human-readable, context-aware decompiled code with threat intelligence.

---

## ⚠️ DISCLAIMER

**WARNING**: This project is for **educational and research purposes only**. It may process potentially malicious code samples. 

**NEVER** execute decompiled or generated code on production systems. Use isolated environments (VMs, Docker containers) exclusively.

---

## ✨ **Latest Enhancements**

### **🎯 Intelligent Function-Level Enhancement**
- **Multi-function processing**: Extracts and enhances ALL functions individually
- **Smart library detection**: Skips standard library functions (printf, malloc, etc.)
- **Context-aware naming**: Preserves original function names with intelligent restoration
- **Non-destructive output**: Enhanced functions appended below original for easy comparison

### **📊 Enhanced Analytics**
- **Per-function statistics**: Character-level improvement tracking for each function
- **Severity scoring**: Threat detection with pattern recognition
- **Performance metrics**: Processing time and enhancement percentage tracking
- **Visual separation**: Clear demarcation between original and enhanced code

### **🔧 Advanced Function Detection**
- **Robust parsing**: Accurately extracts real functions, ignoring code snippets
- **Name validation**: Filters invalid function names (operators, expressions)
- **Flexible matching**: Handles Ghidra-specific formats and standard C declarations

---

## 📊 Project Overview

### **Dual-Path Decompilation Pipeline:**
1. **Traditional Path**: Ghidra decompilation → Human-readable C code
2. **Enhanced Path**: Ghidra decompilation → LLM enhancement → Improved readability

### **Key Features:**
- **Multi-function processing**: Each function enhanced individually for precision
- **Append-only enhancement**: Original code preserved, enhancements added below
- **Smart filtering**: Library functions automatically skipped
- **Real-time statistics**: Processing metrics and improvement tracking
- **Severity analysis**: Threat detection in decompiled code

---

## 📁 Repository Structure

```
B12/
├── app.py                     # Main Flask backend with all endpoints
├── enhance.py                 # LLM enhancement module (FIXED FUNCTION DETECTION)
├── templates/
│   ├── index.html            # Main web interface
├── LLM4Decompile/            # Git submodule
│   ├── ghidra/
│   │   ├── decompile.py      # Ghidra automation script
│   │   └── analyzeHeadless   # Ghidra headless wrapper
├── classifier/               # Language classification module
│   ├── pipeline/
│   │   └── language_inferencer.py
│   └── models/
├── Ghidra_decompiled/        # Ghidra output (gitignored)
├── Enhanced_Decompiled/      # LLM-enhanced output (gitignored)
├── temp_saves/               # Temporary workspaces (gitignored)
├── requirements.txt          # Python dependencies
├── README.md                 # This file
└── .gitignore               # Git ignore rules
```

---

## 🚀 **Quick Start Guide**

### **Option A: Local Setup (Recommended for Developers)**

#### 1. Clone Repository
```bash
git clone --recursive https://github.com/Chefjdeep/B12.git
cd B12
```

#### 2. Set Up Python Environment
```bash
# Create virtual environment
python3 -m venv .venv

# Activate (Linux/macOS)
source .venv/bin/activate

# Activate (Windows)
.venv\Scripts\activate

# Install dependencies
pip install -r requirements.txt
```

#### 3. Install Ghidra
1. Download Ghidra from [ghidra-sre.org](https://ghidra-sre.org/)
2. Extract to a known location
3. Update paths in `app.py`:
```python
GHIDRA_PATH = "/path/to/ghidra_11.0.3_PUBLIC/support/analyzeHeadless"
GHIDRA_SCRIPT = "LLM4Decompile/ghidra/decompile.py"
```

#### 4. Run the Application
```bash
# Start Flask server
python app.py

# Access at: http://localhost:5000
```

### **Option B: Colab + Local Hybrid Setup**

#### 1. Start Colab Backend
```python
# Run your Colab notebook to start LLM4Decompile server
# Get the ngrok URL (e.g., https://xxx.ngrok-free.app)
```

#### 2. Configure Local Frontend
Update `app.py`:
```python
COLAB_NGROK_URL = "https://your-colab-ngrok-url.ngrok-free.app/llm4decompile"
ENHANCEMENT_MODE = "colab"
```

#### 3. Run Local Server
```bash
python app.py
```

---

## 🔧 **Configuration**

### **Key Configuration Variables (app.py)**

```python
# ===============================
# CONFIG: Enhancement Mode
# ===============================
ENHANCEMENT_MODE = "colab"  # "colab" or "local"
COLAB_NGROK_URL = "https://your-colab-ngrok-url.ngrok-free.app/llm4decompile"

# ===============================
# Ghidra Configuration
# ===============================
GHIDRA_PATH = "LLM4Decompile/ghidra/ghidra_11.0.3_PUBLIC/support/analyzeHeadless"
GHIDRA_SCRIPT = "LLM4Decompile/ghidra/decompile.py"
PROJECT_NAME = "tmp_ghidra_proj"
TIMEOUT = 120  # Increased timeout for complex binaries
```

### **Enhancement Modes**

| Mode | Description | Use Case |
|------|-------------|----------|
| `"all"` | Enhance all user-defined functions | Full analysis |
| `"single"` | Enhance first non-library function | Quick testing |
| `"func:NAME"` | Enhance specific function | Targeted analysis |
| `"specific"` | Enhance except excluded functions | Custom selection |

---

## 🌐 **API Endpoints**

### **Core Endpoints**

| Endpoint | Method | Description | Input | Output |
|----------|--------|-------------|-------|--------|
| `/` | GET | Home page | None | Web interface |
| `/status` | GET | System status | None | JSON status |
| `/decompile` | POST | LLM-only decompilation | File | Decompiled C code |
| `/ghidra_decompile` | POST | Ghidra decompilation | .o/.bin file | Ghidra output |
| `/ghidra_enhance` | POST | Ghidra + LLM enhancement | .o/.bin file | Enhanced output |
| `/enhance_code` | POST | Enhance existing code | JSON {code, filename, mode} | Enhanced code |
| `/classify` | POST | Language classification | File | C/C++ classification |

### **Example Usage**

```javascript
// Enhance existing decompiled code
fetch('/enhance_code', {
    method: 'POST',
    headers: {'Content-Type': 'application/json'},
    body: JSON.stringify({
        code: decompiledCode,
        filename: "malware.bin",
        mode: "all"  // or "single", "func:main", "specific"
    })
})
```

### **Response Format**
```json
{
    "enhanced_code": "// Original code...\n\n// Enhanced functions...",
    "severity_score": 65,
    "severity_label": "Medium",
    "enhancement_info": {
        "original_length": 1500,
        "enhanced_length": 3200,
        "difference": 1700,
        "improvement_percent": 113.33
    },
    "improved": true
}
```

---

## 🎯 **How Enhancement Works**

### **Processing Pipeline:**
```
Binary File
    ↓
Ghidra Decompilation
    ↓
Function Extraction (8+ functions detected)
    ↓
Library Filtering (printf, malloc, etc. skipped)
    ↓
Per-function LLM Enhancement
    ↓
Append-enhanced Functions Below Original
    ↓
Statistics Collection & Severity Scoring
```

### **Output Example:**
```c
// ===== GHIDRA DECOMPILATION =====
// Function: encrypt_data
void encrypt_data(char* data, int key) {
    // Original decompiled logic...
}

// ===== LLM ENHANCED FUNCTIONS =====
// --- Enhanced Function: encrypt_data ---
// Original: 120 chars → Enhanced: 450 chars (+275.0%)

/* LLM4Decompile enhanced */
void encrypt_data(char* data, int key) {
    // Enhanced, more readable logic with comments...
    for (int i = 0; data[i] != '\0'; i++) {
        data[i] = data[i] ^ key;  // XOR encryption
    }
}
```

---

## 📊 **Severity Scoring System**

### **Threat Detection Patterns**
| Category | Patterns | Weight |
|----------|----------|--------|
| Shell Execution | `exec`, `system`, `popen`, `CreateProcess` | 40 |
| Network Operations | `socket`, `bind`, `connect`, `send` | 30 |
| Memory Manipulation | `malloc`, `VirtualAlloc`, `WriteProcessMemory` | 25 |
| String Vulnerabilities | `strcpy`, `strcat`, `sprintf` | 25 |
| Obfuscation | XOR loops, bit manipulations, unusual constants | 20 |

### **Scoring Levels**
- **🟢 Low (0-30)**: Benign code, standard operations
- **🟡 Medium (31-70)**: Suspicious patterns, requires review
- **🔴 High (71-100)**: Malicious indicators, immediate attention

---

## 🎯 **Supported File Formats**

### **Input Formats**
- **Binary Files**: `.o`, `.elf`, `.exe`, `.bin`, `.so`, `.dll`
- **Object Files**: COFF, ELF, Mach-O, PE
- **Restrictions**: 32.71 KB typical size (adjustable)

### **Output Features**
- **Original + Enhanced**: Side-by-side comparison
- **Per-function statistics**: Improvement metrics
- **Threat assessment**: Severity scoring
- **Language detection**: C/C++ classification

---

## 🔒 **Security Best Practices**

1. **Isolated Execution**: Always use VMs (VirtualBox, VMware) or containers
2. **Network Isolation**: Disable internet during malware analysis
3. **Sample Sources**: Use only from trusted research repositories
4. **Legal Compliance**: Ensure proper authorization for all binaries
5. **Data Protection**: Never upload sensitive/proprietary code

---

## 🐛 **Troubleshooting**

### **Common Issues & Solutions**

1. **"No functions found"**
   ```python
   # Check function detection in enhance.py
   # Enable debug output in extract_all_functions()
   ```

2. **Network timeouts to Colab**
   ```python
   # Increase timeout in enhance_single_function()
   timeout = 120  # Increase from 60
   ```

3. **Ghidra not producing output**
   ```bash
   # Verify Java installation
   java -version  # Should be OpenJDK 17+
   
   # Check file permissions
   chmod +x LLM4Decompile/ghidra/analyzeHeadless
   ```

4. **Invalid function names detected**
   ```python
   # Update _is_valid_function_name() in enhance.py
   # Adjust validation rules for your binaries
   ```

### **Debug Mode**
```bash
# Run Flask with debug output
python3 app.py --debug

# Check logs for enhancement process
tail -f nohup.out
```

---

## 📈 **Performance Optimization**

### **For Large Binaries:**
```python
# Increase timeouts
TIMEOUT = 300  # Ghidra timeout
timeout = 180  # API request timeout

# Batch processing for many functions
time.sleep(0.5)  # Between function enhancements
```

### **Memory Management:**
```python
# Clear temporary files automatically
shutil.rmtree(save_dir, ignore_errors=True)
```

## 📚 **References & Citations**

### **Primary Research**
```bibtex
@misc{tan2024llm4decompile,
  title={LLM4Decompile: Decompiling Binary Code with Large Language Models}, 
  author={Hanzhuo Tan and Qi Luo and Jing Li and Yuqun Zhang},
  year={2024},
  eprint={2403.05286},
  archivePrefix={arXiv},
  primaryClass={cs.PL}
}
```

### **Related Tools & Frameworks**
- **Ghidra**: NSA's open-source reverse engineering suite
- **LLM4Decompile**: Neural decompilation models
- **angr**: Binary analysis platform
- **Binary Ninja**: Commercial reverse engineering platform

### **Learning Resources**
- [Practical Malware Analysis](https://nostarch.com/malware)
- [The Ghidra Book](https://nostarch.com/ghidra)
- [Binary Analysis with angr](https://docs.angr.io/)

---

## 📜 **License & Attribution**

This project integrates multiple open-source components:

- **LLM4Decompile**: Apache 2.0 License
- **Ghidra**: Apache 2.0 License
- **Flask**: BSD 3-Clause License
---

## **Acknowledgements**

This research builds upon the work of:

- **LLM4Decompile Team** for pioneering neural decompilation
- **NSA Ghidra Team** for the exceptional reverse engineering framework
- **Hugging Face** for model hosting and distribution
- **ngrok** for secure tunneling services
- **Open Source Community** for countless tools and libraries

---

