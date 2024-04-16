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

// Implementación del método de predictor-corrector de cuarto orden de Adams
void PredictorCorrectorCuartoOrdenAdams(double t0, double y0, double z0, double h, double tn) {
    double t = t0, y = y0, z = z0, y_new, z_new;
    double tn_1, yn_1, zn_1, fyn_1, fzn_1;

    while (t < tn) {
        // Predictor de cuarto orden (utilizando el método de Runge-Kutta de cuarto orden)
        fyn_1 = f(t, y, z);
        fzn_1 = g(t, y, z);
        yn_1 = y + h / 24 * (55*fyn_1 - 59*f(t - h, yn_1, zn_1) + 37*f(t - 2*h, yn_1, zn_1) - 9*f(t - 3*h, yn_1, zn_1));
        zn_1 = z + h / 24 * (55*fzn_1 - 59*g(t - h, yn_1, zn_1) + 37*g(t - 2*h, yn_1, zn_1) - 9*g(t - 3*h, yn_1, zn_1));
        tn_1 = t + h;

        // Corrector de cuarto orden
        y_new = y + h / 24 * (9*f(tn_1, yn_1, zn_1) + 19*fyn_1 - 5*f(t - h, yn_1, zn_1) + f(t - 2*h, yn_1, zn_1));
        z_new = z + h / 24 * (9*g(tn_1, yn_1, zn_1) + 19*fzn_1 - 5*g(t - h, yn_1, zn_1) + g(t - 2*h, yn_1, zn_1));

        t = tn_1;
        y = y_new;
        z = z_new;

        cout << "t = " << t << ", y = " << y << ", z = " << z << endl;
    }
}

int main() {
    double t0 = 0.0; // Valor inicial de t
    double y0 = 2.0; // Valor inicial de y
    double z0 = 1.0; // Valor inicial de z
    double h = 0.001; // Tamaño del paso
    double tn = 5; // Valor final de t

    PredictorCorrectorCuartoOrdenAdams(t0, y0, z0, h, tn);

    return 0;
}