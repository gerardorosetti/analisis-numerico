#include <iostream>
#include <cmath>

int main() {
    // Cálculo de desbordamiento
    double x = 1.0;
    while (std::isnormal(x)) {
        x = x * 2;
    }
    std::cout << "El desbordamiento ocurre alrededor de: " << x << std::endl;

    // Cálculo de precisión
    double epsilon = 1.0;
    while (1.0 + epsilon != 1.0) {
        epsilon = epsilon / 2.0;
    }
    epsilon = 2.0 * epsilon;
    std::cout << "La precisión de la máquina es aproximadamente: " << epsilon <<  std::endl;

    return 0;
}