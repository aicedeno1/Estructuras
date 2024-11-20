#include <iostream>
#include <cstdlib>
#include <ctime>
#define MAX 3

using namespace std;


void sumaRecursivaMatrices(int mat1[MAX][MAX], int mat2[MAX][MAX], int resultado[MAX][MAX], int f, int c);


void sumaRecursivaMatrices(int mat1[MAX][MAX], int mat2[MAX][MAX], int resultado[MAX][MAX], int f, int c) {
    if (f < 0) return; 

    
    resultado[f][c] = mat1[f][c] + mat2[f][c];

    
    if (c > 0) {
        sumaRecursivaMatrices(mat1, mat2, resultado, f, c - 1); 
    } else {
        sumaRecursivaMatrices(mat1, mat2, resultado, f - 1, MAX - 1); 
    }
}

int main() {
    int mat1[MAX][MAX], mat2[MAX][MAX], resultado[MAX][MAX];

    // Semilla para valores aleatorios
    srand(time(NULL));

    // Generar valores aleatorios para las matrices
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            mat1[i][j] = rand() % 10; // Números entre 0 y 9
            mat2[i][j] = rand() % 10; // Números entre 0 y 9
        }
    }

    // Imprimir matriz 1
    cout << "Matriz 1:" << endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cout << mat1[i][j] << "\t";
        }
        cout << endl;
    }

    // Imprimir matriz 2
    cout << "\nMatriz 2:" << endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cout << mat2[i][j] << "\t";
        }
        cout << endl;
    }

    // Calcular la suma recursiva
    sumaRecursivaMatrices(mat1, mat2, resultado, MAX - 1, MAX - 1);

    // Imprimir el resultado
    cout << "\nResultado de la suma de matrices:" << endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cout << resultado[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}
