import serial
import matplotlib.pyplot as plt
import numpy as np

# Configure serial port (Update with your ESP32 port)
ser = serial.Serial('/dev/cu.usbserial-0001', 115200, timeout=1)

# Storage for real-time plotting
buffer_size = 100
right_mav = np.zeros(buffer_size)
left_mav = np.zeros(buffer_size)

plt.ion()  # Interactive mode for real-time plotting
fig, ax = plt.subplots()
line1, = ax.plot(right_mav, label="Right MAV")
line2, = ax.plot(left_mav, label="Left MAV")
ax.set_ylim(0, 3)
ax.legend()

while True:
    try:
        # Read line from serial
        line = ser.readline().decode('utf-8').strip()
        if not line:
            continue

        # Parse EMG data
        parts = line.split(",")
        if len(parts) == 6:
            right_mav_val = float(parts[0])
            left_mav_val = float(parts[3])

            # Update buffer
            right_mav = np.roll(right_mav, -1)
            left_mav = np.roll(left_mav, -1)
            right_mav[-1] = right_mav_val
            left_mav[-1] = left_mav_val

            # Update plot
            line1.set_ydata(right_mav)
            line2.set_ydata(left_mav)
            plt.draw()
            plt.pause(0.01)

    except KeyboardInterrupt:
        print("Exiting...")
        ser.close()
        break
