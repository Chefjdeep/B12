import os
import numpy as np
from elftools.elf.elffile import ELFFile
from elftools.elf.sections import SymbolTableSection
import struct

class FeatureExtractor:
    def __init__(self):
        self.feature_names = [
            'file_size',
            'num_sections',
            'has_eh_frame',
            'has_gcc_except_table',
            'uses_libstdc',
            'uses_libc',
            'uses_libgcc_s',
            'has_Z_prefix',
            'has_operator_new',
            'has_cxa_symbols'
        ]
    
    def is_valid_elf(self, filepath):
        """Check if file is a valid ELF binary"""
        try:
            with open(filepath, 'rb') as f:
                # Check ELF magic number
                magic = f.read(4)
                return magic == b'\x7fELF'
        except:
            return False
    
    def extract(self, filepath):
        features = np.zeros(len(self.feature_names), dtype=np.float32)
        
        # Check if file exists and has content
        if not os.path.exists(filepath):
            return features
        
        file_size = os.path.getsize(filepath)
        if file_size < 100:  # Too small to be a real binary
            return features
        
        # Feature 0: File size (normalized)
        features[0] = file_size / (1024 * 1024)  # MB
        
        # Check ELF magic before processing
        if not self.is_valid_elf(filepath):
            return features
        
        try:
            with open(filepath, 'rb') as f:
                elf = ELFFile(f)
                
                # Feature 1: Number of sections
                features[1] = elf.num_sections()
                
                # Features 2-3: Section presence
                for i, section in enumerate(elf.iter_sections()):
                    name = section.name
                    if name == '.eh_frame':
                        features[2] = 1
                    elif name == '.gcc_except_table':
                        features[3] = 1
                
                # Features 4-6: Library imports
                dyn_section = elf.get_section_by_name('.dynamic')
                if dyn_section:
                    for tag in dyn_section.iter_tags():
                        if tag.entry.d_tag == 'DT_NEEDED':
                            lib = tag.needed
                            if 'libstdc++' in lib:
                                features[4] = 1
                            if 'libc.so' in lib or 'libc.' in lib:
                                features[5] = 1
                            if 'libgcc_s' in lib:
                                features[6] = 1
                
                # Features 7-10: Symbol patterns
                for section in elf.iter_sections():
                    if isinstance(section, SymbolTableSection):
                        for symbol in section.iter_symbols():
                            name = symbol.name
                            if not name:
                                continue
                            if name.startswith('_Z'):
                                features[7] = 1
                            if 'operator new' in name or 'operator delete' in name:
                                features[8] = 1
                            if '__cxa_' in name:
                                features[9] = 1
        
        except Exception as e:
            print(f"  Error processing {os.path.basename(filepath)}: {e}")
        
        return features