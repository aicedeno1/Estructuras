#ifndef FUNCIONES_ARBOLES_H
#define FUNCIONES_ARBOLES_H

#include "Arboles.h"
#include "Libro.h"
#include "Autor.h"
#include "LogManager.h"

class BibliotecaManager {
private:
    ArbolBinario<Libro> libros;
    ArbolBinario<Autor> autores;
   

public:
    LogManager& logManager;
    BibliotecaManager(LogManager& log);
    bool agregarLibro(const Libro& libro);
    void mostrarLibros() const;
    bool eliminarLibro(const std::string& codigo);
    void buscarLibros(const std::string& criterio);
    bool agregarAutor(const Autor& autor);
    void mostrarAutores() const;
    bool existeAutor(const Autor& autor) const;
    ArbolBinario<Libro>& getLibros();
    ArbolBinario<Autor>& getAutores();
};

#endif 
