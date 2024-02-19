#include <iostream>
#include <cmath>
#include <iomanip>

double function(double x)
{
    // return pow(x, 2) + pow(x, 9) - log(x * 0.2);
    // return sin(x * M_PI / 180); // Degrees
    // return sin(x);
    // return pow((1 + std::pow(x/2, 2)), 2) * M_PI;
    return log(1 + x)/x;
}

int main()
{
    int n;
    double a, b;

    std::cout << "Los Ordenes de Cuadratula Disponibles son: N = 2, 3, 4, 5, 6, 8, 10" << std::endl;
    std::cout << "Ingrese el número de puntos N: ";
    std::cin >> n;

    if (n <= 0)
    {
        std::cout << "Error: N no puede ser 0 o negativo" << std::endl;
        return EXIT_FAILURE;
    }
    else if (n == 7 || n == 9 || n == 1)
    {
        std::cout << "Error: N = 1, 7 y 9 no están disponibles" << std::endl;
        return EXIT_FAILURE;
    }
    else if (n > 10)
    {
        std::cout << "Error: N > 10 no están disponibles" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Ingrese el límite inferior A: ";
    std::cin >> a;
    std::cout << "Ingrese el límite superior B: ";
    std::cin >> b;

    double  w[11], xa[11];

    for (size_t i = 0; i < 11; ++i)
    {
        w[i] = 0;
        xa[i] = 0;
    }

    if (n == 2)
    {
        xa[2] = 0.5773502691;
        w[2] = 1;
    }
    else if (n == 3)
    {
        xa[2] = 0;
        xa[3] = 0.7745966692;
        w[2] = 0.8888888888;
        w[3] = 0.5555555555;
    }
    else if (n == 4)
    {
        xa[3] = 0.3399810435;
        xa[4] = 0.8611363115;
        w[3] = 0.6521451548;
        w[4] = 0.3478548451;
    }
    else if (n == 5)
    {
        xa[3] = 0;
        xa[4] = 0.5384693101;
        xa[5] = 0.9061798459;
        w[3] = 0.5688888888;
        w[4] = 0.4786286704;
        w[5] = 0.2369268850;
    }
    else if (n == 6)
    {
        xa[4] = 0.2386191860;
        xa[5] = 0.6612093864;
        xa[6] = 0.9324695142;
        w[4] = 0.4679139345;
        w[5] = 0.3607615730;
        w[6] = 0.1713244923;
    }
    else if (n == 8)
    {
        xa[5] = 0.1834346424;
        xa[6] = 0.5255324099;
        xa[7] = 0.7966664774;
        xa[8] = 0.9602898564;
        w[5] = 0.3626837833;
        w[6] = 0.3137066458;
        w[7] = 0.2223810344;
        w[8] = 0.1012285362;
    }
    else if (n == 10)
    {
        xa[6] = 0.1488743389;
        xa[7] = 0.4333953941;
        xa[8] = 0.6794095682;
        xa[9] = 0.8650633666;
        xa[10] = 0.9739065285;
        w[6] = 0.2955242247;
        w[7] = 0.2692667193;
        w[8] = 0.2190863625;
        w[9] = 0.1494513491;
        w[10] = 0.0666713443;
    }

    for (size_t i = 1; i <= n / 2; ++i)
    {
        w[i] = w[n + 1 - i];
        xa[i] = -xa[n + 1 - i];
    }

    for (size_t i = 1; i <= n; ++i)
    {
        xa[i] = (xa[i] * (b - a) + a + b) / 2;
    }

    size_t space = 14;
    std::cout << "Cuadricula:" << std::endl;
    std::cout << "- - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
    std::cout << "N" << std::setw(space) << "X" << std::setw(space) << "F(X)" << std::setw(space) << "W" << std::endl;
    std::cout << "- - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
    std::cout << std::fixed << std::setprecision(8);

    double xi = 0;

    for (size_t i = 1; i <= n; ++i)
    {
        double x = xa[i];
        double f = function(x);
        xi += f * w[i];
        if (i < 10)
        {
            std::cout << 0;
        }
        std::cout << i << std::setw(space) << x << std::setw(space) << f << std::setw(space) << w[i] << std::endl;
    }

    xi *= (b - a) / 2;

    std::cout << "- - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
    std::cout << "El resultado final: " << xi << std::endl;
    std::cout << "- - - - - - - - - - - - - - - - - - - - - - -" << std::endl;

    return EXIT_SUCCESS;
}