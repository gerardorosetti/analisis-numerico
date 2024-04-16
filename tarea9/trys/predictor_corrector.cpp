#include <iostream>
#include <cmath>

// Definición de la ecuación diferencial y' = f(t, y)
double f(double t, double y, double z, double m, double ka, double kr)
{
    return (4 * exp(-3 * t) - ka * z - kr * y) / m;
}

// Método Predictor-Corrector
void predictorCorrector(double t, double y, double z, double h, int n, double m, double ka, double kr)
{
    double y_next_pred, z_next_pred, y_next, z_next;

    for (int i = 0; i * h < n; i++)
    {
        y_next_pred = y + h * z;
        z_next_pred = z + h * f(t, y, z, m, ka, kr);

        z_next = z + h * f(t + h, y_next_pred, z_next_pred, m, ka, kr);
        y_next = y + h * z;

        y = y_next;
        z = z_next;
        t = t + h;

        // Imprimir los valores de t, y, z
        std::cout << "t = " << t << ", y = " << y << ", z = " << z << std::endl;
    }
}

int main()
{
    double h = 0.001;  // Tamaño del paso
    double t = 0.0;    // Tiempo inicial
    double y0 = 2.0;  // Posición inicial
    double z0 = 1.0;  // Velocidad inicial

    double m = 1.0;    // Masa
    double ka = 3.0;  // Constante de amortiguación
    double kr = 2.0; // Constante del resorte

    int n = 5;  // Número de pasos

    // Aplicar el Método Predictor-Corrector
    predictorCorrector(t, y0, z0, h, n, m, ka, kr);

    return 0;
}