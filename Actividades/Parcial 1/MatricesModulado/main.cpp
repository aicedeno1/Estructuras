#include <iostream>
#include "Matriz.h"
#include "Operaciones.h"

int main() {
    Matriz m1, m2;
    m1.ingresarMatrizPorTeclado();
    m2.ingresarMatrizPorTeclado();
    
    Operaciones op;
    
    // Sumar las matrices recursivamente
    int resultado = op.sumaRecursivaMatrices(m1.getMatriz1(), m2.getMatriz2(), MAX - 1, MAX - 1);
    std::cout << "Resultado de la suma recursiva: " << resultado << std::endl;

    return 0;
}
