import pickle
import sys
import json
import numpy as np
from feature_extractor import FeatureExtractor

import joblib
import numpy as np

def predict_binary(filepath):
    # Load trained model bundle from disk
    data = joblib.load('classifier/model_bundle.joblib')
    
    model = data['model']
    extractor = FeatureExtractor()
    
    # Extract feature vector from binary
    features = extractor.extract(filepath)
    
    # Run prediction
    prediction = model.predict([features])[0]
    prob = model.predict_proba([features])[0]

    # Determine language label
    language = "C++" if prediction == 1 else "C"

    # Confidence is the maximum class probability
    confidence = float(np.max(prob))

    return language, confidence


if __name__ == '__main__':
    # Ensure correct CLI usage
    if len(sys.argv) != 2:
        print("Usage: python3 predict_xgb.py <binary_file>")
        sys.exit(1)
    
    language, confidence = predict_binary(sys.argv[1])

    # IMPORTANT CHANGE:
    # Output is now JSON so Flask (or any caller) can parse it safely.
    # No ML logic is moved to Flask.
    output = {
        "language": language,
        "confidence": confidence
    }

    print(json.dumps(output))


#simulator
# import sys
# import json
# import random

# def simulate_prediction():
#     # Randomly choose language
#     language = random.choice(["C", "C++"])

#     # Generate realistic confidence
#     if language == "C++":
#         confidence = random.uniform(0.70, 0.99)
#     else:
#         confidence = random.uniform(0.70, 0.95)

#     return {
#         "language": language,
#         "confidence": round(confidence, 4)
#     }

# if __name__ == "__main__":
#     # Keep CLI interface identical to real script
#     if len(sys.argv) != 2:
#         print("Usage: python predict_xgb_simulator.py <binary_file>")
#         sys.exit(1)

#     output = simulate_prediction()
#     print(json.dumps(output))
