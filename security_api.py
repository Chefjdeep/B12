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
        "explanation": "Recommendation: Do not execute. Malicious behavior detected.\nConfidence: moderate (67%).\nNo high-risk behavioral patterns were identified."
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
        "explanation": "Recommendation: No immediate malicious intent detected.\nConfidence: moderate (70%).\nNo high-risk behavioral patterns were identified."
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
        "explanation": "Recommendation: No immediate malicious intent detected.\nConfidence: moderate (63%).\nStandard output function usage observed."
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
            "apis": ["malloc", "free", "memset", "process"],
            "reason": "Sensitive memory management APIs invoked"
          }
        ],
        "explanation": "Recommendation: Do not execute. Malicious behavior detected.\nConfidence: high (100%).\nHigh-level malicious intent inferred: DATA_EXFILTRATION."
      },
      "signals": {
        "triggers": [
          { "type": "api_category", "category": "file_access", "count": 1 },
          { "type": "api_category", "category": "memory", "count": 3 }
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
        "explanation": "Recommendation: No immediate malicious intent detected.\nConfidence: high (76%).\nRuntime initialization routine."
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
      "function": "install_persistence",
      "function_hash": "b1c9f02a",
      "classification": {
        "malicious": True,
        "confidence": 0.982314221,
        "behavioral_actions": [
          {
            "behavior": "startup_modification",
            "apis": ["open", "write"],
            "reason": "Modifies startup configuration to persist after reboot"
          }
        ],
        "explanation": "Recommendation: Do not execute. Malicious persistence behavior detected.\nConfidence: high (98%).\nHigh-level malicious intent inferred: PERSISTENCE."
      },
      "signals": {
        "triggers": [
          { "type": "api_category", "category": "startup_modification", "count": 1 }
        ],
        "raw_counts": {
          "total_api_calls": 4,
          "unique_sensitive_apis": 2,
          "string_constants": 2,
          "control_structures": 1
        }
      },
      "metadata": {
        "taxonomy_version": "1.0",
        "model_version": "1.0.0"
      }
    },
    {
      "function": "escalate_privileges",
      "function_hash": "e4fa91bc",
      "classification": {
        "malicious": True,
        "confidence": 0.991827551,
        "behavioral_actions": [
          {
            "behavior": "setuid_misuse",
            "apis": ["chmod", "setuid"],
            "reason": "Attempts to grant elevated privileges"
          }
        ],
        "explanation": "Recommendation: Do not execute. Privilege escalation attempt detected.\nConfidence: high (99%).\nHigh-level malicious intent inferred: PRIVILEGE_ESCALATION."
      },
      "signals": {
        "triggers": [
          { "type": "api_category", "category": "setuid_misuse", "count": 1 }
        ],
        "raw_counts": {
          "total_api_calls": 3,
          "unique_sensitive_apis": 2,
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
      "function": "monitor_system",
      "function_hash": "91dc33af",
      "classification": {
        "malicious": True,
        "confidence": 0.60,
        "behavioral_actions": [
          {
            "behavior": "process_enumeration",
            "apis": ["opendir", "readdir"],
            "reason": "Enumerates running system processes"
          }
        ],
        "explanation": "Recommendation: Do not execute. Surveillance activity detected.\nConfidence: high (96%).\nHigh-level malicious intent inferred: SURVEILLANCE."
      },
      "signals": {
        "triggers": [
          { "type": "api_category", "category": "process_enumeration", "count": 1 }
        ],
        "raw_counts": {
          "total_api_calls": 5,
          "unique_sensitive_apis": 2,
          "string_constants": 1,
          "control_structures": 2
        }
      },
      "metadata": {
        "taxonomy_version": "1.0",
        "model_version": "1.0.0"
      }
    },
    {
      "function": "wipe_disk",
      "function_hash": "f02ab991",
      "classification": {
        "malicious": True,
        "confidence": 0.999412771,
        "behavioral_actions": [
          {
            "behavior": "disk_wiping",
            "apis": ["unlink", "remove"],
            "reason": "Recursively deletes critical files"
          }
        ],
        "explanation": "Recommendation: Do not execute. Destructive behavior detected.\nConfidence: very high (99%).\nHigh-level malicious intent inferred: DESTRUCTIVE."
      },
      "signals": {
        "triggers": [
          { "type": "api_category", "category": "recursive_deletion", "count": 3 }
        ],
        "raw_counts": {
          "total_api_calls": 8,
          "unique_sensitive_apis": 2,
          "string_constants": 2,
          "control_structures": 2
        }
      },
      "metadata": {
        "taxonomy_version": "1.0",
        "model_version": "1.0.0"
      }
    },
    {
      "function": "anti_analysis",
      "function_hash": "aa93ef10",
      "classification": {
        "malicious": True,
        "confidence": 0.973882114,
        "behavioral_actions": [
          {
            "behavior": "anti_debugging",
            "apis": ["ptrace"],
            "reason": "Detects debugging or analysis environment"
          }
        ],
        "explanation": "Recommendation: Do not execute. Evasion techniques detected.\nConfidence: high (97%).\nHigh-level malicious intent inferred: EVASION."
      },
      "signals": {
        "triggers": [
          { "type": "api_category", "category": "anti_debugging", "count": 1 }
        ],
        "raw_counts": {
          "total_api_calls": 2,
          "unique_sensitive_apis": 1,
          "string_constants": 0,
          "control_structures": 1
        }
      },
      "metadata": {
        "taxonomy_version": "1.0",
        "model_version": "1.0.0"
      }
    },
    {
      "function": "steal_credentials",
      "function_hash": "d77c01ae",
      "classification": {
        "malicious": True,
        "confidence": 0.988172993,
        "behavioral_actions": [
          {
            "behavior": "shadow_read",
            "apis": ["fopen", "fread"],
            "reason": "Attempts to read credential storage files"
          }
        ],
        "explanation": "Recommendation: Do not execute. Credential theft detected.\nConfidence: high (99%).\nHigh-level malicious intent inferred: CREDENTIAL_THEFT."
      },
      "signals": {
        "triggers": [
          { "type": "api_category", "category": "shadow_read", "count": 1 }
        ],
        "raw_counts": {
          "total_api_calls": 3,
          "unique_sensitive_apis": 2,
          "string_constants": 1,
          "control_structures": 1
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
