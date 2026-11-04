#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>

const double PI = 3.14159265358979323846;

// Function to integrate
double f(double x) {
    return std::sin(x);
}

// Composite trapezoidal rule
double trapezoidal_rule(
    const std::vector<double>& y,
    double h
) {
    const int N = static_cast<int>(y.size()) - 1;

    double sum = 0.5 * y[0] + 0.5 * y[N];

    for (int i = 1; i < N; ++i) {
        sum += y[i];
    }

    return h * sum;
}

// Composite Simpson's 1/3 rule
double simpsons_rule(
    const std::vector<double>& y,
    double h
) {
    const int N = static_cast<int>(y.size()) - 1;

    if (N % 2 != 0) {
        std::cerr
            << "Error: Simpson's rule requires an even number "
            << "of subintervals.\n";

        return NAN;
    }

    double sum = y[0] + y[N];

    for (int i = 1; i < N; ++i) {
        if (i % 2 == 1) {
            sum += 4.0 * y[i];
        } else {
            sum += 2.0 * y[i];
        }
    }

    return (h / 3.0) * sum;
}

int main() {
    const double a = 0.0;
    const double b = PI;

    // Test different numbers of subintervals
    const std::vector<int> grid_sizes = {
        4, 8, 16, 32, 64, 128, 256, 512, 1024
    };

    const double exact = 2.0;

    std::ofstream file("results/integration.csv");

    if (!file.is_open()) {
        std::cerr
            << "Error: Could not open results/integration.csv\n";
        return 1;
    }

    file << "N,trapezoidal,simpson,exact,"
         << "trapezoidal_error,simpson_error\n";

    std::cout << std::fixed << std::setprecision(10);

    std::cout << "Numerical Integration of sin(x) from 0 to pi\n";
    std::cout << "Exact integral = " << exact << "\n\n";

    std::cout << std::setw(8) << "N"
              << std::setw(18) << "Trapezoidal"
              << std::setw(18) << "Simpson"
              << std::setw(18) << "Trap Error"
              << std::setw(18) << "Simp Error"
              << '\n';

    for (int N : grid_sizes) {
        const double h = (b - a) / N;

        std::vector<double> y(N + 1);

        // Generate the grid and evaluate the function
        for (int i = 0; i <= N; ++i) {
            const double x = a + i * h;
            y[i] = f(x);
        }

        const double trap =
            trapezoidal_rule(y, h);

        const double simp =
            simpsons_rule(y, h);

        const double trap_error =
            std::abs(trap - exact);

        const double simp_error =
            std::abs(simp - exact);

        std::cout << std::setw(8) << N
                  << std::setw(18) << trap
                  << std::setw(18) << simp
                  << std::setw(18) << trap_error
                  << std::setw(18) << simp_error
                  << '\n';

        file << N << ","
             << trap << ","
             << simp << ","
             << exact << ","
             << trap_error << ","
             << simp_error << '\n';
    }

    file.close();

    std::cout
        << "\nResults saved to results/integration.csv\n";

    return 0;
}