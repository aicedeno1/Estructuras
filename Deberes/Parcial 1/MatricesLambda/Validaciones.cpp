#include "Validaciones.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <conio.h>

using namespace std;

// Métodos para convertir los tipos de datos
int Validaciones::convertirAEntero(const string& input) {
    int valor;
    istringstream iss(input);
    if (!(iss >> valor)) throw invalid_argument("No es un entero válido");
    return valor;
}

float Validaciones::convertirAFloat(const string& input) {
    float valor;
    istringstream iss(input);
    if (!(iss >> valor)) throw invalid_argument("No es un flotante válido");
    return valor;
}

double Validaciones::convertirADouble(const string& input) {
    double valor;
    istringstream iss(input);
    if (!(iss >> valor)) throw invalid_argument("No es un double válido");
    return valor;
}

// Función para ingresar un número entero
int Validaciones::ingresarEntero(const char* msj) {
    string input = "";
    char c;
    cout << msj;

    while (true) {
        c = getch();
        if (isdigit(c) || c == '-') { // Aceptar números negativos también
            cout << c;
            input += c;
        } else if (c == 8 && !input.empty()) {
            cout << "\b \b";
            input.pop_back();
        } else if (c == 13 && !input.empty()) {
            cout << endl;
            break;
        }
    }

    return convertirAEntero(input);
}

// Función para ingresar un número flotante
float Validaciones::ingresarFloat(const char* msj) {
    string input = "";
    char c;
    bool puntoDecimal = false;
    cout << msj;

    while (true) {
        c = getch();
        if (isdigit(c) || (c == '.' && !puntoDecimal)) {
            if (c == '.') puntoDecimal = true;
            cout << c;
            input += c;
        } else if (c == 8 && !input.empty()) {
            if (input.back() == '.') puntoDecimal = false;
            cout << "\b \b";
            input.pop_back();
        } else if (c == 13 && !input.empty()) {
            cout << endl;
            break;
        }
    }

    return convertirAFloat(input);
}

// Función para ingresar un número double
double Validaciones::ingresarDouble(const char* msj) {
    string input = "";
    char c;
    bool puntoDecimal = false;
    cout << msj;

    while (true) {
        c = getch();
        if (isdigit(c) || (c == '.' && !puntoDecimal)) {
            if (c == '.') puntoDecimal = true;
            cout << c;
            input += c;
        } else if (c == 8 && !input.empty()) {
            if (input.back() == '.') puntoDecimal = false;
            cout << "\b \b";
            input.pop_back();
        } else if (c == 13 && !input.empty()) {
            cout << endl;
            break;
        }
    }

    return convertirADouble(input);
}
