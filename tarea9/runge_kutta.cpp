#include <iostream>
#include <cmath>
using namespace std;

// Definir la función que representa el sistema de ecuaciones diferenciales
double f(double t, double y, double z) {
    return z;
}

double g(double t, double y, double z) {
    return -3*z - 2*y + 4*exp(-3*t);
}

// Implementación del método de Runge-Kutta de segundo orden para un sistema de ecuaciones diferenciales
void rungeKutta(double t0, double y0, double z0, double h, double tn) {
    double t = t0, y = y0, z = z0, y_new, z_new;
    while (t < tn) {
        double k1_y = h * f(t, y, z);
        double k1_z = h * g(t, y, z);
        double k2_y = h * f(t + h, y + k1_y, z + k1_z);
        double k2_z = h * g(t + h, y + k1_y, z + k1_z);
        y_new = y + 0.5 * (k1_y + k2_y);
        z_new = z + 0.5 * (k1_z + k2_z);
        t = t + h;
        y = y_new;
        z = z_new;
        cout << "t = " << t << ", y = " << y << ", z = " << z << endl;
    }
}

int main() {
    double t0 = 0.0; // Valor inicial de t
    double y0 = 2.0; // Valor inicial de y
    double z0 = 1.0; // Valor inicial de z
    double h = 0.1; // Tamaño del paso
    double tn = 1.0; // Valor final de t

    rungeKutta(t0, y0, z0, h, tn);

    return 0;
}