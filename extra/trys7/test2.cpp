#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void BISEC(vector<vector<double>>& A, vector<double>& G, double XL, double XH, double& XM);
void DETERM(vector<vector<double>>& A, vector<double>& G, double X, double& SL);

int main() {
    vector<vector<double>> A(5, vector<double>(5)), T(5, vector<double>(5)), EI(5, vector<double>(5));
    vector<double> U(5), G(5);
    int N = 4;
    A[1] = {0, 4, 3, 2, 1};
    A[2] = {0, 3, 3, 2, 1};
    A[3] = {0, 2, 2, 2, 1};
    A[4] = {0, 1, 1, 1, 1};

    cout << "REDUCCION DE UNA MATRIZ A LA FORMA DE HESSENBERG O TRIDIAGONAL MEDIANTE EL ESQUEMA DE HOUSEHOLDER" << endl;
    cout << "MATRIZ ORIGINAL (DEBE SER SIMETRICA)" << endl;

    for (int I = 1; I <= N; ++I) {
        for (int J = 1; J <= N; ++J) {
            cout << A[I][J] << " ";
        }
        cout << endl;
    }

    for (int IR = 1; IR <= N - 2; ++IR) {
        double S = 0.0;
        for (int I = 1; I <= N; ++I) {
            U[I] = 0;
            if (I > IR + 1) U[I] = A[I][IR];
            if (I > IR) S += A[I][IR] * A[I][IR];
        }
        double W = 1;
        if (A[IR + 1][IR] < 0) W = -1;
        double SSR = sqrt(S);
        double H = S + fabs(A[IR + 1][IR]) * SSR;
        U[IR + 1] = A[IR + 1][IR] + SSR * W;
        double UAU = 0.0;
        for (int I = 1; I <= N; ++I) {
            for (int J = 1; J <= N; ++J) {
                UAU += U[I] * A[I][J] * U[J];
                double B23 = 0.0;
                for (int K = 1; K <= N; ++K) {
                    B23 -= (U[I] * A[K][J] + A[I][K] * U[J]) * U[K];
                }
                T[I][J] = A[I][J] + B23 / H;
            }
        }
        UAU = UAU / (H * H);
        for (int I = 1; I <= N; ++I) {
            for (int J = 1; J <= N; ++J) {
                A[I][J] = T[I][J] + UAU * U[I] * U[J];
                if (fabs(A[I][J]) < 0.000001) A[I][J] = 0;
            }
        }
    }

    cout << "MATRIZ DE HESSENBERG O TRIDIAGONAL" << endl;
    for (int I = 1; I <= N; ++I) {
        for (int J = 1; J <= N; ++J) {
            cout << A[I][J] << " ";
        }
        cout << endl;
    }

    int KM = N;
    for (int L = 1; L <= KM; ++L) {
        if (L == 1) {
            EI[1][1] = A[1][1];
        } else {
            for (int J = 1; J <= L; ++J) {
                double XL = EI[L - 1][J - 1];
                double XH = EI[L - 1][J];
                double XM;
                BISEC(A, G, XL, XH, XM);
                EI[L][J] = XM;
            }
        }
        EI[L][0] = -99;
        EI[L][L + 1] = 99;
        if (L != N) {
            cout << "VALORES PROPIOS DE LA " << L << " X " << L << " SUBMATRIZ PRINCIPAL" << endl;
        } else {
            cout << "RESULTADOS FINALES (VALORES PROPIOS DE LA MATRIZ COMPLETA)" << endl;
        }
        for (int I = 1; I <= L; ++I) {
            cout << EI[L][I] << " ";
        }
        cout << endl;
    }
    cout << "-------------------------" << endl;
    return 0;
}

void BISEC(vector<vector<double>>& A, vector<double>& G, double XL, double XH, double& XM) {
    int KA = 0;
    double YL, YH;
    DETERM(A, G, XL, YL);
    DETERM(A, G, XH, YH);
    do {
        KA++;
        if (KA > 99) return;
        double DX = XH - XL;
        if (DX < 0.0000001) return;
        double XB = XM;
        XM = (XL * YH - XH * YL) / (YH - YL);
        double YM;
        DETERM(A, G, XM, YM);
        if (fabs(XB - XM) < 0.000001) return;
        if (YL * YM < 0) {
            XH = XM;
            YH = YM;
        } else {
            XL = XM;
            YL = YM;
        }
    } while (true);
}

void DETERM(vector<vector<double>>& A, vector<double>& G, double X, double& SL) {
    int L = A.size() - 1;
    G[0] = 1;
    if (L == 1) return;
    G[1] = A[1][1] - X;
    if (L == 1) return;
    for (int K = 2; K <= L; ++K) {
        G[K] = (A[K][K] - X) * G[K - 1] - A[K][K - 1] * A[K][K - 1] * G[K - 2];
    }
    SL = G[L];
}


