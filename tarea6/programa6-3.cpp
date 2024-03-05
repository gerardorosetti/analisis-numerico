#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

void luDecomposition(std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& L, std::vector<std::vector<double>>& U, std::vector<int>& P, bool pivot)
{
    int n = A.size();

    L = std::vector<std::vector<double>>(n, std::vector<double>(n, 0.0));
    U = std::vector<std::vector<double>>(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i)
    {
        L[i][i] = 1.0;
        for (int j = 0; j < n; ++j)
        {
            U[i][j] = A[i][j];
        }
    }

    P = std::vector<int>(n);
    for (int i = 0; i < n; ++i)
    {
        P[i] = i;
    }

    for (int k = 0; k < n - 1; ++k)
    {
        int maxIndex = k;
        double maxVal = std::abs(U[k][k]);
        for (int i = k + 1; i < n; ++i)
        {
            if (std::abs(U[i][k]) > maxVal)
            {
                maxVal = std::abs(U[i][k]);
                maxIndex = i;
            }
        }
        if (maxIndex != k && pivot)
        {
            std::swap(P[k], P[maxIndex]);
            std::swap(U[k], U[maxIndex]);
            for (int i = 0; i < k; ++i)
            {
                std::swap(L[k][i], L[maxIndex][i]);
            }
        }
        for (int i = k + 1; i < n; ++i)
        {
            L[i][k] = U[i][k] / U[k][k];
            for (int j = k; j < n; ++j)
            {
                U[i][j] -= L[i][k] * U[k][j];
            }
        }
    }
}

int main()
{
    const int N = 3;
    std::vector<std::vector<double>> A(N, std::vector<double>(N, 0));
    std::vector<std::vector<double>> L, U;
    std::vector<int> P;
    int space = 10;

    A = {{2, 1, -3}, {-1, 3, 2}, {3, 1, -3}};
    // A = {{-1, 3, 2}, {-1, 3, 2}, {3, 1, -3}};
    // A = {{2, -1, 0}, {-1, 2, -1}, {0, -1, 2}};
    // A = {{2, -1, 0}, {-3, 4, -1}, {0, -1, 2}};
    // A = {{0, 1, -3}, {-1, 3, 2}, {3, 1, -3}};

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

    std::cout << "\nSe se Desea el Pivoteo, Oprima 1; de lo Contrario Oprima Cualquier Tecla: ";
    int NP;
    std::cin >> NP;

    luDecomposition(A, L, U, P, NP == 1);

    std::cout << "\nPermutacion: ";
    for (int I = 0; I < N; ++I)
    {
        std::cout << P[I] + 1 << " ";
    }
    std::cout << std::endl;

    std::cout << "\n- - - - - - - - - - - - - - - -" << std::endl;
    std::cout << "Matrices LU en Forma Compacta:" << std::endl << std::endl;
    std::vector<std::vector<double>> LU(N, std::vector<double>(N, 0));
    double det = 1.0;
    for (int I = 0; I < N; ++I)
    {
        for (int M = 0; M < N; ++M)
        {
            if(I > 0 && M <= I)
            {
                std::cout << std::setw(space) << L[I][M];
                LU[I][M] = L[I][M];
            }
            else
            {
                std::cout << std::setw(space) << U[I][M];
                LU[I][M] = U[I][M];
            }
            if (I == M) det *= U[I][M];
        }
        std::cout << std::endl;
    }

    std::cout << "\nDeterminante = " << ((det < 0) ? -det : det) << std::endl;
    std::cout << "- - - - - - - - - - - - - - - -" << std::endl;

    return 0;
}