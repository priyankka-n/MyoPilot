import joblib
import tensorflow.lite as tflite

# Load trained model
model = joblib.load("emg_classifier.pkl")

# Convert trained model to TensorFlow Lite format
converter = tflite.TFLiteConverter.from_keras_model(model)
tflite_model = converter.convert()

# Save model for ESP32 deployment
with open("emg_model.tflite", "wb") as f:
    f.write(tflite_model)

print("AI Model Converted & Ready for ESP32 Deployment!")
