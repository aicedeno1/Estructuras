/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Gestión de backups para sistema bancario                 *
 * Autor:                           Diaz Stiven, Cedenio Andres                             *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          03/03/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#ifndef BACKUP_MANAGER_H
#define BACKUP_MANAGER_H

#include <string>
#include <vector>
#include "ArbolCuentas.h"
#include "GestorClientes.h"

class BackupManager
{
public:
    // Métodos para gestión de carpetas
    static void crearCarpetaSiNoExiste(const std::string &ruta);
    static std::vector<std::string> listarArchivosEnCarpeta(const std::string &carpeta);

    // Métodos para backup y restauración
    static void restaurarBackupCuentas(ArbolCuentas &arbol);
    static void restaurarBackupClientes(GestorClientes &gestor);

    // Método para realizar backup completo del sistema
    static void crearBackupCompleto(ArbolCuentas &arbol, GestorClientes &gestor);

    // Métodos para historial y seguimiento (backtracking)
    static void registrarOperacion(const std::string &operacion, const std::string &detalles);
    static std::vector<std::string> obtenerHistorialOperaciones(const std::string &fecha);
    static void limpiarHistorialOperaciones(int diasAntiguedad);
};

#endif // BACKUP_MANAGER_H