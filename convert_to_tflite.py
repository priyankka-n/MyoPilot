import os

# Read the TFLite model
tflite_model_path = "emg_model.tflite"

if not os.path.exists(tflite_model_path):
    raise FileNotFoundError(f" ERROR: {tflite_model_path} not found! Run train_model.py first.")

# Read the binary model
with open(tflite_model_path, "rb") as f:
    model_bytes = f.read()

# Convert to a C array
hex_array = ", ".join(f"0x{b:02x}" for b in model_bytes)

# Generate the C header file
header_content = f"""#ifndef MODEL_DATA_H
#define MODEL_DATA_H

const unsigned char model_data[] = {{
    {hex_array}
}};

const unsigned int model_data_len = {len(model_bytes)};

#endif // MODEL_DATA_H
"""

# Save as model_data.h
with open("model_data.h", "w") as f:
    f.write(header_content)

print("Model successfully converted to C array and saved as model_data.h")
