# pipeline/language_inferencer.py
import numpy as np
from features.multi_view_extractor import MultiViewFeatureExtractor
from models.classical_classifier import LanguageClassifier

class LanguageInferencer:
    def __init__(self, model_path):
        
        self.extractor = MultiViewFeatureExtractor()
        self.classifier = LanguageClassifier().load(model_path)
        self.languages = ['C', 'C++']

    def analyze_binary(self, binary_path):
        X = self.classifier.extract_features(binary_path, self.extractor)
        probs = self.classifier.predict_proba(X)[0]

        return {
            lang: float(probs[i])
            for i, lang in enumerate(self.languages)
        } | {'confidence': float(max(probs))}
