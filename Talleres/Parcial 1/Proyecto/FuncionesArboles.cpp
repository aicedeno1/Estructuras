#include "FuncionesArboles.h"
#include <iostream>

BibliotecaManager::BibliotecaManager(LogManager& log) : logManager(log) {}

// Agregar un libro al árbol de libros
bool BibliotecaManager::agregarLibro(const Libro& libro) {
    try {
        // Usar comparador para ordenar los libros por título
        auto comparador = [](const Libro& a, const Libro& b) {
            return a.getTitulo() < b.getTitulo();
        };
        libros.insertar(libro, comparador);
        logManager.escribirLog("Libro agregado: " + libro.getTitulo());
        return true;
    } catch (const std::exception& e) {
        logManager.escribirLog("Error al agregar libro: " + std::string(e.what()));
        return false;
    }
}

// Mostrar todos los libros en orden (recorrido inorden)
void BibliotecaManager::mostrarLibros() const {
    auto mostrar = [](const Libro& libro) {
        std::cout << libro.obtenerInformacion() << std::endl;
    };
    libros.recorrer(mostrar);
}

// Eliminar un libro por su código
bool BibliotecaManager::eliminarLibro(const std::string& codigo) {
    try {
        // Comparador para buscar el libro por código
        auto igual = [&codigo](const Libro& libro1, const Libro& libro2) {
            return libro1.obtenerCodigo() == codigo;
        };
        //libros.eliminar(codigo, igual);
        logManager.escribirLog("Libro eliminado: " + codigo);
        return true;
    } catch (const std::exception& e) {
        logManager.escribirLog("Error al eliminar libro: " + std::string(e.what()));
        return false;
    }
}

// Buscar libros por un criterio en el título
void BibliotecaManager::buscarLibros(const std::string& criterio) {
    auto predicado = [&criterio](const Libro& libro) {
        return libro.getTitulo().find(criterio) != std::string::npos;
    };
    auto procesador = [](const Libro& libro) {
        std::cout << "Encontrado: " << libro.obtenerInformacion() << std::endl;
    };
    libros.buscarPor(predicado, procesador);
}

// Agregar un autor al árbol de autores
bool BibliotecaManager::agregarAutor(const Autor& autor) {
    try {
        // Usar comparador para ordenar autores por nombre completo
        auto comparador = [](const Autor& a, const Autor& b) {
            return a.obtenerNombreCompleto() < b.obtenerNombreCompleto();
        };
        autores.insertar(autor, comparador);
        logManager.escribirLog("Autor agregado: " + autor.obtenerNombreCompleto());
        return true;
    } catch (const std::exception& e) {
        logManager.escribirLog("Error al agregar autor: " + std::string(e.what()));
        return false;
    }
}

// Mostrar todos los autores en orden (recorrido inorden)
void BibliotecaManager::mostrarAutores() const {
    auto mostrar = [](const Autor& autor) {
        std::cout << autor.obtenerNombreCompleto() << " - Fecha de nacimiento: " 
                  << autor.obtenerFechaNacimiento() << std::endl;
    };
    autores.recorrer(mostrar);
}

// Verificar si un autor existe en el árbol de autores
bool BibliotecaManager::existeAutor(const Autor& autor) const {
    auto igual = [&autor](const Autor& a, const Autor& b) {
        return a == b;
    };
    return autores.existe(autor, igual);
}

// Obtener el árbol de libros
ArbolBinario<Libro>& BibliotecaManager::getLibros() {
    return libros;
}

// Obtener el árbol de autores
ArbolBinario<Autor>& BibliotecaManager::getAutores() {
    return autores;
}
