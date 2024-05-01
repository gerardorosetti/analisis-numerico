#include <iostream>
#include <cmath>
using namespace std;

// Definir la función que representa el sistema de ecuaciones diferenciales
double f(double t, double y, double z) {
    return z;
}

double g(double t, double y, double z) {
    return -9.81/1.0*std::sin(y);
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

// Implementación del método de Euler modificado (también conocido como método de Heun) para un sistema de ecuaciones diferenciales
void modifiedEuler(double t0, double y0, double z0, double h, double tn) {
    double t = t0, y = y0, z = z0, y_new, z_new;
    while (t < tn) {
        double f1 = f(t, y, z);
        double g1 = g(t, y, z);
        double f2 = f(t + h, y + h*f1, z + h*g1);
        double g2 = g(t + h, y + h*f1, z + h*g1);

        y_new = y + h * (f1 + f2) / 2.0;
        z_new = z + h * (g1 + g2) / 2.0;

        t = t + h;
        y = y_new;
        z = z_new;

        cout << "t = " << t << ", y = " << y << ", z = " << z << endl;
    }
}

int main() {
    double t0 = 0.0; // Valor inicial de t
    double z0 = 1.0; // Valor inicial de y
    double y0 = 10.0 * M_PI/180; // Valor inicial de z
    double h = 0.00001; // Tamaño del paso
    double tn = 1.1; // Valor final de t

    //backwardEuler(t0, y0, z0, h, tn);
    modifiedEuler(t0, y0, z0, h, tn);

    return 0;
}