/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Archivo principal de proyecto                            *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/


#include "ListaCircularDoble.cpp"
#include "Menu.cpp"

int main() {
    // Configurar la consola para usar UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
     // Verifica y crea la carpeta de backups si no existe
    BackupManager::crearCarpetaSiNoExiste("backup");

    ListaCircularDoble lista;
    // Cargar los libros desde el archivo al iniciar
    try {
        lista.cargarLibrosDesdeArchivo();
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error al cargar los libros desde el archivo: " << e.what() << std::endl;
        return 1;
    }

    mostrarMenu(lista);
    return 0;
}

