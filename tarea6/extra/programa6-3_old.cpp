#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

void PIVOT(int N, std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& EL, int J, std::vector<int>& IP, int& IPC) {
    // double T = 0;
    // int JJ;
    // for (int K = J; K < N; K++) {
    //     if (std::abs(A[K][J]) <= T) continue;
    //     JJ = K;
    //     T = std::abs(A[K][J]);
    // }
    // std::cout << "here" << std::endl;
    int JJ = J;
    double T = std::abs(A[J][J]);
    for (int i = J + 1; i < N; ++i) {
        if (std::abs(A[i][J]) > T) {
            T = std::abs(A[i][J]);
            JJ = i;
        }
    }

    if (JJ == J) return;
    IPC = IPC + 1;
    for (int M = 0; M < N; M++) {
        double tempA = A[J][M];
        A[J][M] = A[JJ][M];
        A[JJ][M] = tempA;
        double tempEL = EL[J][M];
        EL[J][M] = EL[JJ][M];
        EL[JJ][M] = tempEL;
    }
    int IT = IP[J];
    IP[J] = IP[JJ];
    IP[JJ] = IT;
    std::cout << "NUMERO DE PERMUTACIONES = " << IPC << std::endl;
}

// void PIVOT(int N, std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& EL, int J, std::vector<int>& IP, int& IPC)
// {
//     float T = 0;
//     int JJ = J;
//     for (int K = J; K < N; ++K)
//     {
//         if (std::abs(A[K][J]) > T)
//         {
//             JJ = K;
//             T = std::abs(A[K][J]);
//         }
//     }
//     if (JJ == J) return;

//     IPC += 1;
//     for (int M = 0; M < N; ++M)
//     {
//         std::swap(A[J][M], A[JJ][M]);
//         std::swap(EL[J][M], EL[JJ][M]);
//     }
//     std::swap(IP[J], IP[JJ]);

//     std::cout << "\nNumero de Pivoteos = " << IPC << std::endl;
// }

int main()
{
    const int N = 3;
    std::vector<std::vector<double>> A(N, std::vector<double>(N, 0));
    std::vector<std::vector<double>> EL(N, std::vector<double>(N, 0));
    std::vector<int> IP(N, 0);
    float L;
    int NP, IPC = 1;
    int space = 10;

    A = {{2, 1, -3}, {-1, 3, 2}, {3, 1, -3}};
    // A = {{2, -1, 0}, {-1, 2, -1}, {0, -1, 2}};
    // A = {{2, -1, 0}, {-3, 4, -1}, {0, -1, 2}};

    std::cout << std::fixed << std::setprecision(5);

    std::cout << "\nN = " << N << std::endl;
    std::cout << "\n- - - - - - - - - - - - - - - -" << std::endl;
    std::cout << "Matriz Original:" << std::endl << std::endl;
    for (int I = 0; I < N; ++I)
    {
        for (int J = 0; J < N; ++J)
        {
            std::cout << std::setw(space) << A[I][J];
        }
        std::cout << std::endl;
    }
    std::cout << "- - - - - - - - - - - - - - - -" << std::endl;

    std::cout << "\nSe se Desea el Pivoteo, Oprima 1; de lo Contrario Oprima 0: ";
    std::cin >> NP;

    for (int I = 0; I < N; ++I)
    {
        IP[I] = I + 1;
        for (int J = 0; J < N; ++J)
        {
            EL[I][J] = 0;
        }
    }

    int J = 1;
    if (NP == 1) PIVOT(N, A, EL, J, IP, IPC);

    for (J = 0; J < N; ++J)
    {
        EL[0][J] = A[0][J];
    }

    for (int I = 1; I < N; ++I)
    {
        EL[I][0] = A[I][0] / EL[0][0];
    }

    for (int M = 1; M < N; ++M)
    {
        if (NP == 1) PIVOT(N, A, EL, M, IP, IPC);
        for (J = M; J < N; ++J)
        {
            float S = 0;
            for (int K = 0; K < M; ++K)
            {
                S += EL[M][K] * EL[K][J];
            }
            EL[M][J] = A[M][J] - S;
        }
        for (int I = M + 1; I < N; ++I)
        {
            float S = 0;
            for (int K = 0; K < M; ++K)
            {
                S += EL[I][K] * EL[K][M];
            }
            EL[I][M] = (A[I][M] - S) / EL[M][M];
        }
    }

    std::cout << "\nPermutacion: ";
    for (int I = 0; I < N; ++I)
    {
        std::cout << IP[I] << " ";
    }
    std::cout << std::endl;

    std::cout << "\n- - - - - - - - - - - - - - - -" << std::endl;
    std::cout << "Matrices LU en Forma Compacta:" << std::endl << std::endl;
    for (int I = 0; I < N; ++I)
    {
        for (int M = 0; M < N; ++M)
        {
            std::cout << std::setw(space) << EL[I][M] ;
        }
        std::cout << std::endl;
    }

    float DE = 1;
    for (int I = 0; I < N; ++I)
    {
        DE *= EL[I][I];
    }
    if (IPC == static_cast<int>(IPC / 2) * 2) DE = -DE;
    std::cout << "\nDeterminante = " << DE << std::endl;
    std::cout << "- - - - - - - - - - - - - - - -" << std::endl;

    return 0;
}