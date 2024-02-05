#include <iostream>
#include <cmath>
#include <iomanip>

double function(double x)
{
    return pow((1 + std::pow(x/2, 2)), 2) * M_PI;
}

double trapz(double a, double b, int n)
{
    double h = (b - a) / n;
    double s = 0;
    double x;
    double w;

    for (int i = 0; i <= n; ++i)
    {
        x = a + i * h;
        w = (i == 0 || i == n) ? 1 : 2;
        s += w * function(x);
    }

    return s * h / 2;
}

double simpson(double a, double b, int n)
{
    double s = 0.0;
    double ss = 0.0;
    int ls = (n / 2 * 2 == n) ? 0 : 3;
    double h = (b - a) / n;

    for (size_t i = 0; i <= 3; ++i)
    {
        double x = a + h * i;
        double w = (i == 0 || i == 3) ? 1 : 3;
        ss = ss + w * function(x);
    }

    ss = ss * h * 3 / 8;

    if (n == 3)
    {
        return ss;
    }

    for (size_t i = 0; i <= n - ls; ++i)
    {
        double x = a + h * (i + ls);
        double w = 2;

        if (int(i / 2) * 2 + 1 == i)
        {
            w = 4;
        }

        if (i == 0 || i == n - ls)
        {
            w = 1;
        }
        s = s + w * function(x);
    }

    return ss + s * h / 3;
}

int main()
{
    double a, b;
    size_t n, option;

    std::cout << "Ingrese 0 para la regla del trapecio o 1 para la regla de Simpson: ";
    std::cin >> option;

    std::string question = (option == 0) ? "intervalos" : "datos";
    std::cout << "Ingrese el número de " << question << " N: ";
    std::cin >> n;

    std::cout << "Ingrese el límite inferior de integración A: ";
    std::cin >> a;

    std::cout << "Ingrese el límite superior de integración B: ";
    std::cin >> b;

    if ((n > 0 && option == 0) || (option == 1 && n > 1))
    {
        double result = (option == 0) ? trapz(a, b, n) : simpson(a, b, n);
        std::cout << std::fixed << std::setprecision(5);
        std::cout << "\nResultado final: " << result << std::endl;
    }
    else
    {
        std::cout << "La entrada no es válida, por favor repita." << std::endl;
    }

    return EXIT_SUCCESS;
}