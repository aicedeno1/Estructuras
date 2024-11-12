#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <conio.h> // Necesario para getch()

using namespace std;

class Validaciones {
public:
    int ingresarAutomatico(const char *msj);

private:
    int convertirAEntero(const string& input);
    float convertirAFloat(const string& input);
    double convertirADouble(const string& input);
    char convertirALetra(const string& input);
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

char Validaciones::convertirALetra(const string& input) {
    if (input.length() == 1 && isalpha(input[0])) {
        return input[0];
    }
    throw invalid_argument("No es una letra válida");
}

// Función principal que detecta y convierte automáticamente el tipo de dato
int Validaciones::ingresarAutomatico(const char *msj) {
    string input;
    bool numeroIngresado = false; // Indicador para verificar si ya se ingresó un número
    bool letraIngresada = false;  // Indicador para verificar si ya se ingresó una letra

    while (true) {
        cout << msj;
        input = "";  // Limpiar el input antes de empezar a leer
        
        // Ciclo de lectura del input con validación de caracteres
        while (true) {
            char c = getch();  // Obtener el carácter ingresado
            if (isdigit(c) || (c == '.' && input.find('.') == string::npos)) {  // Aceptar números y un solo punto decimal
                cout << c;
                input += c;
                numeroIngresado = true;  // Marcar que se ingresó un número
            } 
            else if (isalpha(c) && !numeroIngresado) {  // Solo permitir letras si no se ingresó un número antes
                cout << c;
                input += c;
                letraIngresada = true;  // Marcar que se ingresó una letra
                break;  // Si se ingresa una letra, se termina el ciclo
            } 
            else if (c == 8 && !input.empty()) {  // Manejar la tecla Backspace
                cout << "\b \b";  // Eliminar el último carácter
                input.pop_back();
            }
            else if (c == 13 && !input.empty()) {  // Al presionar Enter, procesar el input
                cout << endl;
                break;
            }
            // Si se presiona una tecla no válida después de que se ha ingresado un número, no hacer nada
            else if (numeroIngresado && isalpha(c)) {
                continue;
            }
        }

        // Intentamos convertir a los tipos de datos y lanzar excepciones si no es posible
        try {
            // Si ya se ingresó un número y el input es letra, o viceversa, lanzar excepción
            if ((numeroIngresado && isalpha(input[0])) || (letraIngresada && isdigit(input[0]))) {
                throw invalid_argument("Cambio de tipo de dato no permitido");
            }

            // Intentar convertir a entero
            try {
                int resultado = convertirAEntero(input);
                numeroIngresado = true; // Indicar que se ingresó un número
                return static_cast<int>(resultado); // Retornar el valor convertido a entero
            } catch (const invalid_argument&) {}

            // Intentar convertir a flotante
            try {
                float resultado = convertirAFloat(input);
                numeroIngresado = true; // Indicar que se ingresó un número
                return static_cast<int>(resultado); // Convertir el valor a int antes de retornar
            } catch (const invalid_argument&) {}

            // Intentar convertir a double
            try {
                double resultado = convertirADouble(input);
                numeroIngresado = true; // Indicar que se ingresó un número
                return static_cast<int>(resultado); // Convertir el valor a int antes de retornar
            } catch (const invalid_argument&) {}

            // Intentar convertir a letra
            try {
                char resultado = convertirALetra(input);
                letraIngresada = true; // Indicar que se ingresó una letra
                return static_cast<int>(resultado); // Convertir el valor a int antes de retornar
            } catch (const invalid_argument&) {
                cout << "Entrada inválida. Debe ser un número o una letra." << endl;
            }
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }
    }
}

int main() {
    Validaciones val;
    int resultado = val.ingresarAutomatico("Ingrese un valor: ");
    cout << "\nValor ingresado (convertido a int): " << resultado << endl;

    return 0;
}
