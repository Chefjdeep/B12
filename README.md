# B12 – Intelligent Decompilation and Malware Analysis using LLMs

[![Python 3.10+](https://img.shields.io/badge/python-3.10+-blue.svg)](https://www.python.org/downloads/)
[![Flask](https://img.shields.io/badge/Flask-API-green.svg)](https://flask.palletsprojects.com/)
[![Ghidra](https://img.shields.io/badge/Ghidra-Reverse_Engineering-orange.svg)](https://ghidra-sre.org/)
[![LLM4Decompile](https://img.shields.io/badge/LLM4Decompile-AI_Decompilation-purple.svg)](https://github.com/albertan017/LLM4Decompile)
[![Research Use](https://img.shields.io/badge/Use-Research-yellow.svg)](#disclaimer)

This repository contains **B12**, a research‑oriented project that integrates **LLM‑based binary decompilation**, **Ghidra automation**, and a **Flask + ngrok API** for remote analysis. The system is designed for **educational and research purposes only**.

---

## ⚠️ DISCLAIMER

This project may include malware‑like code samples for testing and research.

DO NOT execute any generated or sample code on a live or production system. Use isolated VMs or sandbox environments only.

---

## 📊 Project Overview

### Key Features:
- **Dual Decompilation**: Compare AI vs traditional decompilation results
- **Threat Analysis**: Automatic severity scoring for suspicious patterns
- **Real-time Processing**: Live analysis with progress visualization
- **Cross-Platform**: Works on Linux, macOS, and via Colab

---

## 📁 Repository Structure

```
B12/
├── app.py                     # Main Flask backend
├── enhance.py                 # LLM enhancement module
├── templates/
│   ├── index.html            # Main web interface
├── LLM4Decompile/            # Git submodule
│   ├── ghidra/
│   │   ├── decompile.py      # Ghidra automation script
│   │   └── analyzeHeadless   # Ghidra headless wrapper
├── Ghidra_decompiled/        # Ghidra output (gitignored)
├── Enhanced_Decompiled/      # LLM-enhanced output (gitignored)
├── temp_saves/               # Temporary workspaces (gitignored)
├── requirements.txt          # Python dependencies
├── README.md                 # This file
└── .gitignore               # Git ignore rules
```

---

## 🛠️ **Quick Start Guide**

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

### **Option B: Google Colab Setup (Recommended for Research/Testing)**

#### 1. Open Colab Notebook
```python
# Copy the Colab script from Colab_setup.ipynb
# Or run the provided Colab notebook
```

#### 2. Configure ngrok (Free tier)
1. Sign up at [ngrok.com](https://ngrok.com/)
2. Get your auth token
3. Add to Colab secrets as `NGROK_AUTH_TOKEN`

#### 3. Run the Cells
Execute all cells to:
- Install dependencies
- Load LLM4Decompile model
- Start Flask server
- Create ngrok tunnel

#### 4. Connect Your UI
Use the provided ngrok URL in your frontend:
```javascript
// In your HTML frontend
const COLAB_URL = "https://your-ngrok-url.ngrok-free.app/llm4decompile";
```

---

## 🔧 **Configuration**

### **Key Configuration Variables (app.py)**

```python

# Enhancement Mode (Choose one)
ENHANCEMENT_MODE = "colab"  # or "local"
COLAB_NGROK_URL = "https://your-ngrok-url.ngrok-free.app/llm4decompile"
```
---

## 🌐 **API Endpoints**

### **Core Endpoints**

| Endpoint | Method | Description | Input | Output |
|----------|--------|-------------|-------|--------|
| `/` | GET | Home/status page | None | JSON status |
| `/decompile` | POST | LLM-only decompilation | File | Decompiled C code |
| `/ghidra_decompile` | POST | Ghidra decompilation | .o/.asm file | Ghidra output |
| `/ghidra_enhance` | POST | Ghidra + LLM enhancement | .o/.asm file | Enhanced output |
| `/status` | GET | System status | None | JSON status |

### **Example API Usage**

```bash
# Test LLM decompilation
curl -X POST -F "file=@test.o" http://localhost:5000/decompile

# Test Ghidra decompilation
curl -X POST -F "file=@test.o" http://localhost:5000/ghidra_decompile

# Test enhancement
curl -X POST -F "file=@test.o" http://localhost:5000/ghidra_enhance
```

---

## 📊 **Severity Scoring System**

The system analyzes decompiled code for suspicious patterns:

### **Risk Categories**

| Score | Level | Description |
|-------|-------|-------------|
| 0-30 | 🟢 Low | Benign code, standard functions |
| 31-70 | 🟡 Medium | Suspicious patterns, review recommended |
| 71-100 | 🔴 High | Malicious indicators, immediate review needed |

### **Detection Patterns**
- **Shellcode indicators**: `exec`, `system`, `CreateProcess`
- **Memory manipulation**: `VirtualAlloc`, `WriteProcessMemory`
- **Network operations**: `socket`, `bind`, `connect`
- **Obfuscation**: High entropy, packed code patterns
- **Persistence**: Registry modifications, startup entries

---

## 🎯 **Supported File Formats**

### **Input Formats**
- **Binary**: `.o`, `.obj`, `.bin`, `.elf`
- **Assembly**: `.asm`, `.s`
- **Object Files**: COFF, ELF, Mach-O

### **Output Formats**
- Decompiled C code
- Severity analysis report
- Hex dump (for binary files)
- Threat radar visualization

---

## 🔒 **Security Best Practices**

1. **Isolation**: Always run in VM/sandbox (VMware, VirtualBox, Docker)
2. **Network Isolation**: Disable internet access during analysis
3. **Sample Sources**: Only analyze samples from trusted research repositories
4. **Legal Compliance**: Ensure you have authorization to analyze binaries
5. **Data Protection**: Don't upload sensitive/proprietary binaries

---

## 🐛 **Troubleshooting**

### **Common Issues**

1. **Ghidra not found**
   ```bash
   # Verify Java installation
   java -version
   
   # Check Ghidra path
   ls -la /path/to/ghidra/analyzeHeadless
   ```

2. **CUDA out of memory**
   ```python
   # Reduce batch size in app.py
   max_new_tokens = 512  # instead of 2048
   ```

3. **ngrok connection issues**
   ```bash
   # Check ngrok status
   ngrok http 5000
   
   # Verify firewall allows port 5000
   ```

### **Debug Mode**
Enable debug logging in `app.py`:
```python
app.run(host="0.0.0.0", port=5000, debug=True)
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

### **Related Projects**
- **Ghidra**: [https://ghidra-sre.org/](https://ghidra-sre.org/)
- **LLM4Decompile**: [https://github.com/albertan017/LLM4Decompile](https://github.com/albertan017/LLM4Decompile)

### **Learning Resources**
- [Practical Binary Analysis](https://practicalbinaryanalysis.com/)
- [The Ghidra Book](https://nostarch.com/ghidra)
- [LLM Security Research Papers](https://arxiv.org/list/cs.CR/recent)

---

## 📜 **License**

This project is provided for **academic and research purposes only**.

**Important**:
- Check licenses of submodules (LLM4Decompile, Ghidra)
- Respect software licenses of analyzed binaries

---

## **Acknowledgements**

This project gratefully acknowledges:

- **LLM4Decompile Team**: For pioneering work in neural decompilation
- **NSA Ghidra Team**: For the excellent reverse engineering framework
- **Hugging Face**: For hosting the model weights
- **ngrok**: For providing tunneling services
- **Open Source Community**: For countless tools and libraries

LLM4Decompile enables research into neural decompilation and significantly contributes to academic and practical exploration of machine-learning-assisted reverse engineering. This repository uses LLM4Decompile and Ghidra strictly for **educational and research purposes**.
---
