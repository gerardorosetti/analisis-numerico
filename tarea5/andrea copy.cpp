#include <iostream>
#include <cmath>
using namespace std;

const int MAX_POINTS = 10;
const int MAX_DERIVATIVES = 11;

int N, KM, KDR, KN;
float A[10][11], EL[10], B[10][11], C[10], CF[11];
float FF, F, Z;
float MT = 6;

void gauss() {
    int NM = N - 1;
    int N1 = N + 1;
    for (int I = 11; I <= NM; ++I) {
        int IPV = I;
        int I1 = I + 1;
        for (int J = I1; J <= N; ++J) {
            if (abs(A[IPV][I]) < abs(A[J][I])) IPV = J;
        }
        if (IPV != I) {
            for (int JC = 1; JC <= N1; ++JC) {
                float TM = A[I][JC];
                A[I][JC] = A[IPV][JC];
                A[IPV][JC] = TM;
            }
        }
        for (int JR = I1; JR <= N; ++JR) {
            if (A[JR][I] == 0) continue;
            if (A[I][I] == 0)
            {
                cout<< I << JR ;
                for(int i = 0; i < 3; ++i )
                {
                    cout<< A[I][i];
                }
            }

            float R = A[JR][I] / A[I][I];
            for (int KC = I1; KC <= N1; ++KC) {
                A[JR][KC] -= R * A[I][KC];
            }
        }
    }
    if (A[N][N] == 0) {
        cout << "La matriz es singular" << endl;
        return;
    }
    A[N][N+1] /= A[N][N];
    for (int NV = NM; NV > 0; --NV) {
        float VA = A[NV][N+1];
        float NV1 = NV + 1;
        for (int K = NV1; K <= N; ++K) {
            VA -= A[NV][K] * A[K][N+1];
        }
        A[NV][N+1] = VA / A[NV][NV];
    }
}

int main()
{
    cout << "CSL/F5 -1 CALCULO DE APROXIMACIONES POE DIFERENCIAS" << endl << endl;
    cout << "NUMERO DE PUNTOS?" << endl;
    cin >> KM;
    cout << "NUMERO DE PUNTOS EN LA RETICULA?" << endl;
    for (int K = 0; K < KM; ++K) {
        cout << "INDICE DEL PUNTO " << K + 1 << "?" << endl;
        cin >> EL[K];
    }
    cout << "DE EL ORDEN DE LA DERIVADA" << endl;
    cin >> KDR;
    Z = 1.0;

    for (int I = 0; I < KDR; ++I) {
        Z *= static_cast<float>(I);
    }

    for (int K = 0; K < KM + 2; ++K) {
        for (int L = 1; L < KM; ++L) {
            if (K == 1) A[K][L] = 1.0;
            if (K > 1) A[K][L] = pow(EL[L], K-1);
            B[K][L] = A[K][L];
        }
    }
    FF = 1.0;
    for (int K = 0; K < KM; ++K) {
        A[K][KM+1] = 0.0;
        if (K-1 == KDR) A[K][KM+1] = Z;
    }
    N = KM;
    float KMP2 = KM + 2;
    gauss();

    for (int K = 0; K < KM + 2; ++K) {
        C[K] = 0.0;
        for(int L = 0; L < KM; ++L)
        {
            C[K] = C[K] + B[K][L]*A[L][KM+1];
        }
    }
    F = 1000.0;
    for(int K = 0; K < KM; ++K){
        if (A[K][KM+1] == 0) continue;
        if (abs(A[K][KM+1]) < 0.0001) continue;
        float U = abs(A[K][KM+1]);
        if (U < FF) F = U;
    }
    for (int K = 0; K < KM; ++K) {
        CF[K] = A[K][KM+1] / F;
    }
    cout << "ESQUEMA DE DIFERENCIAS" << endl;
    for (int K = 0; K < KM; ++K) {
        float FINV = 1.0 / F;
        cout << "+[" << CF[K] << "/(" << FINV << "" << KDR << ")]  F(" << EL[K] << ")" << endl;
    }
    cout << endl;
    cout << "TERMINO DEL ERROR" << endl;
    for (int K = 0; K < KM + 2; ++K) {
        if (abs(C[K]) < 0.00000001) C[K] = 0;
    }
    float DD = 1.0;
    for (int K = 0; K < KM; ++K) {
        DD *= static_cast<float>(K);
    }
    std::cout << KM << KM+2;
    for (int K = KM ; K < KM + 2; ++K) {
        float CM = -C[K];
        float CPDD = -C[K] / DD;
        int KM1 = K - 1;
        int NH = KM1 - KDR;
        if ((K == KM + 1) && (CM != 0))
        {
            cout << "(" << CM << "/" << DD << ")" << NH << "  F^(" << KM1 << ")" << endl;
        }
        if (K == KM + 2)
        {
            cout << "(" << CM << "/" << DD << ")" << NH << "  F^(" << KM1 << ")" << endl;
        }
        DD *= static_cast<float>(K);
    }
    cout << "----------------------------------" << endl << endl;
    cout << "TERMINAR" << endl;
    return 0;
}