#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

const short MAX_POINTS = 10;
const short MAX_DERIVATIVES = 11;

float function(float x)
{
    // return pow(x, 3);
    // return sin(x);
    // return log(1 + x)/x;
    return tan(x);
}

void gauss(float** A, int N)
{
    int NM = N - 1;
    int N1 = N + 1;
    for (int I = 1; I <= NM; ++I)
    {
        int IPV = I;
        int I1 = I + 1;
        for (int J = I1; J <= N; ++J)
        {
            if (std::abs(A[IPV][I]) < std::abs(A[J][I])) IPV = J;
        }
        if (IPV != I)
        {
            for (int JC = 1; JC <= N1; ++JC)
            {
                float TM = A[I][JC];
                A[I][JC] = A[IPV][JC];
                A[IPV][JC] = TM;
            }
        }
        for (int JR = I1; JR <= N; ++JR)
        {
            if (A[JR][I] == 0) continue;
            if (A[I][I] == 0)
            {
                std::cout<< I << JR ;
                for(int i = 0; i < 3; ++i )
                {
                    std::cout<< A[I][i];
                }
            }

            float R = A[JR][I] / A[I][I];
            for (int KC = I1; KC <= N1; ++KC)
            {
                A[JR][KC] -= R * A[I][KC];
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
    float EL[MAX_POINTS + 3], B[MAX_POINTS + 3][MAX_DERIVATIVES + 3], C[MAX_POINTS + 3], CF[MAX_DERIVATIVES + 3];
    float FF, F, Z;

    float **A = new float*[MAX_POINTS + 3];
    for (size_t i = 0; i < MAX_POINTS + 3; i++)
    {
        A[i] = new float[MAX_DERIVATIVES + 3];
    }

    std::cout << "Calculo de Aproximaciones por Diferencias" << std::endl << std::endl;
    std::cout << "Ingrese el Numero de Puntos: ";
    std::cin >> KM;
    if (KM > MAX_POINTS)
    {
        std::cout << "El numero de puntos no puede ser mayor a 10, intente nuevamente" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "\nNumero de Puntos en la Reticula\n" << std::endl;
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
    std::cout << "\n-------------------------------------------" << std::endl;
    std::cout << "Esquema de Diferencias" << std::endl;
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
    std::cout << "-------------------------------------------" << std::endl << std::endl;

    float result = 0;
    float H = 0.05;
    float point = 2;
    for (int K = 1; K <= KM; ++K)
    {
        float FINV = 1.0 / F;
        result += (CF[K] / (FINV * pow(H,KDR))) * function(point + EL[K] * H);
    }

    std::cout << "Mostrando Ejemplo con los Valores:\nH = " << H << "\nPunto: " << point << std::endl;
    std::cout << "Resultado: " << result << std::endl;

    for (size_t i = 0; i < MAX_POINTS + 3; ++i)
    {
        delete[] A[i];
    }
    delete[] A;

    return 0;
}