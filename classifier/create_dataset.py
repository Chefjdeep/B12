# create_dataset.py
from dataset.dataset_generator import DatasetGenerator
from dataset.sample_code import SampleCodeGenerator
import os, json

os.makedirs("./dataset/C", exist_ok=True)
os.makedirs("./dataset/C++", exist_ok=True)

dataset_gen = DatasetGenerator()
code_gen = SampleCodeGenerator()

metadata = []

for code in code_gen.generate_c_codes():
    metadata.extend(dataset_gen.generate_c_sample(code, "./dataset/C"))

for code in code_gen.generate_cpp_codes():
    metadata.extend(dataset_gen.generate_cpp_sample(code, "./dataset/C++"))

with open("./dataset/metadata.json", "w") as f:
    json.dump(metadata, f, indent=2)

print(f"Dataset generated with {len(metadata)} binaries.")
