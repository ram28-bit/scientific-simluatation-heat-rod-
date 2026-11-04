#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>

int main() {

    // 1. Generate the numerical grid
    const int N = 11;
    const double L = 1.0;
    const double dx = L / (N - 1);

    std::vector<double> x(N);
    std::vector<double> f(N);
    std::vector<double> numerical_derivative(N);
    std::vector<double> exact_derivative(N);

    // 2. Calculate function values
    for (int i = 0; i < N; ++i) {
        x[i] = i * dx;
        f[i] = std::sin(x[i]);
    }

    // 3. Calculate numerical derivatives
    for (int i = 0; i < N; ++i) {

        if (i == 0) {
            // Forward difference at the left boundary
            numerical_derivative[i] =
                (f[i + 1] - f[i]) / dx;
        }

        else if (i == N - 1) {
            // Backward difference at the right boundary
            numerical_derivative[i] =
                (f[i] - f[i - 1]) / dx;
        }

        else {
            // Central difference at interior points
            numerical_derivative[i] =
                (f[i + 1] - f[i - 1]) / (2.0 * dx);
        }

        // 4. Calculate the exact derivative
        exact_derivative[i] = std::cos(x[i]);
    }

    // 5. Print the results
    std::cout << std::fixed << std::setprecision(6);

    std::cout << "x"
              << "\tNumerical"
              << "\tExact"
              << "\tError\n";

    for (int i = 0; i < N; ++i) {

        double error = std::abs(
            numerical_derivative[i] - exact_derivative[i]
        );

        std::cout << x[i] << "\t"
                  << numerical_derivative[i] << "\t"
                  << exact_derivative[i] << "\t"
                  << error << "\n";
    }

    // 6. Save the results to a CSV file
    std::ofstream file("results/derivative.csv");

    if (!file.is_open()) {
        std::cerr << "Error: Could not open results/derivative.csv\n";
        return 1;
    }

    file << "x,numerical,exact,error\n";

    for (int i = 0; i < N; ++i) {

        double error = std::abs(
            numerical_derivative[i] - exact_derivative[i]
        );

        file << x[i] << ","
             << numerical_derivative[i] << ","
             << exact_derivative[i] << ","
             << error << "\n";
    }

    file.close();

    std::cout << "\nResults saved to results/derivative.csv\n";

    return 0;
}