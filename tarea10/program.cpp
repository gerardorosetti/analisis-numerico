#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

const double T0 = 70.0; //Temperatura al Tiempo 0 (0 minutos) (Valor de frontera inicial)
const double T5 = 45.0; //Temperatura al Tiempo 5 (5 minutos) (Valor de frontera final)
const double T_room = 15.0; //Temperatura de la habitacion
const double T_oven = 70.0; //Temperatura del horno
const double h = 0.000001; // Paso de tiempo
const double L = 5.0; // Longitud del dominio del tiempo
const double L2 = 10.0; // Longitud del dominio del tiempo

// Definición de la función de la EDO cuando esta fuera del horno:
double f1(double T, double b) {
    return b * (T - T_room);
}

// Definición de la función de la EDO cuando se vuelve a meter en el horno:
double f2(double T, double b) {
    return b * (T - T_oven);
}

double getBeta()
{
    double b = 0; // Valor inicial de b
    double t = 0; // tiempo 0
    double T0_temp = T0; // variable temporal
    const double db = 0.00001; // Incremento para ajustar b
    const double tolerance = 0.001; // Tolerancia para la condición de frontera
    while (std::abs(T0_temp - T5) > tolerance) {
        T0_temp = T0; // Reiniciar la temperatura inicial en cada iteración
        t = 0;
        while (t < 5) {
            T0_temp += 0.001 * f1(T0_temp, b);
            t += 0.001;
        }
        if (T0_temp > T5) {
            b -= db;
        } else {
            b += db;
        }
    }

    std::cout << "El valor de b encontrado es: " << b << std::endl;

    return b;
}

void solveHeatEquation()
{
    //double b = ((1.0 / 5.0) * log(6.0 / 11.0));
    double b = getBeta();
    int N = L / h;
    std::vector<double> T(N + 1);

    T[0] = T0;
    //T[N] = T5;

    for (int i = 1; i <= N; i++)
    {
        T[i] = T[i - 1] + h * f1(T[i - 1], b);
    }

    std::cout << "La temperatura del pastel a las 9:05 am es: " << T[N] << " °C" << std::endl << std::setprecision(8);

    T[0] = T[N];
    N = L / h;

    for (int i = 1; i <= N; i++)
    {
        T[i] = T[i - 1] + h * f1(T[i - 1], b);
    }

    std::cout << "La temperatura del pastel a las 9:10 am es: " << T[N] << " °C" << std::endl;

    int N2 = L2 / h;
    std::vector<double> T2(N2 + 1);
    T2[0] = T[N];

    for (int i = 1; i <= N2; i++)
    {
        T2[i] = T2[i - 1] + h * f2(T2[i - 1], b);
    }

    std::cout << "La temperatura del pastel a las 9:20 am es: " << T2[N2] << " °C" << std::endl;
}

int main()
{
    solveHeatEquation();
    return 0;
}