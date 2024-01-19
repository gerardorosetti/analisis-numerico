#include <iostream>
#include <cfloat>
#include <locale.h>
#include <limits>

#ifdef _WIN32
    #include <windows.h>
    void set_output_special_chars()
    {
        SetConsoleOutputCP(CP_UTF8);
        std::setlocale(LC_ALL, "");
    }
#else
    #include <unistd.h>
    void set_output_special_chars()
    {
        std::setlocale(LC_ALL, "");
    }
#endif

#include <iostream>
#include <cfloat>

int main() {
    set_output_special_chars();
    double current_number = 1.0;
    double last_number = 0.0;

    while (current_number < DBL_MAX && current_number > last_number) {
        last_number = current_number;
        current_number *= 2.0;
    }

    std::cout << "El desbordamiento ocurre alrededor de: " << last_number << std::endl;
    std::cout << "El límite para desbordamiento en double es: " << DBL_MAX << std::endl;
    std::cout << "diff " << DBL_MAX - last_number << std::endl;

    return 0;
}

// int main() {

//     set_output_special_chars();

//     float last_number = 0.0f;
//     float current_number = 1.0f;

//     while (current_number > last_number) {
//         last_number = current_number;
//         current_number *= 2.0f;
//     }
//     last_number /= 2.0f;

//     std::cout << "El desbordamiento ocurre alrededor de: " << last_number << std::endl;
//     std::cout << "El límite para desbordamiento en float es: " << FLT_MAX << std::endl;
//     std::cout << "El límite para desbordamiento en double es: " << DBL_MAX << std::endl;

//     return 0;
// }