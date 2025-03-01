import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.svm import SVC
from sklearn.metrics import accuracy_score
import joblib

# Simulated training dataset (MAV, RMS, ZCR values for each movement)
data = {
    "MAV": [0.50, 0.45, 0.40, 0.42, 0.55, 0.52, 0.38, 0.41],
    "RMS": [0.60, 0.58, 0.50, 0.52, 0.62, 0.59, 0.48, 0.50],
    "ZCR": [20, 18, 14, 15, 22, 19, 13, 14],
    "Label": ["forward", "backward", "right", "left", "forward", "backward", "right", "left"]
}

# Convert to DataFrame
df = pd.DataFrame(data)
df.to_csv("emg_training_data.csv", index=False)  # Save for future use

print("Simulated EMG dataset created!")

# Extract features & labels
X = df[["MAV", "RMS", "ZCR"]].values  # Feature matrix
y = df["Label"].values  # Class labels (movement commands)

# Split into training & testing sets (80% train, 20% test)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Train the SVM classifier
model = SVC(kernel="linear")
model.fit(X_train, y_train)

# Test model performance
y_pred = model.predict(X_test)
accuracy = accuracy_score(y_test, y_pred)
print(f"Model Training Complete! Accuracy: {accuracy:.2f}")

# Save the trained model
joblib.dump(model, "emg_classifier.pkl")
print("AI Model Saved as 'emg_classifier.pkl'!")
