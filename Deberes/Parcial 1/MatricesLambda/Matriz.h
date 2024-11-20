#ifndef MATRIZ_H
#define MATRIZ_H

class Matriz {
private:
    int** matriz1;
    int** matriz2;
    int** matrizR;
    int dim;

public:
    Matriz();  
    Matriz(int dim);  
    ~Matriz();  // Destructor para liberar la memoria dinámica

    int getDim() const;
    int** getMatriz1();
    int** getMatriz2();
    int** getMatrizR();

    void imprimirMatriz(int** matriz);
    void liberarMatriz(int** matriz);
    void sumarMatricesConRecursion();  // Cambiado a sumar de forma recursiva

private:
    void inicializarMatrices();
    void sumarMatricesRecursivo(int i, int j);  // Función recursiva para sumar las matrices
};

#endif
