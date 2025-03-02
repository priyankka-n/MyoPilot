import numpy as np
from scipy import signal

def bandpass_filter(emg_data, lowcut=20, highcut=450, fs=1000, order=4):
    nyquist = 0.5 * fs
    low, high = lowcut / nyquist, highcut / nyquist
    b, a = signal.butter(order, [low, high], btype='band')
    return signal.filtfilt(b, a, emg_data)

def extract_features(right_signal, left_signal):
    # Apply filtering
    right_filtered = bandpass_filter(right_signal)
    left_filtered = bandpass_filter(left_signal)

    # Extract MAV, RMS, ZCR for both cheeks
    features = {
        "right_MAV": np.mean(np.abs(right_filtered)),
        "right_RMS": np.sqrt(np.mean(right_filtered**2)),
        "right_ZCR": np.sum(np.diff(np.sign(right_filtered)) != 0),
        "left_MAV": np.mean(np.abs(left_filtered)),
        "left_RMS": np.sqrt(np.mean(left_filtered**2)),
        "left_ZCR": np.sum(np.diff(np.sign(left_filtered)) != 0),
    }
    return features
