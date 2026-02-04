import sys
import json
import joblib
import numpy as np
from feature_extractor import FeatureExtractor


def predict_binary(filepath, model_path="classifier/model_bundle.joblib"):
    # Load trained model bundle
    bundle = joblib.load(model_path)

    model = bundle['model']
    scaler = bundle['scaler']
    feature_names = bundle['feature_names']

    extractor = FeatureExtractor()

    # Extract features
    features = extractor.extract(filepath)
    if features is None:
        raise RuntimeError("Feature extraction failed")

    features = np.asarray(features, dtype=float)

    # Safety check
    if len(features) != len(feature_names):
        raise ValueError(
            f"Feature length mismatch: expected {len(feature_names)}, got {len(features)}"
        )

    # Scale features (CRITICAL)
    features_scaled = scaler.transform([features])

    # Predict
    prediction = int(model.predict(features_scaled)[0])
    prob = model.predict_proba(features_scaled)[0]

    language = "C++" if prediction == 1 else "C"
    confidence = float(np.max(prob))

    return language, confidence


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Usage: python3 predict_xgb.py <binary_file>")
        sys.exit(1)

    language, confidence = predict_binary(sys.argv[1])

    # JSON output for Flask / API
    output = {
        "language": language,
        "confidence": confidence
    }

    print(json.dumps(output))
