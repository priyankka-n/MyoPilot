import numpy as np
import scipy.signal as signal
import matplotlib.pyplot as plt

# Simulated EMG raw signal (Replace with actual ESP32 data later)
emg_signal = np.random.randn(1000) * 0.5  # Simulated noisy EMG data

# Bandpass Filter (20-450Hz)
def bandpass_filter(signal, lowcut=20, highcut=450, fs=1000, order=4):
    nyquist = 0.5 * fs
    low, high = lowcut / nyquist, highcut / nyquist
    b, a = signal.butter(order, [low, high], btype='band')
    return signal.filtfilt(b, a, signal)

filtered_emg = bandpass_filter(emg_signal)  # Apply filter

# Feature Extraction
mav = np.mean(np.abs(filtered_emg))  # Mean Absolute Value
rms = np.sqrt(np.mean(filtered_emg**2))  # Root Mean Square
zcr = np.sum(np.diff(np.sign(filtered_emg)) != 0)  # Zero Crossing Rate

print(f"EMG Features - MAV: {mav:.4f}, RMS: {rms:.4f}, ZCR: {zcr}")

# Plot Filtered EMG Signal
plt.figure(figsize=(10, 4))
plt.plot(filtered_emg, color='blue', linewidth=1)
plt.title("Filtered EMG Signal")
plt.xlabel("Time (samples)")
plt.ylabel("Amplitude")
plt.grid(True)
plt.show()

