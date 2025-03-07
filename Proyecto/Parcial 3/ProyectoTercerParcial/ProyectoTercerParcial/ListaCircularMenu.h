

#ifndef LISTA_CIRCULAR_MENU_H
#define LISTA_CIRCULAR_MENU_H

#include <string>

// Estructura para el nodo del menú
struct NodoMenu
{
    std::string dato;
    NodoMenu *siguiente;
    NodoMenu *anterior;

    NodoMenu(std::string valor) : dato(valor), siguiente(nullptr), anterior(nullptr) {}
};

class ListaCircularMenu
{
private:
    NodoMenu *cabeza;
    int tamano;

public:
    // Constructor y destructor
    ListaCircularMenu();
    ~ListaCircularMenu();

    // Operaciones
    void insertar(std::string opcion);
    std::string obtenerOpcion(int indice);

    // Getters
    NodoMenu *getPrimero() const;
    int getTamano() const;

    // Operaciones adicionales
    void vaciar();
};

#endif // LISTA_CIRCULAR_MENU_H