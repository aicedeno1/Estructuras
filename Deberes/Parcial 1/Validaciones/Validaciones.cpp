#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <conio.h> 
using namespace std;

class Validaciones {
public:
    int ingresarEntero(const char *msj);
    float ingresarFloat(const char *msj);
    double ingresarDouble(const char *msj);
    string ingresarString(const char *msj);
    string ingresarLetras(const char *msj);

private:
    int convertirAEntero(const string& input);
    float convertirAFloat(const string& input);
    double convertirADouble(const string& input);
};

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

// Función para ingresar solo letras
string Validaciones::ingresarLetras(const char *msj) {
    string input = "";
    cout << msj;

    while (true) {
        char c = getch();
        if (isalpha(c)) {
            cout << c;
            input += c;
        }
        else if (c == 8 && !input.empty()) {
            cout << "\b \b";
            input.pop_back();
        }
        else if (c == 13 && !input.empty()) {
            cout << endl;
            break;
        }
        else if (c == 13 && input.empty()) {
            cout << "\nDebe ingresar al menos una letra." << endl;
        }
    }

    return input;
}

// Ingresar un número entero
int Validaciones::ingresarEntero(const char *msj) {
    string input = "";
    char c;
    cout << msj;

    while (true) {
        c = getch();
        if (isdigit(c)) {
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

// Ingresar un número flotante
float Validaciones::ingresarFloat(const char *msj) {
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

// Ingresar un número double
double Validaciones::ingresarDouble(const char *msj) {
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

// Ingresar un string
string Validaciones::ingresarString(const char *msj) {
    string input = "";
    char c;
    cout << msj;

    while ((c = getch()) != 13) {
        if (isalpha(c)) {
            cout << c;
            input += c;
        } else if (c == 8 && !input.empty()) {
            cout << "\b \b";
            input.pop_back();
        }
    }
    cout << endl;
    return input;
}

// Función principal para probar las entradas
int main() {
    Validaciones val;

    int entero = val.ingresarEntero("Ingrese un numero entero: ");
    cout << "Entero ingresado: " << entero << endl;

    float flotante = val.ingresarFloat("Ingrese un numero flotante: ");
    cout << "Flotante ingresado: " << flotante << endl;

    double doble = val.ingresarDouble("Ingrese un numero double: ");
    cout << "Double ingresado: " << doble << endl;

    string letras = val.ingresarLetras("Ingrese una cadena de letras: ");
    cout << "Letras ingresadas: " << letras << endl;

    string texto = val.ingresarString("Ingrese una cadena alfanumerica: ");
    cout << "Cadena ingresada: " << texto << endl;

    return 0;
}
