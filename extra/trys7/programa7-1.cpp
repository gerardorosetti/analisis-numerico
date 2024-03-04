#include <iostream>
#include <cmath>

void DETMNT(int N, double A[20][20], double& DET);

int main() {
    double A[20][20], FF[21], RA[21], DF[21][21], B[20][20];
    double CC[21], MV[21];
    int N = 4;

    std::cout << "CSL/F7 -1 METODO DR INTERPOLACION (FORTRAN)" << std::endl;

    B[0][0] = 4; B[0][1] = 3; B[0][2] = 2; B[0][3] = 1;
    B[1][0] = 3; B[1][1] = 3; B[1][2] = 2; B[1][3] = 1;
    B[2][0] = 2; B[2][1] = 2; B[2][2] = 2; B[2][3] = 1;
    B[3][0] = 1; B[3][1] = 1; B[3][2] = 1; B[3][3] = 1;

    std::cout << "ORDEN DE LA MATRIZ = " << N << std::endl;
    std::cout << "MATRIZ" << std::endl;
    for (int I = 0; I < N; I++) {
        for (int J = 0; J < N; J++) {
            std::cout << B[I][J] << " ";
        }
        std::cout << std::endl;
    }

    double DE;
    std::cout << "DELTA LAMBDA ?" << std::endl;
    std::cin >> DE;

    for (int JJ = 0; JJ <= N; JJ++) {
        RA[JJ] = JJ * DE;
        std::cout << "LAMBDA = " << RA[JJ] << std::endl;

        for (int J = 0; J < N; J++) {
            for (int I = 0; I < N; I++) {
                A[I][J] = B[I][J];
            }
            A[J][J] = A[J][J] - RA[JJ];
        }

        double S;
        DETMNT(N, A, S);
        FF[JJ] = S;
    }

    for (int I = 0; I <= N; I++) {
        DF[I][0] = FF[I];
    }

    int M = N;
    for (int J = 1; J < N; J++) {
        M = M - 1;
        for (int I = 0; I <= M; I++) {
            DF[I][J] = DF[I + 1][J - 1] - DF[I][J - 1];
        }
    }

    std::cout << "TABLA DE DIFERENCIAS PARA LOS DETERMINANTES" << std::endl;
    for (int I = 0; I <= N; I++) {
        std::cout << RA[I] << " ";
        for (int J = 0; J <= N - I; J++) {
            std::cout << DF[I][J] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "COEFICIENTES DE MARKOV" << std::endl;
    for (int I = 0; I <= N; I++) {
        CC[I] = 0;
        MV[I] = 0;
    }
    MV[1] = 1;
    CC[0] = DF[0][0];
    CC[1] = DF[0][1];

    for (int K = 2; K <= N; K++) {
        for (int L = K; L >= 1; L--) {
            MV[L] = (MV[L - 1] - (K - 1) * MV[L]) / K;
            CC[L] = CC[L] + MV[L] * DF[0][K];
        }
        for (int L = 1; L <= K; L++) {
            std::cout << MV[L] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "RESULTADO FINAL" << std::endl;
    std::cout << "POTENCIA, COEFICIENTES" << std::endl;
    for (int I = 0; I <= N; I++) {
        CC[I] = CC[I] / pow(DE, I);
        std::cout << "  " << I << "     " << CC[I] << std::endl;
    }

    std::cout << "--------------------------------------" << std::endl;

    int K;
    std::cout << "OPRIMA 1 PARA CONTINUAR, 00 PARA TERMINAR" << std::endl;
    std::cin >> K;

    return 0;
}

void DETMNT(int N, double A[20][20], double& DET) {
    int PV, PC;
    PC = 0;

    for (int I = 0; I < N - 1; I++) {
        PV = I;
        for (int J = I + 1; J < N; J++) {
            if (std::abs(A[PV][I]) < std::abs(A[J][I])) {
                PV = J;
            }
        }
        if (PV != I) {
            for (int JC = 0; JC < N; JC++) {
                double TM = A[I][JC];
                A[I][JC] = A[PV][JC];
                A[PV][JC] = TM;
            }
            PC = PC + 1;
        }
        for (int JR = I + 1; JR < N; JR++) {
            if (A[JR][I] != 0) {
                double R = A[JR][I] / A[I][I];
                for (int KC = I + 1; KC < N; KC++) {
                    A[JR][KC] = A[JR][KC] - R * A[I][KC];
                }
            }
        }
    }

    if (A[N - 1][N - 1] != 0) {
        DET = 1;
        for (int I = 0; I < N; I++) {
            DET = DET * A[I][I];
        }
        if (PC % 2 != 0) {
            DET = -DET;
        }
        std::cout << "DETERMINANTE = " << DET << std::endl;
        std::cout << "NUMERO DE PIVOTEOS = " << PC << std::endl;
    } else {
        std::cout << "LA MATRIZ ES SINGULAR" << std::endl;
    }
}