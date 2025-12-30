# B12 – Intelligent Decompilation and Malware Analysis using LLMs

This repository contains **B12**, a research‑oriented project that integrates **LLM‑based binary decompilation**, **Ghidra automation**, and a **Flask + ngrok API** for remote analysis. The system is designed for **educational and research purposes only**.

---

## 📌 Project Overview

B12 combines:

* **LLM4Decompile** (as a Git submodule) for ASM → C decompilation using large language models
* **Ghidra headless decompiler** for classical binary analysis
* **Flask API** backend
* **ngrok** for exposing Colab‑hosted models to a local or web UI
* Optional **severity scoring** logic for suspicious or malicious code patterns

The project supports:

* Uploading assembly or object files
* LLM‑based decompilation
* Ghidra‑based decompilation
* Integration with a frontend UI

---

## ⚠️ Disclaimer

This project may include **malware‑like code samples** for testing and research.

**DO NOT execute any generated or sample code on a live or production system.**
Use isolated VMs or sandbox environments only.

---

## 📁 Repository Structure

```
B12/
├── app.py                     # Main Flask backend (LLM + Ghidra routes)
├── templates/
│   └── ghidra.html            # Optional web UI
├── LLM4Decompile/             # Git submodule (LLM4Binary project)
├── Ghidra_decompiled/         # Output directory (ignored in git)
├── temp_saves/                # Temporary Ghidra workspace (ignored)
├── requirements.txt           # Python dependencies (optional)
├── .gitignore
└── README.md
```

---

## 🧩 Prerequisites

### System Requirements

* Python **3.10+**
* Linux or macOS (Apple Silicon supported)
* At least **12–16 GB RAM** recommended
* GPU recommended (CUDA or Apple MPS)

### External Tools

* **Java 17+** (required for Ghidra)
* **Ghidra 11.x** (installed locally)

---

## 🔗 Clone the Repository

```bash
git clone https://github.com/Chefjdeep/B12.git
cd B12
```

Initialize the submodule:

```bash
git submodule update --init --recursive
```

---

## 🐍 Python Environment Setup

Create and activate a virtual environment:

```bash
python3 -m venv .venv
source .venv/bin/activate
```

Install dependencies:

```bash
pip install torch transformers flask flask-cors pyngrok accelerate
```

---

## 🧠 Running the LLM Decompiler Locally

Edit the model path if required:

```python
MODEL_PATH = "LLM4Binary/llm4decompile-1.3b-v1.5"
```

Run the Flask server:

```bash
python app.py
```

The API will be available at:

```
http://localhost:5000
```

---

## 🌍 Running on Google Colab with ngrok (Recommended)

1. Open a new **Google Colab** notebook
2. Copy the Colab‑specific script from this repository
3. Add your ngrok auth token in Colab secrets as:

```
NGROK_AUTH_TOKEN
```

4. Run the notebook

You will receive a public endpoint like:

```
https://xxxx.ngrok.io/decompile
```

This endpoint can be connected to your local or web frontend.

---

## ⚙️ Ghidra Decompilation Setup

Update paths in `app.py`:

```python
GHIDRA_PATH = "/path/to/ghidra/support/analyzeHeadless"
GHIDRA_SCRIPT = "ghidra/decompile.py"
```

Supported file types:

* `.o`
* `.asm`

The output will be saved to:

```
Ghidra_decompiled/
```

---

## 🔌 API Endpoints

### LLM Decompile

```
POST /decompile
```

**Input:** multipart form with `file`

**Output:**

```json
{
  "decompiled_code": "..."
}
```

---

### Ghidra Decompile

```
POST /ghidra_decompile
```

**Input:** `.o` or `.asm` file

**Output:** Decompiled C‑like code and logs

---

## 📊 Severity Scoring (Optional)

Severity is calculated based on static heuristics such as:

* Shellcode patterns
* Function pointer execution
* RWX memory behavior
* Obfuscation indicators

Severity range:

* 0–30 → Low risk
* 31–70 → Medium risk
* 71–100 → High risk

---

## 🧹 Git Notes

* Large Ghidra files are ignored via `.gitignore`
* `LLM4Decompile` is included as a **Git submodule**

---

## 📚 References

* LLM4Decompile: [https://github.com/albertan017/LLM4Decompile](https://github.com/albertan017/LLM4Decompile)
@misc{tan2024llm4decompile,
      title={LLM4Decompile: Decompiling Binary Code with Large Language Models}, 
      author={Hanzhuo Tan and Qi Luo and Jing Li and Yuqun Zhang},
      year={2024},
      eprint={2403.05286},
      archivePrefix={arXiv},
      primaryClass={cs.PL}
}
* Ghidra: [https://ghidra-sre.org/](https://ghidra-sre.org/)


---


## 📜 License

This project is intended for **academic and research use only**.
Refer to individual submodules for their respective licenses.

---

## Acknowledgements

This project gratefully acknowledges the **LLM4Decompile** project for providing the foundational large language model used for binary-to-source decompilation.

* **LLM4Decompile Repository**: [https://github.com/albertan017/LLM4Decompile](https://github.com/albertan017/LLM4Decompile)

LLM4Decompile enables research into neural decompilation and significantly contributes to academic and practical exploration of machine-learning-assisted reverse engineering. This repository uses LLM4Decompile strictly for **educational and research purposes**.
