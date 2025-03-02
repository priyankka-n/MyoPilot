import serial
import numpy as np
import joblib

model = joblib.load("ai_model/emg_classifier.pkl")
ser = serial.Serial('/dev/ttyUSB0', 115200) # UPDATE HERE

while True:
    data = ser.readline().decode().strip()
    try:
        right_mav, right_rms, right_zcr, left_mav, left_rms, left_zcr = map(float, data.split(","))
        features = np.array([[right_mav, right_rms, right_zcr, left_mav, left_rms, left_zcr]])
        predicted_movement = model.predict(features)
        print(f"Predicted Rover Command: {predicted_movement[0]}")
    except ValueError:
        print("Invalid data received. Skipping...")
