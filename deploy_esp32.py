import joblib
import tensorflow as tf
import numpy as np

# Load the trained model
model = joblib.load("ai_model/emg_classifier.pkl")

# Convert the model to a TensorFlow-compatible function
def model_fn(features):
    return model.predict(features)

# Create a dummy input for conversion (same shape as real EMG features)
dummy_input = np.array([[0.5, 0.6, 20]], dtype=np.float32)  # Example MAV, RMS, ZCR values

# Convert to TensorFlow Lite
converter = tf.lite.TFLiteConverter.from_concrete_functions([tf.function(model_fn).get_concrete_function(dummy_input)])
tflite_model = converter.convert()

# Save the converted model
with open("ai_model/emg_model.tflite", "wb") as f:
    f.write(tflite_model)

print("AI Model Successfully Converted to TensorFlow Lite for ESP32 Deployment!")
