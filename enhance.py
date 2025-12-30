# enhance.py - LLM4Decompile Enhancement Module
import re
import os
import datetime
import requests

# ==============================================================
# 🔧 ENHANCER CLASS
# ==============================================================

class LLM4DecompileEnhancer:
    def __init__(self, use_local_model=False, colab_url="https://ja-precongested-ungenuinely.ngrok-free.dev/llm4decompile"):
        """
        Initialize the enhancer
        """
        self.use_local_model = use_local_model
        self.colab_url = colab_url
        
        print(f"🔧 Initializing enhancer with Colab URL: {colab_url}")
    
    def extract_func0(self, ghidra_code):
        """
        Extract the first function from Ghidra decompiled code
        and rename it to 'func0' as LLM4Decompile expects
        """
        print("🔍 Extracting first function from Ghidra output...")
        
        # Clean Ghidra artifacts first
        clean_code = self._clean_ghidra_artifacts(ghidra_code)
        
        # Find the function named 'func0' specifically
        # Pattern: return_type func0(params)
        func_pattern = r'(\w+)\s+func0\s*\(([^)]*)\)'
        match = re.search(func_pattern, clean_code)
        
        if not match:
            print("⚠️ No 'func0' function found in Ghidra output")
            
            # Try to find any function with 'func' in name
            func_pattern = r'(\w+)\s+func\d*\s*\(([^)]*)\)'
            match = re.search(func_pattern, clean_code)
            
            if not match:
                # Try to find any function that prints "Hello, World!"
                for line in clean_code.split('\n'):
                    if 'puts' in line and 'Hello' in line:
                        # Find the function containing this line
                        print("🔍 Found Hello World print statement, searching for containing function...")
                        return self._extract_containing_function(clean_code, line)
        
        if not match:
            print("⚠️ No suitable function found in Ghidra output")
            return None
        
        # Get the full function (from function declaration to closing brace)
        func_start = match.start()
        func_name = "func0" if "func0" in match.group() else match.group().split()[1].split('(')[0]
        
        print(f"📝 Found function: {func_name}")
        
        # Find the complete function body
        func_code = self._extract_complete_function_body(clean_code, func_start)
        
        if not func_code:
            print("⚠️ Could not extract complete function body")
            return None
        
        # Rename function to 'func0' if it's not already
        if func_name != "func0":
            func_code = re.sub(
                r'\b' + re.escape(func_name) + r'\b',
                'func0',
                func_code,
                count=1  # Only replace the first occurrence (function name)
            )
            print(f"📝 Renamed {func_name} to func0")
        
        # Clean up Ghidra types
        func_code = self._clean_ghidra_types(func_code)
        
        print(f"✅ Extracted func0: {func_code[:100]}...")
        return func_code
    
    def _extract_containing_function(self, code, target_line):
        """Extract the function containing a specific line"""
        lines = code.split('\n')
        
        # Find the line with Hello World
        target_idx = -1
        for i, line in enumerate(lines):
            if 'puts' in line and 'Hello' in line:
                target_idx = i
                break
        
        if target_idx == -1:
            return None
        
        # Find function start (going backwards)
        func_start = -1
        for i in range(target_idx, -1, -1):
            if lines[i].strip() and ')' in lines[i] and '{' in lines[i+1]:
                func_start = i
                break
        
        # Find function end (going forward)
        if func_start != -1:
            brace_count = 0
            func_lines = []
            for i in range(func_start, len(lines)):
                line = lines[i]
                func_lines.append(line)
                brace_count += line.count('{') - line.count('}')
                if brace_count == 0 and i > func_start:
                    break
            
            return '\n'.join(func_lines)
        
        return None
    
    def _extract_complete_function_body(self, code, start_pos):
        """Extract complete function body from start position"""
        # Find the opening brace
        open_brace = code.find('{', start_pos)
        if open_brace == -1:
            return None
        
        # Find matching closing brace
        brace_count = 1
        current_pos = open_brace + 1
        
        while brace_count > 0 and current_pos < len(code):
            if code[current_pos] == '{':
                brace_count += 1
            elif code[current_pos] == '}':
                brace_count -= 1
            current_pos += 1
        
        if brace_count == 0:
            return code[start_pos:current_pos]
        
        return None
    
    def _clean_ghidra_types(self, code):
        """Convert Ghidra types to standard C types"""
        # Replace undefined types
        code = re.sub(r'\bundefined8\b', 'int', code)
        code = re.sub(r'\bundefined4\b', 'int', code)
        code = re.sub(r'\bundefined2\b', 'short', code)
        code = re.sub(r'\bundefined1\b', 'char', code)
        code = re.sub(r'\bundefined\b', 'void', code)
        
        # Clean up pointer syntax
        code = re.sub(r'\b(\w+)\s*\*\s*\*', r'\1**', code)
        code = re.sub(r'\b(\w+)\s*\*', r'\1*', code)
        
        return code
    
    def _clean_ghidra_artifacts(self, code):
        """Remove Ghidra-specific artifacts"""
        # Remove Ghidra warning comments
        code = re.sub(r'/\* WARNING:.*?\*/', '', code, flags=re.DOTALL)
        code = re.sub(r'// WARNING:.*?\n', '', code)
        
        # Remove Ghidra's undefined variable comments
        code = re.sub(r'/\*.*?undefined.*?\*/', '', code, flags=re.DOTALL)
        
        # Remove bad instruction warnings
        code = re.sub(r'/\* WARNING: Bad instruction.*?\*/', '', code, flags=re.DOTALL)
        code = re.sub(r'/\* WARNING: Control flow.*?\*/', '', code, flags=re.DOTALL)
        code = re.sub(r'/\* WARNING: Removing unreachable.*?\*/', '', code, flags=re.DOTALL)
        code = re.sub(r'/\* WARNING: Unknown calling.*?\*/', '', code, flags=re.DOTALL)
        code = re.sub(r'/\* WARNING: Globals starting.*?\*/', '', code, flags=re.DOTALL)
        
        # Remove do-nothing blocks
        code = re.sub(r'do \{[^}]*/\* WARNING: Do nothing block[^}]*\} while\( true \);', '', code, flags=re.DOTALL)
        
        # Remove EXTERNAL function stubs
        code = re.sub(r'// Function: <EXTERNAL>::\w+.*?\n.*?\n', '', code, flags=re.DOTALL)
        
        # Remove halt_baddata lines
        code = re.sub(r'\s*halt_baddata\(\);\s*', '', code)
        
        # Remove excessive blank lines
        code = re.sub(r'\n\s*\n\s*\n', '\n\n', code)
        
        # Remove duplicate functions (keep only one)
        lines = code.split('\n')
        seen_functions = set()
        unique_lines = []
        
        for line in lines:
            # Check if this line defines a function
            if '// Function:' in line:
                func_name = line.split(':')[-1].strip()
                if func_name not in seen_functions:
                    seen_functions.add(func_name)
                    unique_lines.append(line)
                else:
                    # Skip this duplicate function
                    continue
            else:
                unique_lines.append(line)
        
        code = '\n'.join(unique_lines)
        
        return code.strip()
    
    def create_llm4decompile_prompt(self, func0_code):
        """
        Create EXACT prompt format that LLM4Decompile expects:
        "# This is the assembly code:\n" + code + "\n# What is the source code?\n"
        
        Even though it's C code, we'll use the same format as assembly
        """
        prompt = f"# This is the assembly code:\n{func0_code}\n# What is the source code?\n"
        return prompt
    
    def enhance_with_colab(self, ghidra_code, filename="unknown.c"):
        """
        Extract func0 from Ghidra decompiled code, send to LLM4Decompile,
        and return enhanced result
        """
        if not self.colab_url:
            print("⚠️ No Colab URL configured")
            return ghidra_code
        
        # Extract func0 from Ghidra output
        func0_code = self.extract_func0(ghidra_code)
        
        if not func0_code:
            print("⚠️ Could not extract func0, returning original")
            return ghidra_code
        
        print(f"🚀 Sending func0 to LLM4Decompile API...")
        print(f"📝 Func0 code length: {len(func0_code)} chars")
        
        # Create the EXACT prompt format LLM4Decompile expects
        prompt = self.create_llm4decompile_prompt(func0_code)
        
        # Convert to bytes
        file_bytes = prompt.encode('utf-8')
        
        try:
            # Send to Colab API
            files = {'file': (f'func0_{filename}', file_bytes)}
            response = requests.post(self.colab_url, files=files, timeout=60)
            
            print(f"📡 API Response status: {response.status_code}")
            
            if response.status_code == 200:
                result = response.json()
                enhanced_output = result.get('decompiled_code', '')
                severity = result.get('severity', 0)
                
                print(f"✅ Received enhanced output from LLM4Decompile")
                print(f"📊 Severity score: {severity}")
                
                # Post-process the enhanced output
                enhanced_func = self._postprocess_enhanced_output(enhanced_output, func0_code)
                
                # Replace func0 with enhanced version in original code
                enhanced_full = self._replace_func0_in_code(ghidra_code, func0_code, enhanced_func)
                
                return enhanced_full
            else:
                print(f"❌ API Error {response.status_code}: {response.text[:200]}")
                return ghidra_code
                
        except Exception as e:
            print(f"❌ Request failed: {e}")
            import traceback
            traceback.print_exc()
            return ghidra_code
    
    def _postprocess_enhanced_output(self, llm_output, original_func):
        """
        Clean up LLM4Decompile output
        """
        # Remove the prompt if it's included
        if "# What is the source code?" in llm_output:
            parts = llm_output.split("# What is the source code?")
            if len(parts) > 1:
                llm_output = parts[1].strip()
        
        # Remove any markdown code blocks
        llm_output = re.sub(r'```[a-z]*\s*', '', llm_output)
        llm_output = re.sub(r'```\s*', '', llm_output)
        
        # Make sure it's still func0
        if 'func0' not in llm_output:
            # Try to find function name and rename to func0
            func_pattern = r'\b(int|void|char|float|double|long|short)\s+(\w+)\s*\('
            match = re.search(func_pattern, llm_output)
            if match:
                func_name = match.group(2)
                llm_output = re.sub(r'\b' + re.escape(func_name) + r'\b', 'func0', llm_output, count=1)
        
        # Add enhancement header
        timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        header = f"/* LLM4Decompile enhanced function - {timestamp} */\n"
        
        return header + llm_output.strip()
    
    def _replace_func0_in_code(self, original_code, original_func0, enhanced_func):
        """
        Replace the original func0 with enhanced version in the full code
        """
        if original_func0 not in original_code:
            # If we can't find exact match, append enhanced version
            print("⚠️ Could not find exact func0 match, appending enhanced version")
            separator = "\n" + "="*60 + "\n"
            enhanced_header = "/* LLM4Decompile ENHANCED FUNCTION */\n\n"
            return original_code + separator + enhanced_header + enhanced_func
        
        # Replace func0 with enhanced version
        enhanced_code = original_code.replace(original_func0, enhanced_func, 1)
        
        # Add overall enhancement header
        timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        header = f"""/*
 * ===================================================
 * LLM4Decompile Enhancement Applied
 * Time: {timestamp}
 * Enhanced function: func0
 * ===================================================
 */
"""
        return header + "\n" + enhanced_code
    
    def enhance_code(self, ghidra_code, filename="unknown.c"):
        """
        Main enhancement function
        """
        print(f"✨ Enhancing {filename} with LLM4Decompile...")
        
        if self.colab_url:
            return self.enhance_with_colab(ghidra_code, filename)
        else:
            print("⚠️ No enhancement method available, returning original")
            return ghidra_code
    
    def get_enhancement_info(self, original_len, enhanced_len):
        """Get enhancement statistics"""
        return {
            "original_length": original_len,
            "enhanced_length": enhanced_len,
            "difference": enhanced_len - original_len,
            "improvement_percent": round((enhanced_len - original_len) / max(original_len, 1) * 100, 2)
        }