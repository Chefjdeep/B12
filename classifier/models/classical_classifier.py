# models/classical_classifier.py
import numpy as np
import pickle
from sklearn.ensemble import RandomForestClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.preprocessing import StandardScaler
import xgboost as xgb

class LanguageClassifier:
    def __init__(self, model_type='xgboost'):
        self.model_type = model_type
        self.scaler = StandardScaler()
        self.feature_names = None
        
        if model_type == 'xgboost':
            self.model = xgb.XGBClassifier(
                n_estimators=100,
                max_depth=5,
                learning_rate=0.1,
                objective='multi:softprob',
                num_class=2,
                eval_metric='mlogloss'
            )
        elif model_type == 'rf':
            self.model = RandomForestClassifier(n_estimators=100, random_state=42)
        else:
            self.model = LogisticRegression(max_iter=1000)

    def extract_features(self, binary_path, extractor):
        features = extractor.extract_all_features(binary_path)

        if self.feature_names is None:
            self.feature_names = sorted(features.keys())

        vector = np.array([features.get(f, 0) for f in self.feature_names])
        return vector.reshape(1, -1)

    def train(self, X, y):
        if not hasattr(self, "encoder") or self.encoder is None:
            from sklearn.preprocessing import LabelEncoder
            self.encoder = LabelEncoder()

        y_encoded = self.encoder.fit_transform(y)
        X_scaled = self.scaler.fit_transform(X)
        self.model.fit(X_scaled, y_encoded)
        return self

    def predict_proba(self, X):
        X_scaled = self.scaler.transform(X)
        return self.model.predict_proba(X_scaled)

    def save(self, path):
        with open(path, 'wb') as f:
            pickle.dump(self.__dict__, f)

    def load(self, path):
        with open(path, 'rb') as f:
            self.__dict__.update(pickle.load(f))
        return self
