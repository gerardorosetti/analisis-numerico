#include <iostream>
#include <cmath>
#include <chrono>

double func_y(double z) {
    return z;
}

double func_z(double y, double z, double t, double m, double ka, double kr) {
    return (-ka * z - kr * y + 4 * exp(-3 * t)) / m;
}

void predictor_corrector(double &y, double &z, double &t, double h, double m, double ka, double kr) {
    double y_pred, z_pred;

    // Paso Predictor
    double y_predictor = y + h * func_y(z);
    double z_predictor = z + h * func_z(y, z, t, m, ka, kr);

    // Paso Corrector
    y_pred = y + h / 2 * (func_y(z) + func_y(z_predictor));
    z_pred = z + h / 2 * (func_z(y, z, t, m, ka, kr) + func_z(y_predictor, z_predictor, t + h, m, ka, kr));

    y = y_pred;
    z = z_pred;
    t += h;
}

int main() {

    auto start = std::chrono::high_resolution_clock::now();

    double y = 2.0;  // Valor inicial de y
    double z = 1.0;  // Valor inicial de z
    double t = 0.0;  // Valor inicial de t
    double h = 0.01;  // Paso tam

    const double m = 1.0;
    const double ka = 3.0;
    const double kr = 2.0;

    double tn = 4.99; // tiempo final

    // Perform iterations
    for (t = 0; t < tn;) {
        predictor_corrector(y, z, t, h, m, ka, kr);
        std::cout << "t = " << t << ", y = " << y << ", z = " << z << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration_ms = end - start;
    std::cout << "Tiempo de ejecución: " << duration_ms.count() << " ms" << std::endl;

    return 0;
}