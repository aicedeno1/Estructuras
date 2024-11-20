#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <conio.h>

extern "C" {
    __declspec(dllexport) int ingresarEntero(const char* msj) {
        std::string input = "";
        char c;
        std::cout << msj;

        while (true) {
            c = getch();
            if (isdigit(c)) {
                std::cout << c;
                input += c;
            } else if (c == 8 && !input.empty()) { // Retroceso
                std::cout << "\b \b";
                input.pop_back();
            } else if (c == 13 && !input.empty()) { // Enter
                std::cout << std::endl;
                break;
            }
        }

        int valor;
        std::istringstream(input) >> valor;
        return valor;
    }
}
