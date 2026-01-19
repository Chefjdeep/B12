# enhance.py - REAL Heuristic Enhancement Module (ML-Ready Version)
import re
import os
from typing import Dict, List, Tuple, Optional

class HeuristicEnhancer:
    def __init__(self):
        """Initialize with transformation rules"""
        print("🔧 Initializing REAL heuristic enhancer...")
        
        # Type conversions from Ghidra to standard C
        self.type_mappings = {
            'undefined8': 'long long',
            'undefined4': 'int', 
            'undefined2': 'short',
            'undefined1': 'char',
            'undefined': 'void',
            'byte': 'unsigned char',
            'word': 'unsigned short',
            'dword': 'unsigned int',
            'qword': 'unsigned long long',
            'ulong': 'unsigned long',
            'ushort': 'unsigned short',
            'uint': 'unsigned int',
        }
        
        # Critical security functions - MUST be detected by ML
        self.critical_security_functions = {
            'gets': 'CRITICAL: Buffer overflow vulnerability',
            '_gets': 'CRITICAL: Buffer overflow vulnerability',
            'system': 'SECURITY: Command injection risk',
            '_system': 'SECURITY: Command injection risk',
            'strcpy': 'WARNING: Use strncpy with bounds checking',
            'strcat': 'WARNING: Use strncat with bounds checking',
            'sprintf': 'WARNING: Use snprintf to prevent overflow',
            'scanf': 'SECURITY: Unsafe input function',
            '_scanf': 'SECURITY: Unsafe input function',
            'memcpy': 'WARNING: Check buffer bounds',
            'memset': 'Note: Memory initialization',
            'malloc': 'Note: Memory allocation',
            'free': 'Note: Memory deallocation',
            'printf': 'Note: Output function',
            '_printf': 'Note: Output function',
        }
        
        # Function purpose inference
        self.function_purposes = {
            'unsafe_buffer': 'Buffer overflow demonstration',
            'command_execution': 'Command injection demonstration',
            'entry': 'Program entry point',
            'main': 'Program entry point',
            'stack_chk_fail': 'Stack overflow detection',
            'init': 'Initialization function',
            'setup': 'Setup function',
            'process': 'Data processing function',
            'handle': 'Event handler',
            'callback': 'Callback function',
            'get': 'Data retrieval',
            'set': 'Data assignment',
            'create': 'Object creation',
            'destroy': 'Object destruction',
            'open': 'Resource opening',
            'close': 'Resource closing',
            'read': 'Data reading',
            'write': 'Data writing',
        }
        
        # Common pointer patterns to simplify
        self.pointer_patterns = {
            'PTR____': 'ptr_',
            'PTR__': 'ptr_',
            'DAT_': 'data_',
            'LAB_': 'label_',
            'FUN_': 'func_',
        }
    
    def enhance_code_new(self, ghidra_code: str, filename: str = "unknown.c") -> str:
        """
        Apply REAL heuristic enhancements to Ghidra decompiled code
        Returns clean, enhanced code optimized for ML security classification
        """
        print(f"✨ Applying ML-ready heuristic enhancements to {filename}...")
        
        # Step 1: Clean Ghidra artifacts
        cleaned_code = self._clean_ghidra_artifacts(ghidra_code)
        
        # Step 2: Convert types
        enhanced_code = self._convert_types(cleaned_code)
        
        # Step 3: Fix function names
        enhanced_code = self._fix_function_names(enhanced_code)
        
        # Step 4: Improve variable names
        enhanced_code = self._improve_variable_names(enhanced_code)
        
        # Step 5: Simplify pointer patterns for ML
        enhanced_code = self._simplify_pointers(enhanced_code)
        
        # Step 6: Add security annotations
        enhanced_code = self._add_security_annotations(enhanced_code)
        
        # Step 7: Clean formatting for ML readability
        enhanced_code = self._clean_formatting_ml(enhanced_code)
        
        # Step 8: Create final output
        final_code = self._create_ml_output(enhanced_code, filename)
        
        print(f"ML-ready enhancement complete")
        return final_code
    
    def _clean_ghidra_artifacts(self, code: str) -> str:
        """Remove Ghidra-specific artifacts but keep useful information"""
        lines = code.split('\n')
        cleaned_lines = []
        
        for line in lines:
            # Skip empty lines at start
            if not line.strip() and len(cleaned_lines) == 0:
                continue
            
            # Remove warning lines but keep as comments if useful
            if 'WARNING:' in line or 'warning:' in line.lower():
                if 'jumptable' in line or 'recover' in line or 'Subroutine' in line:
                    clean_line = line.replace('WARNING:', '// Note:')
                    clean_line = clean_line.replace('warning:', '// Note:')
                    cleaned_lines.append(clean_line.strip())
                continue
            
            # Remove RAM/hex comments that confuse ML
            if '/* WARNING: ' in line and '*/' in line:
                continue
            
            # Remove excessive separator lines
            if line.strip().startswith('/* ==') and '== */' in line:
                continue
            
            # Keep function headers
            if line.strip().startswith('// Function:'):
                cleaned_lines.append(line)
                continue
            
            # Process the line
            cleaned_line = line
            
            # Remove Ghidra's weird comment artifacts
            cleaned_line = re.sub(r'/\*.*?RAM.*?\*/', '', cleaned_line)
            cleaned_line = re.sub(r'/\*.*?Could not.*?\*/', '// Note: Control flow unclear', cleaned_line)
            cleaned_line = re.sub(r'/\*.*?Treating.*?\*/', '', cleaned_line)
            
            # Remove excessive spaces
            cleaned_line = re.sub(r'\s+', ' ', cleaned_line).strip()
            
            if cleaned_line:
                cleaned_lines.append(cleaned_line)
        
        return '\n'.join(cleaned_lines)
    
    def _convert_types(self, code: str) -> str:
        """Convert Ghidra types to standard C types for ML consistency"""
        enhanced = code
        
        # Convert basic types
        for ghidra_type, c_type in self.type_mappings.items():
            pattern = r'\b' + re.escape(ghidra_type) + r'\b'
            enhanced = re.sub(pattern, c_type, enhanced)
        
        # Fix pointer syntax for consistency
        enhanced = re.sub(r'(\w+)\s*\*\s*(\w+)', r'\1* \2', enhanced)
        enhanced = re.sub(r'(\w+)\s*\*\s*\*', r'\1**', enhanced)
        
        # Convert param_X to argX
        enhanced = re.sub(r'\b(param_)(\d+)\b', r'arg\2', enhanced)
        
        # Convert local_X to varX
        enhanced = re.sub(r'\b(local_)(\d+|[a-fA-F0-9]+)\b', r'var\2', enhanced)
        
        # Convert stack variables
        enhanced = re.sub(r'\bacStack_([0-9a-fA-F]+)\b', r'buffer_\1', enhanced)
        
        return enhanced
    
    def _fix_function_names(self, code: str) -> str:
        """Fix function names for better ML pattern recognition"""
        enhanced = code
        
        # Remove leading underscores from standard functions for ML consistency
        std_functions = ['printf', 'scanf', 'malloc', 'free', 'strlen', 'strcpy', 
                        'memcpy', 'memset', 'calloc', 'realloc', 'gets', 'system']
        
        for func in std_functions:
            pattern = r'\b_' + re.escape(func) + r'\b'
            enhanced = re.sub(pattern, func, enhanced)
        
        # Simplify Ghidra generated names
        enhanced = re.sub(r'\bFUN_([0-9a-fA-F]+)\b', r'func_\1', enhanced)
        enhanced = re.sub(r'\bLAB_([0-9a-fA-F]+)\b', r'label_\1', enhanced)
        
        return enhanced
    
    def _improve_variable_names(self, code: str) -> str:
        """Improve variable names for ML semantic understanding"""
        lines = code.split('\n')
        enhanced_lines = []
        
        for line in lines:
            enhanced_line = line
            
            # Improve common Ghidra variable patterns
            variable_patterns = [
                (r'\biVar(\d+)\b', r'var\1'),
                (r'\buVar(\d+)\b', r'uvar\1'),
                (r'\bsVar(\d+)\b', r'size\1'),
                (r'\bpcVar(\d+)\b', r'str\1'),
                (r'\bpvVar(\d+)\b', r'ptr\1'),
                (r'\bpiVar(\d+)\b', r'int_ptr\1'),
                (r'\bpuVar(\d+)\b', r'uint_ptr\1'),
                (r'\blocalVar(\d+)\b', r'local\1'),
            ]
            
            for pattern, replacement in variable_patterns:
                enhanced_line = re.sub(pattern, replacement, enhanced_line)
            
            enhanced_lines.append(enhanced_line)
        
        return '\n'.join(enhanced_lines)
    
    def _simplify_pointers(self, code: str) -> str:
        """Simplify pointer patterns for ML readability"""
        enhanced = code
        
        # Simplify complex pointer names
        for pattern, replacement in self.pointer_patterns.items():
            enhanced = re.sub(pattern, replacement, enhanced)
        
        # Remove excessive underscores
        enhanced = re.sub(r'_{3,}', '_', enhanced)
        
        return enhanced
    
    def _add_security_annotations(self, code: str) -> str:
        """Add security annotations - CRITICAL for ML classification"""
        lines = code.split('\n')
        enhanced_lines = []
        
        for line in lines:
            # Skip if already has security annotation
            if 'SECURITY:' in line or 'CRITICAL:' in line or 'WARNING:' in line:
                enhanced_lines.append(line)
                continue
            
            enhanced_line = line
            
            # Check for security-sensitive functions
            for func, warning in self.critical_security_functions.items():
                # Match whole word to avoid partial matches
                pattern = r'\b' + re.escape(func) + r'\b'
                if re.search(pattern, line):
                    # Don't add duplicate comments
                    if '//' not in line:
                        enhanced_line = f"{line}  // {warning}"
                    elif '//' in line and warning not in line:
                        # Append warning to existing comment
                        enhanced_line = line.replace('//', f'// {warning} - ')
                    break
            
            enhanced_lines.append(enhanced_line)
        
        return '\n'.join(enhanced_lines)
    
    def _clean_formatting_ml(self, code: str) -> str:
        """Clean up code formatting specifically for ML analysis"""
        lines = code.split('\n')
        formatted_lines = []
        indent_level = 0
        in_function = False
        
        i = 0
        while i < len(lines):
            line = lines[i]
            stripped = line.strip()
            
            # Skip empty lines at document start
            if not stripped and len(formatted_lines) == 0:
                i += 1
                continue
            
            # Handle function headers
            if stripped.startswith('// Function:'):
                # Add blank line before new function (except first)
                if formatted_lines and formatted_lines[-1] != '':
                    formatted_lines.append('')
                formatted_lines.append(line)
                in_function = True
                i += 1
                continue
            
            # Handle multi-line function declarations
            if in_function and stripped and not stripped.startswith('//'):
                if '{' in stripped:
                    # Function body starts
                    formatted_lines.append(stripped)
                    indent_level = 1
                    in_function = False
                else:
                    # Function declaration continues
                    formatted_lines.append(stripped)
                i += 1
                continue
            
            # Skip completely empty lines within formatting
            if not stripped:
                # Only add blank line if previous line wasn't blank
                if formatted_lines and formatted_lines[-1] != '':
                    formatted_lines.append('')
                i += 1
                continue
            
            # Skip preprocessor lines
            if stripped.startswith('#'):
                formatted_lines.append(stripped)
                i += 1
                continue
            
            # Apply indentation
            if stripped.endswith('}'):
                indent_level = max(0, indent_level - 1)
            
            indent = '    ' * indent_level
            
            # Clean the line: remove trivial comments for ML
            if '//' in stripped:
                parts = stripped.split('//', 1)
                code_part = parts[0].rstrip()
                comment_part = parts[1].strip()
                
                # Keep only security-related comments
                if any(keyword in comment_part for keyword in 
                      ['SECURITY:', 'CRITICAL:', 'WARNING:', 'Note:', 'Purpose:']):
                    formatted_lines.append(indent + code_part + '  // ' + comment_part)
                else:
                    # Remove trivial comments
                    if code_part:
                        formatted_lines.append(indent + code_part)
            else:
                formatted_lines.append(indent + stripped)
            
            # Adjust indentation for next line
            if stripped.endswith('{'):
                indent_level += 1
            
            i += 1
        
        # Clean up: remove consecutive blank lines
        result_lines = []
        for i, line in enumerate(formatted_lines):
            if i > 0 and line == '' and formatted_lines[i-1] == '':
                continue
            result_lines.append(line)
        
        # Ensure one blank line between functions
        final_lines = []
        in_func_body = False
        
        for i, line in enumerate(result_lines):
            final_lines.append(line)
            
            # Check if we're ending a function
            if line.strip().startswith('}'):
                # Look ahead to see if next line starts a new function
                if i + 1 < len(result_lines) and result_lines[i + 1].strip():
                    if result_lines[i + 1].strip().startswith('// Function:'):
                        final_lines.append('')
        
        return '\n'.join(final_lines)
    
    def _create_ml_output(self, enhanced_code: str, filename: str) -> str:
        """Create clean output optimized for ML security classification"""
        lines = enhanced_code.split('\n')
        
        # Remove any duplicate headers from previous enhancements
        clean_lines = []
        header_found = False
        
        for line in lines:
            # Skip old enhancement headers
            if 'Heuristic Enhanced Decompilation' in line:
                continue
            if 'Ghidra Time:' in line:
                continue
            if 'Enhancement Status:' in line:
                continue
            if 'Enhancement Time:' in line:
                continue
            
            # Only include the main header once
            if 'Enhanced decompilation' in line and not header_found:
                clean_lines.append(line)
                header_found = True
                continue
            elif 'Enhanced decompilation' in line and header_found:
                continue
            
            # Skip duplicate security headers
            if 'Security vulnerabilities annotated' in line and header_found:
                continue
            
            clean_lines.append(line)
        
        # Determine needed includes
        includes = set()
        code_text = '\n'.join(clean_lines)
        
        if 'printf' in code_text or 'scanf' in code_text:
            includes.add('#include <stdio.h>')
        if 'malloc' in code_text or 'free' in code_text:
            includes.add('#include <stdlib.h>')
        if 'strlen' in code_text or 'strcpy' in code_text:
            includes.add('#include <string.h>')
        
        # Build final output
        output_lines = []
        
        # Add minimal header
        output_lines.append(f"/* Enhanced: {filename} */")
        
        # Add includes if any
        if includes:
            output_lines.append('')
            output_lines.extend(sorted(includes))
        
        # Add the cleaned code
        if output_lines and output_lines[-1] != '':
            output_lines.append('')
        
        output_lines.extend(clean_lines)
        
        return '\n'.join(output_lines)
    
    def get_enhancement_info(self, original_len: int, enhanced_len: int) -> dict:
        """Get enhancement statistics"""
        return {
            "original_length": original_len,
            "enhanced_length": enhanced_len,
            "difference": enhanced_len - original_len,
            "improvement_percent": round((enhanced_len - original_len) / max(original_len, 1) * 100, 2)
        }
    
    def enhance_code(self, ghidra_code: str, filename: str = "unknown.c", mode: str = "all", **kwargs) -> str:
        """Backward compatibility method - uses new ML-ready enhancement"""
        return self.enhance_code_new(ghidra_code, filename)