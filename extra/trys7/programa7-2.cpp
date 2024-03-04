#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void bisection(vector<vector<double>>& A, double XL, double XH, double& XM);
void determinant(vector<vector<double>>& A, double X, double& SL);

int main() {
    int N = 4;
    vector<vector<double>> A(N, vector<double>(N)), T(N, vector<double>(N)), EI(N+1, vector<double>(N+2));
    vector<double> U(N), G(N);
    double SSR, H, UAU, B23;
    int W;

    // Data initialization
    A = {{4, 3, 2, 1}, {3, 3, 2, 1}, {2, 2, 2, 1}, {1, 1, 1, 1}};

    cout << "REDUCCION DE UNA MATRIZ A LA FORMA DE HESSENBERG O TRIDIAGONAL MEDIANTE EL ESQUEMA DE HOUSEHOLDER" << endl;
    cout << "MATRIZ ORIGINAL (DEBE SER SIMETRICA)" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    for (int IR = 0; IR < N - 2; ++IR) {
        double s = 0;
        fill(U.begin(), U.end(), 0);
        for (int i = 0; i < N; ++i) {
            if (i > IR + 1) U[i] = A[i][IR];
            if (i > IR) s += A[i][IR] * A[i][IR];
        }
        W = (A[IR + 1][IR] < 0) ? -1 : 1;
        SSR = sqrt(s);
        H = s + fabs(A[IR + 1][IR]) * SSR;
        U[IR + 1] = A[IR + 1][IR] + SSR * W;
        UAU = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                UAU += U[i] * A[i][j] * U[j];
                if (i <= IR && j <= IR) {
                    T[i][j] = A[i][j];
                    continue;
                }
                if (j == IR && i >= IR + 2) {
                    T[i][j] = 0;
                    continue;
                }
                B23 = 0;
                for (int k = 0; k < N; ++k) {
                    B23 -= (U[i] * A[k][j] + A[i][k] * U[j]) * U[k];
                }
                T[i][j] = A[i][j] + B23 / H;
            }
        }
        UAU /= (H * H);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                A[i][j] = T[i][j] + UAU * U[i] * U[j];
                if (fabs(A[i][j]) < 0.000001) A[i][j] = 0;
            }
        }
    }

    cout << "MATRIZ DE HESSENBERG O TRIDIAGONAL" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    // Dummy read simulation
    int DUMM;
    cout << "PARA CONTINUAR, OPRIMA 1 Y LA TECLA ENTER" << endl;
    cin >> DUMM;

    for (int L = 1; L <= N; ++L) {
        if (L == 1) {
            EI[1][1] = A[0][0];
        } else {
            for (int J = 1; J <= L; ++J) {
                double XL = EI[L-1][J-1];
                double XH = EI[L-1][J];
                double XM;
                bisection(A, XL, XH, XM);
                EI[L][J] = XM;
            }
        }
        EI[L][0] = -99;
        EI[L][L+1] = 99;
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

void bisection(vector<vector<double>>& A, double XL, double XH, double& XM) {
    int KA = 0;
    double YL, YH, YM;
    determinant(A, XL, YL);
    determinant(A, XH, YH);
    while (KA < 100) {
        KA++;
        double DX = XH - XL;
        if (DX < 0.0000001) return;
        if (DX > 1) {
            XM = (XL + XH) / 2;
        } else {
            XM = (XL * YH - XH * YL) / (YH - YL);
        }
        determinant(A, XM, YM);
        if (fabs(YL * YM) < 0) {
            XH = XM;
            YH = YM;
        } else {
            XL = XM;
            YL = YM;
        }
    }
}

void determinant(vector<vector<double>>& A, double X, double& SL) {
    int L = A.size();
    vector<double> G(L);
    G[0] = 1;
    if (L == 1) {
        SL = G[0];
        return;
    }
    G[1] = A[1][1] - X;
    for (int K = 2; K < L; ++K) {
        G[K] = (A[K][K] - X) * G[K-1] - A[K][K-1] * A[K][K-1] * G[K-2];
    }
    SL = G[L-1];
}