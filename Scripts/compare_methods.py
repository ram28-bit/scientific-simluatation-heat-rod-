import csv
import matplotlib.pyplot as plt

time = []
euler = []
rk2 = []
rk4 = []
exact = []

with open("results/method_comparison.csv", "r", newline="") as file:
    reader = csv.DictReader(file)

    for row in reader:
        time.append(float(row["time"]))
        euler.append(float(row["euler"]))
        rk2.append(float(row["rk2"]))
        rk4.append(float(row["rk4"]))
        exact.append(float(row["exact"]))

# Graph 1: Compare the temperature solutions
plt.figure(figsize=(10, 6))

plt.plot(time, euler, "o-", label="Euler")
plt.plot(time, rk2, "s-", label="RK2")
plt.plot(time, rk4, "^-", label="RK4")
plt.plot(time, exact, "--", label="Exact solution")

plt.xlabel("Time")
plt.ylabel("Temperature (°C)")
plt.title("Comparison of Numerical ODE Solvers")

plt.grid(True)
plt.legend()
plt.tight_layout()

plt.savefig("results/method_comparison.png", dpi=150)
plt.show()

# Graph 2: Compare absolute errors
euler_error = [abs(a - b) for a, b in zip(euler, exact)]
rk2_error = [abs(a - b) for a, b in zip(rk2, exact)]
rk4_error = [abs(a - b) for a, b in zip(rk4, exact)]

plt.figure(figsize=(10, 6))

plt.semilogy(time, euler_error, label="Euler error")
plt.semilogy(time, rk2_error, label="RK2 error")
plt.semilogy(time, rk4_error, label="RK4 error")

plt.xlabel("Time")
plt.ylabel("Absolute error (°C, logarithmic scale)")
plt.title("Numerical Accuracy Comparison")

plt.grid(True)
plt.legend()
plt.tight_layout()

plt.savefig("results/method_errors.png", dpi=150)
plt.show()

print("Comparison graphs saved in results/.")