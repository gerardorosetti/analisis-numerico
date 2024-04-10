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

// Implementación del método de Euler hacia atrás de segundo orden para un sistema de ecuaciones diferenciales
void backwardEuler(double t0, double y0, double z0, double h, double tn) {
    double t = t0, y = y0, z = z0, y_new, z_new;
    while (t < tn) {
        y_new = y + h * f(t + h, y + h * f(t, y, z), z + h * g(t, y, z));
        z_new = z + h * g(t + h, y + h * f(t, y, z), z + h * g(t, y, z));
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

    backwardEuler(t0, y0, z0, h, tn);

    return 0;
}