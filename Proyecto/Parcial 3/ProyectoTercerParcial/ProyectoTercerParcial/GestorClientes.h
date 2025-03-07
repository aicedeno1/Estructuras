

#ifndef GESTOR_CLIENTES_H
#define GESTOR_CLIENTES_H

#include <vector>
#include <string>
#include "Cliente.h"
#include "Usuario.h"

class GestorClientes
{
private:
    std::vector<Cliente> clientes;
    std::string archivoClientes;
    bool evitarGuardar;

public:
    // Constructor
    GestorClientes();

    // Operaciones principales
    bool agregarCliente(const Cliente &cliente);
    bool eliminarCliente(const std::string &cedula);
    Cliente *buscarCliente(const std::string &cedula);
    Cliente *buscarClientePorUsuario(const std::string &username);
    std::vector<Cliente> listarClientes() const;

    // Verificación de existencia
    bool existeCliente(const std::string &cedula);
    bool existeUsuario(const std::string &username);

    // Validación de credenciales
    Usuario *autenticarUsuario(const std::string &username, const std::string &password);

    // Gestión de archivos
    void guardarClientesEnArchivo();
    void cargarClientesDesdeArchivo();

    // Métodos para backup
    void crearBackup(const std::string &nombreArchivo);
    void restaurarBackup(const std::string &nombreArchivo);

    // Configurar backup
    void setEvitarGuardar(bool valor);
};

#endif // GESTOR_CLIENTES_H