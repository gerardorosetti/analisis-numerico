#include <iostream>
#include <cmath>

// Definición de la función de la EDO:
double f(double T, double b) {
    return b * (T - 15);
}

int main() {
    // Condiciones iniciales
    double T0 = 70.0;
    double T5 = 45.0;
    double b = 0; // Valor inicial de b
    double db = 0.00000001; // Incremento para ajustar b
    double tolerance = 0.0000001; // Tolerancia para la condición de frontera
    double t = 0;

    while (std::abs(T0 - T5) > tolerance) {
        T0 = 70; // Reiniciar la temperatura inicial en cada iteración
        t = 0;
        std::cout << "El valor de b encontrado es: " << b << std::endl;

        // Método de Euler para calcular T en t = 5
        while (t < 5) {
            T0 += 0.01 * f(T0, b);
            t += 0.01;
        }

        // Ajuste de b basado en el resultado en t = 5
        if (T0 > T5) {
            b -= db;
        } else {
            b += db;
        }
    }

    // Impresión del valor de 'b' encontrado
    std::cout << "El valor de b encontrado es: " << b << std::endl;

    return 0;
}