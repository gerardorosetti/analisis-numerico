#include <iostream>
#include <cmath>
#include <iomanip>

// Definición de la función que se va a evaluar
double fun(double x) {
    return x * x * x - 3 * x * x - x + 3;
}

int main() {

    double a, c, ep;
    int il;

    // std::cout << "Ingrese la Cota Inferior A: ";
    // std::cin >> a;
    // std::cout << "Ingrese la Cota Superior C: ";
    // std::cin >> c;
    // std::cout << "Ingrese la Tolerancia EP: ";
    // std::cin >> ep;
    // std::cout << "Ingrese el Limite de Iteraciones IL: ";
    // std::cin >> il;

    a = 0.0;
    c = 3.0;
    ep = 0.0001;
    il = 20;

    double ya = fun(a);
    double yc = fun(c);
    int it = 0;

    size_t space = 14;

    std::cout << "It" << std::setw(space) << "A" << std::setw(space) << "B" << std::setw(space) << "C" << std::setw(space) << "F(A)" << std::setw(space) << "F(B)" << std::setw(space) << "F(C)" << std::setw(space + 8) << "ABS(F(C) - F(A))/2" << std::endl;

    while (true)
    {
        it++;
        double b = (a + c) / 2;
        double yb = fun(b);

        if (it < 10)
        {
            std::cout << "0";
        }
        std::cout << it << std::setw(14) << a << std::setw(14) << b << std::setw(14) << c << std::setw(14) << ya << std::setw(14) << yb << std::setw(14) << yc << std::setw(14) << std::abs(yc - ya) / 2 << std::endl;

        if (it > il)
        {
            std::cout << "Se ha Excedido el Limite de Iteraciones" << std::endl;
            break;
        }
        if (std::abs(b - a) < ep)
        {
            std::cout << "Se ha Satisfecho la Tolerancia" << std::endl;
            break;
        }
        if (ya * yb <= 0)
        {
            c = b;
            yc = yb;
        }
        else
        {
            a = b;
            ya = yb;
        }
    }

    std::cout << "Resultado Final: Raiz Aproximada = " << (a + c) / 2 << std::endl;

    int ks;
    std::cout << "Ingrese 1 para Continuar, 0 para Terminar: ";
    std::cin >> ks;

    if (ks == 1)
    {
        main();
    }

    return 0;
}