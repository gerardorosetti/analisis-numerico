#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

void gauss(int N, std::vector<std::vector<double>>& A);
double fun(int K, double X);

int main()
{
    const int IN = 6;
    std::vector<double> X = {0.1, 0.4, 0.5, 0.7, 0.7, 0.9};
    std::vector<double> Y = {0.61, 0.92, 0.99, 1.52, 1.47, 2.03};
    std::vector<std::vector<double>> A(11, std::vector<double>(12));
    std::vector<double> GG(IN);
    int LP, NORD, M;

    std::cout << "CSL/FS-1 AJUSTE DE CURVAS MEDIANTE MINIMOS CUADRADOS" << std::endl;
    std::cout << " OPRIMA 0 PARA AJUSTE POLINOMIAL" << std::endl;
    std::cout << " 1 PARA COMBINACION LINEAL" << std::endl;
    std::cin >> LP;

    if (LP == 1)
    {
        std::cout << " DE EL NUMERO DE FUNCIONES EN LA COMBINACION LINEAL" << std::endl;
        std::cout << " (POR EL MOMENTO SOLO SE DISPONE DE CUATRO FUNCIONES)" << std::endl;
        std::cin >> M;
    }
    else
    {
        std::cout << " DE EL ORDEN DEL POLINOMIO" << std::endl;
        std::cin >> NORD;
        M = NORD + 1;
    }

    // Inicializaciond de la matriz
    for (int K = 1; K <= M; ++K)
    {
        for (int J = 1; J <= M + 1; ++J)
        {
            A[K][J] = 0.0;
        }
    }

    if (LP == 1)
    {
        // Combinacion Lineal
        for (int I = 0; I < IN; ++I)
        {
            for (int K = 1; K <= M; ++K)
            {
                double FK = fun(K, X[I]);
                for (int J = 1; J <= M; ++J)
                {
                    A[K][J] += FK * fun(J, X[I]);
                }
                A[K][M + 1] += Y[I] * FK;
            }
        }
    }
    else
    {
        // Ajuste Polinomial
        for (int K = 1; K <= M; ++K)
        {
            for (int I = 0; I < IN; ++I)
            {
                for (int J = 1; J <= M; ++J)
                {
                    int JJ = K - 1 + J - 1;
                    double YY = 1.0;
                    if (JJ != 0) YY = std::pow(X[I], JJ);
                    A[K][J] += YY;
                }
                int JEX = K - 1;
                double YY = 1.0;
                if (JEX != 0) YY = std::pow(X[I], JEX);
                A[K][M + 1] += Y[I] * YY;
            }
        }
    }

    // Solucion
    for (int I = 1; I <= M; ++I)
    {
        for (int J = 1; J <= M + 1; ++J)
        {
            std::cout << std::setw(11) << std::setprecision(4) << std::scientific << A[I][J] << " ";
        }
        std::cout << std::endl;
    }

    gauss(M, A);

    std::cout << "DETERMINACION DE COEFICIENTES" << std::endl;
    if (LP == 1)
    {
        std::cout << "FUNCION" << std::setw(12) << "COEFICIENTE" << std::endl;
    }
    else
    {
        std::cout << "POTENCIA" << std::setw(12) << "COEFICIENTE" << std::endl;
    }
    std::cout << "- - - - - - - - - - -" << std::endl;

    for (int I = 1; I <= M; ++I)
    {
        if (LP == 1)
        {
            std::cout << std::setw(4) << I << std::setw(14) << std::setprecision(6) << std::fixed << A[I][M + 1] << std::endl;
        }
        else
        {
            std::cout << std::setw(4) << I - 1 << std::setw(14) << std::setprecision(6) << std::fixed << A[I][M + 1] << std::endl;
        }
    }

    std::cout << "- - - - - - - - - - -" << std::endl;

    // Evaluaciond del error
    std::cout << "EVALUACION DEL ERROR" << std::endl;
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << std::setw(4) << "I" <<  std::setw(8) << "X(I)" << std::setw(9) << "Y(I)" << std::setw(13) << "POLINOMIO" << std::setw(12) << "DESVIACION" << std::endl;
    std::cout << "----------------------------------------------" << std::endl;
    for (int I = 0; I < IN; ++I)
    {
        GG[I] = 0.0;
        for (int K = 1; K <= M; ++K)
        {
            if (LP == 1)
            {
                GG[I] += A[K][M + 1] * fun(K, X[I]);
            }
            else
            {
                GG[I] += A[K][M + 1] * std::pow(X[I], K - 1);
            }
        }
        std::cout << std::setw(4) << I + 1 << std::setw(8) << std::setprecision(2) << std::fixed << X[I] << std::setw(10) << std::setprecision(5) << Y[I] << std::setw(12) << std::setprecision(7) << GG[I] << std::setw(11) << std::setprecision(6) << Y[I] - GG[I] << std::endl;
    }
    std::cout << "----------------------------------------------" << std::endl;

    return 0;
}

void gauss(int N, std::vector<std::vector<double>>& A)
{
    for (int I = 1; I < N; ++I)
    {
        int IPV = I;
        for (int J = I + 1; J <= N; ++J)
        {
            if (std::abs(A[IPV][I]) < std::abs(A[J][I])) IPV = J;
        }
        if (IPV != I)
        {
            for (int JC = 1; JC <= N + 1; ++JC)
            {
                std::swap(A[I][JC], A[IPV][JC]);
            }
        }
        for (int JR = I + 1; JR <= N; ++JR)
        {
            if (A[JR][I] != 0)
            {
                double R = A[JR][I] / A[I][I];
                for (int KC = I + 1; KC <= N + 1; ++KC)
                {
                    A[JR][KC] -= R * A[I][KC];
                }
            }
        }
    }
    //sustitucion hacia atras
    if (A[N][N] == 0) return;
    A[N][N + 1] /= A[N][N];
    for (int NV = N - 1; NV >= 1; --NV)
    {
        double VA = A[NV][N + 1];
        for (int K = NV + 1; K <= N; ++K)
        {
            VA -= A[NV][K] * A[K][N + 1];
        }
        A[NV][N + 1] = VA / A[NV][NV];
    }
}

double fun(int K, double X)
{
    if (K == 1) return 1;
    if (K == 2) return X;
    if (K == 3) return std::sin(X);
    if (K == 4) return std::exp(X);
    return 0;
}