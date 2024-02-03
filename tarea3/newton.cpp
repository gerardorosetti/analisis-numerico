#include <iostream>
#include <cmath>
#include <iomanip>

void function(double x, double &y, double &yd)
{
    y = std::pow(x, 3) - 5.0 * std::pow(x, 2) + 6.0 * x;
    yd = 3.0 * std::pow(x, 2) - 10.0 * x + 6.0;
}

int main() {

    double Ep, x, y, yd, XB;
    int n = 0, k;

    std::cout << "Ingrese la Tolerancia: ";
    std::cin >> Ep;
    std::cout << "Ingrese Estimacion Inicial para la Raiz: ";
    std::cin >> x;

    size_t space = 20;

    std::cout << "It"<< std::setw(space) << "X(N - 1)" << std::setw(space) << "Y(N - 1)" << std::setw(space) << "X(N)" << std::endl;
    do
    {
        XB = x;
        function(x, y, yd);
        double x_old = x;
        x = x - y / yd;
        std::cout << ++n << std::setw(space) << x_old << std::setw(space) << y << std::setw(space) << x << std::endl;
    } while (std::abs(x - XB) >= Ep);

    std::cout << std::endl;
    std::cout << "Solucion Final: " << x << std::endl << "Para Repetir, Oprima 1: ";
    std::cin >> k;

    if (k == 1)
    {
        std::cout << std::endl;
        main();
    }

    return 0;
}