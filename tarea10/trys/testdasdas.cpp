#include <iostream>
#include <cmath>
using namespace std;

const double Beta = (1.0/5.0) * log(6.0/11.0);
//const double tolerance = 1e-6;
const double tolerance = 0.001;

double f(double t, double T) {
    return Beta * (T - 15.0);
}

double shoot(double t) {
    double T0 = 70.0;  // Valor inicial de T
    double T1 = t;     // Valor de T(5)
    double h = 0.0001;  // Tamaño de paso

    while (abs(T1 - 45.0) > tolerance) {
        double T2 = T0 + h * f(0, T0);
        T1 = T0 + h * f(5, T2);
        T0 = T2;
        //cout << "val : " << abs(T1 - 45.0) << endl;
    }

    return T1;
}

int main() {
    double T5 = shoot(5);
    double T10 = (T5 - 45) * (10.0 - 5.0) / (5.0 - 0.0) + 45;  // Interpolación lineal

    cout << "El valor de T(10) es: " << T10 << endl;

    return 0;
}