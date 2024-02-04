#include <iostream>
#include <cmath>

using namespace std;

// Subrutina para evaluar la función a integrar
void FUN(double &F, double X) {
    F = sin(X); // Aquí se debe definir la función a integrar, en este caso se utiliza el seno como ejemplo
}

int main() {
    int N;
    double A, B;

    cout << "Ingrese el número de puntos N: ";
    cin >> N;
    cout << "Ingrese el límite inferior A: ";
    cin >> A;
    cout << "Ingrese el límite superior B: ";
    cin >> B;

    double XA[] = {0, 0, 0.5773502691, 0.7745966692, 0.3399810435, 0.8611363115, 0, 0.5384693101, 0.9061798459, 0, 0.2386191860, 0.6612093864, 0.9324695142, 0, 0.1834346424, 0.5255324099, 0.7966664774, 0.9602898564, 0, 0.1488743389, 0.4333953941, 0.6794095682, 0.8650633666, 0.9739065285};
    double W[] = {0, 0, 1, 0.8888888888, 0.5555555555, 0.6521451548, 0.3478548451, 0.5688888888, 0.4786286704, 0.2369268850, 0.4679139345, 0.3607615730, 0.1713244923, 0.3626837833, 0.3137066458, 0.2223810344, 0.1012285362, 0, 0.2955242247, 0.2692667193, 0.2190863625, 0.1494513491, 0.0666713443};

    if (N == 2) {
        XA[2] = 0.5773502691;
        W[2] = 1;
    } else if (N == 3) {
        XA[2] = 0;
        XA[3] = 0.7745966692;
        W[2] = 0.8888888888;
        W[3] = 0.5555555555;
    } else if (N == 4) {
        XA[3] = 0.3399810435;
        XA[4] = 0.8611363115;
        W[3] = 0.6521451548;
        W[4] = 0.3478548451;
    } else if (N == 5) {
        XA[3] = 0;
        XA[4] = 0.5384693101;
        XA[5] = 0.9061798459;
        W[3] = 0.5688888888;
        W[4] = 0.4786286704;
        W[5] = 0.2369268850;
    } else if (N == 6) {
        XA[4] = 0.2386191860;
        XA[5] = 0.6612093864;
        XA[6] = 0.9324695142;
        W[4] = 0.4679139345;
        W[5] = 0.3607615730;
        W[6] = 0.1713244923;
    } else if (N == 8) {
        XA[5] = 0.1834346424;
        XA[6] = 0.5255324099;
        XA[7] = 0.7966664774;
        XA[8] = 0.9602898564;
        W[5] = 0.3626837833;
        W[6] = 0.3137066458;
        W[7] = 0.2223810344;
        W[8] = 0.1012285362;
    } else if (N == 10) {
        XA[6] = 0.1488743389;
        XA[7] = 0.4333953941;
        XA[8] = 0.6794095682;
        XA[9] = 0.8650633666;
        XA[10] = 0.9739065285;
        W[6] = 0.2955242247;
        W[7] = 0.2692667193;
        W[8] = 0.2190863625;
        W[9] = 0.1494513491;
        W[10] = 0.0666713443;
    }

    if (N < 0) {
        cout << "Error: N no puede ser negativo" << endl;
        return 1;
    } else if (N == 7 || N == 9) {
        cout << "Error: N = 7 y 9 no están disponibles" << endl;
        return 1;
    }

    // Inicialización de la fórmula
    // double P1 = 3.1415927;
    // for (int J = 1; J <= N / 2; J++) {
    //     W[J] = W[N - J];
    //     XA[J] = -XA[N - J];
    // }

    // for (int J = 1; J <= N; J++) {
    //     XA[J] = (XA[J] * (B - A) + A + B) / 2;
    // }


    for (int j = 1; j <= N / 2; j++) {
        W[j] = W[N + 1 - j];
        XA[j] = -XA[N + 1 - j];
    }

    for (int j = 1; j <= N; j++) {
        XA[j] = (XA[j] * (B - A) + A + B) / 2;
    }

    // double XI = 0;
    // for (int J = 1; J <= N; J++) {
    //     double X = XA[J];
    //     FUN(F, X);
    //     XI += F * W[J];
    // }
    // XI *= (B - A) / 2;

    // cout << "El resultado final es: " << XI << endl;
    
    double XI = 0;
    for (int J = 1; J <= N; J++) {
        double X = XA[J];
        double F;
        FUN(F, X);
        XI += F * W[J];
    }
    XI *= (B - A) / 2;

    cout << "El resultado final: " << XI << endl;

    return 0;
}
