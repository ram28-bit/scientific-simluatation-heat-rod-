#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <omp.h>

int main() {
    // Physical parameters
    const double L = 1.0;
    const double alpha = 0.01;

    // Numerical parameters
    const int N = 101;
    const double dx = L / (N - 1);
    const double dt = 0.0001;
    const double final_time = 0.1;
    const int steps = static_cast<int>(final_time / dt);

    // Stability parameter
    const double r = alpha * dt / (dx * dx);

    if (r > 0.5) {
        std::cerr << "Error: unstable time step. Reduce dt.\n";
        return 1;
    }

    std::vector<double> x(N);
    std::vector<double> u(N, 0.0);
    std::vector<double> next_u(N, 0.0);

    // Initial temperature distribution
    for (int i = 0; i < N; ++i) {
        x[i] = i * dx;
        u[i] = std::sin(M_PI * x[i] / L);
    }

    // Fixed boundary temperatures
    u.front() = 0.0;
    u.back() = 0.0;

    std::ofstream file("results/heat_equation_openmp.csv");

    if (!file.is_open()) {
        std::cerr << "Error: Could not open results/heat_equation_openmp.csv\n";
        return 1;
    }

    file << "time,x,temperature\n";

    // Save the initial condition
    for (int i = 0; i < N; ++i) {
        file << 0.0 << "," << x[i] << "," << u[i] << "\n";
    }

    // Time integration
    for (int n = 1; n <= steps; ++n) {

        // Parallelize the spatial calculations using OpenMP
        #pragma omp parallel for
        for (int i = 1; i < N - 1; ++i) {
            next_u[i] = u[i] + r *
                (u[i + 1] - 2.0 * u[i] + u[i - 1]);
        }

        // Maintain boundary conditions
        next_u.front() = 0.0;
        next_u.back() = 0.0;

        u.swap(next_u);

        const double time = n * dt;

        // Save every time step
        for (int i = 0; i < N; ++i) {
            file << time << "," << x[i] << "," << u[i] << "\n";
        }
    }

    file.close();

    std::cout << "Heat equation simulation completed!\n";
    std::cout << "Grid points: " << N << "\n";
    std::cout << "Time steps: " << steps << "\n";
    std::cout << "Stability parameter r: " << r << "\n";
    std::cout << "Results saved to results/heat_equation_openmp.csv\n";
    std::cout << "OpenMP maximum threads: " << omp_get_max_threads() << "\n";

    return 0;
}