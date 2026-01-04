# pipeline/trainer.py
import os
import json
import numpy as np
from sklearn.model_selection import train_test_split, cross_val_score
from features.multi_view_extractor import MultiViewFeatureExtractor
from models.classical_classifier import LanguageClassifier

class ModelTrainer:
    def __init__(self, dataset_dir):
        self.dataset_dir = dataset_dir
        
    def build_dataset(self):
        X, y = [], []
        extractor = MultiViewFeatureExtractor()

        with open(os.path.join(self.dataset_dir, 'metadata.json')) as f:
            metadata = json.load(f)

        feature_names = None

        for item in metadata:
            features = extractor.extract_all_features(item['path'])

            if feature_names is None:
                feature_names = sorted(features.keys())

            X.append([features.get(f, 0) for f in feature_names])
            y.append(item['language'])

        return np.array(X), np.array(y), feature_names

    def train_and_evaluate(self, output_model):
        X, y, feature_names = self.build_dataset()

        X_train, X_test, y_train, y_test = train_test_split(
            X, y, test_size=0.2, stratify=y, random_state=42
        )

        clf = LanguageClassifier()
        clf.feature_names = feature_names
        clf.train(X_train, y_train)

        y_train_enc = clf.encoder.transform(y_train)
        y_test_enc = clf.encoder.transform(y_test)

        X_train_s = clf.scaler.transform(X_train)
        X_test_s = clf.scaler.transform(X_test)

        train_preds = clf.model.predict_proba(X_train_s).argmax(axis=1)
        test_preds = clf.model.predict_proba(X_test_s).argmax(axis=1)

        train_acc = (train_preds == y_train_enc).mean()
        test_acc = (test_preds == y_test_enc).mean()

        print("Train accuracy:", train_acc)
        print("Test accuracy:", test_acc)

        clf.save(output_model)
        return clf, test_acc
