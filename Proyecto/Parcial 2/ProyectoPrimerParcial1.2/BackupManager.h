/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación Nodo para Árbol Rojo-Negro                *
 * Autor:                          Stiven Diaz, Andres Cedeño                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/
#ifndef BACKUPMANAGER_H
#define BACKUPMANAGER_H

#include <string>
#include <vector>
#include "ArbolRojoNegro.h"

class BackupManager
{
public:
    // Métodos estáticos de la clase
    static void crearCarpetaSiNoExiste(const std::string &ruta);
    static std::vector<std::string> listarArchivosEnCarpeta(const std::string &carpeta);
    static void restaurarBackup(ArbolRojoNegro &arbol);

private:
    // Constructor privado para evitar instanciación
    BackupManager() = default;
};

#endif // BACKUPMANAGER_H
