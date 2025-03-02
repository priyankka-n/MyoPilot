import numpy as np
import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers
import tensorflow.lite as tflite
import joblib

# Simulated Training Data (Replace with Real EMG Data Later)
# Format: [MAV Right, RMS Right, ZCR Right, MAV Left, RMS Left, ZCR Left] → Movement
data = np.array([
    [0.5, 0.6, 10, 0.4, 0.5, 12, 0],  # No movement
    [1.2, 1.3, 20, 0.5, 0.6, 14, 1],  # Left cheek clench → Turn Left
    [0.5, 0.6, 15, 1.3, 1.4, 22, 2],  # Right cheek clench → Turn Right
    [1.2, 1.3, 25, 1.3, 1.4, 28, 3],  # Both cheeks clench → Move Forward
])

X, y = data[:, :-1], data[:, -1]  # Features & Labels

# Define a TinyML-Friendly Neural Network
model = keras.Sequential([
    layers.Dense(6, activation="relu", input_shape=(6,)),  # 6 Features
    layers.Dense(4, activation="softmax")  # 4 Output Classes (0=Stop, 1=Left, 2=Right, 3=Forward)
])

# Compile & Train
model.compile(optimizer="adam", loss="sparse_categorical_crossentropy", metrics=["accuracy"])
model.fit(X, y, epochs=100, verbose=1)

# Save Normal Model (For Debugging)
model.save("emg_model.keras")
joblib.dump((X, y), "training_data.pkl")  # Save data for reference

# Convert Model to TFLite Micro
converter = tflite.TFLiteConverter.from_keras_model(model)
tflite_model = converter.convert()

# Save Model for ESP32 Deployment
with open("emg_model.tflite", "wb") as f:
    f.write(tflite_model)

print("Model training complete! TFLite model saved as emg_model.tflite")