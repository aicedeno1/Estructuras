#include "Validaciones1.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <conio.h>

#include "Validaciones1.h"
#include <iostream>

float Validaciones::ingresarFloat(const char* msj) {
    float input;
    std::cout << msj;
    std::cin >> input;
    return input;
}

double Validaciones::ingresarDouble(const char* msj) {
    double input;
    std::cout << msj;
    std::cin >> input;
    return input;
}


float Validaciones::ingresarFloat(const char* msj) {
    string input;
    while (true) {
        cout << msj;
        input = "";
        char c;
        while ((c = getch()) != 13) {  // Enter key
            if (isdigit(c) || (c == '.' && input.find('.') == string::npos)) {
                cout << c;
                input += c;
            } else if (c == 8 && !input.empty()) {  // Backspace key
                cout << "\b \b";
                input.pop_back();
            }
        }
        cout << endl;
        try {
            return convertirAFloat(input);
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }
    }
}

double Validaciones::ingresarDouble(const char* msj) {
    string input;
    while (true) {
        cout << msj;
        input = "";
        char c;
        while ((c = getch()) != 13) {  // Enter key
            if (isdigit(c) || (c == '.' && input.find('.') == string::npos)) {
                cout << c;
                input += c;
            } else if (c == 8 && !input.empty()) {  // Backspace key
                cout << "\b \b";
                input.pop_back();
            }
        }
        cout << endl;
        try {
            return convertirADouble(input);
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }
    }
}
