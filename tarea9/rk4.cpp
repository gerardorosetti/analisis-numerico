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

// Función para evaluar las derivadas
void evaluateDerivatives(double t, double y, double z, double& dy_dt, double& dz_dt) {
    dy_dt = z;
    dz_dt = (-ka * z - kr * y + f(t)) / m;
}

// Método de Runge-Kutta de cuarto orden (RK4)
void rungeKutta(double t, double& y, double& z, double h) {
    double dy1, dy2, dy3, dy4;
    double dz1, dz2, dz3, dz4;

    evaluateDerivatives(t, y, z, dy1, dz1);
    evaluateDerivatives(t + h / 2, y + h / 2 * dy1, z + h / 2 * dz1, dy2, dz2);
    evaluateDerivatives(t + h / 2, y + h / 2 * dy2, z + h / 2 * dz2, dy3, dz3);
    evaluateDerivatives(t + h, y + h * dy3, z + h * dz3, dy4, dz4);

    y += h * (dy1 + 2 * dy2 + 2 * dy3 + dy4) / 6;
    z += h * (dz1 + 2 * dz2 + 2 * dz3 + dz4) / 6;
}

int main() {
    double t = 0.0;   // Tiempo inicial
    double y = 2.0;   // Condición inicial de y
    double z = 1.0;   // Condición inicial de z (y')

    double h = 0.01;   // Tamaño del paso
    double tn = 4.99;

    // Iteración del Método de Runge-Kutta de cuarto orden
    while (t < tn) {  // <-- Modificar el tiempo final según sea necesario
        rungeKutta(t, y, z, h);
        t += h;

        // Imprimir o almacenar los resultados, según sea necesario
        std::cout << "t = " << t << ", y = " << y << ", z = " << z << std::endl;
    }

    return 0;
}