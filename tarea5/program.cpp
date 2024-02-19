#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

const short MAX_POINTS = 10;
const short MAX_DERIVATIVES = 11;

void gauss(std::vector<std::vector<float>>& A, int N)
{
    int NM = N - 1;
    int N1 = N + 1;
    for (int i = 1; i <= NM; ++i)
    {
        int IPV = i;
        int i1 = i + 1;
        for (int j = i1; j <= N; ++j)
        {
            if (std::abs(A[IPV][i]) < std::abs(A[j][i])) IPV = j;
        }
        if (IPV != i)
        {
            for (int JC = 1; JC <= N1; ++JC)
            {
                float TM = A[i][JC];
                A[i][JC] = A[IPV][JC];
                A[IPV][JC] = TM;
            }
        }
        for (int JR = i1; JR <= N; ++JR)
        {
            if (A[JR][i] == 0) continue;
            if (A[i][i] == 0)
            {
                std::cout<< i << JR ;
                for(int g = 0; g < 3; ++g)
                {
                    std::cout<< A[i][g];
                }
            }

            float R = A[JR][i] / A[i][i];
            for (int KC = i1; KC <= N1; ++KC)
            {
                A[JR][KC] -= R * A[i][KC];
            }
        }
    }
    if (A[N][N] == 0)
    {
        std::cout << "La matriz es singular" << std::endl;
        return;
    }
    A[N][N+1] /= A[N][N];
    for (int NV = NM; NV > 0; --NV)
    {
        float VA = A[NV][N+1];
        float NV1 = NV + 1;
        for (int K = NV1; K <= N; ++K)
        {
            VA -= A[NV][K] * A[K][N+1];
        }
        A[NV][N+1] = VA / A[NV][NV];
    }
}

int main()
{
    int N, KM, KDR, KN;
    float EL[MAX_POINTS + 1], B[MAX_POINTS + 1][MAX_DERIVATIVES + 1], C[MAX_POINTS + 1], CF[MAX_DERIVATIVES + 1];
    std::vector<std::vector<float>> A(MAX_POINTS + 1, std::vector<float>(MAX_DERIVATIVES + 1, 0));
    float FF, F, Z;

    std::cout << "Calculo de Aproximaciones por Diferencias" << std::endl << std::endl;
    std::cout << "Ingrese el Numero de Puntos: ";
    std::cin >> KM;
    std::cout << "\nNUMERO DE PUNTOS EN LA RETICULA?\n" << std::endl;
    for (int K = 1; K <= KM; ++K)
    {
        std::cout << "Indice del Punto " << K << ": ";
        std::cin >> EL[K];
    }
    std::cout << "\nIngrese el Numero de Orden de la Derivada: ";
    std::cin >> KDR;
    Z = 1.0;

    for (int I = 1; I <= KDR; ++I)
    {
        Z *= static_cast<float>(I);
    }

    for (int K = 1; K <= KM + 2; ++K)
    {
        for (int L = 1; L <= KM; ++L)
        {
            if (K == 1) A[K][L] = 1.0;
            if (K > 1) A[K][L] = pow(EL[L], K-1);
            B[K][L] = A[K][L];
        }
    }
    FF = 1.0;
    for (int K = 1; K <= KM; ++K)
    {
        A[K][KM+1] = 0.0;
        if (K-1 == KDR) A[K][KM+1] = Z;
    }
    N = KM;
    float KMP2 = KM + 2;

    gauss(A, N);

    for (int K = 1; K <= KM + 2; ++K)
    {
        C[K] = 0.0;
        for(int L = 1; L <= KM; ++L)
        {
            C[K] = C[K] + B[K][L]*A[L][KM+1];
        }
    }
    F = 1000.0;
    for(int K = 1; K <= KM; ++K){
        if (A[K][KM+1] == 0) continue;
        if (std::abs(A[K][KM+1]) < 0.0001) continue;
        float U = std::abs(A[K][KM+1]);
        if (U < FF) F = U;
    }
    for (int K = 1; K <= KM; ++K)
    {
        CF[K] = A[K][KM+1] / F;
    }
    std::cout << "\nEsquema de Diferencias" << std::endl;
    std::cout << std::fixed << std::setprecision(5);
    for (int K = 1; K <= KM; ++K)
    {
        float FINV = 1.0 / F;
        std::cout << "+[ " << CF[K] << "/(" << FINV << " H**" << KDR << ")]  F(" << EL[K] << "H)" << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Termino del Error" << std::endl;
    for (int K = 1; K <= KM + 2; ++K)
    {
        if (std::abs(C[K]) < 0.00000001) C[K] = 0;
    }
    float DD = 1.0;
    for (int K = 1; K <= KM; ++K)
    {
        DD *= static_cast<float>(K);
    }
    for (int K = KM + 1; K <= KM + 2; ++K)
    {
        float CM = -C[K];
        float CPDD = -C[K] / DD;
        int KM1 = K - 1;
        int NH = KM1 - KDR;
        if ((K == KM + 1) && (CM != 0))
        {
            std::cout << "(" << CM << "/" << DD << ")H**" << NH << "  F^(" << KM1 << ")" << std::endl;
        }
        if (K == KM + 2)
        {
            std::cout << "(" << CM << "/" << DD << ")H**" << NH << "  F^(" << KM1 << ")" << std::endl;
        }
        DD *= static_cast<float>(K);
    }
    std::cout << "----------------------------------" << std::endl << std::endl;
    std::cout << "TERMINAR" << std::endl;
    return EXIT_SUCCESS;
}