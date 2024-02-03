#include <iostream>
#include <fstream>
#include <vector>

int main (int argc, char * argv[])
{

    //return 0.1 * std::pow(x, 3) + 5 * std::pow(x, 2) - exp(x);

    std::ifstream data_file{"data.txt"};

    std::vector<std::string> lines{};

    while(!data_file.eof())
    {
        std::string line;
        std::getline(data_file, line);
        lines.push_back(line);
    }

    for (int i = 1; i < argc; ++i)
    {
        std::cout << argv[i] << std::endl;
    }

    for (std::string line: lines)
    {
        std::cout << line << std::endl;
    }

    return EXIT_SUCCESS;
}