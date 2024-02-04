#include <iostream>
#include <cmath>

double func(double x) {
    return (1 + std::pow(x/2, 2))*(1 + std::pow(x/2, 2))*3.14159;
}

void trapz(double& s, int n, double a, double b) {
    double h = (b - a) / n;
    s = 0;
    double x;
    double w;
    for (int i = 0; i <= n; i++) {
        x = a + i * h;
        w = (i == 0 || i == n) ? 1 : 2;
        s += w * func(x);
    }
    s = s * h / 2;
}

void simps(double& ss, int n, double a, double b) {
    double h = (b - a) / n;
    ss = func(a) + func(b);
    double x;
    for (int i = 1; i < n; i++) {
        x = a + i * h;
        if (i % 2 == 0) {
            ss += 2 * func(x);
        } else {
            ss += 4 * func(x);
        }
    }
    ss = ss * h / 3;
}

int main() {
    int isimp, n;
    double a, b, result;

    std::cout << "Ingrese 0 para la regla del trapecio o 1 para la regla de Simpson: ";
    std::cin >> isimp;
    std::cout << "Número de intervalos: ";
    std::cin >> n;
    std::cout << "Límite inferior de integración: ";
    std::cin >> a;
    std::cout << "Límite superior de integración: ";
    std::cin >> b;

    if ((n > 0 && isimp == 0) || (isimp == 1 && n > 1)) {
        if (isimp == 0) {
            trapz(result, n, a, b);
        } else {
            simps(result, n, a, b);
        }
        std::cout << "Resultado: " << result << std::endl;
    } else {
        std::cout << "La entrada no es válida, por favor repita." << std::endl;
    }

    return 0;
}
