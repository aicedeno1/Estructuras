#ifndef NODOMENU_H
#define NODOMENU_H

#include <string>
using namespace std;

class NodoMenu {
public:
    string dato;
    NodoMenu* siguiente;
    NodoMenu* anterior;
    
    NodoMenu(string valor) : dato(valor), siguiente(nullptr), anterior(nullptr) {}
};

#endif