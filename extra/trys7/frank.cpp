#include <iostream>
#include <cmath>

void DETERM(double G[], double A[][11], int L, double X, double &SL) {
    G[0] = 1;
    if (L == 1)
        return;
    G[1] = A[1][1] - X;
    if (L == 1)
        return;
    for (int K = 2; K <= L; K++) {
        G[K] = (A[K][K] - X) * G[K - 1] - A[K][K - 1] * A[K][K - 1] * G[K - 2];
    }
    SL = G[L];
}

void BISEC(double G[], double A[][11], double XL, double XH, double &XM) {
    int KA = 0;
    double YL, YH, YM, DX, XB;

    DETERM(G, A, XL, YL);
    DETERM(G, A, XH, YH);

    while (++KA <= 99) {
        DX = XH - XL;
        if (DX < 0.0000001)
            return;
        if (DX > 1) {
            XM = (XL + XH) / 2;
            DETERM(G, A, XM, YM);
            continue;
        }

        XB = XM;
        XM = (XL * YH - XH * YL) / (YH - YL);
        DETERM(G, A, XM, YM);

        if (std::abs(XB - XM) < 0.000001)
            return;

        if (YL * YM < 0) {
            XH = XM;
            YH = YM;
        } else {
            XL = XM;
            YL = YM;
        }
    }
}

int main() {
    int N = 4;
    double A[11][11], U[11], T[11][11];
    double G[11], EI[11][11];

    // Inicializar matriz A (datos de ejemplo)
    A[1][1] = 4; A[1][2] = 3; A[1][3] = 2; A[1][4] = 1;
    A[2][1] = 3; A[2][2] = 3; A[2][3] = 2; A[2][4] = 1;
    A[3][1] = 2; A[3][2] = 2; A[3][3] = 2; A[3][4] = 1;
    A[4][1] = 1; A[4][2] = 1; A[4][3] = 1; A[4][4] = 1;

    std::cout << "REDUCCION DE UNA MATRIZ A LA FORMA DE HESSENBERG O TRIDIAGONAL MEDIANTE EL ESQUEMA DE HOUSEHOLDER\n";
    std::cout << "MATRIZ ORIGINAL (DEBE SER SIMETRICA)\n";
    for (int I = 1; I <= N; I++) {
        for (int J = 1; J <= N; J++) {
            std::cout << A[I][J] << " ";
        }
        std::cout << "\n";
    }

    // for (int IR = 1; IR <= N - 2; IR++) {
    //     // Lógica de reducción de matriz a forma Hessenberg o tridiagonal
    //     // ...

    // }

for (int IR = 1; IR <= N - 2; IR++) {
    double S = 0;
    for (int I = 1; I <= N; I++) {
        U[I] = 0;
        if (I > IR + 1) U[I] = A[I][IR];
        if (I > IR) S = S + A[I][IR] * A[I][IR];
    }
    double W = 1;
    if (A[IR + 1][IR] < 0) W = -1;
    double SSR = sqrt(S);
    double H = S + abs(A[IR + 1][IR]) * SSR;
    U[IR + 1] = A[IR + 1][IR] + SSR * W;
    double UAU = 0;
    for (int I = 1; I <= N; I++) {
        for (int J = 1; J <= N; J++) {
            UAU = UAU + U[I] * A[I][J] * U[J];
            if ((I <= IR) && (J <= IR)) {
                T[I][J] = A[I][J];
                continue;
            }
            if ((J == IR) && (I >= IR + 2)) {
                T[I][J] = 0;
                continue;
            }
            double B23 = 0;
            for (int K = 1; K <= N; K++) {
                B23 = B23 - (U[I] * A[K][J] + A[I][K] * U[J]) * U[K];
            }
            T[I][J] = A[I][J] + B23 / H;
        }
    }
    UAU = UAU / H / H;
    for (int I = 1; I <= N; I++) {
        for (int J = 1; J <= N; J++) {
            A[I][J] = T[I][J] + UAU * U[I] * U[J];
            if (abs(A[I][J]) < 0.000001) A[I][J] = 0;
        }
    }
}


    // Cálculo de valores propios
    for (int L = 1; L <= N; L++) {
        if (L == 1) {
            EI[1][1] = A[1][1];
        } else {
            int KM = 0;
            for (int J = 1; J <= L; J++) {
                double XL = EI[L-1][J-1];
                double XH = EI[L-1][J];
                KM = J;
                double XM;
                BISEC(G, A, XL, XH, XM);
                EI[L][J] = XM;
            }
        }
    }

    // Imprimir resultados finales
    // ...

std::cout << "MATRIZ DE HESSENBERG O TRIDIAGONAL\n";
std::cout << "\n";
for (int I = 1; I <= N; I++) {
    for (int J = 1; J <= 4; J++) {
        std::cout << A[I][J] << " ";
    }
    std::cout << "\n";
}
std::cout << "\n";
std::cout << "PARA CONTINUAR, OPRIMA 1 Y LA TECLA ENTER\n";
std::cin >> DUMM;
std::cout << "\n";

int KM = N;
for (int L = 1; L <= KM; L++) {
    if (L == 1) {
        EI[L][1] = A[1][1];
    } else {
        for (int J = 1; J <= L; J++) {
            double XL = EI[L - 1][J - 1];
            double XH = EI[L - 1][J];
            KM = J;
            double XM;
            BISEC(G, A, XL, XH, XM);
            EI[L][J] = XM;
        }
    }

    EI[L][0] = -99;
    EI[L][L + 1] = 99;
    if (L != N) {
        std::cout << "\n";
        std::cout << "VALORES PROPIOS DE LA " << L << " x " << L << " SUBMATRIZ PRINCIPAL\n";
    } else {
        std::cout << "\n";
        std::cout << "RESULTADOS FINALES (VALORES PROPIOS DE LA MATRIZ COMPLETA)\n";
    }
    for (int I = 1; I <= L; I++) {
        std::cout << EI[L][I] << " ";
    }
    std::cout << "\n";
}

std::cout << "-------------------------\n";
std::cout << "\n";
std::cout << "\n";


    return 0;
}
