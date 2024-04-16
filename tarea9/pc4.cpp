#include <iostream>
#include <cmath>
#include <chrono>

double func_y(double z) {
    return z;
}

double func_z(double y, double z, double t, double m, double ka, double kr) {
    return (-ka * z - kr * y + 4 * exp(-3 * t)) / m;
}

void calcular_valores_previos(double &y, double &z, double &t, double h, double m, double ka, double kr, int num_pasos) {
    double y_prev[num_pasos];
    double z_prev[num_pasos];

    // Calcular los valores previos
    for (int i = 0; i < num_pasos; i++) {
        double y_temp = y;
        double z_temp = z;
        double t_temp = t;

        // Paso hacia atrás para calcular los valores previos
        y_temp -= (h / 24.0) * (55 * func_y(z) - 59 * func_y(z_prev[0]) + 37 * func_y(z_prev[1]) - 9 * func_y(z_prev[2]));
        z_temp -= (h / 24.0) * (55 * func_z(y, z, t, m, ka, kr) - 59 * func_z(y_prev[0], z_prev[0], t - h, m, ka, kr) + 37 * func_z(y_prev[1], z_prev[1], t - 2 * h, m, ka, kr) - 9 *func_z(y_prev[2], z_prev[2], t - 3 * h, m, ka, kr));
        t_temp -= h;

        // Almacenar los valores previos
        y_prev[i] = y;
        z_prev[i] = z;

        // Restaurar los valores originales
        y = y_temp;
        z = z_temp;
        t = t_temp;
    }
}

void predictor_corrector_adams_4th_order(double &y, double &z, double &t, double h, double m, double ka, double kr, double y_prev, double z_prev, double y_prev2, double z_prev2, double y_prev3, double z_prev3) {
    double y_predictor, z_predictor, y_corrector, z_corrector;

    // Predictor (4th order)
    y_predictor = y + (h / 24.0) * (55 * func_y(z) - 59 * func_y(z_prev) + 37 * func_y(z_prev2) - 9 * func_y(z_prev3));
    z_predictor = z + (h / 24.0) * (55 * func_z(y, z, t, m, ka, kr) - 59 * func_z(y_prev, z_prev, t - h, m, ka, kr) + 37 * func_z(y_prev2, z_prev2, t - 2 * h, m, ka, kr) - 9 * func_z(y_prev3, z_prev3, t - 3 * h, m, ka, kr));

    // Corrector (4th order)
    y_corrector = y + (h / 24.0) * (9 * func_y(z_predictor) + 19 * func_y(z) - 5 * func_y(z_prev) + func_y(z_prev2));
    z_corrector = z + (h / 24.0) * (9 * func_z(y, z, t, m, ka, kr) + 19 * func_z(y, z, t, m, ka, kr) - 5 * func_z(y_prev, z_prev, t - h, m, ka, kr) + func_z(y_prev2, z_prev2, t - 2 * h, m, ka, kr));

    // Update values
    y = y_corrector;
    z = z_corrector;
    t += h;
}

int main() {
    double y = 2.0;  // Valor inicial de y
    double z = 1.0;  // Valor inicial de z
    double t = 0.0;  // Valor inicial de t
    double h = 0.01;  // Paso de tiempo
    const double m = 1.0;
    const double ka = 3.0;
    const double kr = 2.0;
    double tn = 4.99; // Tiempo final

    // Calcular los valores previos necesarios
    double y_prev, z_prev, y_prev2, z_prev2, y_prev3, z_prev3;
    calcular_valores_previos( y, z, t, h, m, ka, kr, 3);

    // Loop para aplicar el método de predictor-corrector de Adams de cuarto orden
    while (t < tn) {

        predictor_corrector_adams_4th_order(y, z, t, h, m, ka, kr, y_prev, z_prev, y_prev2, z_prev2, y_prev3, z_prev3);

        y_prev3 = y_prev2; z_prev3 = z_prev2;
        y_prev2 = y_prev; z_prev2 = z_prev;
        y_prev = y;
        z_prev = z;
        std::cout << "t = " << t << ", y = " << y << ", z = " << z << std::endl;
    }

    return 0;
}