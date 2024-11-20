#include <iostream>
#include <vector>
using namespace std;

// Función recursiva que divide el arreglo y lo suma
int suma_recursiva(const vector<int>& arr, int n) {
    if (n == 0)  
        return 0;
    else
        return arr[n - 1] + suma_recursiva(arr, n - 1); 
}

int main() {
    int tamano;
    cout << "Ingrese el tamanio del arreglo: ";
    cin >> tamano;

    vector<int> arr(tamano);  

    cout << "Ingrese los elementos del arreglo:" << endl;
    for (int i = 0; i < tamano; ++i) {
        cin >> arr[i];
    }

    int resultado = suma_recursiva(arr, arr.size());  // Llamada inicial con el tamaño del arreglo
    cout << "La suma de los elementos es: " << resultado << endl;

    return 0;
}
