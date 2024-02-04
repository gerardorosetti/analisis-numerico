#include <iostream>
#include <cmath>

double function(double x) {
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
        s += w * function(x);
    }
    s = s * h / 2;
}

void simps(double& ss, int n, double a, double b) {
    double h = (b - a) / n;
    ss = 0;
    if (n % 2 == 0) {
        for (int i = 0; i <= n; i += 3) {
            double w = (i == 0 || i == n) ? 1 : 3;
            ss += w * function(a + i * h);
        }
        ss = ss * h * 3 / 8;
    } else {
        int ls = 3;
        for (int i = 0; i <= n - ls; i++) {
            double x = a + h * (i + ls);
            double w = (i % 2 == 0) ? 4 : 2;
            w = (i == 0 || i == n-ls) ? 1 : w;
            ss += w * function(x);
        }
        ss = ss * h / 3;
    }
}

int main() {
    int isimp, n;
    double a, b, s;

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
            trapz(s, n, a, b);
        } else {
            simps(s, n, a, b);
        }
        std::cout << "Resultado final: " << s << std::endl;
    } else {
        std::cout << "La entrada no es válida, por favor repita." << std::endl;
    }

    return 0;
}
