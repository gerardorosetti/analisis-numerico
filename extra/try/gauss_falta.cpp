#include <iostream>
#include <cmath>

void fun(double &f, double x) { // Subrutina para evaluar la función a integrar
    f = sin(x);
}

int main() {
    int n;
    double a, b, xi, w[11], xa[11], f, x, p1 = 3.1415927;

    std::cout << "CSL/F4 -4 CUADRATURA DE GAUSS" << std::endl;
    std::cout << "LOS ORDENES DE CUADRATURAS DISPONIBLES SON N = 2, 3, 4, 5, 6, 8, 10" << std::endl;
    std::cout << "N: ";
    std::cin >> n;

    if (n < 0) {
        std::cout << "Error: N debe ser mayor o igual a 0" << std::endl;
        return 1;
    }

    if (n == 7 || n == 9) {
        std::cout << "N = 7 y 9 no están disponibles" << std::endl;
        return 1;
    }

    std::cout << "EL LIMITE INFERIOR A: ";
    std::cin >> a;
    std::cout << "EL LIMITE SUPERIOR B: ";
    std::cin >> b;

    if (n == 2) {
        xa[2] = 0.5773502691;
        w[2] = 1;
    } else if (n == 3) {
        xa[2] = 0;
        xa[3] = 0.7745966692;
        w[2] = 0.8888888888;
        w[3] = 0.5555555555;
    } else if (n == 4) {
        xa[3] = 0.3399810435;
        xa[4] = 0.8611363115;
        w[3] = 0.6521451548;
        w[4] = 0.3478548451;
    } else if (n == 5) {
        xa[3] = 0;
        xa[4] = 0.5384693101;
        xa[5] = 0.9061798459;
        w[3] = 0.5688888888;
        w[4] = 0.4786286704;
        w[5] = 0.2369268850;
    } else if (n == 6) {
        xa[4] = 0.2386191860;
        xa[5] = 0.6612093864;
        xa[6] = 0.9324695142;
        w[4] = 0.4679139345;
        w[5] = 0.3607615730;
        w[6] = 0.1713244923;
    } else if (n == 8) {
        xa[5] = 0.1834346424;
        xa[6] = 0.5255324099;
        xa[7] = 0.7966664774;
        xa[8] = 0.9602898564;
        w[5] = 0.3626837833;
        w[6] = 0.3137066458;
        w[7] = 0.2223810344;
        w[8] = 0.1012285362;
    } else if (n == 10) {
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

    for (int j = 1; j <= n / 2; j++) {
        w[j] = w[n + 1 - j];
        xa[j] = -xa[n + 1 - j];
    }

    for (int j = 1; j <= n; j++) {
        xa[j] = (xa[j] * (b - a) + a + b) / 2;
    }

    xi =  xi * (b - a) / 2;