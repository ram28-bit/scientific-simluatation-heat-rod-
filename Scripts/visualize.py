import csv
import matplotlib.pyplot as plt

time = []
numerical = []
exact = []
error = []

with open("results/cooling.csv", "r", newline="") as file:
    reader = csv.DictReader(file)

    for row in reader:
        time.append(float(row["time"]))
        numerical.append(float(row["numerical"]))
        exact.append(float(row["exact"]))
        error.append(float(row["error"]))

# Plot temperature over time
plt.figure(figsize=(9, 5))

plt.plot(time, numerical, "o-", label="Euler numerical solution")
plt.plot(time, exact, "--", label="Exact solution")

plt.xlabel("Time")
plt.ylabel("Temperature (°C)")
plt.title("Newton's Law of Cooling")

plt.grid(True)
plt.legend()
plt.tight_layout()

plt.savefig("results/cooling_temperature.png", dpi=150)
plt.show()

# Plot numerical error
plt.figure(figsize=(9, 5))

plt.plot(time, error, "o-", label="Absolute error")

plt.xlabel("Time")
plt.ylabel("Absolute error (°C)")
plt.title("Euler Method: Numerical Error")

plt.grid(True)
plt.legend()
plt.tight_layout()

plt.savefig("results/cooling_error.png", dpi=150)
plt.show()

print("Cooling simulation graphs saved.")