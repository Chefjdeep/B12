# enhance.py - LLM4Decompile Enhancement Module (FIXED FUNCTION DETECTION)
import re
import os
import datetime
import requests
import time
from typing import Set

# ==============================================================
# 🔧 ENHANCER CLASS
# ==============================================================

class LLM4DecompileEnhancer:
    def __init__(self, use_local_model=False, colab_url="https://joetta-colorimetric-audra.ngrok-free.dev/llm4decompile"):
        """
        Initialize the enhancer
        """
        self.use_local_model = use_local_model
        self.colab_url = colab_url
        
        print(f"🔧 Initializing enhancer with Colab URL: {colab_url}")
    
    def extract_all_functions(self, ghidra_code):
        """
        Extract ALL functions from Ghidra decompiled code
        Returns a dictionary of function_name: function_code
        """
        print("🔍 Extracting all functions from Ghidra output...")
        
        # Clean Ghidra artifacts first
        clean_code = self._clean_ghidra_artifacts(ghidra_code)
        
        # More robust approach: Find function declarations line by line
        lines = clean_code.split('\n')
        functions = {}
        current_func = None
        func_start_line = -1
        func_lines = []
        brace_count = 0
        in_function = False
        in_comment_block = False
        
        for i, line in enumerate(lines):
            # Skip comment lines
            stripped_line = line.strip()
            
            # Handle block comments
            if '/*' in line and '*/' not in line:
                in_comment_block = True
                continue
            if in_comment_block:
                if '*/' in line:
                    in_comment_block = False
                continue
            
            # Check for function declaration
            if not in_function and not stripped_line.startswith('//'):
                # Look for function declaration patterns
                func_match = self._detect_function_declaration(line)
                if func_match:
                    func_name = func_match.group(2)
                    
                    # VALIDATE function name
                    if self._is_valid_function_name(func_name):
                        current_func = func_name
                        func_start_line = i
                        func_lines = [line]
                        brace_count = 0
                        
                        # Check if opening brace is on same line
                        if '{' in line:
                            brace_count += line.count('{')
                            in_function = True
                        else:
                            # Opening brace might be on next line
                            in_function = True  # Start collecting even without brace yet
                    else:
                        print(f"⚠️ Skipping invalid function name: '{func_name}'")
                elif in_function and not current_func:
                    # We might already be in a function but didn't catch declaration
                    continue
            elif in_function:
                # We're inside a function, collect lines
                func_lines.append(line)
                brace_count += line.count('{')
                brace_count -= line.count('}')
                
                # Check if function has ended
                if brace_count == 0:
                    # Save the function
                    if current_func:
                        func_code = '\n'.join(func_lines)
                        
                        # Add function header if available
                        header = ""
                        if func_start_line > 0 and func_start_line < len(lines):
                            # Look for function comment in previous 5 lines
                            for j in range(max(0, func_start_line - 5), func_start_line):
                                if "// Function:" in lines[j]:
                                    header = lines[j] + '\n'
                                    break
                        
                        functions[current_func] = header + func_code
                        print(f"📝 Found function: {current_func} ({len(func_code)} chars)")
                    
                    # Reset for next function
                    in_function = False
                    current_func = None
                    func_lines = []
        
        # Handle case where function ends at end of file
        if in_function and current_func and func_lines:
            func_code = '\n'.join(func_lines)
            functions[current_func] = func_code
            print(f"📝 Found function (at EOF): {current_func} ({len(func_code)} chars)")
        
        print(f"✅ Extracted {len(functions)} functions")
        
        # Debug: print found functions
        if not functions:
            print("⚠️ Debug: No functions found. Sample of cleaned code:")
            print(clean_code[:500])
        
        return functions
    
    def _is_valid_function_name(self, name):
        """
        Check if a name looks like a valid function name
        """
        if not name:
            return False
        
        # Invalid patterns in function names
        invalid_patterns = [
            r'^\*',  # Starts with pointer
            r'==',  # Contains comparison
            r'!=',  # Contains not equal
            r'<=', r'>=',  # Contains comparison
            r'\+\+', r'--',  # Contains increment/decrement
            r'\+=', r'-=', r'\*=', r'/=', r'%=',  # Contains assignment operators
            r'&&', r'\|\|',  # Contains logical operators
            r'&', r'\|', r'\^', r'~',  # Contains bitwise operators
            r'<<', r'>>',  # Contains shift operators
            r'\?', r':',  # Contains ternary operator
            r'\.', r'->',  # Contains member access
            r'\[', r'\]',  # Contains array access
            r'\(', r'\)',  # Contains parentheses
        ]
        
        for pattern in invalid_patterns:
            if re.search(pattern, name):
                return False
        
        # Function names should be alphanumeric with underscores
        if not re.match(r'^[a-zA-Z_][a-zA-Z0-9_]*$', name):
            return False
        
        # Should not be a C keyword
        c_keywords = {
            'if', 'else', 'while', 'for', 'do', 'switch', 'case', 'default',
            'break', 'continue', 'return', 'goto', 'sizeof', 'typedef',
            'struct', 'union', 'enum', 'const', 'volatile', 'static',
            'extern', 'auto', 'register', 'inline', 'restrict', 'if',
            'else', 'while', 'for', 'do', 'switch', 'case'
        }
        
        if name in c_keywords:
            return False
        
        # Should not be just a number or weird combination
        if re.match(r'^\d+$', name):
            return False
        
        return True
    
    def _detect_function_declaration(self, line):
        """
        Detect if a line contains a function declaration
        Handle Ghidra's format specifically
        """
        stripped = line.strip()
        
        # Skip obvious non-function lines
        if not stripped:
            return None
            
        # Skip lines that are clearly not function declarations
        skip_patterns = [
            r'^\s*[{};]',  # Braces or semicolons
            r'^\s*\w+\s*=\s*',  # Variable assignment
            r'^\s*return\s+',  # Return statement
            r'^\s*if\s*\(',  # If statement
            r'^\s*for\s*\(',  # For loop
            r'^\s*while\s*\(',  # While loop
            r'^\s*else\s*',  # Else statement
            r'^\s*case\s+',  # Case statement
            r'^\s*default\s*:',  # Default case
            r'^\s*break\s*;',  # Break statement
            r'^\s*continue\s*;',  # Continue statement
            r'^\s*goto\s+',  # Goto statement
            r'^\s*//',  # Comment
            r'^\s*/\*',  # Block comment
            r'^\s*\*',  # Comment continuation
        ]
        
        for pattern in skip_patterns:
            if re.match(pattern, stripped):
                return None
        
        # Look for REAL function declarations
        # Pattern: return_type name(params) 
        # Must have valid return type and function name
        
        valid_return_types = [
            'void', 'int', 'char', 'short', 'long', 'float', 'double',
            'signed', 'unsigned', 'size_t', 'ssize_t', 'pid_t', 'time_t',
            'undefined4', 'undefined8', 'undefined2', 'undefined1', 'undefined'
        ]
        
        # Enhanced function pattern
        func_patterns = [
            # Standard: return_type name(params)
            r'^([a-zA-Z_][\w\s*\*]+)\s+([a-zA-Z_]\w+)\s*\(([^)]*)\)\s*(?:{|$)',
            # With void parameter: return_type name(void)
            r'^([a-zA-Z_][\w\s*\*]+)\s+([a-zA-Z_]\w+)\s*\(\s*void\s*\)\s*(?:{|$)',
            # Ghidra style: undefined4 name(params)
            r'^(undefined[1248]?)\s+([a-zA-Z_]\w+)\s*\(([^)]*)\)\s*(?:{|$)',
        ]
        
        for pattern in func_patterns:
            match = re.match(pattern, stripped)
            if match:
                return_type = match.group(1).strip()
                func_name = match.group(2)
                
                # Validate it's not just a variable declaration
                # Check for common non-function patterns
                invalid_patterns = [
                    r'\s*=\s*[^;]+;',  # Variable assignment
                    r'\s*\[\s*\d*\s*\]',  # Array declaration
                    r'\s*,\s*\w+',  # Multiple variable declaration
                ]
                
                has_invalid = False
                for invalid_pattern in invalid_patterns:
                    if re.search(invalid_pattern, stripped):
                        has_invalid = True
                        break
                
                if not has_invalid:
                    # Additional check: function name should not contain operators
                    if not any(op in func_name for op in ['*', '&', '+', '-', '=', '<', '>', '==', '!=', '(', ')']):
                        return match
        
        return None
    
    def _looks_like_variable_declaration(self, line, func_name):
        """
        Try to distinguish between function declarations and variable declarations
        """
        # Common patterns that indicate variable declarations
        variable_patterns = [
            r'=\s*[^;]+;',  # Has an assignment
            r'\[\s*\d*\s*\]',  # Array declaration
            r'\)\s*;',  # Function pointer assignment ending with semicolon
        ]
        
        for pattern in variable_patterns:
            if re.search(pattern, line):
                return True
        
        # Check for function declaration patterns
        func_patterns = [
            r'\)\s*\{',  # Opening brace after params
            r'\)\s*$',  # Just params, no semicolon (likely function declaration)
        ]
        
        for pattern in func_patterns:
            if re.search(pattern, line):
                return False
        
        # Default: assume it's a function if no variable indicators found
        return False
    
    def extract_single_function(self, ghidra_code, func_name):
        """
        Extract a specific function by name from Ghidra decompiled code
        """
        print(f"🔍 Extracting function '{func_name}' from Ghidra output...")
        
        # Try multiple strategies
        # Strategy 1: Look for "// Function: func_name" pattern
        lines = ghidra_code.split('\n')
        
        for i, line in enumerate(lines):
            if f"// Function: {func_name}" in line or f"// Function: {func_name}(" in line:
                # Found function header, now find the actual function
                for j in range(i + 1, min(i + 10, len(lines))):
                    if self._detect_function_declaration(lines[j]):
                        # Found function declaration
                        return self._extract_function_from_line(ghidra_code, j)
        
        # Strategy 2: Look for function declaration directly
        for i, line in enumerate(lines):
            if func_name in line and self._detect_function_declaration(line):
                # Verify it's the right function
                match = self._detect_function_declaration(line)
                if match and match.group(2) == func_name:
                    return self._extract_function_from_line(ghidra_code, i)
        
        print(f"⚠️ Function '{func_name}' not found")
        return None
    
    def _extract_function_from_line(self, code, start_line_idx):
        """Extract a complete function starting from a specific line"""
        lines = code.split('\n')
        func_lines = []
        brace_count = 0
        found_start = False
        
        for i in range(start_line_idx, len(lines)):
            line = lines[i]
            
            if not found_start:
                # Add the function declaration line
                func_lines.append(line)
                found_start = True
            else:
                func_lines.append(line)
            
            # Count braces
            brace_count += line.count('{')
            brace_count -= line.count('}')
            
            # Check if function has ended
            if brace_count == 0 and found_start and i > start_line_idx:
                break
        
        if func_lines:
            func_code = '\n'.join(func_lines)
            
            # Add function header if available
            header = ""
            if start_line_idx > 0:
                # Look for function comment in previous 5 lines
                for j in range(max(0, start_line_idx - 5), start_line_idx):
                    if "// Function:" in lines[j]:
                        header = lines[j] + '\n'
                        break
            
            return header + func_code
        
        return None
    
    def _clean_ghidra_types(self, code):
        """Convert Ghidra types to standard C types"""
        # Replace undefined types
        type_mapping = {
            r'\bundefined8\b': 'long',
            r'\bundefined4\b': 'int',
            r'\bundefined2\b': 'short',
            r'\bundefined1\b': 'char',
            r'\bundefined\b': 'void',
            r'\bundefined_(\d+)\b': r'int\1',  # undefined_X
        }
        
        for pattern, replacement in type_mapping.items():
            code = re.sub(pattern, replacement, code)
        
        # Clean up pointer syntax
        code = re.sub(r'\b(\w+)\s*\*\s*\*', r'\1**', code)
        code = re.sub(r'\b(\w+)\s*\*', r'\1*', code)
        
        # Replace Ghidra-specific param names
        code = re.sub(r'\bparam_(\d+)\b', r'arg\1', code)
        code = re.sub(r'\blocal_(\d+)\b', r'local\1', code)
        
        return code
    
    def _clean_ghidra_artifacts(self, code):
        """Remove Ghidra-specific artifacts but keep structure"""
        # First, remove all block comments with warnings
        code = re.sub(r'/\*.*?WARNING.*?\*/', '', code, flags=re.DOTALL)
        
        # Remove single line warnings
        lines = code.split('\n')
        clean_lines = []
        
        for line in lines:
            # Keep function headers
            if line.strip().startswith('// Function:'):
                clean_lines.append(line)
            # Keep decompilation headers
            elif line.strip().startswith('// =====') or line.strip().startswith('// Method:') or \
                 line.strip().startswith('// Processing') or line.strip().startswith('// File:') or \
                 line.strip().startswith('// Size:'):
                clean_lines.append(line)
            # Remove warning lines
            elif 'WARNING:' in line or 'warning:' in line.lower():
                continue
            # Keep everything else
            else:
                clean_lines.append(line)
        
        # Join back
        code = '\n'.join(clean_lines)
        
        # Remove excessive blank lines
        code = re.sub(r'\n\s*\n\s*\n', '\n\n', code)
        
        return code.strip()
    
    def create_llm4decompile_prompt(self, func_code, func_name="func"):
        """
        Create EXACT prompt format that LLM4Decompile expects
        """
        # For LLM4Decompile, we present it as "assembly code" but it's actually decompiled C
        prompt = f"# This is the assembly code:\n{func_code}\n# What is the source code?\n"
        return prompt
    
    def enhance_single_function(self, func_code, func_name="func", filename="unknown.c", max_retries=2):
        """
        Enhance a single function using LLM4Decompile with retry logic
        """
        if not self.colab_url:
            print(f"⚠️ No Colab URL configured, skipping enhancement for {func_name}")
            return func_code
        
        print(f"🚀 Sending function '{func_name}' to LLM4Decompile API...")
        print(f"📝 Code length: {len(func_code)} chars")
        
        # Create the EXACT prompt format LLM4Decompile expects
        prompt = self.create_llm4decompile_prompt(func_code, func_name)
        
        # Convert to bytes
        file_bytes = prompt.encode('utf-8')
        
        for attempt in range(max_retries + 1):
            try:
                # Send to Colab API with increasing timeout
                timeout = 60 * (attempt + 1)  # 60s, 120s, 180s
                files = {'file': (f'{func_name}_{filename}', file_bytes)}
                response = requests.post(self.colab_url, files=files, timeout=timeout)
                
                print(f"📡 API Response status: {response.status_code}")
                
                if response.status_code == 200:
                    result = response.json()
                    enhanced_output = result.get('decompiled_code', '')
                    severity = result.get('severity', 0)
                    
                    print(f"✅ Received enhanced output for '{func_name}'")
                    print(f"📊 Severity score: {severity}")
                    
                    # Post-process the enhanced output
                    enhanced_func = self._postprocess_enhanced_output(enhanced_output, func_code, func_name)
                    
                    return enhanced_func
                else:
                    print(f"❌ API Error {response.status_code} for '{func_name}': {response.text[:200]}")
                    if attempt < max_retries:
                        print(f"🔄 Retrying... (attempt {attempt + 1}/{max_retries})")
                        time.sleep(2 ** attempt)  # Exponential backoff
                        continue
                    return func_code
                    
            except Exception as e:
                print(f"❌ Request failed for '{func_name}' (attempt {attempt + 1}): {e}")
                if attempt < max_retries:
                    print(f"🔄 Retrying... (attempt {attempt + 1}/{max_retries})")
                    time.sleep(2 ** attempt)  # Exponential backoff
                    continue
                return func_code
        
        return func_code  
    def enhance_all_functions(self, ghidra_code, filename="unknown.c", exclude_functions=None):
        """
        Extract ALL functions from Ghidra decompiled code, send each to LLM4Decompile,
        and return enhanced result with all functions APPENDED below original
        """
        if not self.colab_url:
            print("⚠️ No Colab URL configured")
            return ghidra_code
        
        # Extract all functions
        functions = self.extract_all_functions(ghidra_code)
        
        if not functions:
            print("⚠️ No functions found, returning original")
            return ghidra_code
        
        # Set of functions to exclude
        exclude_functions = exclude_functions or set()
        
        enhanced_functions = {}
        enhancement_stats = {}
        
        print(f"🔄 Enhancing {len(functions)} functions...")
        
        # Process each function
        for func_name, func_code in functions.items():
            # Skip library/system functions
            if self._is_library_function(func_name):
                print(f"⏭️ Skipping library function: {func_name}")
                enhanced_functions[func_name] = func_code
                continue
            
            if func_name in exclude_functions:
                print(f"⏭️ Skipping excluded function: {func_name}")
                enhanced_functions[func_name] = func_code
                continue
            
            print(f"📤 Processing function: {func_name}")
            # Enhance the function
            enhanced_func = self.enhance_single_function(func_code, func_name, filename)
            
            # Store the enhanced function
            enhanced_functions[func_name] = enhanced_func
            
            # Calculate statistics
            orig_len = len(func_code)
            enh_len = len(enhanced_func)
            diff = enh_len - orig_len
            improvement = round(diff / max(orig_len, 1) * 100, 2)
            
            enhancement_stats[func_name] = {
                'original_length': orig_len,
                'enhanced_length': enh_len,
                'difference': diff,
                'improvement_percent': improvement
            }
            
            print(f"📊 {func_name}: {orig_len} → {enh_len} chars ({improvement:+}%)")
            
            # Small delay to avoid rate limiting
            time.sleep(0.5)
        
        # Reconstruct the enhanced code by APPENDING below original
        enhanced_full = self._append_enhanced_functions(ghidra_code, functions, enhanced_functions, enhancement_stats)
        
        return enhanced_full
    
    def _append_enhanced_functions(self, original_code, original_functions, enhanced_functions, stats):
        """
        Append enhanced functions below original code (never replace)
        """
        print("🔧 Appending enhanced functions below original code...")
        
        # Start with original code intact
        result = original_code
        
        # Check if we have any enhanced functions to append
        enhanced_count = 0
        for func_name in enhanced_functions:
            if func_name in original_functions and enhanced_functions[func_name] != original_functions[func_name]:
                if not self._is_library_function(func_name):
                    enhanced_count += 1
        
        if enhanced_count == 0:
            print("⚠️ No enhanced functions to append")
            return result
        
        # Add separator and header
        separator = "\n\n" + "="*80 + "\n"
        timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        
        # Calculate overall statistics
        total_original = sum(s['original_length'] for s in stats.values())
        total_enhanced = sum(s['enhanced_length'] for s in stats.values())
        total_diff = total_enhanced - total_original
        total_improvement = round(total_diff / max(total_original, 1) * 100, 2)
        
        header = f"""// ===================================================
// LLM4Decompile ENHANCED FUNCTIONS (APPENDED BELOW)
// ===================================================
// Enhancement Time: {timestamp}
// Total enhanced functions: {enhanced_count}
// Statistics: {total_original} → {total_enhanced} chars ({total_improvement:+}%)
// ===================================================

"""
        
        # Build enhanced section
        enhanced_section = ""
        
        # Append each enhanced function that's different from original
        for func_name, enhanced_func in enhanced_functions.items():
            if func_name in original_functions:
                original_func = original_functions[func_name]
                
                # Only append if enhanced version is different and not a library function
                if enhanced_func != original_func and not self._is_library_function(func_name):
                    # Add function header with comparison
                    func_header = f"// --- Enhanced Function: {func_name} ---\n"
                    func_header += f"// Original: {len(original_func)} chars → Enhanced: {len(enhanced_func)} chars "
                    func_header += f"({stats[func_name]['improvement_percent']:+}%)\n"
                    func_header += "// ===================================================\n\n"
                    
                    enhanced_section += func_header + enhanced_func + "\n\n"
                    print(f"✅ Appending enhanced function: {func_name}")
        
        # Only add separator and header if we have enhanced functions
        if enhanced_section.strip():
            return result + separator + header + enhanced_section
        else:
            print("⚠️ No enhanced functions to append (all identical to original)")
            return result
    
    def _is_library_function(self, func_name):
        """Check if a function is a library/system function"""
        # Standard C library functions
        std_library_functions = {
            'printf', 'scanf', 'malloc', 'free', 'calloc', 'realloc',
            'strcpy', 'strcat', 'strlen', 'strcmp', 'memcpy', 'memset',
            'fopen', 'fclose', 'fread', 'fwrite', 'exit', 'abort',
            'atoi', 'atof', 'system', 'time', 'rand', 'srand',
            'gets', 'puts', 'sprintf', 'snprintf', 'sscanf',
        }
        
        # POSIX/Unix functions
        posix_functions = {
            'open', 'close', 'read', 'write', 'fork', 'exec', 'pipe',
            'socket', 'bind', 'connect', 'listen', 'accept',
        }
        
        # Compiler/OS internal functions (usually start with __)
        internal_functions = {
            '__stack_chk_fail', '__stack_chk_guard', '__libc_start_main',
            '__gmon_start__', '__cxa_finalize', '__do_global_dtors_aux',
        }
        
        # Check all categories
        all_library_funcs = std_library_functions | posix_functions | internal_functions
        
        # Direct name match
        if func_name in all_library_funcs:
            return True
        
        # Functions starting with double underscore (compiler internals)
        if func_name.startswith('__'):
            return True
        
        # Common patterns (but be careful with user functions starting with single underscore!)
        # Let's NOT exclude single underscore functions - they're often user code
        
        return False
    
    def _postprocess_enhanced_output(self, llm_output, original_func, func_name):
        """
        Clean up LLM4Decompile output for a single function
        """
        # Remove the prompt if it's included
        if "# What is the source code?" in llm_output:
            parts = llm_output.split("# What is the source code?")
            if len(parts) > 1:
                llm_output = parts[1].strip()
        
        # Remove any markdown code blocks
        llm_output = re.sub(r'```[a-z]*\s*', '', llm_output)
        llm_output = re.sub(r'```\s*', '', llm_output)
        
        # Ensure function name is preserved
        # Look for function declaration in enhanced output
        func_pattern = r'([a-zA-Z_][\w\s*\*]+)\s+([a-zA-Z_]\w*)\s*\(([^)]*)\)'
        match = re.search(func_pattern, llm_output)
        
        if match:
            enhanced_func_name = match.group(2)
            # If LLM changed the function name, restore the original
            if enhanced_func_name != func_name:
                llm_output = re.sub(r'\b' + re.escape(enhanced_func_name) + r'\b', func_name, llm_output, count=1)
                print(f"📝 Restored function name: {enhanced_func_name} → {func_name}")
        
        # Clean up any remaining Ghidra types
        llm_output = self._clean_ghidra_types(llm_output)
        
        # Add enhancement header
        timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        header = f"/* LLM4Decompile enhanced - {timestamp} */\n"
        
        return header + llm_output.strip()
    
    def enhance_code(self, ghidra_code, filename="unknown.c", mode="all", exclude_functions=None):
        """
        Main enhancement function - ALWAYS appends enhanced version below original
        """
        print(f"✨ Enhancing {filename} with LLM4Decompile (APPEND mode)...")
        
        if not self.colab_url:
            print("⚠️ No enhancement method available, returning original")
            return ghidra_code
        
        if mode == "all":
            # Enhance all functions (except libraries) and append
            return self.enhance_all_functions(ghidra_code, filename, exclude_functions)
        elif mode == "single":
            # Enhance only the first non-library function and append
            functions = self.extract_all_functions(ghidra_code)
            if functions:
                for func_name, func_code in functions.items():
                    if not self._is_library_function(func_name):
                        print(f"🎯 Enhancing first non-library function: {func_name}")
                        enhanced_func = self.enhance_single_function(func_code, func_name, filename)
                        return self._append_single_function(ghidra_code, func_name, func_code, enhanced_func)
            
            print("⚠️ No non-library functions found, returning original")
            return ghidra_code
        elif mode == "specific":
            # Enhance specific functions by name and append
            if exclude_functions:
                return self.enhance_all_functions(ghidra_code, filename, exclude_functions)
            else:
                print("⚠️ No specific functions provided, enhancing all")
                return self.enhance_all_functions(ghidra_code, filename)
        elif mode.startswith("func:"):
            # Enhance a specific function by name and append
            target_func = mode[5:]  # Remove "func:" prefix
            func_code = self.extract_single_function(ghidra_code, target_func)
            if func_code:
                enhanced_func = self.enhance_single_function(func_code, target_func, filename)
                return self._append_single_function(ghidra_code, target_func, func_code, enhanced_func)
            else:
                print(f"⚠️ Function '{target_func}' not found, returning original")
                return ghidra_code
        else:
            print(f"⚠️ Unknown mode '{mode}', returning original")
            return ghidra_code
    
    def _append_single_function(self, original_code, func_name, original_func, enhanced_func):
        """Append a single enhanced function below original code"""
        print(f"📎 Appending enhanced function '{func_name}' below original...")
        
        # Only append if enhanced is different
        if enhanced_func == original_func:
            print(f"⏭️ No changes for {func_name}, returning original")
            return original_code
        
        # Add separator and header
        separator = "\n\n" + "="*80 + "\n"
        timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        
        header = f"""// ===================================================
// LLM4Decompile ENHANCED FUNCTION: {func_name}
// ===================================================
// Enhancement Time: {timestamp}
// Original: {len(original_func)} chars → Enhanced: {len(enhanced_func)} chars
// ===================================================

"""
        
        return original_code + separator + header + enhanced_func + "\n"
    
    def get_enhancement_info(self, original_len, enhanced_len):
        """
        Get enhancement statistics - Flask compatible version
        Accepts lengths (not strings) to match your endpoint
        """
        return {
            "original_length": int(original_len),
            "enhanced_length": int(enhanced_len),
            "difference": int(enhanced_len - original_len),
            "improvement_percent": round((enhanced_len - original_len) / max(original_len, 1) * 100, 2)
        }