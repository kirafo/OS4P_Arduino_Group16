import numpy as np
import matplotlib.pyplot as plt

# -------------------------
# 1. Configuration
# -------------------------

FILENAME = "./data/data001.csv"   # change to your file name/path
DELIMITER = ","             # your CSV uses commas
HAS_HEADER = True           # first row is header


# -------------------------
# 2. Load CSV with NumPy
# -------------------------

skiprows = 1 if HAS_HEADER else 0

data = np.loadtxt(FILENAME, delimiter=DELIMITER, skiprows=skiprows)

print("Loaded data from", FILENAME)
print("Shape (rows, cols):", data.shape)
print("First 5 rows:\n", data[:5])


# -------------------------
# 3. Extract columns
# -------------------------
# CSV structure:
# Time (seconds),CO2 (ppm),Temperature (C),Pressure (Pa),Humidity (%)

time = data[:, 0]        # Time (seconds)
co2 = data[:, 1]         # CO2 (ppm)
temperature = data[:, 2] # Temperature (C)
pressure = data[:, 3]    # Pressure (Pa)
humidity = data[:, 4]    # Humidity (%)

print("\nColumn checks (first 5 values):")
print("Time       :", time[:5])
print("CO2        :", co2[:5])
print("Temperature:", temperature[:5])
print("Pressure   :", pressure[:5])
print("Humidity   :", humidity[:5])


# -------------------------
# 4. Basic analysis
# -------------------------

print("\nBasic statistics:")
print("CO2:        min =", np.min(co2),        "max =", np.max(co2),        "mean =", np.mean(co2))
print("Temperature: min =", np.min(temperature), "max =", np.max(temperature), "mean =", np.mean(temperature))
print("Pressure:    min =", np.min(pressure),   "max =", np.max(pressure),   "mean =", np.mean(pressure))
print("Humidity:    min =", np.min(humidity),   "max =", np.max(humidity),   "mean =", np.mean(humidity))

threshold_co2 = 800
mask_high_co2 = co2 > threshold_co2
print("\nSamples with CO2 >", threshold_co2, "ppm:", mask_high_co2.sum())


# -------------------------
# 5. Plotting
# -------------------------

# 5.1 CO2 over time
plt.figure(figsize=(10, 4))
plt.plot(time, co2, color="tab:green")
plt.xlabel("Time (s)")
plt.ylabel("CO2 (ppm)")
plt.title("CO2 over time")
plt.grid(True)
plt.tight_layout()
plt.show()

# 5.2 Temperature and humidity over time
plt.figure(figsize=(10, 4))
plt.plot(time, temperature, label="Temperature (°C)", color="tab:red")
plt.plot(time, humidity,    label="Humidity (%)",    color="tab:blue")
plt.xlabel("Time (s)")
plt.ylabel("Value")
plt.title("Temperature and humidity over time")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

# 5.3 Pressure over time
plt.figure(figsize=(10, 4))
plt.plot(time, pressure, color="tab:purple")
plt.xlabel("Time (s)")
plt.ylabel("Pressure (Pa)")
plt.title("Pressure over time")
plt.grid(True)
plt.tight_layout()
plt.show()

# 5.4 Optional: smoothed CO2 (simple moving average)
window = 10  # number of points in moving window
if len(co2) >= window:
    kernel = np.ones(window) / window
    co2_smooth = np.convolve(co2, kernel, mode="valid")
    time_smooth = time[window - 1 : window - 1 + len(co2_smooth)]

    plt.figure(figsize=(10, 4))
    plt.plot(time, co2, label="Raw CO2", alpha=0.4, color="tab:green")
    plt.plot(time_smooth, co2_smooth, label=f"Smoothed CO2 (window={window})", color="black")
    plt.xlabel("Time (s)")
    plt.ylabel("CO2 (ppm)")
    plt.title("CO2 with simple moving average")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.show()
else:
    print("\nNot enough data points to compute a moving average with window =", window)