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
    for (int i = 0; i <= n; ++i) {
        x = a + i * h;
        w = (i == 0 || i == n) ? 1 : 2;
        s += w * func(x);
    }
    s = s * h / 2;
}

void simps(double& SS, int N, double a, double b) {
    double A = a, B = b, H = (b - a) / N;
    // double S = 0, Ss = 0;
    double S = 0;
    SS = 0;
    int LS;
    
    if (N/2*2 == N) {
        LS = 0;
    } else {
        LS = 3;
        for (int i = 0; i < 3; i++) { // Regla de 3/8 de Simpson si N es impar
            double X = A + H * i;
            double W = 3;
            if (i == 0 || i == 3) {
                W = 1;
            }
            // Ss = Ss + W * func(X);
            SS = SS + W * func(X);
        }
        // Ss = Ss * H * 3/8;
        SS = SS * H * 3/8;
        if (N == 3) {
            return;
        }
    }
    
    for (int i = 0; i < N - LS; i++) { // Regla de 1/3 de Simpson
        double X = A + H * (i + LS);
        double W = 2;
        if (int(i / 2)*2 + 1 == i) {
            W = 4;
        }
        if (i == 0 || i == N - LS) {
            W = 1;
        }
        S = S + W * func(X);
    }
    
    // SS = Ss + S * H / 3;
    SS = SS + S * H / 3;
}

// void simps(double& ss, int n, double a, double b) {
//     double h = (b - a) / n;
//     ss = 0;
//     if (n % 2 == 0) {
//         for (int i = 0; i <= n; i += 3) {
//             double w = (i == 0 || i == n) ? 1 : 3;
//             ss += w * func(a + i * h);
//         }
//         ss = ss * h * 3 / 8;
//     } else {
//         int ls = 3;
//         for (int i = 0; i <= n - ls; i++) {
//             double x = a + h * (i + ls);
//             double w = (i % 2 == 0) ? 4 : 2;
//             w = (i == 0 || i == n-ls) ? 1 : w;
//             ss += w * func(x);
//         }
//         ss = ss * h / 3;
//     }
// }

// void simps(double& ss, int n, double a, double b) {
//     double h = (b - a) / n;
//     ss = func(a) + func(b);
//     double x;
//     for (int i = 1; i < n; i++) {
//         x = a + i * h;
//         if (i % 2 == 0) {
//             ss += 2 * func(x);
//         } else {
//             ss += 4 * func(x);
//         }
//     }
//     ss = ss * h / 3;
// }

// void simps(double& ss, int n, double a, double b) {
//     double h = (b - a) / n;
//     ss = func(a) + func(b);
//     double x;
//     for (int i = 1; i < n; i++) {
//         x = a + i * h;
//         if (i % 2 == 0) {
//             ss += 2 * func(x);
//         } else {
//             ss += 4 * func(x);
//         }
//     }
//     ss = ss * h / 3;
// }

// void simps(double& ss, int n, double a, double b) {
//     double h = (b - a) / n;
//     ss = 0;
//     if (n % 2 == 0) {
//         for (int i = 0; i <= n; i += 3) {
//             double w = (i == 0 || i == n) ? 1 : 3;
//             ss += w * function(a + i * h);
//         }
//         ss = ss * h * 3 / 8;
//     } else {
//         int ls = 3;
//         for (int i = 0; i <= n - ls; i++) {
//             double x = a + h * (i + ls);
//             double w = (i % 2 == 0) ? 4 : 2;
//             w = (i == 0 || i == n-ls) ? 1 : w;
//             ss += w * function(x);
//         }
//         ss = ss * h / 3;
//     }
// }

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
