#include <iostream>
#include <cmath>
using namespace std;

const int MAX_POINTS = 100;
const int MAX_FUNCTIONS = 10;

double X[MAX_POINTS + 1];
double Y[MAX_POINTS + 1];
double A[MAX_FUNCTIONS + 1][MAX_FUNCTIONS + 2];
double GG[MAX_POINTS + 1];

// Function definitions
double FUN(int K, double X) {
    // First function
    if (K == 1) return 1.0;
    // Second function
    if (K == 2) return X;
    // Third function
    if (K == 3) return sin(X);
    // Fourth function
    if (K == 4) return exp(X);
    return 0.0;
}

// Gauss elimination subroutine
void GAUSS(int N, double A[MAX_FUNCTIONS + 1][MAX_FUNCTIONS + 2]) {
    for (int I = 1; I <= N - 1; ++I) {
        int IPV = I;
        for (int J = I + 1; J <= N; ++J) {
            if (abs(A[IPV][I]) < abs(A[J][I])) IPV = J;
        }
        if (IPV != I) {
            for (int JC = 1; JC <= N + 1; ++JC) {
                double TM = A[I][JC];
                A[I][JC] = A[IPV][JC];
                A[IPV][JC] = TM;
            }
        }
        for (int JR = I + 1; JR <= N; ++JR) {
            if (A[JR][I] != 0) {
                if (A[I][I] == 0.0) {
                    cout << "La matriz es singular" << endl;
                    return;
                }
                double R = A[JR][I] / A[I][I];
                for (int KC = I + 1; KC <= N + 1; ++KC) {
                    A[JR][KC] -= R * A[I][KC];
                }
            }
        }
    }
    if (A[N][N] == 0) {
        cout << "La matriz es singular" << endl;
        return;
    }
    A[N][N + 1] /= A[N][N];
    for (int NV = N - 1; NV >= 1; --NV) {
        double VA = A[NV][N + 1];
        for (int K = NV + 1; K <= N; ++K) {
            VA -= A[NV][K] * A[K][N + 1];
        }
        A[NV][N + 1] = VA / A[NV][NV];
    }
}

int main() {
    cout << "CSL/FS-1 AJUSTE DE CURVAS MEDIANTE MINIMOS CUADRADOS" << endl;

    // Numero de puntos dados.
    int IN = 6;
    double xData[6] = {0.1, 0.4, 0.5, 0.7, 0.7, 0.9};
    double yData[6] = {0.61, 0.92, 0.99, 1.52, 1.47, 2.03};

    cout << "OPRIMA 0 PARA AJUSTE POLINOMIAL" << endl;
    cout << "1 PARA COMBINACION LINEAL" << endl;
    int M;
    int LP;
    cin >> LP;

    if (LP != 1) {
        cout << "DE EL ORDEN DEL POLINOMIO" << endl;
        int NORD;
        cin >> NORD;
        int M = NORD + 1;

        // Inicialización de la matriz
        for (int K = 1; K <= M; ++K) {
            for (int J = 1; J <= M + 1; ++J) {
                A[K][J] = 0.0;
            }
        }
        
        // Desarrollo de la matriz para el ajuste polinomial
        for (int K = 1; K <= M; ++K) {
            for (int I = 1; I <= IN; ++I) {
                for (int J = 1; J <= M; ++J) {
                    int JJ = K - 1 + J - 1;
                    double YY = 1.0;
                    if (JJ != 0) YY = pow(xData[I], JJ);
                    A[K][J] += YY;
                }
                int JEX = K - 1;
                double YY = 1.0;
                if (JEX != 0) YY = pow(xData[I], JEX);
                A[K][M + 1] += yData[I] * YY;
            }
        }
    } else {
        cout << "DE EL NUMERO DE FUNCIONES EN LA COMBINACION LINEAL" << endl;
        cin >> M;

        for (int I = 1; I <= IN; ++I) {
            for (int K = 1; K <= M; ++K) {
                double FK = FUN(K, xData[I]);
                for (int J = 1; J <= M; ++J) {
                    A[K][J] += FK * FUN(J, xData[I]);
                }
                A[K][M + 1] += yData[I] * FK;
            }
        }
    }

    // Solucion
    int N = M;
    GAUSS(M, A);

    cout << "DETERMINACION DE COEFICIENTES" << endl;
    cout << "- - - - - - - - -" << endl;
    for (int I = 1; I <= M; ++I) {
        if (LP == 1)
            cout << "FUNCION COEFICIENTE " << I << ": " << A[I][M + 1] << endl;
        else
            cout << "POTENCIA COEFICIENTE " << I - 1 << ": " << A[I][M + 1] << endl;
    }
    cout << "- - - - - - - - - - -" << endl;

    // Evaluacion del error
    cout << "EVALUACION DEL ERROR" << endl;
    cout << "----------------------------------" << endl;
    cout << "I X(I) Y(I) POLINOMIO DESVIACION" << endl;
    cout << "----------------------------------" << endl;
    for (int I = 1; I <= IN; ++I) {
        double GG_I = 0.0;
        for (int K = 1; K <= M; ++K) {
            if (LP == 1)
                GG_I += A[K][M + 1] * FUN(K, xData[I]);
            else
                GG_I += A[K][M + 1] * pow(xData[I], (K - 1));
        }
        cout << I << " " << xData[I] << " " << yData[I] << " " << GG_I << " " << yData[I] - GG_I << endl;
    }

    return 0;
}
