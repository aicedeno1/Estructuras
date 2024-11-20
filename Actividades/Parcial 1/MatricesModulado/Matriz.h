#ifndef MATRIZ_H
#define MATRIZ_H

class Matriz {
private:
    int matriz[MAX][MAX];

public:
    Matriz();
    void ingresarMatrizPorTeclado();
    void imprimirMatriz() const;
    int** getMatriz1() const;
    int** getMatriz2() const;
};

#endif
