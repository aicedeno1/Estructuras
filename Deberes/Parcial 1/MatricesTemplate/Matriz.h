    #ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>

template <typename T>
class Matriz {
private:
    T** matriz;
    int dim;

public:
    Matriz() : matriz(nullptr), dim(0) {}

    Matriz(int dim) : dim(dim) {
        matriz = new T*[dim];
        for (int i = 0; i < dim; ++i) {
            matriz[i] = new T[dim]{};
        }
    }

    ~Matriz() {
        for (int i = 0; i < dim; ++i) {
            delete[] matriz[i];
        }
        delete[] matriz;
    }

    void setElemento(int fila, int col, T valor) {
        if (fila >= 0 && fila < dim && col >= 0 && col < dim) {
            matriz[fila][col] = valor;
        }
    }

    T getElemento(int fila, int col) const {
        if (fila >= 0 && fila < dim && col >= 0 && col < dim) {
            return matriz[fila][col];
        }
        return T();
    }

    int getDim() const {
        return dim;
    }

    void imprimir() const {
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                std::cout << matriz[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Función para sumar dos matrices
    Matriz<T> sumar(const Matriz<T>& m1) const {
        Matriz<T> resultado(dim);

        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                resultado.setElemento(i, j, this->getElemento(i, j) + m1.getElemento(i, j));
            }
        }
        return resultado;
    }
};

#endif // MATRIZ_H
