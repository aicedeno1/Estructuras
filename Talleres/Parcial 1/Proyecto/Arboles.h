#ifndef ARBOLES_H
#define ARBOLES_H

#include <iostream>
#include <functional>
#include <queue>

template <typename T>
class ArbolBinario {
private:
    struct Nodo {
        T dato;
        Nodo* izquierdo;
        Nodo* derecho;
        
        Nodo(const T& valor) : dato(valor), izquierdo(nullptr), derecho(nullptr) {}
    };
    
    Nodo* raiz;
    
    // Métodos privados auxiliares
    Nodo* insertar(Nodo* nodo, const T& valor, const std::function<bool(const T&, const T&)>& comparador) {
        if (nodo == nullptr) {
            return new Nodo(valor);
        }
        
        if (comparador(valor, nodo->dato)) {
            nodo->izquierdo = insertar(nodo->izquierdo, valor, comparador);
        } else if (comparador(nodo->dato, valor)) {
            nodo->derecho = insertar(nodo->derecho, valor, comparador);
        }
        
        return nodo;
    }
    
    void destruir(Nodo* nodo) {
        if (nodo) {
            destruir(nodo->izquierdo);
            destruir(nodo->derecho);
            delete nodo;
        }
    }
    
    void recorridoInorden(Nodo* nodo, const std::function<void(const T&)>& funcion) const {
        if (nodo) {
            recorridoInorden(nodo->izquierdo, funcion);
            funcion(nodo->dato);
            recorridoInorden(nodo->derecho, funcion);
        }
    }
    
    Nodo* buscar(Nodo* nodo, const T& valor, const std::function<bool(const T&, const T&)>& igual) const {
        if (nodo == nullptr || igual(nodo->dato, valor)) {
            return nodo;
        }
        
        if (igual(valor, nodo->dato)) {
            return buscar(nodo->izquierdo, valor, igual);
        }
        return buscar(nodo->derecho, valor, igual);
    }
    
    Nodo* encontrarMinimo(Nodo* nodo) {
        while (nodo->izquierdo != nullptr) {
            nodo = nodo->izquierdo;
        }
        return nodo;
    }
    
    Nodo* eliminar(Nodo* nodo, const T& valor, const std::function<bool(const T&, const T&)>& igual) {
        if (nodo == nullptr) {
            return nodo;
        }
        
        if (igual(valor, nodo->dato)) {
            nodo->izquierdo = eliminar(nodo->izquierdo, valor, igual);
        } else if (igual(nodo->dato, valor)) {
            nodo->derecho = eliminar(nodo->derecho, valor, igual);
        } else {
            if (nodo->izquierdo == nullptr) {
                Nodo* temp = nodo->derecho;
                delete nodo;
                return temp;
            } else if (nodo->derecho == nullptr) {
                Nodo* temp = nodo->izquierdo;
                delete nodo;
                return temp;
            }
            
            Nodo* temp = encontrarMinimo(nodo->derecho);
            nodo->dato = temp->dato;
            nodo->derecho = eliminar(nodo->derecho, temp->dato, igual);
        }
        return nodo;
    }

public:
    ArbolBinario() : raiz(nullptr) {}
    
    ~ArbolBinario() {
        destruir(raiz);
    }
    
    void insertar(const T& valor, const std::function<bool(const T&, const T&)>& comparador) {
        raiz = insertar(raiz, valor, comparador);
    }
    
    void recorrer(const std::function<void(const T&)>& funcion) const {
        recorridoInorden(raiz, funcion);
    }
    
    bool existe(const T& valor, const std::function<bool(const T&, const T&)>& igual) const {
        return buscar(raiz, valor, igual) != nullptr;
    }
    
    void eliminar(const T& valor, const std::function<bool(const T&, const T&)>& igual) {
        raiz = eliminar(raiz, valor, igual);
    }
    
    void limpiar() {
        destruir(raiz);
        raiz = nullptr;
    }
    
    // Método para buscar usando un predicado personalizado
    void buscarPor(const std::function<bool(const T&)>& predicado, 
                   const std::function<void(const T&)>& procesador) const {
        if (!raiz) return;
        
        std::queue<Nodo*> cola;
        cola.push(raiz);
        
        while (!cola.empty()) {
            Nodo* actual = cola.front();
            cola.pop();
            
            if (predicado(actual->dato)) {
                procesador(actual->dato);
            }
            
            if (actual->izquierdo) cola.push(actual->izquierdo);
            if (actual->derecho) cola.push(actual->derecho);
        }
    }
};
#endif 