#ifndef MATRIZ_H
#define MATRIZ_H

class Matriz {
private:
    int** matriz1;
    int** matriz2;
    int** matrizR;
    int dim;  // Tamaño de la matriz (no mayor que 3)

public:
    // Constructor por defecto
    Matriz();

    // Constructor con dimensiones y matrices
    Matriz(int dim);

    // Getters y Setters
    int getDim() const;
    void setDim(int dim);

    int** getMatriz1();
    void setMatriz1(int** matriz1);

    int** getMatriz2();
    void setMatriz2(int** matriz2);

    int** getMatrizR();
    void setMatrizR(int** matrizR);

    // Métodos para imprimir matrices
    void imprimirMatriz(int** matriz);
    void liberarMatriz(int** matriz);

    // Método para sumar matrices
    void sumarMatrices();
};

#endif
