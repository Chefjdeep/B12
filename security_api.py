from flask import Flask, request, jsonify
import tempfile
import os

app = Flask(__name__)

# ---- EXTENDED STATIC MOCK RESPONSE ----
MOCK_RESPONSE = {
    "file": "tests/test_samples/high_O0_20260105_153210_ghidra.c",
    "analysis_time": "2026-01-05T16:27:10.729133",
    "functions": [
        {
            "function": "_init",
            "function_hash": "34f77a10",
            "classification": {
                "malicious": True,
                "confidence": 0.6672955186685552,
                "behavioral_actions": [],
                "explanation": (
                    "Recommendation: Do not execute. Malicious behavior detected.\n"
                    "Confidence: moderate (67%).\n"
                    "No high-risk behavioral patterns were identified."
                )
            },
            "signals": {
                "triggers": [],
                "raw_counts": {
                    "total_api_calls": 1,
                    "unique_sensitive_apis": 0,
                    "string_constants": 0,
                    "control_structures": 0
                }
            },
            "metadata": {
                "taxonomy_version": "1.0",
                "model_version": "1.0.0"
            }
        },

        {
            "function": "main",
            "function_hash": "fad58de7",
            "classification": {
                "malicious": True,
                "confidence": 0.7021341189341123,
                "behavioral_actions": [],
                "explanation": (
                    "Recommendation: No immediate malicious intent detected.\n"
                    "Confidence: moderate (70%).\n"
                    "No high-risk behavioral patterns were identified."
                )
            },
            "signals": {
                "triggers": [],
                "raw_counts": {
                    "total_api_calls": 1,
                    "unique_sensitive_apis": 0,
                    "string_constants": 0,
                    "control_structures": 0
                }
            },
            "metadata": {
                "taxonomy_version": "1.0",
                "model_version": "1.0.0"
            }
        },

        {
            "function": "printf",
            "function_hash": "afa0ff8b",
            "classification": {
                "malicious": False,
                "confidence": 0.6290519237504679,
                "behavioral_actions": [],
                "explanation": (
                    "Recommendation: No immediate malicious intent detected.\n"
                    "Confidence: moderate (63%).\n"
                    "Standard output function usage observed."
                )
            },
            "signals": {
                "triggers": [],
                "raw_counts": {
                    "total_api_calls": 1,
                    "unique_sensitive_apis": 0,
                    "string_constants": 1,
                    "control_structures": 0
                }
            },
            "metadata": {
                "taxonomy_version": "1.0",
                "model_version": "1.0.0"
            }
        },

        {
            "function": "func0",
            "function_hash": "f60a777f",
            "classification": {
                "malicious": True,
                "confidence": 0.9999999878400466,
                "behavioral_actions": [
                    {
                        "behavior": "file_access",
                        "apis": ["fwrite"],
                        "reason": "Sensitive file write API invoked"
                    },
                    {
                        "behavior": "memory",
                        "apis": ["malloc", "free", "memset"],
                        "reason": "Sensitive memory management APIs invoked"
                    }
                ],
                "explanation": (
                    "Recommendation: Do not execute. Malicious behavior detected.\n"
                    "Confidence: high (100%).\n"
                    "High-level malicious intent inferred: DATA_EXFILTRATION."
                )
            },
            "signals": {
                "triggers": [
                    {
                        "type": "api_category",
                        "category": "file_access",
                        "count": 1
                    },
                    {
                        "type": "api_category",
                        "category": "memory",
                        "count": 3
                    }
                ],
                "raw_counts": {
                    "total_api_calls": 6,
                    "unique_sensitive_apis": 4,
                    "string_constants": 1,
                    "control_structures": 1
                }
            },
            "metadata": {
                "taxonomy_version": "1.0",
                "model_version": "1.0.0"
            }
        },

        {
            "function": "__libc_start_main",
            "function_hash": "a8dd954f",
            "classification": {
                "malicious": False,
                "confidence": 0.7577194296654912,
                "behavioral_actions": [],
                "explanation": (
                    "Recommendation: No immediate malicious intent detected.\n"
                    "Confidence: high (76%).\n"
                    "Runtime initialization routine."
                )
            },
            "signals": {
                "triggers": [],
                "raw_counts": {
                    "total_api_calls": 1,
                    "unique_sensitive_apis": 0,
                    "string_constants": 0,
                    "control_structures": 0
                }
            },
            "metadata": {
                "taxonomy_version": "1.0",
                "model_version": "1.0.0"
            }
        }
    ]
}

@app.route("/analyze", methods=["POST"])
def analyze():
    if "file" not in request.files:
        return jsonify({"error": "No file provided"}), 400

    file = request.files["file"]

    with tempfile.NamedTemporaryFile(delete=False, suffix=".c") as tmp:
        file.save(tmp.name)
        tmp_path = tmp.name

    try:
        return jsonify(MOCK_RESPONSE), 200
    finally:
        if os.path.exists(tmp_path):
            os.unlink(tmp_path)

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5500)
