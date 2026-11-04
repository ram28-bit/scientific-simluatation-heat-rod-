#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

int main() {
    // Physical parameters
    const double room_temperature = 25.0;
    const double k = 0.1;

    // Simulation parameters
    const double T_initial = 100.0;
    const double dt = 0.5;
    const double final_time = 20.0;

    const int steps = static_cast<int>(final_time / dt);

    double T = T_initial;
    double t = 0.0;

    // Open CSV output file
    std::ofstream file("results/cooling.csv");

    if (!file.is_open()) {
        std::cerr << "Error: Could not open results/cooling.csv\n";
        return 1;
    }

    file << "time,numerical,exact,error\n";

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Time\tNumerical\tExact\t\tError\n";

    for (int i = 0; i <= steps; ++i) {
        // Exact analytical solution
        const double exact =
            room_temperature
            + (T_initial - room_temperature) * std::exp(-k * t);

        const double error = std::abs(T - exact);

        std::cout << t << "\t"
                  << T << "\t"
                  << exact << "\t"
                  << error << '\n';

        file << t << ","
             << T << ","
             << exact << ","
             << error << '\n';

        // Euler update
        if (i < steps) {
            const double dTdt = -k * (T - room_temperature);

            T = T + dt * dTdt;
            t += dt;
        }
    }

    file.close();

    std::cout << "\nResults saved to results/cooling.csv\n";

    return 0;
}