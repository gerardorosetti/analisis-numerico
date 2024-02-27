// Función para calcular el determinante de una matriz 2x2
double calcularDeterminante2x2(std::vector<std::vector<double>> matriz) {
    return matriz[0][0] * matriz[1][1] - matriz[0][1] * matriz[1][0];
}

// Función para calcular el determinante de una matriz 3x3
double calcularDeterminante3x3(std::vector<std::vector<double>> matriz) {
    int det = 0;
    for (int i = 0; i < 3; i++) {
        det += matriz[0][i] * (matriz[1][(i + 1) % 3] * matriz[2][(i + 2) % 3] - matriz[1][(i + 2) % 3] * matriz[2][(i + 1) % 3]);
    }
    return det;
}

double calcularDeterminante(std::vector<std::vector<double>> matriz) {
    int size = matriz.size();
    if (size == 2) {
        return calcularDeterminante2x2(matriz);
    } else if (size == 3) {
        return calcularDeterminante3x3(matriz);
    } else {
        double det = 0;
        for (int i = 0; i < size; i++) {
            double cofactor = std::pow(-1, i) * matriz[0][i] * calcularDeterminante(matriz);
            det += cofactor;
        }
        return det;
    }
}