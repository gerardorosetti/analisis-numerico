#include <iostream>
#include <cmath>
#include <iomanip>

// Función a integrar (aquí debes definir la función que desees integrar)
double function(double x)
{
    return pow((1 + std::pow(x/2, 2)), 2) * M_PI;
}

double trapz(double a, double b, int n) {
    double h = (b - a) / n;
    double s = 0;
    double x;
    double w;
    for (int i = 0; i <= n; ++i) {
        x = a + i * h;
        w = (i == 0 || i == n) ? 1 : 2;
        s += w * function(x);
    }
    s = s * h / 2;
    return s;
}

double simpson(double A, double B, int N) {
    double S = 0;
    double SS = 0;
    int LS;

    double H = (B - A) / N;

    // S = 0;
    // SS = 0;
    if (N / 2 * 2 == N) {
        LS = 0;
    } else {
        LS = 3;
        for (int I = 0; I <= 3; I++) {
            double X = A + H * I;
            double W = 3;
            if (I == 0 || I == 3) {
                W = 1;
            }
            SS = SS + W * function(X);
        }
        SS = SS * H * 3 / 8;
        if (N == 3) {
            return SS;
        }
    }

    for (int I = 0; I <= N - LS; I++) {
        double X = A + H * (I + LS);
        double W = 2;
        if (int(I / 2) * 2 + 1 == I) {
            W = 4;
        }
        if (I == 0 || I == N - LS) {
            W = 1;
        }
        S = S + W * function(X);
    }
    SS = SS + S * H / 3;
    return SS;

}

int main() {
    double a, b;
    int n;

    // Solicitar al usuario los límites de integración y el número de intervalos
    std::cout << "Ingrese el límite inferior de integración a: ";
    std::cin >> a;
    std::cout << "Ingrese el límite superior de integración b: ";
    std::cin >> b;
    std::cout << "Ingrese el número de intervalos n: ";
    std::cin >> n;

    // Calcular la integral utilizando el método de Simpson
    double resultado = simpson(a, b, n);
    std::cout << std::fixed << std::setprecision(5);
    std::cout << "El resultado de la integración numérica es: " << resultado << std::endl;

    resultado = trapz(a, b, n * 2);
    std::cout << "El resultado de la integración numérica es: " << resultado << std::endl;


    return 0;
}