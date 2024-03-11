#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Function prototypes
void gauss(int N, vector<vector<double>>& A);
double fun(int K, double X);

int main() {
    const int IN = 6;
    vector<double> X = {0.1, 0.4, 0.5, 0.7, 0.7, 0.9};
    vector<double> Y = {0.61, 0.92, 0.99, 1.52, 1.47, 2.03};
    vector<vector<double>> A(11, vector<double>(12));
    vector<double> GG(IN);
    int LP, NORD, M;

    cout << "CSL/FS-1 AJUSTE DE CURVAS MEDIANTE MINIMOS CUADRADOS" << endl;
    cout << " OPRIMA 0 PARA AJUSTE POLINOMIAL" << endl;
    cout << " 1 PARA COMBINACION LINEAL" << endl;
    cin >> LP;

    if (LP == 1) {
        cout << " DE EL NUMERO DE FUNCIONES EN LA COMBINACION LINEAL" << endl;
        cout << " (POR EL MOMENTO SOLO SE DISPONE DE CUATRO FUNCIONES)" << endl;
        cin >> M;
    } else {
        cout << " DE EL ORDEN DEL POLINOMIO" << endl;
        cin >> NORD;
        M = NORD + 1;
    }

    // Initialization of the matrix
    for (int K = 1; K <= M; ++K) {
        for (int J = 1; J <= M + 1; ++J) {
            A[K][J] = 0.0;
        }
    }

    if (LP == 1) {
        // Combination linear
        for (int I = 0; I < IN; ++I) {
            for (int K = 1; K <= M; ++K) {
                double FK = fun(K, X[I]);
                for (int J = 1; J <= M; ++J) {
                    A[K][J] += FK * fun(J, X[I]);
                }
                A[K][M + 1] += Y[I] * FK;
            }
        }
    } else {
        // Polynomial fit
        for (int K = 1; K <= M; ++K) {
            for (int I = 0; I < IN; ++I) {
                for (int J = 1; J <= M; ++J) {
                    int JJ = K - 1 + J - 1;
                    double YY = 1.0;
                    if (JJ != 0) YY = pow(X[I], JJ);
                    A[K][J] += YY;
                }
                int JEX = K - 1;
                double YY = 1.0;
                if (JEX != 0) YY = pow(X[I], JEX);
                A[K][M + 1] += Y[I] * YY;
            }
        }
    }

    // Solution
    for (int I = 1; I <= M; ++I) {
        for (int J = 1; J <= M + 1; ++J) {
            cout << setw(11) << setprecision(3) << scientific << A[I][J] << " ";
        }
        cout << endl;
    }

    gauss(M, A);

    cout << "DETERMINACION DE COEFICIENTES" << endl;
    if (LP == 1) {
        cout << "FUNCION COEFICIENTE" << endl;
    } else {
        cout << "POTENCIA COEFICIENTE" << endl;
    }
    cout << "- - - - - - - - -" << endl;

    for (int I = 1; I <= M; ++I) {
        if (LP == 1) {
            cout << setw(4) << I << setw(12) << setprecision(6) << fixed << A[I][M + 1] << endl;
        } else {
            cout << setw(4) << I - 1 << setw(12) << setprecision(6) << fixed << A[I][M + 1] << endl;
        }
    }

    cout << "- - - - - - - - - - -" << endl;

    // Error evaluation
    cout << "EVALUACION DEL ERROR" << endl;
    cout << "----------------------------------" << endl;
    cout << " I X(I) Y(I) POLINOMIO DESVIACION" << endl;
    cout << "----------------------------------" << endl;
    for (int I = 0; I < IN; ++I) {
        GG[I] = 0.0;
        for (int K = 1; K <= M; ++K) {
            if (LP == 1) {
                GG[I] += A[K][M + 1] * fun(K, X[I]);
            } else {
                GG[I] += A[K][M + 1] * pow(X[I], K - 1);
            }
        }
        cout << setw(4) << I + 1 << setw(8) << setprecision(2) << fixed << X[I] << setw(10) << setprecision(5) << Y[I] << setw(12) << setprecision(7) << GG[I] << setw(11) << setprecision(6) << Y[I] - GG[I] << endl;
    }
    cout << "----------------------------" << endl;

    return 0;
}

void gauss(int N, vector<vector<double>>& A) {
    for (int I = 1; I < N; ++I) {
        int IPV = I;
        for (int J = I + 1; J <= N; ++J) {
            if (abs(A[IPV][I]) < abs(A[J][I])) IPV = J;
        }
        if (IPV != I) {
            for (int JC = 1; JC <= N + 1; ++JC) {
                swap(A[I][JC], A[IPV][JC]);
            }
        }
        for (int JR = I + 1; JR <= N; ++JR) {
            if (A[JR][I] != 0) {
                double R = A[JR][I] / A[I][I];
                for (int KC = I + 1; KC <= N + 1; ++KC) {
                    A[JR][KC] -= R * A[I][KC];
                }
            }
        }
    }
    if (A[N][N] == 0) return;
    A[N][N + 1] /= A[N][N];
    for (int NV = N - 1; NV >= 1; --NV) {
        double VA = A[NV][N + 1];
        for (int K = NV + 1; K <= N; ++K) {
            VA -= A[NV][K] * A[K][N + 1];
        }
        A[NV][N + 1] = VA / A[NV][NV];
    }
}

double fun(int K, double X) {
    if (K == 1) return 1;
    if (K == 2) return X;
    if (K == 3) return sin(X);
    if (K == 4) return exp(X);
    return 0; // Default case
}