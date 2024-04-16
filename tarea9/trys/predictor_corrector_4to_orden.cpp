#include <iostream>
#include <cmath>

// Parámetros del sistema
double m = 1.0;
double ka = 3.0/* tu valor */;
double kr = 2.0/* tu valor */;

// Definición de la función f(t)
double f(double t) {
    return 4 * exp(-3 * t);
}

// Método de Predictor-Corrector de cuarto orden
void predictorCorrector(double t, double& y, double& z, double h) {
    double z0, z1, z2, z3, y0, y1, y2, y3;

    // Predictor (Método de Euler)
    z0 = z + h * ((-ka * z - kr * y + f(t)) / m);
    y0 = y + h * z;

    // Estimación de k1 y m1
    double k1 = (-ka * z - kr * y + f(t)) / m;
    double m1 = z;

    // Corrector
    z1 = z + (h / 2) * (k1 + (-ka * z0 - kr * y0 + f(t + h)) / m);
    y1 = y + (h / 2) * (m1 + z0);

    // Estimación de k2 y m2
    double k2 = (-ka * z1 - kr * y1 + f(t + h)) / m;
    double m2 = z1;

    // Corrección
    z2 = z + (h / 2) * (k2 + (-ka * z1 - kr * y1 + f(t + h)) / m);
    y2 = y + (h / 2) * (m2 + z1);

    // Estimación de k3 y m3
    double k3 = (-ka * z2 - kr * y2 + f(t + h)) / m;
    double m3 = z2;

    // Nuevo predictor
    z3 = z + h * (k3 + (-ka * z2 - kr * y2 + f(t + h)) / m);
    y3 = y + h * (m3 + z2);

    // Calculando la corrección final
    z = z + (h / 6) * (k1 + 2 * k2 + 2 * k3 + (-ka * z3 - kr * y3 + f(t + h)) / m);
    y = y + (h / 6) * (m1 + 2 * m2 + 2 * m3 + z3);
}

int main() {
    double t = 0.0;   // Tiempo inicial
    double y = 2.0;   // Condición inicial de y
    double z = 1.0;   // Condición inicial de z (y')

    double h = 0.001;   // Tamaño del paso
    double tn = 4.99;

    // Iteración del Método de Predictor-Corrector
    while (t < tn) {  // <-- Modificar el tiempo final según sea necesario
        predictorCorrector(t, y, z, h);
        t += h;

        // Imprimir o almacenar los resultados, según sea necesario
        std::cout << "t = " << t << ", y = " << y << ", z = " << z << std::endl;
    }

    return 0;
}