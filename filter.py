import numpy as np
import scipy.signal as signal
import matplotlib.pyplot as plt

# Simulated EMG raw signal (Replace with actual ESP32 data once we have that figured out lol)
emg_signal = np.random.randn(1000) * 0.5  # Simulated noisy EMG data

# My bandpass filter (20-450Hz)
def bandpass_filter(signal, lowcut=20, highcut=450, fs=1000, order=4):
    nyquist = 0.5 * fs
    low = lowcut / nyquist
    high = highcut / nyquist
    b, a = signal.butter(order, [low, high], btype='band')
    return signal.filtfilt(b, a, signal)

filtered_emg = bandpass_filter(emg_signal)

# Feature Extraction, we love data science
mav = np.mean(np.abs(filtered_emg))  # Mean Absolute Value
rms = np.sqrt(np.mean(filtered_emg**2))  # Root Mean Square
zcr = np.sum(np.diff(np.sign(filtered_emg)) != 0)  # Zero Crossing Rate

print(f"EMG Features - MAV: {mav}, RMS: {rms}, ZCR: {zcr}")

# Plotting that clean and filtered signal hehe
plt.plot(filtered_emg)
plt.title("Filtered EMG Signal")
plt.show()
