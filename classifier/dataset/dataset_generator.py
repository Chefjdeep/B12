# dataset/dataset_generator.py
import subprocess
import os
import tempfile
from pathlib import Path

class DatasetGenerator:
    def __init__(self):
        self.compilers = ['gcc', 'clang', 'g++', 'clang++']
        self.opt_levels = ['-O0', '-O1', '-O2', '-O3', '-Os']
        
    def generate_c_sample(self, source_code, output_dir):
        """Compile C code with variations"""
        samples = []
        
        for compiler in ['gcc', 'clang']:
            for opt in self.opt_levels:
                for stripped in [True, False]:
                    output_path = os.path.join(
                        output_dir,
                        f'c_{compiler}_{opt}_{"stripped" if stripped else "debug"}.bin'
                    )
                    
                    cmd = [compiler, opt, '-o', output_path]
                    if stripped:
                        cmd.append('-s')
                    
                    # Add source file
                    with tempfile.NamedTemporaryFile(mode='w', suffix='.c', delete=False) as f:
                        f.write(source_code)
                        source_file = f.name
                    
                    cmd.append(source_file)
                    
                    try:
                        subprocess.run(cmd, check=True, capture_output=True)
                        samples.append({
                            'path': output_path,
                            'language': 'C',
                            'compiler': compiler,
                            'opt_level': opt,
                            'stripped': stripped
                        })
                    except:
                        pass
                    
                    os.unlink(source_file)
        
        return samples
    
    def generate_cpp_sample(self, source_code, output_dir):
        """Compile C++ code with variations"""
        samples = []
        
        for compiler in ['g++', 'clang++']:
            for opt in self.opt_levels:
                for stripped in [True, False]:
                    output_path = os.path.join(
                        output_dir,
                        f'cpp_{compiler}_{opt}_{"stripped" if stripped else "debug"}.bin'
                    )
                    
                    cmd = [compiler, opt, '-o', output_path]
                    if stripped:
                        cmd.append('-s')
                    
                    # Add source file
                    with tempfile.NamedTemporaryFile(mode='w', suffix='.cpp', delete=False) as f:
                        f.write(source_code)
                        source_file = f.name
                    
                    cmd.append(source_file)
                    
                    try:
                        subprocess.run(cmd, check=True, capture_output=True)
                        samples.append({
                            'path': output_path,
                            'language': 'C++',
                            'compiler': compiler,
                            'opt_level': opt,
                            'stripped': stripped
                        })
                    except:
                        pass
                    
                    os.unlink(source_file)
        
        return samples