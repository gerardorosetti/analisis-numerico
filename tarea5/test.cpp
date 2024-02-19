#include <iostream>
#include <cmath>
using namespace std;

const int MAX_POINTS = 10;
const int MAX_DERIVATIVES = 11;

int N, KM, KDR, KN;
float A[MAX_POINTS + 2][MAX_POINTS], EL[MAX_POINTS], B[MAX_POINTS + 2][MAX_POINTS], C[MAX_POINTS], CF[MAX_POINTS];
float FF, F, Z;

void gauss() {
    int NM = N - 1;
    int N1 = N + 1;
    for (int I = 0; I < NM; ++I) {
        int IPV = I;
        int I1 = I + 1;
        for (int J = I1; J < N; ++J) {
            if (abs(A[IPV][I]) < abs(A[J][I])) IPV = J;
        }
        if (IPV != I) {
            for (int JC = 0; JC < N1; ++JC) {
                float TM = A[I][JC];
                A[I][JC] = A[IPV][JC];
                A[IPV][JC] = TM;
            }
        }
        for (int JR = I1; JR < N; ++JR) {
            if (A[JR][I] == 0) continue;
            float R = A[JR][I] / A[I][I];
            for (int KC = I1; KC < N1; ++KC) {
                A[JR][KC] -= R * A[I][KC];
            }
        }
    }
    if (A[N - 1][N - 1] == 0) {
        cout << "La matriz es singular" << endl;
        exit(1);
    }
    A[N - 1][N] /= A[N - 1][N - 1];
    for (int NV = NM - 1; NV >= 0; --NV) {
        float VA = A[NV][N];
        for (int K = NV + 1; K < N; ++K) {
            VA -= A[NV][K] * A[K][N];
        }
        A[NV][N] = VA / A[NV][NV];
    }
}

int main() {
    cout << "CSL/F5 -1 CALCULO DE APROXIMACIONES POE DIFERENCIAS" << endl << endl;
    int KK;
    while (true) {
        cout << "NUMERO DE PUNTOS?" << endl;
        cin >> KM;
        if (KM > 2 || KM <= 10) break;
        cout << "ENTRADA NO VALIDA. POR FAVOR REPITA LA ENTRADA" << endl;
    }
    cout << "NUMERO DE PUNTOS EN LA RETICULA?" << endl;
    for (int K = 0; K < KM; ++K) {
        cout << "INDICE DEL PUNTO " << K + 1 << "?" << endl;
        cin >> EL[K];
    }
    cout << "DE EL ORDEN DE LA DERIVADA" << endl;
    cin >> KDR;
    Z = 1.0;
    for (int I = 1; I <= KDR; ++I) {
        Z *= static_cast<float>(I);
    }
    for (int K = 0; K <= KM + 1; ++K) {
        for (int L = 0; L < KM; ++L) {
            if (K == L + 1) A[K][L] = 1.0;
            if (K > 0) A[K][L] = pow(EL[L], K);
            B[K][L] = A[K][L];
        }
    }
    for (int K = 0; K < KM; ++K) {
        A[K][KM] = 0.0;
        if (K == KDR - 1) A[K][KM] = Z;
    }
    N = KM;
    gauss();
    FF = 1;
    for (int K = 0; K < KM; ++K) {
        if (A[K][KM] == 0) continue;
        if (abs(A[K][KM]) < 0.0001) continue;
        float U = abs(A[K][KM]);
        if (U < FF) FF = U;
    }
    for (int K = 0; K < KM; ++K) {
        CF[K] = A[K][KM] / FF;
    }
    cout << "ESQUEMA DE DIFERENCIAS" << endl;
    for (int K = 0; K < KM; ++K) {
        float FINV = 1.0 / FF;
        cout << "+[" << CF[K] << "/(" << FINV << "**" << KDR << ")]F(" << EL[K] << ")" << endl;
    }
    cout << endl;
    cout << "TERMINO DEL ERROR" << endl;
    for (int K = 0; K <= KM + 1; ++K) {
        if (abs(C[K]) < 0.00000001) C[K] = 0;
    }
    float DD = 1.0;
    for (int K = 1; K <= KM; ++K) {
        DD *= static_cast<float>(K);
    }
    for (int K = KM; K <= KM + 1; ++K) {
        float CM = -C[K];
        float CPDD = -C[K] / DD;
        int KM1 = K - 1;
        int NH = KM1 - KDR;
        if ((K == KM + 1) && (CM != 0)) {
            cout << "(" << CM << "/" << DD << ")**" << NH << "F^(" << KM1 << ")" << endl;
        }
        if (K == KM + 2) {
            cout << "(" << CM << "/" << DD << ")**" << NH << "F^(" << KM1 << ")" << endl;
        }
        DD *= static_cast<float>(K);
    }
    cout << "----------------------------------" << endl << endl;
    cout << "OPRIMA 1 PARA CONTINUAR 00 PARA TERMINAR" << endl;
    cin >> KK;
    if (KK != 1) return 0;
    cout << endl;
    return 0;
}