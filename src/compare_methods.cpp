#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

double cooling_rate(double t, double T) {
    const double k = 0.1;
    const double room_temperature = 25.0;

    return -k * (T - room_temperature);
}

int main() {
    const double T_initial = 100.0;
    const double room_temperature = 25.0;

    const double dt = 0.5;
    const double final_time = 20.0;

    const int steps = static_cast<int>(final_time / dt);

    double euler = T_initial;
    double rk2 = T_initial;
    double rk4 = T_initial;

    double t = 0.0;

    std::ofstream file("results/method_comparison.csv");

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open results/method_comparison.csv\n";
        return 1;
    }

    file << "time,euler,rk2,rk4,exact\n";

    std::cout << std::fixed << std::setprecision(6);

    std::cout << "Time\tEuler\t\tRK2\t\tRK4\t\tExact\n";

    for (int i = 0; i <= steps; ++i) {
        const double exact =
            room_temperature
            + (T_initial - room_temperature) * std::exp(-0.1 * t);

        std::cout << t << "\t"
                  << euler << "\t"
                  << rk2 << "\t"
                  << rk4 << "\t"
                  << exact << "\n";

        file << t << ","
             << euler << ","
             << rk2 << ","
             << rk4 << ","
             << exact << "\n";

        if (i == steps) {
            break;
        }

        // Euler method
        const double euler_slope = cooling_rate(t, euler);
        euler += dt * euler_slope;

        // RK2 midpoint method
        const double k1 = cooling_rate(t, rk2);

        const double k2 = cooling_rate(
            t + dt / 2.0,
            rk2 + dt * k1 / 2.0
        );

        rk2 += dt * k2;

        // RK4 method
        const double r1 = cooling_rate(t, rk4);

        const double r2 = cooling_rate(
            t + dt / 2.0,
            rk4 + dt * r1 / 2.0
        );

        const double r3 = cooling_rate(
            t + dt / 2.0,
            rk4 + dt * r2 / 2.0
        );

        const double r4 = cooling_rate(
            t + dt,
            rk4 + dt * r3
        );

        rk4 += (dt / 6.0) * (
            r1 + 2.0 * r2 + 2.0 * r3 + r4
        );

        t += dt;
    }

    file.close();

    std::cout << "\nResults saved to results/method_comparison.csv\n";

    return 0;
}

