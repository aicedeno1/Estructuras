#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class IngresarDatos {
public:
    // Método para ingresar un valor entero y convertirlo a char
    static char ingresarEntero(const string &mensaje) {
        string input;
        int valor;
        while (true) {
            try {
                cout << mensaje;
                cin >> input;
                valor = stoi(input); // Convierte a int
                return static_cast<char>(valor); // Convierte a char
            } catch (invalid_argument &e) {
                cerr << "Entrada inválida. Intente nuevamente.\n";
            } catch (out_of_range &e) {
                cerr << "Número fuera de rango. Intente nuevamente.\n";
            }
        }
    }

    // Método para ingresar un valor flotante y convertirlo a char
    static char ingresarFlotante(const string &mensaje) {
        string input;
        float valor;
        while (true) {
            try {
                cout << mensaje;
                cin >> input;
                valor = stof(input); // Convierte a float
                return static_cast<char>(valor); // Convierte a char
            } catch (invalid_argument &e) {
                cerr << "Entrada inválida. Intente nuevamente.\n";
            } catch (out_of_range &e) {
                cerr << "Número fuera de rango. Intente nuevamente.\n";
            }
        }
    }

    // Método para ingresar un valor double y convertirlo a char
    static char ingresarDouble(const string &mensaje) {
        string input;
        double valor;
        while (true) {
            try {
                cout << mensaje;
                cin >> input;
                valor = stod(input); // Convierte a double
                return static_cast<char>(valor); // Convierte a char
            } catch (invalid_argument &e) {
                cerr << "Entrada inválida. Intente nuevamente.\n";
            } catch (out_of_range &e) {
                cerr << "Número fuera de rango. Intente nuevamente.\n";
            }
        }
    }
};

int main() {
    char valorEntero = IngresarDatos::ingresarEntero("Ingrese un valor entero: ");
    cout << "Valor ingresado como entero (convertido a char): " << valorEntero << endl;

    char valorFlotante = IngresarDatos::ingresarFlotante("Ingrese un valor flotante: ");
    cout << "Valor ingresado como flotante (convertido a char): " << valorFlotante << endl;

    char valorDouble = IngresarDatos::ingresarDouble("Ingrese un valor double: ");
    cout << "Valor ingresado como double (convertido a char): " << valorDouble << endl;

    return 0;
}
