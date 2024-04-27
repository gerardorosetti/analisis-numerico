#include <iostream>
#include <cmath>

// Definir la función Beta
double beta = (1.0/5.0) * log(6.0/11.0);

// Definir la EDO como una función
double dT_dt(double t, double T) {
    return beta * (T - 15.0);
}

// Implementación del método de Euler para resolver la EDO
double euler(double t, double T, double h) {
    return T + h * dT_dt(t, T);
}

int main() {
    // Definir las condiciones iniciales
    double T0 = 70.0;
    double T_end = 45.0;
    double t = 0.0;
    double t_end = 5.0;
    double h = 0.01; // Tamaño del paso

    // Adivinar el valor inicial de T_end
    double T_guess = 60.0; // Puedes ajustar este valor inicial

    // Iterar hasta alcanzar la precisión deseada
    double epsilon = 0.001; // Puedes ajustar la precisión
    while (std::abs(T_guess - T_end) > epsilon) {
        // Resolver la EDO con el valor inicial adivinado
        double T = T0;
        for (double ti = t; ti < t_end; ti += h) {
            T = euler(ti, T, h);
        }
        std::cout << "T" << T_guess << std::endl;
        // Ajustar el valor inicial adivinado para acercarse a T_end
        T_guess = T_guess - 0.1 * (T - T_end);
    }

    // Imprimir la solución final
    std::cout << "El valor inicial de T para T(5) = 45 es: " << T_guess << std::endl;

    return 0;
}
