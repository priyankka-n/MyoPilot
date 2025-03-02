import joblib
import numpy as np

# Load trained model
model = joblib.load("ai_model/emg_classifier.pkl")

# Simulated EMG input
new_emg_signal = np.array([[0.48, 0.56, 18]])  # MAV, RMS, ZCR

# Predict movement command
predicted_movement = model.predict(new_emg_signal)
print(f"Predicted Rover Command: {predicted_movement[0]}")
