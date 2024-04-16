#include <iostream>
#include <cmath>

double func_y(double z) {
    return z;
}

double func_z(double y, double z, double t, double m, double ka, double kr) {
    return (-ka * z - kr * y + 4 * exp(-3 * t)) / m;
}

void predictor_corrector_4th_order(double &y, double &z, double &t, double h, double m, double ka, double kr) {
    double y_pred, z_pred;

    // Predictor step
    double y_predictor = y + h * func_y(z);
    double z_predictor = z + h * func_z(y, z, t, m, ka, kr);

    // Corrector step
    y_pred = y + h / 2 * (func_y(z) + func_y(z_predictor));
    z_pred = z + h / 2 * (func_z(y, z, t, m, ka, kr) + func_z(y_predictor, z_predictor, t + h, m, ka, kr));

    y = y_pred;
    z = z_pred;
    t += h;
}

int main() {
    double y = 2.0;  // Initial value for y
    double z = 1.0;  // Initial value for z
    double t = 0.0;  // Initial value for t
    double m = 1.0;  // Replace with actual value of m
    double ka = 3.0; // Replace with actual value of ka
    double kr = 2.0; // Replace with actual value of kr
    double h = 0.01;  // Step size

    double tn = 4.99;

    // Perform iterations
    for (t = 0; t < tn;) {
        predictor_corrector_4th_order(y, z, t, h, m, ka, kr);
        // Output or use the updated y, z, and t as needed
        std::cout << "t = " << t << ", y = " << y << ", z = " << z << std::endl;
    }

    return 0;
}