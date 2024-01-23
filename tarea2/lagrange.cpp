#include <iostream>
#include <fstream>
#include <vector>

int main (int argc, char * argv[])
{
    auto split = [] (std::string string, char break_char = ' ')
    {
        std::vector<std::string> result{};
        std::string temp = "";
        for (size_t i = 0; i < string.length(); ++i)
        {
            if (string[i] == break_char)
            {
                result.push_back(temp);
                temp = "";
                continue;
            }
            temp += string[i];
        }
        result.push_back(temp);
        return result;
    };

    std::ifstream data_file{"data.txt"};

    std::vector<std::string> lines{};

    while(!data_file.eof())
    {
        std::string line;
        std::getline(data_file, line);
        lines.push_back(line);
    }

    const size_t n = stoi(lines[0]);
    double x[n + 1];
    double f[n + 1];

    std::vector<std::string> xsv{split(lines[1])};
    std::vector<std::string> fsv{split(lines[2])};

    for (size_t i = 0; i <= n; ++i)
    {
        x[i] = stod(xsv[i]);
        f[i] = stod(fsv[i]);
    }

    std::cout << "Interpolación de Lagrange" << std::endl;
    std::cout << "\nTabla de Valores Utilizados" << std::endl;
    std::cout << "I\tX(I)\tF(I)" << std::endl;

    for (int i = 0; i <= n; ++i) {
        std::cout << i << "\t" << x[i] << "\t" << f[i] << std::endl;
    }

    short ans;
    do
    {
        double xa;
        std::cout << "\nIngrese el x Deseado: ";
        std::cin >> xa;
        //Lagrange
        double y_res = 0.0;
        for (int i = 0; i <= n; ++i) {
            double z = 1.0;
            for (int j = 0; j <= n; ++j) {
                if (i != j) {
                    z = z * (xa - x[j]) / (x[i] - x[j]);
                }
            }
            y_res += z * f[i];
        }

        if (xa > x[n] || xa < x[0])
        {
            std::cout << "ADVERTENCIA: X ESTA EN EL RANGO DE EXTRAPOLACION" << std::endl;
        }

        std::cout << "Resultado de la Interpolación: G(" << xa << ") = " << y_res << std::endl << std::endl;
        std::cout << "Ingrese 1 para Continuar, 0 para Terminar: ";
        std::cin >> ans;
    } while(ans == 1);

    return EXIT_SUCCESS;
}