import numpy as np
import matplotlib.pyplot as plt

# -------------------------
# 1. Configuration
# -------------------------

# Change this to your actual file name / path
FILENAME = "./data/data001.csv"

# Change this to your delimiter, e.g. "," or ";"
DELIMITER = ","

# Set this to True if the first line is a header row (column names)
HAS_HEADER = True


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
# Adjust indices to match your actual column order.
# For example, if your CSV is:
# time,co2,temperature,humidity
# then:
#   time        -> column 0
#   co2         -> column 1
#   temperature -> column 2
#   humidity    -> column 3

time = data[:, 0]        # change if your time column is elsewhere
co2 = data[:, 1]         # CO2 column index
temperature = data[:, 2] # temperature column index
humidity = data[:, 3]    # humidity column index

print("\nColumn checks:")
print("Time (first 5):", time[:5])
print("CO2  (first 5):", co2[:5])
print("Temp (first 5):", temperature[:5])
print("Hum  (first 5):", humidity[:5])


# -------------------------
# 4. Basic analysis
# -------------------------

print("\nBasic statistics:")
print("CO2:  min =", np.min(co2), "max =", np.max(co2), "mean =", np.mean(co2))
print("Temp: min =", np.min(temperature), "max =", np.max(temperature), "mean =", np.mean(temperature))
print("Hum:  min =", np.min(humidity), "max =", np.max(humidity), "mean =", np.mean(humidity))

# Example: how many samples where CO2 > 800 ppm?
threshold = 800
mask_high_co2 = co2 > threshold
print("\nSamples with CO2 >", threshold, "ppm:", mask_high_co2.sum())


# -------------------------
# 5. Plotting
# -------------------------

# 5.1 CO2 over time
plt.figure(figsize=(10, 4))
plt.plot(time, co2, color="tab:green")
plt.xlabel("Time")          # adjust units if needed, e.g. "Time (s)"
plt.ylabel("CO2 (ppm)")
plt.title("CO2 over time")
plt.grid(True)
plt.tight_layout()
plt.show()

# 5.2 Temperature and humidity over time (same figure)
plt.figure(figsize=(10, 4))
plt.plot(time, temperature, label="Temperature (°C)", color="tab:red")
plt.plot(time, humidity, label="Humidity (%)", color="tab:blue")
plt.xlabel("Time")
plt.ylabel("Value")
plt.title("Temperature and humidity over time")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

# 5.3 CO2 vs sample index (if time is missing or weird)
indices = np.arange(len(co2))
plt.figure(figsize=(10, 4))
plt.plot(indices, co2, color="tab:green")
plt.xlabel("Sample index")
plt.ylabel("CO2 (ppm)")
plt.title("CO2 over samples (index)")
plt.grid(True)
plt.tight_layout()
plt.show()

# 5.4 Optional: smoothed CO2 (simple moving average)
window = 10  # number of points in moving window; adjust as you like
if len(co2) >= window:
    kernel = np.ones(window) / window
    co2_smooth = np.convolve(co2, kernel, mode="valid")

    # For plotting, align time to the smoothed series length
    time_smooth = time[window - 1 : window - 1 + len(co2_smooth)]

    plt.figure(figsize=(10, 4))
    plt.plot(time, co2, label="Raw CO2", alpha=0.4, color="tab:green")
    plt.plot(time_smooth, co2_smooth, label=f"Smoothed CO2 (window={window})", color="black")
    plt.xlabel("Time")
    plt.ylabel("CO2 (ppm)")
    plt.title("CO2 with simple moving average")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.show()
else:
    print("\nNot enough data points to compute a moving average with window =", window)


