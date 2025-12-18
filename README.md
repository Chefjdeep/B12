# 🧠 Machine Learning Aided Decompilation and Malicious Code Analysis

This project integrates **Ghidra**, **Machine Learning**, and a **Flask web interface** for analyzing and decompiling binary code.

## 🚀 Features
- Upload `.o` or `.asm` files
- AI/LLM-based decompilation
- Ghidra-based decompilation
- Real-time **Code Severity Gauge** (speedometer visualization)

## 🧩 Setup
1. Clone the repository:
   ```bash
   git clone https://github.com//Chefjdeep/B12.git
   cd B12

========================================
Severity Scoring Rules — 0..100 Scale
========================================

Purpose
-------
This document defines a rule-based severity scoring system for decompiled
code (C / assembly). The severity score ranges from 0 to 100 and is intended
to indicate potential harm/exploitability:
  - 0..20   => Low / Safe
  - 21..60  => Medium risk
  - 61..100 => High / Malicious

Guiding principle
-----------------
Compute a weighted sum of detected suspicious features, apply caps and
small negative weight for benign operations, then clamp the result to [0,100].
Optionally smooth the final value for display stability.

Feature categories and suggested weights
----------------------------------------
Each detection contributes to the score. The weights below are starting
recommendations; tune according to your dataset and model.

1) Dangerous functions (examples)
   - system, exec*, popen, popen2, strcpy, gets, sprintf, memcpy misuse
   - weight_per_occurrence: 10

2) Self-modifying / shellcode-like behavior
   - writing executable bytes to memory, inline shellcode arrays, mprotect+write+exec pattern,
     function-pointer execution of memory region
   - weight_flag: 50 (if detected at least once)

3) Memory safety issues
   - unbounded copy to fixed buffer, use-after-free, double-free, unsafe casts
   - weight_per_detected_issue: 25

4) External untrusted input influence
   - reading data from stdin, files, environment variables, command-line args, network
   - weight_flag: 10

5) Network or system control
   - socket/connect/bind, fork+exec for remote persistence, registry edits (Windows)
   - weight_per_occurrence: 30

6) Obfuscation / encoding / dynamic API resolution
   - XOR/rotate loops over strings, encoded payloads decoded at runtime
   - weight_flag: 25

7) Privilege escalation attempts
   - setuid, setgid, chown to sensitive paths, writing to /etc, modifying ACLs
   - weight_flag: 40

8) Benign operations (negative weight)
   - printf, basic arithmetic, standard file write (non-destructive)
   - negative_weight_per_occurrence: -5

Scoring formula (pseudocode)
---------------------------
1. Initialize score = 0
2. For each dangerous function occurrence: score += 10 * count
3. If shellcode-like behavior detected: score += 50
4. For memory-safety issues detected: score += 25 * count
5. If external untrusted input used: score += 10
6. For each network/system control occurrence: score += 30 * count
7. If obfuscation detected: score += 25
8. If privilege escalation pattern detected: score += 40
9. Subtract benign operations influence: score += (-5) * benign_count
10. Clip score to [0, 100]
11. Optionally apply smoothing:
      final = int(0.7 * score + 0.3 * previous_score)   // reduce needle jitter

Example
-------
- Code with strcpy (1), reads file input (flag), and no other flags:
  score = 10 (strcpy) + 10 (external input) = 20  -> Low / borderline medium.

- Code with shellcode array + exec via function pointer:
  score = 50 (shellcode) + maybe +10 (if external input) = 60 -> High.

Python implementation (rule-based detector)
------------------------------------------
# Save this block as severity_rules.py or copy into your backend.
# This is a simple deterministic feature-based scorer.
# It assumes you pass in a plain text string `code_text` (decompiled C/ASM).
# The detector is intentionally conservative and interpretable.

import re

# Precompiled regexes for detection
DANGEROUS_FUNCS = [
    r'\\bsystem\\s*\\(',
    r'\\bexecv\\s*\\(',
    r'\\bexecvp\\s*\\(',
    r'\\bpopen\\s*\\(',
    r'\\bstrcpy\\s*\\(',
    r'\\bgets\\s*\\(',
    r'\\bsprintf\\s*\\(',
    r'\\bmemcpy\\s*\\('
]

SHELLCODE_PATTERNS = [
    r'unsigned char\\s+.*shellcode',      # shellcode array
    r'0x[0-9A-Fa-f]{2}\\s*,\\s*0x[0-9A-Fa-f]{2}',  # byte array pattern
    r'\\bmprotect\\b',
    r'\\bVirtualAlloc\\b.*MEM_COMMIT',     # windows style
    r'\\bPROT_EXEC\\b'
]

MEMORY_ISSUE_PATTERNS = [
    r'\\bstrcpy\\b',      # also counted as dangerous func
    r'\\bstrcat\\b',
    r'\\bgets\\b',
    r'\\bmemcpy\\b.*\\bsizeof\\b',  # suspicious memcpy without bound checks
    r'\\bfree\\b.*\\bfree\\b'       # double-free simple heuristic (pattern match approximate)
]

NETWORK_FUNCTIONS = [
    r'\\bsocket\\b',
    r'\\bconnect\\b',
    r'\\bbind\\b',
    r'\\blisten\\b',
    r'\\bsend\\b',
    r'\\brecv\\b'
]

OBFUSCATION_PATTERNS = [
    r'for\\s*\\(.*xor',   # xor loops
    r'\\bxor\\b.*\\b0x',
    r'decode\\(',         # common decode function name
    r'base64_decode'      # common name
]

PRIV_ESC_PATTERNS = [
    r'\\bsetuid\\b',
    r'\\bsetgid\\b',
    r'\\bchown\\b',
    r'\\bchmod\\b'
]

BENIGN_PATTERNS = [
    r'\\bprintf\\b',
    r'\\bscanf\\b',
    r'\\bmalloc\\b',   # neutral but can be listed as benign influence
    r'\\bfopen\\b'
]

def count_matches(patterns, text):
    total = 0
    for p in patterns:
        total += len(re.findall(p, text, flags=re.IGNORECASE))
    return total

def detect_flag(patterns, text):
    for p in patterns:
        if re.search(p, text, flags=re.IGNORECASE):
            return True
    return False

def compute_severity(code_text, previous_score=0):
    """
    Compute severity (0..100) from code_text.
    previous_score: optional int to smooth the output visually.
    Returns: dict { 'score': int, 'label': str, 'details': {...} }
    """
    text = code_text or ""
    score = 0

    # Dangerous function occurrences
    dangerous_count = count_matches(DANGEROUS_FUNCS, text)
    score += 10 * dangerous_count

    # Shellcode-like behavior (flag)
    if detect_flag(SHELLCODE_PATTERNS, text):
        score += 50

    # Memory safety issues
    memory_issues = count_matches(MEMORY_ISSUE_PATTERNS, text)
    score += 25 * memory_issues

    # External input influence (flag)
    if re.search(r'\\b(stdin|fgets|fread|recvfrom|recv|read\\(|open\\(|fopen\\()\\b', text, flags=re.IGNORECASE):
        score += 10

    # Network / system control functions
    network_count = count_matches(NETWORK_FUNCTIONS, text)
    score += 30 * network_count

    # Obfuscation detection
    if detect_flag(OBFUSCATION_PATTERNS, text):
        score += 25

    # Privilege escalation attempts
    if detect_flag(PRIV_ESC_PATTERNS, text):
        score += 40

    # Benign operations reduce confidence slightly
    benign_count = count_matches(BENIGN_PATTERNS, text)
    score += (-5) * benign_count

    # Ensure integer and clamp
    score = int(round(score))
    if score < 0:
        score = 0
    if score > 100:
        score = 100

    # Optional smoothing for UI (prevent needle jitter)
    if previous_score is not None:
        smoothed = int(round(0.7 * score + 0.3 * previous_score))
        score = smoothed

    # Label
    if score < 30:
        label = "Low"
    elif score < 70:
        label = "Medium"
    else:
        label = "High"

    details = {
        'dangerous_count': dangerous_count,
        'memory_issues': memory_issues,
        'network_count': network_count,
        'benign_count': benign_count,
        'shellcode_detected': detect_flag(SHELLCODE_PATTERNS, text),
        'obfuscation_detected': detect_flag(OBFUSCATION_PATTERNS, text),
        'priv_esc_detected': detect_flag(PRIV_ESC_PATTERNS, text)
    }

    return {
        'score': score,
        'label': label,
        'details': details
    }

# Example usage:
# code = open("decompiled_output.c").read()
# result = compute_severity(code, previous_score=10)
# print(result)

Notes and tuning
----------------
1) This rule-based approach is deterministic and interpretable, useful for
   initial testing and UI display. For production use, consider training a
   classifier (random forest, gradient-boosted trees, or neural model) on
   labeled malicious/benign examples and use its probability as a severity score.

2) Combine LLM interpretation (semantic understanding) with rule-based
   features. For example, LLM may output "this code attempts to spawn a shell",
   which you can map to a high-weight flag.

3) Adjust weights based on false positives and false negatives observed in
   your dataset.

4) When showing the score to users, always add context: show detected tags
   (e.g., ["strcpy", "shellcode array", "fopen"]) so a human analyst can
   quickly triage.

End of file.
