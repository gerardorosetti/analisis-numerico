#include <iostream>
#include <vector>

using namespace std;

// Función para realizar el cálculo de la aproximación por diferencias y los coeficientes
void calcularAproximacionDiferencias(int L, int p, vector<int>& indices, vector<double>& coeficientes) {
    // Realizar los cálculos de la aproximación por diferencias y los coeficientes aquí
    double h = 1.0; // Suponiendo que el intervalo de separación es 1, según la descripción proporcionada

    for (int k = 0; k < L; k++) {
        coeficientes[k] = 0.0;
        for (int i = 0; i < L; i++) {
            if (i != k) {
                double producto = 1.0;
                for (int j = 0; j < L; j++) {
                    if (j != k && j != i) {
                        producto *= (indices[k] - indices[j]);
                    }
                }
                coeficientes[k] += 1.0 / (indices[k] - indices[i]) * producto;
            }
        }
    }

    // Calcular el término del error para k > L
    double errorTerm = 0.0; // Cálculo del término del error para k > L

    // En este punto, los coeficientes de la aproximación por diferencias se calculan y se almacenan en el vector coeficientes
}

void eliminacionGaussiana(vector<vector<double>>& A, vector<double>& b) {
    int n = A.size();

    for (int i = 0; i < n; i++) {
        // Pivoteo parcial
        int maxRow = i;
        for (int j = i + 1; j < n; j++) {
            if (abs(A[j][i]) > abs(A[maxRow][i])) {
                maxRow = j;
            }
        }
        swap(A[i], A[maxRow]);
        swap(b[i], b[maxRow]);

        // Eliminación hacia adelante
        for (int j = i + 1; j < n; j++) {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k < n; k++) {
                A[j][k] -= factor * A[i][k];
            }
            b[j] -= factor * b[i];
        }
    }

    // Sustitución hacia atrás
    vector<double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }

    // La solución de las ecuaciones lineales se guarda en el vector x
}


int main() {
    int L; // Número de puntos en la retícula
    int p; // Orden de la derivada a aproximar

    // Pedir al usuario el número de puntos en la retícula
    cout << "Ingrese el número de puntos en la retícula (máximo 10): ";
    cin >> L;

    // Validar que el número de puntos esté dentro del rango permitido
    if (L < 1 || L > 10) {
        cout << "El número de puntos en la retícula debe estar entre 1 y 10. Por favor, inténtelo de nuevo." << endl;
        return 1; // Salir del programa con código de error
    }

    // Definir los arreglos para almacenar los índices de los puntos de la retícula y los coeficientes
    vector<int> indices(L);
    vector<double> coeficientes(L);

    // Pedir al usuario los índices de los puntos de la retícula
    cout << "Ingrese los índices de los puntos de la retícula:" << endl;
    for (int i = 0; i < L; i++) {
        cout << "Punto " << i + 1 << ": ";
        cin >> indices[i];
    }

    // Pedir al usuario el orden de la derivada a aproximar
    cout << "Ingrese el orden de la derivada que se desea aproximar: ";
    cin >> p;

    // Realizar el cálculo de la aproximación por diferencias y los coeficientes
    calcularAproximacionDiferencias(L, p, indices, coeficientes);

    cout << "\nindices:\n";
    for (auto i: indices)
    {
        cout << i << endl;
    }
    cout << "\nend_indices:\n";

    cout << "coeficientes:\n";
    for (auto i: coeficientes)
    {
        cout << i << endl;
    }
    cout << "end_coeficientes:\n";


    vector<vector<double>> A(L, vector<double>(L, 0.0));
    // for (int i = 0; i < L; i++) {
    //     for (int j = 0; j < L; j++) {
    //         // Asignar los valores correspondientes a la matriz A según la aproximación por diferencias
    //         // Dependiendo de la naturaleza específica de la aproximación, se asignarán los valores correspondientes
    //         A[i][j] = /* valor correspondiente basado en la aproximación por diferencias y los índices */;
    //     }
    // }

// Llenar la matriz A usando una aproximación por diferencias finitas hacia adelante de primer orden para la primera derivada
for (int i = 0; i < L; i++) {
    for (int j = 0; j < L; j++) {
        if (i == j) {
            A[i][j] = -1.0; // Coeficiente en la posición (i, i)
        } else if (j == i + 1) {
            A[i][j] = 1.0; // Coeficiente en la posición (i, i+1)
        } else {
            A[i][j] = 0.0; // Otros coeficientes son cero
        }
    }
}


    // Resolver las ecuaciones lineales mediante el método de eliminación gaussiana
    eliminacionGaussiana(A, coeficientes);

    // Mostrar los coeficientes de la aproximación por diferencias como salida
    cout << "Los coeficientes de la aproximación por diferencias son:" << endl;
    for (int i = 0; i < L; i++) {
        cout << "Coeficiente " << i + 1 << ": " << coeficientes[i] << endl;
    }

// Imprimir el esquema de diferencias
float FF =1;
cout << "ESQUEMA DE DIFERENCIAS" << endl;
for (int K = 0; K < L; ++K) {
    float FINV = 1.0 / FF;
    cout << "+[" << coeficientes[K] << "/(" << FINV << "**" << p << ")]F(" << indices[K] << ")" << endl;
}
cout << endl;

// Imprimir término del error
cout << "TERMINO DEL ERROR" << endl;
for (int K = 0; K <= L + 1; ++K) {
    if (abs(coeficientes[K]) < 0.00000001) coeficientes[K] = 0;
}
float DD = 1.0;
for (int K = 1; K <= L; ++K) {
    DD *= static_cast<float>(K);
}
for (int K = L; K <= L + 1; ++K) {
    float CM = -coeficientes[K];
    float CPDD = -coeficientes[K] / DD;
    int L1 = K - 1;
    int NH = L1 - p;
    if ((K == L + 1) && (CM != 0)) {
        cout << "(" << CM << "/" << DD << ")**" << NH << "F^(" << L1 << ")" << endl;
    }
    if (K == L + 2) {
        cout << "(" << CM << "/" << DD << ")**" << NH << "F^(" << L1 << ")" << endl;
    }
    DD *= static_cast<float>(K);
}


    return 0;
}
