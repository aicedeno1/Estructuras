#include "Validaciones1.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <conio.h>
using namespace std;

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

float Validaciones::convertirAFloat(const string& input) {
    try {
        return stof(input);  // Convierte el string a float
    } catch (const invalid_argument& e) {
        throw invalid_argument("No es un número válido.");
    }
}

double Validaciones::convertirADouble(const string& input) {
    try {
        return stod(input);  // Convierte el string a double
    } catch (const invalid_argument& e) {
        throw invalid_argument("No es un número válido.");
    }
}
