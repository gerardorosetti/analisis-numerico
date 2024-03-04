#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

void DETMNT(int N, vector<vector<double>>& A, double& DET);

int main() {
    const int N = 4;
    vector<vector<double>> A(20, vector<double>(20)), B(20, vector<double>(20)), DF(21, vector<double>(21));
    vector<double> FF(21), RA(21), CC(21), MV(21);
    double DE;

    cout << "CSL/F7 -1 METODO DR INTERPOLACION (FORTRAN)" << endl;
    cout << "ORDEN DE LA MATRIZ = " << N << endl;
    cout << "MATRIZ" << endl;

    B = {{4, 3, 2, 1}, {3, 3, 2, 1}, {2, 2, 2, 1}, {1, 1, 1, 1}};

    for (int I = 0; I < N; ++I) {
        for (int J = 0; J < N; ++J) {
            cout << setw(12) << setprecision(5) << scientific << B[I][J] << " ";
        }
        cout << endl;
    }

    cout << "DELTA LAMBDA ?" << endl;
    cin >> DE;

    for (int JJ = 0; JJ <= N; ++JJ) {
        RA[JJ] = JJ * DE;
        cout << "LAMBDA= " << RA[JJ] << endl;
        for (int J = 0; J < N; ++J) {
            for (int I = 0; I < N; ++I) {
                A[I][J] = B[I][J];
            }
            A[J][J] = A[J][J] - RA[JJ];
        }
        double S;
        DETMNT(N, A, S);
        FF[JJ] = S;
    }

    for (int I = 0; I <= N; ++I) {
        DF[I][0] = FF[I];
    }

    int M = N;
    for (int J = 1; J <= N; ++J) {
        M = M - 1;
        for (int I = 0; I <= M; ++I) {
            DF[I][J] = DF[I + 1][J - 1] - DF[I][J - 1];
        }
    }

    cout << "TABLA DE DIFERENCIAS PARA LOS DETERMINANTES" << endl;
    for (int I = 0; I <= N; ++I) {
        cout << setw(8) << fixed << setprecision(4) << RA[I] << " ";
        for (int J = 0; J <= N - I; ++J) {
            cout << setw(12) << setprecision(3) << scientific << DF[I][J] << " ";
        }
        cout << endl;
    }

    cout << "COEFICIENTES DE MARKOV" << endl;
    fill(CC.begin(), CC.end(), 0);
    fill(MV.begin(), MV.end(), 0);
    MV[1] = 1;
    CC[0] = DF[0][0];
    CC[1] = DF[0][1];

    for (int K = 2; K <= N; ++K) {
        for (int L = K; L >= 1; --L) {
            MV[L] = (MV[L - 1] - (K - 1) * MV[L]) / K;
            CC[L] += MV[L] * DF[0][K];
        }
        for (int L = 1; L <= K; ++L) {
            cout << setw(12) << setprecision(7) << fixed << MV[L] << " ";
        }
        cout << endl;
    }

    cout << "- - - RESULTADO FINAL - - -" << endl;
    cout << " POTENCIA, COEFICIENTES" << endl;
    for (int I = 0; I <= N; ++I) {
        CC[I] = CC[I] / pow(DE, I);
        cout << setw(3) << I << setw(10) << fixed << setprecision(4) << CC[I] << endl;
    }

    cout << "--------------------------------------" << endl;
    cout << "OPRIMA 1 PARA CONTINUAR, 00 PARA TERMINAR" << endl;
    int K;
    cin >> K;
    if (K == 1) {
        // This would normally loop back to the start, but we can't do that in C++ without restructuring the code.
    }

    return 0;
}

void DETMNT(int N, vector<vector<double>>& A, double& DET) {
    int PV, PC = 0;
    DET = 1;

    for (int I = 0; I < N - 1; ++I) {
        PV = I;
        for (int J = I + 1; J < N; ++J) {
            if (abs(A[PV][I]) < abs(A[J][I])) PV = J;
        }
        if (PV != I) {
            for (int JC = 0; JC < N; ++JC) {
                swap(A[I][JC], A[PV][JC]);
            }
            PC = PC + 1;
        }
        for (int JR = I + 1; JR < N; ++JR) {
            if (A[JR][I] != 0) {
                double R = A[JR][I] / A[I][I];
                for (int KC = I + 1; KC < N; ++KC) {
                    A[JR][KC] -= R * A[I][KC];
                }
            }
        }
    }

    if (A[N - 1][N - 1] == 0) {
        cout << "LA MATRIZ ES SINGULAR" << endl;
        return;
    }

    for (int I = 0; I < N; ++I) {
        DET *= A[I][I];
    }
    if (PC % 2 != 0) DET = -DET;

    cout << "DETERMINANTE = " << DET << endl;
    cout << "NUMERO DE PIVOTEOS= " << PC << endl;
}
