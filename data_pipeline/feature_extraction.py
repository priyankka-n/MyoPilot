import serial
import numpy as np
import csv
import time

# Update this to match your ESP32's Serial Port
SERIAL_PORT = "/dev/cu.usbserial-0001"  # Change to your actual port
BAUD_RATE = 115200
SAMPLES_PER_WINDOW = 50  # Matches sampleSize in adc.ino
OUTPUT_CSV = "emg_features.csv"

# Serial connection to ESP32
ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
time.sleep(2)  # Give time to establish connection


def compute_features(signal):
    """ Compute MAV, RMS, and ZCR for an EMG signal window """
    if len(signal) == 0:
        return 0, 0, 0

    mav = np.mean(np.abs(signal))  # Mean Absolute Value
    rms = np.sqrt(np.mean(np.square(signal)))  # Root Mean Square
    zcr = np.sum(np.diff(np.sign(signal)) != 0)  # Zero Crossing Rate

    return mav, rms, zcr


def extract_features():
    print(f"Listening to ESP32 on {SERIAL_PORT}... Press CTRL+C to stop.")

    with open(OUTPUT_CSV, mode="w", newline="") as file:
        writer = csv.writer(file)
        writer.writerow(["MAV_Left", "RMS_Left", "ZCR_Left", "MAV_Right", "RMS_Right", "ZCR_Right", "Movement"])

        while True:
            try:
                # Read line from ESP32
                line = ser.readline().decode("utf-8").strip()
                if not line:
                    continue

                # Parse ADC values
                if line.startswith("Detector ="):
                    detector = int(line.split("=")[-1].strip())
                    movement = 0  # Default STOP
                    if detector == 1:
                        movement = 1  # LEFT
                    elif detector == 2:
                        movement = 2  # RIGHT
                    elif detector == 3:
                        movement = 3  # FORWARD

                elif "ADC1" in line and "ADC2" in line:
                    parts = line.split()
                    adc1 = int(parts[1])  # Left cheek
                    adc2 = int(parts[3])  # Right cheek

                    left_signal.append(adc1)
                    right_signal.append(adc2)

                    if len(left_signal) >= SAMPLES_PER_WINDOW:
                        # Compute Features
                        mav_left, rms_left, zcr_left = compute_features(left_signal)
                        mav_right, rms_right, zcr_right = compute_features(right_signal)

                        # Save to CSV
                        writer.writerow([mav_left, rms_left, zcr_left, mav_right, rms_right, zcr_right, movement])
                        print(
                            f"Saved: {mav_left}, {rms_left}, {zcr_left}, {mav_right}, {rms_right}, {zcr_right}, {movement}")

                        # Reset signals
                        left_signal.clear()
                        right_signal.clear()

            except KeyboardInterrupt:
                print("\n Stopped Feature Extraction.")
                break
            except Exception as e:
                print(f"⚠ Error: {e}")


if __name__ == "__main__":
    left_signal = []
    right_signal = []
    extract_features()
