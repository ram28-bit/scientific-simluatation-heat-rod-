import pandas as pd
import numpy as np
serial = pd.read_csv("results/heat_equation.csv")
parallel = pd.read_csv("results/heat_equation_openmp.csv")
serial_temp = serial["temperature"].to_numpy()
parallel_temp = parallel["temperature"].to_numpy()

if len(serial_temp) != len(parallel_temp):
    raise ValueError("The files have different numbers of rows.")

max_difference = np.max(np.abs(serial_temp - parallel_temp))

print("Serial vs OpenMP Comparison")
print("----------------------------")
print(f"Serial data points: {len(serial_temp)}")
print(f"Parallel data points: {len(parallel_temp)}")
print(f"Maximum temperature difference: {max_difference:.12e}")

if np.allclose(serial_temp, parallel_temp, rtol=1e-12, atol=1e-12):
    print("PASS: Serial and parallel results agree.")
else:
    print("CHECK: Results differ.")