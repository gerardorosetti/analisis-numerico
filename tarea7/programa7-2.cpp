#include <iostream>
#include <cmath>
#include <iomanip>

int L;

void DETERM(double G[], double A[][11], double X, double &SL)
{
    G[0] = 1;
    if (L == 1) return;
    G[1] = A[1][1] - X;
    if (L == 1) return;
    for (int K = 2; K <= L; K++)
    {
        G[K] = (A[K][K] - X) * G[K - 1] - A[K][K - 1] * A[K][K - 1] * G[K - 2];
    }
    SL = G[L];
}

void BISEC(double G[], double A[][11], double XL, double XH, double &XM)
{
    int KA = 0;
    double YL, YH, DX, XB, YM;
    DETERM(G, A, XL, YL);
    DETERM(G, A, XH, YH);
    while (true)
    {
        KA++;
        if (KA > 99) return;
        DX = XH - XL;
        if (DX < 0.0000001) return;
        if (DX > 1)
        {
            XM = (XL + XH) / 2;
            DETERM(G, A, XM, YM);
            if (YL * YM < 0)
            {
                XH = XM;
                YH = YM;
                continue;
            }
            XL = XM;
            YL = YM;
            continue;
        }
        XB = XM;
        XM = (XL * YH - XH * YL) / (YH - YL);
        DETERM(G, A, XM, YM);
        if (std::abs(XB - XM) < 0.000001) return;
        if (YL * YM < 0)
        {
            XH = XM;
            YH = YM;
            continue;
        }
        XL = XM;
        YL = YM;
    }
}

int main()
{
    // Variables
    double A[11][11], U[11], T[11][11], EI[11][11];
    int N;
    // Inicialización de datos
    N = 4;
    double dataA[4][4] = {{4, 3, 2, 1}, {3, 3, 2, 1}, {2, 2, 2, 1}, {1, 1, 1, 1}};
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            A[i][j] = dataA[i-1][j-1];
        }
    }

    // Reducción de la matriz a forma tridiagonal
    for (int IR = 1; IR <= N - 2; ++IR)
    {
        double S = 0;
        for (int I = 1; I <= N; ++I)
        {
            U[I] = 0;
            if (I > IR + 1) U[I] = A[I][IR];
            if (I > IR) S += A[I][IR] * A[I][IR];
        }
        double W = 1;
        if (A[IR + 1][IR] < 0) W = -1;
        double SSR = sqrt(S);
        double H = S + std::abs(A[IR + 1][IR]) * SSR;
        U[IR + 1] = A[IR + 1][IR] + SSR * W;
        double UAU = 0;
        for (int I = 1; I <= N; ++I)
        {
            for (int J = 1; J <= N; ++J)
            {
                UAU += U[I] * A[I][J] * U[J];
                if ((I <= IR) && (J <= IR))
                {
                    T[I][J] = A[I][J];
                    continue;
                }
                if ((J == IR) && (I >= IR + 2))
                {
                    T[I][J] = 0;
                    continue;
                }
                double B23 = 0;
                for (int K = 1; K <= N; ++K)
                {
                    B23 -= (U[I] * A[K][J] + A[I][K] * U[J]) * U[K];
                }
                T[I][J] = A[I][J] + B23 / H;
            }
        }
        UAU /= H * H;
        for (int I = 1; I <= N; ++I)
        {
            for (int J = 1; J <= N; ++J)
            {
                A[I][J] = T[I][J] + UAU * U[I] * U[J];
                if (std::abs(A[I][J]) < 0.000001) A[I][J] = 0;
            }
        }
    }

    short space = 15;
    std::cout << std::fixed << std::setprecision(5) << std::scientific;

    std::cout << "MATRIZ TRIDIAGONAL RESULTANTE:\n";
    for (int I = 1; I <= N; ++I)
    {
        for (int J = 1; J <= N; ++J)
        {
            std::cout << std::setw(space) << A[I][J];
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    std::cout << "VALORES PROPIOS:\n";
    int KM = N;
    for (L = 1; L <= KM; ++L)
    {
        if (L == 1)
        {
            EI[1][1] = A[1][1];
        }
        else
        {
            for (int J = 1; J <= L; ++J)
            {
                double XL = EI[L - 1][J - 1];
                double XH = EI[L - 1][J];
                int KM = J;
                double XM;
                BISEC(U, A, XL, XH, XM);
                EI[L][J] = XM;
            }
        }
        EI[L][0] = -99;
        EI[L][L + 1] = 99;
        if (L != N)
        {
            std::cout << "\nVALORES PROPIOS DE LA SUBMATRIZ PRINCIPAL " << L << " x " << L  << std::endl;
        }
        else
        {
            std::cout << "\nRESULTADOS FINALES (VALORES PROPIOS DE LA MATRIZ COMPLETA)" << std::endl;
            std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - -"  << std::endl;
        }
        for (int I = 1; I <= L; ++I)
        {
            std::cout << EI[L][I] << " ";
        }
        std::cout  << std::endl;
    }
    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
    return 0;
}