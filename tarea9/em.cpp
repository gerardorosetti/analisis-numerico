#include <iostream>
#include <cmath>
#include <chrono>

// Parámetros del sistema
const double m = 1.0;
const double ka = 3.0;
const double kr = 2.0;

// Definición de la función f(t)
double f(double t) {
    return 4 * exp(-3 * t);
}

// Método de Euler Modificado
void eulerModificado(double t, double& y, double& z, double h) {
    double z_next = z + h * ((-ka * z - kr * y + f(t)) / m);
    double y_next = y + h * (z + 0.5 * h * ((-ka * z - kr * y + f(t)) / m));

    y = y_next;
    z = z_next;
}

int main() {

    auto start = std::chrono::high_resolution_clock::now();

    double t = 0.0;   // Tiempo inicial
    double y = 2.0;   // Condición inicial de y
    double z = 1.0;   // Condición inicial de z (y')

    double h = 0.01;   // Tamaño del paso
    double tn = 4.99;  // tiempo final

    // Iteración del Método de Euler Modificado
    while (t < tn) {
        eulerModificado(t, y, z, h);
        t += h;
        std::cout << "t = " << t << ", y = " << y << ", z = " << z << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration_ms = end - start;
    std::cout << "Tiempo de ejecución: " << duration_ms.count() << " ms" << std::endl;

    return 0;
}