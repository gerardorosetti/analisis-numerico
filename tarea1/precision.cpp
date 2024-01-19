#include <iostream>
#include <locale.h>

#ifdef _WIN32
    #include <windows.h>
    void set_output_special_chars()
    {
        SetConsoleOutputCP(CP_UTF8);
    }
#else
    #include <unistd.h>
    void set_output_special_chars()
    {
        std::setlocale(LC_ALL, "");
    }
#endif

int main() {

    set_output_special_chars();

    // Cálculo de precisión
    double epsilon = 1.0;

    while (epsilon + 1.0 > 1.0) {
        epsilon = epsilon / 2.0;
    }

    std::cout << "La precisión de la máquina es aproximadamente: " << epsilon <<  std::endl;

    return 0;
}