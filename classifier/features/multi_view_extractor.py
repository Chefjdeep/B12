# features/multi_view_extractor.py
import re
from collections import Counter
import lief

class MultiViewFeatureExtractor:
    def __init__(self):
        self.feature_views = {}

    def disassemble(self, binary_path):
        """Simple disassembler - returns list of assembly lines"""
        try:
            import subprocess
            result = subprocess.run(
                ['objdump', '-d', binary_path],
                capture_output=True,
                text=True
            )
            lines = result.stdout.split('\n')
            asm_lines = [line for line in lines if '\t' in line]
            return asm_lines[:1000]
        except:
            return []

    def extract_strings(self, binary_path):
        """Extract strings from binary"""
        try:
            import subprocess
            result = subprocess.run(
                ['strings', binary_path],
                capture_output=True,
                text=True
            )
            return result.stdout.split('\n')
        except:
            return []

    def extract_all_features(self, binary_path):
        """Extract features from all views"""
        features = {}
        features.update(self.extract_symbol_features(binary_path))
        disassembly = self.disassemble(binary_path)
        features.update(self.extract_opcode_ngrams(disassembly))
        features.update(self.extract_cfg_statistics(disassembly))
        features.update(self.extract_string_features(binary_path))
        return features

    def extract_symbol_features(self, binary_path):
        """View 1: Library and symbol analysis"""
        binary = lief.parse(binary_path)
        if binary is None:
            return {
                'num_imports': 0,
                'num_exports': 0,
                'has_cpp_symbols': False,
                'has_c_symbols': False,
                'mangling_ratio': 0.0
            }

        symbols = []
        if hasattr(binary, "symbols") and binary.symbols:
            symbols = [s.name for s in binary.symbols if s.name]

        # Imports
        num_imports = len(binary.imports) if hasattr(binary, "imports") and binary.imports else 0

        # Exports (ELF vs PE safely)
        if isinstance(binary, lief.ELF.Binary):
            num_exports = len(binary.exports) if hasattr(binary, "exports") and binary.exports else 0
        elif isinstance(binary, lief.PE.Binary):
            num_exports = len(binary.exported_functions) if hasattr(binary, "exported_functions") and binary.exported_functions else 0
        else:
            num_exports = 0

        cpp_patterns = [r'^_Z', r'__cxa', r'__gxx', r'operator', r'typeinfo', r'vtable']
        c_patterns = [r'^[a-zA-Z_][a-zA-Z0-9_]*$']

        cpp_count = sum(1 for s in symbols if any(re.search(p, s) for p in cpp_patterns))
        c_count = sum(1 for s in symbols if any(re.search(p, s) for p in c_patterns))

        return {
        'num_imports': num_imports,
        'num_exports': num_exports,
        'has_cpp_symbols': cpp_count > 0,
        'has_c_symbols': c_count > 0,
        'mangling_ratio': cpp_count / len(symbols) if symbols else 0.0
        }

    def extract_opcode_ngrams(self, disassembly, n=2):
        opcodes = []

        for line in disassembly:
            if '\t' in line:
                opcode_part = line.split('\t')[-1].strip()
                opcode = opcode_part.split()[0]
                opcodes.append(opcode)

        ngrams = ['_'.join(opcodes[i:i+n]) for i in range(len(opcodes)-n+1)]
        counts = Counter(ngrams)

        return {
            f'ngram_{k}': v / len(ngrams)
            for k, v in counts.most_common(20)
        } if ngrams else {}

    def extract_cfg_statistics(self, disassembly):
        total = len(disassembly)
        calls = sum('call' in l for l in disassembly)
        indirect = sum('call' in l and '*' in l for l in disassembly)
        jumps = sum(any(j in l for j in ['jmp', 'je', 'jne']) for l in disassembly)
        funcs = sum('push' in l and 'rbp' in l for l in disassembly)

        return {
            'num_functions': funcs,
            'indirect_call_ratio': indirect / calls if calls else 0,
            'jump_density': jumps / total if total else 0,
            'complexity': (calls + jumps) / total if total else 0
        }

    def extract_string_features(self, binary_path):
        strings = self.extract_strings(binary_path)

        return {
            'has_rtti_strings': any(s for s in strings if 'typeinfo' in s or 'vtable' in s),
            'has_stl_strings': any(s for s in strings if 'std::' in s or 'vector' in s),
            'string_entropy': 0
        }
