#include <iostream>
using namespace std;

// Función factorial con recursividad de cola
int factorialTail(int n, int acumulador = 1) {
    if (n == 0 || n == 1) {
        return acumulador;
    }
    return factorialTail(n - 1, acumulador * n); // Llamada recursiva de cola
}

int main() {
    int n = 4;
    cout << "Factorial de " << n << " es: " << factorialTail(n) << endl;
    return 0;
}
