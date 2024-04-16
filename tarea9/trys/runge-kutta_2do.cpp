#include <iostream>
#include <iomanip>
#include <cmath>

const double g = 9.81; // Gravedad en m/s^2

int main()
{
    //double T, K, M, B, Z, Y, H;
    // T = 0.0;
    // K = 100.0;
    // M = 0.5;
    // B = 10.0;
    // Z = 0.0;
    // Y = 1.0;
    // H = 0.001;

    // T = 0.0;
    // K = 10.0;
    // M = 2;
    // B = 2.0;
    // Z = 0.0;
    // Y = 2.0;
    // H = 0.001;

    double T = 0.0;
    double K, M, B, Z, Y, H;
    double f = 4.0 * std::exp(-3 * T); // Función f(t) = 4 * e^(-3t)

    // Constantes y condiciones iniciales dadas en el problema
    M = 10.0;
    K = 6.0;
    B = 2.0;
    Y = 2.0;
    Z = 1.0;
    H = 0.001;

    double KM = K / M;
    double BM = B / M;

    std::cout << "CSL/F9-1 ESQUEMA DE RUNGE-KUTTA DE SEGUNDO ORDEN" << std::endl;
    std::cout << std::setw(4) << 'T' << std::setw(13) << 'Y' << std::setw(16) << 'Z' << std::endl;
    std::cout << std::setprecision(5) << std::fixed << T  << std::setprecision(6) << std::fixed << std::scientific << std::setw(16) << Y << std::setw(16) << Z << std::endl;
    for (int N = 1; N <= 20; ++N)
    {
        for (int KOUNT = 1; KOUNT <= 50; ++KOUNT)
        {
            T = T + H;
            double K1 = H * Z;
            double L1 = -H * (BM * Z + KM * Y);
            double K2 = H * (Z + L1);
            double L2 = -H * (BM * (Z + L1) + KM * (Y + K1));
            Y = Y + (K1 + K2) / 2;
            Z = Z + (L1 + L2) / 2;
            f = 4.0 * exp(-3 * T); // Actualización de f(t) en cada iteración
        }
        std::cout << std::setprecision(5) << std::fixed << T  << std::setprecision(6) << std::fixed << std::scientific << std::setw(16) << Y << std::setw(16) << Z << std::endl;
    }

    return EXIT_SUCCESS;
}