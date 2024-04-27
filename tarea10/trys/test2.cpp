#include <iostream>
#include <cmath>
using namespace std;

class Pastel {
private:
    double temperatura;
    double pasoTiempo;
    double ambiente;

public:
    Pastel(double tempInicial, double paso, double tempAmbiente) {
        temperatura = tempInicial;
        pasoTiempo = paso;
        ambiente = tempAmbiente;
    }

    double coeficienteTransferencia() {
        return (1.0/5.0) * log(6.0/11.0);
    }

    void calcularTemperatura(int pasos) {
        for (int i = 0; i < pasos; i++) {
            temperatura += coeficienteTransferencia() * (temperatura - ambiente) * pasoTiempo;
        }
    }

    double obtenerTemperatura() {
        return temperatura;
    }
};

int main() {
    // Condiciones iniciales y de frontera
    double temperaturaInicial = 70.0; // Temperatura inicial del pastel
    double temperaturaAmbiente = 15.0; // Temperatura ambiente
    double tiempoTotal = 0.3333; // 20 minutos (0.3333 horas)
    double pasoTiempo = 0.08333; // 5 minutos (0.08333 horas)
    int numPasos = tiempoTotal / pasoTiempo; // Número de pasos de tiempo

    // Crear objeto de la clase Pastel
    Pastel miPastel(temperaturaInicial, pasoTiempo, temperaturaAmbiente);

    // Calcular la temperatura del pastel en cada paso de tiempo
    miPastel.calcularTemperatura(numPasos);

    // Obtener la temperatura del pastel a las 9:20 am
    double temperatura920am = miPastel.obtenerTemperatura();

    // Mostrar la temperatura del pastel a las 9:20 am
    cout << "La temperatura del pastel a las 9:20 am es: " << temperatura920am << " grados F" << endl;

    return 0;
}