#include <iostream>
using namespace std;

// 1. Recursividad Directa (Factorial)
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// 2. Recursividad Indirecta (Funciones A y B)
void funcionA(int n);
void funcionB(int n);

void funcionA(int n) {
    if (n <= 0) return;
    cout << "funcionA: " << n << endl;
    funcionB(n - 1);
}

void funcionB(int n) {
    if (n <= 0) return;
    cout << "funcionB: " << n << endl;
    funcionA(n - 1);
}

// 3. Recursividad de Cola (Cuenta Regresiva)
void cuentaAtras(int n) {
    if (n <= 0) return;
    cout << n << " ";
    cuentaAtras(n - 1);
}

// 4. Recursividad de Cabeza (Cuenta Adelante)
void cuentaAdelante(int n) {
    if (n <= 0) return;
    cuentaAdelante(n - 1);
    cout << n << " ";
}

// 5. Recursividad Anidada (Suma Doble)
int sumaDoble(int n) {
    if (n <= 0) return 0;
    return n + sumaDoble(n - 1) + sumaDoble(n - 2);
}

// 6. Recursividad Mutua (Par e Impar)
bool esPar(int n);
bool esImpar(int n);

bool esPar(int n) {
    if (n == 0) return true;
    return esImpar(n - 1);
}

bool esImpar(int n) {
    if (n == 0) return false;
    return esPar(n - 1);
}

// 7. Recursividad Binaria (Potencia)
int potencia(int base, int exponente) {
    if (exponente == 0) return 1;
    int resultado = potencia(base, exponente / 2);
    if (exponente % 2 == 0)
        return resultado * resultado;
    else
        return base * resultado * resultado;
}

int main() {
    int opcion, n, base, exponente;

    do {
        cout << "\nMenu de Recursividad\n";
        cout << "1. Factorial (Recursividad Directa)\n";
        cout << "2. Alternar entre A y B (Recursividad Indirecta)\n";
        cout << "3. Cuenta Regresiva (Recursividad de Cola)\n";
        cout << "4. Cuenta Adelante (Recursividad de Cabeza)\n";
        cout << "5. Suma Doble (Recursividad Anidada)\n";
        cout << "6. Verificar Par o Impar (Recursividad Mutua)\n";
        cout << "7. Potencia (Recursividad Binaria)\n";
        cout << "8. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "Ingrese un numero para calcular factorial: ";
                cin >> n;
                cout << "Factorial de " << n << " es: " << factorial(n) << endl;
                break;

            case 2:
                cout << "Ingrese un numero para alternar entre A y B: ";
                cin >> n;
                funcionA(n);
                break;

            case 3:
                cout << "Ingrese un numero para cuenta regresiva: ";
                cin >> n;
                cuentaAtras(n);
                cout << endl;
                break;

            case 4:
                cout << "Ingrese un numero para cuenta adelante: ";
                cin >> n;
                cuentaAdelante(n);
                cout << endl;
                break;

            case 5:
                cout << "Ingrese un numero para suma doble: ";
                cin >> n;
                cout << "Resultado de suma doble: " << sumaDoble(n) << endl;
                break;

            case 6:
                cout << "Ingrese un numero para verificar si es par o impar: ";
                cin >> n;
                if (esPar(n)) 
                    cout << n << " es par" << endl;
                else 
                    cout << n << " es impar" << endl;
                break;

            case 7:
                cout << "Ingrese base y exponente para calcular potencia: ";
                cin >> base >> exponente;
                cout << base << "^" << exponente << " es: " << potencia(base, exponente) << endl;
                break;

            case 8:
                cout << "Saliendo..." << endl;
                break;

            default:
                cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 8);

    return 0;
}
