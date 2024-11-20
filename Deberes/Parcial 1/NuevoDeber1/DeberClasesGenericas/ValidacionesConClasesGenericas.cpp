#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <conio.h> 
using namespace std;

class Validaciones {
public:
    template<typename T>
    T ingresarAutomatico(const char *msj);

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

// Función para ingresar solo letras (bloqueando los números)
string Validaciones::ingresarLetras(const char *msj) {
    string input = "";
    cout << msj;

    while (true) {
        char c = getch();  // Obtener el carácter ingresado
        if (isalpha(c)) {  // Aceptar solo letras
            cout << c;
            input += c;
        }
        else if (c == 8 && !input.empty()) {  // Manejar la tecla Backspace
            cout << "\b \b";  // Eliminar el último carácter
            input.pop_back();
        }
        else if (c == 13 && !input.empty()) {  // Al presionar Enter, procesar el input
            cout << endl;
            break;
        }
        else if (c == 13 && input.empty()) {  // Si el usuario presiona Enter sin escribir nada
            cout << "\nDebe ingresar al menos una letra." << endl;
        }
    }

    return input;
}

// Función principal que detecta y convierte automáticamente el tipo de dato
template<typename T>
T Validaciones::ingresarAutomatico(const char *msj) {
    string input;
    bool numeroIngresado = false;

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
            else if (c == 8 && !input.empty()) {  // Manejar la tecla Backspace
                cout << "\b \b";  // Eliminar el último carácter
                input.pop_back();
            }
            else if (c == 13 && !input.empty()) {  // Al presionar Enter, procesar el input
                cout << endl;
                break;
            }
        }

        // Intentamos convertir el input a distintos tipos usando la plantilla
        try {
            if (is_same<T, int>::value) {
                // Si el tipo es int, convertir a entero y retornarlo
                return convertirAEntero(input);
            }
            else if (is_same<T, float>::value) {
                // Si el tipo es float, convertir a float y luego a int para devolverlo como entero
                float resultado = convertirAFloat(input);
                return static_cast<int>(resultado);  // Convertir el valor de float a int
            }
            else if (is_same<T, double>::value) {
                // Si el tipo es double, convertir a double y luego a int para devolverlo como entero
                double resultado = convertirADouble(input);
                return static_cast<int>(resultado);  
            }
            else {
                throw invalid_argument("Tipo de dato no soportado");
            }
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }
    }
}

int main() {
    Validaciones val;

    
    int resultado = val.ingresarAutomatico<int>("Ingrese un número: ");
    cout << "\nValor ingresado (convertido a int): " << resultado << endl;

   
    string letras = val.ingresarLetras("Ingrese una cadena de letras: ");
    cout << "\nCadena ingresada: " << letras << endl;

    return 0;
}