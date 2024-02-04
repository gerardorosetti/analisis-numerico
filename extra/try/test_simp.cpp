#include <iostream>
#include <cmath>

using namespace std;

// Función a integrar (aquí debes definir la función que desees integrar)
double f(double x)
{
    return pow((1 + std::pow(x/2, 2)), 2) * M_PI;
}

// Método de Simpson para la integración numérica
// double simpson(double a, double b, int n) {
//     double h = (b - a) / n;
//     double sum = f(a) + f(b);

//     for (int i = 1; i < n; i += 2) {
//         double x = a + i * h;
//         sum += 4 * f(x);
//     }

//     for (int i = 2; i < n - 1; i += 2) {
//         double x = a + i * h;
//         sum += 2 * f(x);
//     }

//     return sum * h / 3;
// }

// float simpson(float a, float b, int n)
// {
// 	float h, x[n+1], sum = 0;
// 	int j;
// 	// h = (b-a)/n;
//     h = (b-a)/n;
	
// 	x[0] = a;
	
// 	for(j=1; j<=n; j++)
// 	{
// 		x[j] = a + h*j;
// 	}
	
// 	for(j=1; j<=n/2; j++)
// 	{
// 		sum += f(x[2*j - 2]) + 4*f(x[2*j - 1]) + f(x[2*j]);
// 	}
	
// 	return sum*h/3;
// }

// double simpsonUnTercio(double a, double b, int n) {
//     double sum = f(0);

//     for(int i = 1; i < n - 1; i += 2) {
//         sum += 4*f(i);
//         if(i < n - 2)
//             sum += 2*f(i+1);
//     }

//     sum += f(n-1);
//     sum *= (b-a)/(3*(n-1));
//     return sum;
// }

// double simpsonTresOctavos(double a, double b, int n) {
//     double sum = f(0);

//     for(int i = 1; i < n - 1; i+=3) {
//         sum += 3*f(i);
//         if(i < n - 2)
//             sum += 3*f(i+1);
//         if(i < n - 3)
//             sum += 2*f(i+2);
//     }

//     sum += f(n-1);
//     sum *= ((b-a)*3.0)/(8.0*(n-1));
//     return sum;
// }

double simpsonUnTercio(double *values, double a, double b, int n) {
    double sum = values[0];

    for(int i = 1; i < n - 1; i += 2)
    {
        sum += 4*values[i];
        if(i < n - 2)
            sum += 2*values[i+1];
    }

    sum += values[n-1];
    sum *= (b-a)/(3*(n-1));
    return sum;
}

double simpsonTresOctavos(double *values, double a, double b, int n) {
    double sum = values[0];

    for(int i = 1; i < n - 1; i+=3)
    {
        sum += 3*values[i];
        if(i < n - 2)
            sum += 3*values[i+1];
        if(i < n - 3)
            sum += 2*values[i+2];
    }

    sum += values[n-1];
    sum *= ((b-a)*3.0)/(8.0*(n-1));
    return sum;
}

double simpson(double a, double b, int n)
{
    double v[n];
    double h = (b - a) / (n - 1);
    double i = a;
    for(int j = 0; i <= b; i+=h, j++)
    {
        v[j] = f(i);
    }
    if(n % 2 == 1)
    {
        return simpsonUnTercio(v ,a, b, n);
    }
    // else if(n % 3 == 1)
    // {
    //     return simpsonTresOctavos(v, a, b, n);
    // }
    else{
        double acc = simpsonTresOctavos(v, a, a+(3*h), 4);
        double w[n - 3];
        for(int j = 0; j+3 < n; j++)
        {
            w[j] = v[j + 3];
        }
        return acc + simpsonUnTercio(w, a+(3*h), b, n-3);
    }
}

double trapz(double a, double b, int n) {
    double h = (b - a) / n;
    double s = 0;
    double x;
    double w;
    for (int i = 0; i <= n; ++i) {
        x = a + i * h;
        w = (i == 0 || i == n) ? 1 : 2;
        s += w * f(x);
    }
    s = s * h / 2;
    return s;
}

int main() {
    double a, b;
    int n;

    // Solicitar al usuario los límites de integración y el número de intervalos
    cout << "Ingrese el límite inferior de integración a: ";
    cin >> a;
    cout << "Ingrese el límite superior de integración b: ";
    cin >> b;
    cout << "Ingrese el número de intervalos n: ";
    cin >> n;

    // Calcular la integral utilizando el método de Simpson
    double resultado = simpson(a, b, n);
    cout << "El resultado de la integración numérica es: " << resultado << endl;

    resultado = trapz(a, b, n * 2);
    cout << "El resultado de la integración numérica es: " << resultado << endl;


    return 0;
}