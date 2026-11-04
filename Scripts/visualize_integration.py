import csv
import matplotlib.pyplot as plt

N = []
trapezoidal = []
simpson = []
exact = []
trap_error = []
simp_error = []

with open("results/integration.csv", "r", newline="") as file:
    reader = csv.DictReader(file)

    for row in reader:
        N.append(int(row["N"]))
        trapezoidal.append(float(row["trapezoidal"]))
        simpson.append(float(row["simpson"]))
        exact.append(float(row["exact"]))
        trap_error.append(float(row["trapezoidal_error"]))
        simp_error.append(float(row["simpson_error"]))

# Graph 1: Integral estimates
plt.figure(figsize=(10, 6))

plt.plot(N, trapezoidal, "o-", label="Trapezoidal Rule")
plt.plot(N, simpson, "s-", label="Simpson's Rule")
plt.axhline(y=2.0, linestyle="--", label="Exact Integral")

plt.xlabel("Number of Subintervals (N)")
plt.ylabel("Integral Estimate")
plt.title("Numerical Integration: Accuracy vs Grid Size")

plt.grid(True)
plt.legend()
plt.tight_layout()

plt.savefig("results/integration_comparison.png", dpi=150)
plt.show()

# Graph 2: Absolute error
plt.figure(figsize=(10, 6))

plt.loglog(N, trap_error, "o-", label="Trapezoidal Error")
plt.loglog(N, simp_error, "s-", label="Simpson's Error")

plt.xlabel("Number of Subintervals (N)")
plt.ylabel("Absolute Error")
plt.title("Numerical Integration: Error Convergence")

plt.grid(True, which="both")
plt.legend()
plt.tight_layout()

plt.savefig("results/integration_error.png", dpi=150)
plt.show()

print("Integration graphs saved in results/.")