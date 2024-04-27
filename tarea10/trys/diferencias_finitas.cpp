#include <iostream>
#include <vector>
#include <cmath>

// Definir las constantes y parámetros
const double T0 = 70;  // Condición inicial T(0)
const double T5 = 45;  // Condición de frontera T(5)
const double Beta = 1.0/5.0 * log(6.0/11.0);  // Parámetro Beta

const double dt = 0.01;  // Paso de tiempo
const double dx = 1.0;   // Paso espacial
const int N = 500;       // Número de puntos en el dominio espacial

const double T_initial = 70.0;  // Temperatura inicial en todos los puntos

// Función para resolver la EDO usando diferencias finitas
void solveHeatEquation() {
    // Crear un vector para almacenar la temperatura en cada punto en el tiempo actual
    std::vector<double> T(N, T_initial);
    
    // Iterar en el tiempo
    for (double t = 0; t <= 5; t += dt) {
        // Crear un vector temporal para almacenar la temperatura en el siguiente paso de tiempo
        std::vector<double> T_next(N, 0.0);
        
        // Aplicar el esquema de diferencias finitas para cada punto espacial
        for (int i = 1; i < N - 1; i++) {
            T_next[i] = T[i] + Beta * dt * (T[i - 1] - 2 * T[i] + T[i + 1]) / (dx * dx);
        }
        
        // Actualizar los valores de temperatura
        T = T_next;
    }
    
    // Imprimir el resultado final
    std::cout << "La temperatura final en el dominio es:\n";
    for (int i = 0; i < N; i++) {
        std::cout << "T(" << i*dx << ") = " << T[i] << "\n";
    }
}

int main() {
    solveHeatEquation();
    
    return 0;
}