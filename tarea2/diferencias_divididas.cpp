#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

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

    std::ifstream data_file{"data2.txt"};

    std::vector<std::string> lines{};

    while(!data_file.eof())
    {
        std::string line;
        std::getline(data_file, line);
        lines.push_back(line);
    }

    const size_t n = stoi(lines[0]);
    double x[n + 1];
    double f[n + 1][n + 1];

    std::vector<std::string> xsv{split(lines[1])};
    std::vector<std::string> fsv{split(lines[2])};

    for (size_t i = 0; i <= n; ++i)
    {
        x[i] = stod(xsv[i]);
        f[i][0] = stod(fsv[i]);

        for (size_t j = 1; j <= n; ++j)
        {
            f[i][j] = 0.0;
        }
    }

    //Tabla de Diferencias Divididas
    for (size_t k = 1; k <= n; k++)
    {
        for (size_t i = 0; i <= n - k; i++)
        {
            f[i][k] = (f[i + 1][k - 1] - f[i][k - 1]) / (x[i + k] - x[i]);
        }
    }

    std::cout << "I" << std::setw(10) << "X(I)";

    for (size_t i = 0; i <= n; ++i)
    {
            std::cout << std::setw(12) << "F(I," << i << ")";
    }

    std::cout << std::endl;
    std::cout << std::fixed << std::setprecision(5);

    for (size_t i = 0; i <= n; i++)
    {
        std::cout << i << std::setw(11) << x[i];

        for (size_t k = 0; k <= n - i; k++)
        {
            std::cout << std::setw(14) << f[i][k];
        }
        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}