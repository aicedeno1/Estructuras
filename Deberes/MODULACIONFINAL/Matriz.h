#pragma once
class Matriz {
private:
    int** matriz1;
    int** matriz2;
    int** matrizR;
    int dim;

public:
    Matriz();
    Matriz(int**, int**, int**, int);
    int getDim();
    void setDim(int);
    int** getMatriz1();
    void setMatriz1(int**);
    int** getMatriz2();
    void setMatriz2(int**);
    int** getMatrizR();
    void setMatrizR(int**);
};
