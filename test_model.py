import joblib
import numpy as np

# Load the trained model
model = joblib.load("emg_classifier.pkl")

# Simulated new EMG signal (replace with real ESP32 data later)
new_emg_signal = np.array([[0.48, 0.56, 18]])  # MAV, RMS, ZCR

# Predict movement command
predicted_movement = model.predict(new_emg_signal)
print(f"Predicted Rover Command: {predicted_movement[0]}")
