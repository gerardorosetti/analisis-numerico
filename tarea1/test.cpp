#include <iostream>
#include <cfloat>

int main() {
    double current_number = 1.0;
    double last_number = 0.0;

    while (current_number < DBL_MAX && current_number > last_number) {
        last_number = current_number;
        current_number *= 2.0;
    }

    std::cout << "El desbordamiento ocurre alrededor de: " << last_number << std::endl;
    std::cout << "El límite para desbordamiento en double es: " << DBL_MAX << std::endl;

    return 0;
}