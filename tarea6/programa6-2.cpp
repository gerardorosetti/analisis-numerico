#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

void GAUSS(int N, std::vector<std::vector<double>>& A);

int main() {
    const int N = 3;
    std::vector<std::vector<double>> A(11, std::vector<double>(21, 0.0));

    A[1] = {0, 2, 1, -3, 1, 0, 0};
    A[2] = {0, -1, 3, 2, 0, 1, 0};
    A[3] = {0, 3, 1, -3, 0, 0, 1};

    int space = 14;
    std::cout << std::fixed << std::setprecision(5) << std::scientific;

    std::cout << "\nINVERSION DE UNA MATRIZ" << std::endl << std::endl;
    std::cout << "\n- - - - - - - - - - - - - - - - - - - - - -" << std::endl;
    std::cout << "LA MATRIZ ORIGINAL:\n\n";
    for (int I = 1; I <= N; ++I) {
        for (int J = 1; J <= 3; ++J) {
            std::cout << std::setw(space) << A[I][J];
        }
        std::cout << std::endl;
    }
    std::cout << "- - - - - - - - - - - - - - - - - - - - - -" << std::endl;

    GAUSS(N, A);

    std::cout << "- - - - - - - - - - - - - - - - - - - - - -" << std::endl;
    std::cout << "MATRIZ INVERSA:" << std::endl << std::endl;
    for (int I = 1; I <= N; ++I) {
        for (int J = N + 1; J <= N * 2; ++J) {
            std::cout << std::setw(space) << A[I][J];
        }
        std::cout << std::endl;
    }
    std::cout << "- - - - - - - - - - - - - - - - - - - - - -" << std::endl;

    return 0;
}

void GAUSS(int N, std::vector<std::vector<double>>& A) {
    double EPS = 1.0;
    while (1.0 + EPS > 1.0) {
        EPS /= 2.0;
    }
    EPS *= 2;
    std::cout << "\nEPSILON DE LA MAQUINA = " << EPS << std::endl;
    double EPS2 = EPS * 2;
    double DET = 1.0;
    int PV;
    double TM, R, TEMP, VA;

    for (int I = 1; I <= N - 1; ++I) {
        PV = I;
        for (int J = I + 1; J <= N; ++J) {
            if (std::abs(A[PV][I]) < std::abs(A[J][I])) PV = J;
        }
        if (PV != I) {
            for (int JC = 1; JC <= N * 2; ++JC) {
                TM = A[I][JC];
                A[I][JC] = A[PV][JC];
                A[PV][JC] = TM;
            }
            DET = -DET;
        }
        if (A[I][I] == 0) {
            std::cout << "\nLA MATRIZ ES SINGULAR" << std::endl;
            return;
        }

        for (int JR = I + 1; JR <= N; ++JR) {
            if (A[JR][I] != 0) {
                R = A[JR][I] / A[I][I];
                for (int KC = I + 1; KC <= N * 2; ++KC) {
                    TEMP = A[JR][KC];
                    A[JR][KC] -= R * A[I][KC];
                    if (std::abs(A[JR][KC]) < EPS2 * TEMP) A[JR][KC] = 0.0;
                }
            }
        }
    }

    for (int I = 1; I <= N; ++I) {
        DET *= A[I][I];
    }
    std::cout << "\nDETERMINANTE = " << DET << std::endl << std::endl;

    if (A[N][N] == 0) {
        std::cout << "\nLA MATRIZ ES SINGULAR" << std::endl;
        return;
    }

    for (int M = N + 1; M <= N * 2; ++M) {
        A[N][M] /= A[N][N];
        for (int NV = N - 1; NV >= 1; --NV) {
            VA = A[NV][M];
            for (int K = NV + 1; K <= N; ++K) {
                VA -= A[NV][K] * A[K][M];
            }
            A[NV][M] = VA / A[NV][NV];
        }
    }
}

