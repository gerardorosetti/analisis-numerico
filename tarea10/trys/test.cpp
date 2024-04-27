#include <iostream>
using namespace std;

// Función que representa la ecuación diferencial del enfriamiento del pastel
double dTdt(double T, double k, double Tambiente) {
    return -k * (T - Tambiente);
}

int main() {
    // Condiciones iniciales
    double T = 70; // Temperatura inicial del pastel
    double t = 0; // Tiempo inicial
    double Tambiente = 15; // Temperatura ambiente
    double k = 0.1; // Constante de enfriamiento (valor de ejemplo)

    // Paso de tiempo
    double dt = 5; // Incremento de tiempo (5 minutos)

    // Calculando la temperatura del pastel a los 5 minutos
    T = T + dTdt(T, k, Tambiente) * dt;

    // Imprimiendo la temperatura del pastel a los 5 minutos
    cout << "Temperatura del pastel a los 5 minutos: " << T << " F" << endl;

    // Regresando al horno (cambiando la temperatura ambiente)
    Tambiente = 70; // Nueva temperatura ambiente

    // Calculando la temperatura del pastel a los 10 minutos
    T = T + dTdt(T, k, Tambiente) * dt;

    // Imprimiendo la temperatura del pastel a los 10 minutos
    cout << "Temperatura del pastel a los 10 minutos: " << T << " F" << endl;

    // Calculando la temperatura del pastel a los 20 minutos
    T = T + dTdt(T, k, Tambiente) * dt;

    // Imprimiendo la temperatura del pastel a los 20 minutos
    cout << "Temperatura del pastel a los 20 minutos: " << T << " F" << endl;

    return 0;
}