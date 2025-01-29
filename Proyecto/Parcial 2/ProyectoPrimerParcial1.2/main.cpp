/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación Nodo para Árbol Rojo-Negro                *
 * Autor:                          Stiven Diaz, Andres Cedeño                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#include "ArbolRojoNegro.h"
#include "Menu.h"
#include "BackupManager.h"
#include <windows.h>

int main()
{
    // Configurar la consola para usar UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Verifica y crea la carpeta de backups si no existe
    BackupManager::crearCarpetaSiNoExiste("backup");

    ArbolRojoNegro arbol;

    // Cargar los libros desde el archivo al iniciar
    try
    {
        arbol.cargarLibrosDesdeArchivo();
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error al cargar los libros desde el archivo: " << e.what() << std::endl;
        return 1;
    }

    mostrarMenu(arbol);
    return 0;
}
