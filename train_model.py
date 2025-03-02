import pandas as pd
from sklearn.svm import SVC
import joblib

# Training data (MAV, RMS, ZCR for each cheek)
data = {
    "right_MAV": [0.50, 0.60, 0.45, 0.70],
    "right_RMS": [0.55, 0.65, 0.42, 0.75],
    "right_ZCR": [20, 25, 15, 30],
    "left_MAV": [0.50, 0.30, 0.70, 0.40],
    "left_RMS": [0.55, 0.32, 0.72, 0.45],
    "left_ZCR": [20, 10, 35, 15],
    "Label": ["forward", "left", "right", "stop"]
}

df = pd.DataFrame(data)
X = df.drop("Label", axis=1)
y = df["Label"]

model = SVC(kernel="linear")
model.fit(X, y)

joblib.dump(model, "ai_model/emg_classifier.pkl")
print("AI Model Updated for 3-electrode System!")
