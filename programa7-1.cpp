#include <iostream>
#include <iomanip>
#include <cmath>

void DETMNT(int N, double A[20][20], double& DET)
{
    int PC = 0;
    for (int I = 0; I < N - 1; ++I)
    {
        int PV = I;
        for (int J = I + 1; J < N; ++J)
        {
            if (std::abs(A[PV][I]) < std::abs(A[J][I]))
                PV = J;
        }
        if (PV != I)
        {
            for (int JC = 0; JC < N; ++JC)
            {
                double TM = A[I][JC];
                A[I][JC] = A[PV][JC];
                A[PV][JC] = TM;
            }
            PC += 1;
        }
        for (int JR = I + 1; JR < N; ++JR)
        {
            if (A[JR][I] != 0)
            {
                double R = A[JR][I] / A[I][I];
                for (int KC = I + 1; KC < N; ++KC)
                {
                    A[JR][KC] -= R * A[I][KC];
                }
            }
        }
    }
    if (A[N - 1][N - 1] == 0)
    {
        std::cout << "LA MATRIZ ES SINGULAR" << std::endl;
        DET = 0;
        return;
    }
    DET = 1;
    for (int I = 0; I < N; ++I)
    {
        DET *= A[I][I];
    }
    if (PC % 2 != 0)
        DET = -DET;
    std::cout << "DETERMINANTE = " << DET << std::endl;
    std::cout << "NUMERO DE PIVOTEOS = " << PC << std::endl;
}

int main()
{
    const int N = 4;
    double A[20][20], FF[21], RA[21], DF[21][21], B[20][20], CC[21], MV[21], DE, S;

    std::cout << "CSL/F7 -1 METODO DE INTERPOLACION" << std::endl << std::endl;
    std::cout << std::fixed << std::setprecision(5);
    // Inicialización de B
    double init_B[N][N] = {
        {4, 3, 2, 1},
        {3, 3, 2, 1},
        {2, 2, 2, 1},
        {1, 1, 1, 1}
    };
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            B[i][j] = init_B[i][j];
        }
    }
    std::cout << std::fixed << std::setprecision(5) << std::scientific;
    std::cout << "ORDEN DE LA MATRIZ = " << N << std::endl;
    std::cout << "MATRIZ" << std::endl;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            std::cout << std::setw(12) << B[i][j];
        }
        std::cout << std::endl;
    }

    std::cout << std::fixed << std::setprecision(5);

    std::cout << std::endl << "DELTA LAMBDA = ";
    std::cin >> DE;

    for (int JJ = 0; JJ <= N; ++JJ)
    {
        RA[JJ] = JJ * DE;
        std::cout << std::endl << "LAMBDA = " << RA[JJ] << std::endl;
        for (int J = 0; J < N; ++J)
        {
            for (int I = 0; I < N; ++I)
            {
                A[I][J] = B[I][J];
            }
            A[J][J] -= RA[JJ];
        }
        DETMNT(N, A, S);
        FF[JJ] = S;
    }

    for (int I = 0; I <= N; ++I)
    {
        DF[I][0] = FF[I];
    }

    int M = N;
    for (int J = 1; J <= N; ++J)
    {
        M = M - 1;
        for (int I = 0; I <= M; ++I)
        {
            DF[I][J] = DF[I + 1][J - 1] - DF[I][J - 1];
        }
    }

    std::cout << std::endl << "TABLA DE DIFERENCIAS PARA LOS DETERMINANTES" << std::endl;
    for (int I = 0; I <= N; ++I)
    {
        // std::cout << std::fixed << std::setprecision(4);
        std::cout << RA[I] /*<< std::fixed << std::setprecision(2)*/;
        for (int J = 0; J <= N - I; ++J)
        {
            //std::cout << std::fixed << std::setprecision(5) << std::scientific;
            std::cout << std::setw(15) << DF[I][J];
        }
        std::cout << std::endl;
    }
    std::cout << std::fixed << std::setprecision(7);
    std::cout << std::endl << "COEFICIENTES DE MARKOV" << std::endl;
    for (int I = 0; I <= N; ++I)
    {
        CC[I] = 0;
        MV[I] = 0;
    }

    MV[1] = 1;
    CC[0] = DF[0][0];
    CC[1] = DF[0][1];
    for (int K = 2; K <= N; ++K)
    {
        for (int L = K; L >= 1; --L)
        {
            MV[L] = (MV[L - 1] - (K - 1) * MV[L]) / K;
            CC[L] += MV[L] * DF[0][K];
        }
        for (int L = 1; L <= K; ++L)
        {
            std::cout << std::setw(12) << MV[L];
        }
        std::cout << std::endl;
    }

    std::cout << std::fixed << std::setprecision(4);
    std::cout << std::endl << "- - - RESULTADO FINAL - - -" << std::endl;
    std::cout << "POTENCIA, COEFICIENTES" << std::endl;
    for (int I = 0; I <= N; ++I)
    {
        CC[I] /= std::pow(DE, I);
        std::cout << std::setw(6) << I << std::setw(18) << CC[I] << std::endl;
    }

    std::cout << std::endl << "--------------------------------------" << std::endl;

    int K;
    return 0;
}