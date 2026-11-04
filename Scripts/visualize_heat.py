import pandas as pd
import matplotlib.pyplot as plt

# Load simulation results
df = pd.read_csv("results/heat_equation.csv")

# Plot the temperature distribution at selected times
plt.figure(figsize=(10, 6))

selected_times = [0.0, 0.025, 0.05, 0.075, 0.1]

for target_time in selected_times:
    actual_time = df["time"].iloc[
        (df["time"] - target_time).abs().argmin()
    ]

    snapshot = df[df["time"] == actual_time]

    plt.plot(
        snapshot["x"],
        snapshot["temperature"],
        label=f"t = {actual_time:.3f}"
    )

plt.xlabel("Position along rod (x)")
plt.ylabel("Temperature (u)")
plt.title("1D Heat Equation: Temperature Evolution")
plt.legend()
plt.grid(True)
plt.tight_layout()

plt.savefig("results/heat_equation.png", dpi=300)
plt.show()

# Validate against the analytical solution
alpha = 0.01
L = 1.0
final_time = df["time"].max()

final_data = df[df["time"] == final_time].copy()

final_data["exact"] = (
    final_data["x"].apply(
        lambda x: __import__("math").sin(__import__("math").pi * x / L)
    )
    * __import__("math").exp(
        -alpha * ( __import__("math").pi / L) ** 2 * final_time
    )
)

error = (
    final_data["temperature"] - final_data["exact"]
).abs()

print(f"Final simulation time: {final_time:.4f}")
print(f"Maximum absolute error: {error.max():.8e}")