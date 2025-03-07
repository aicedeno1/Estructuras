

#ifndef GESTOR_INTEGRADO_H
#define GESTOR_INTEGRADO_H

#include "GestorClientes.h"
#include "ArbolCuentas.h"
#include "BackupManager.h"
#include <string>
#include <vector>

class GestorIntegrado
{
private:
    GestorClientes &gestorClientes;
    ArbolCuentas &arbolCuentas;
    BackupManager &backupManager;

    // Método para generar un número de cuenta único
    std::string generarNumeroCuenta() const;

    // Método auxiliar para limpiar el buffer de entrada
    void limpiarBuffer() const;

public:
    // Constructor
    GestorIntegrado(GestorClientes &gestorClientes, ArbolCuentas &arbolCuentas, BackupManager &backupManager);

    // Métodos para gestión integrada de clientes y cuentas
    bool registrarClienteConCuenta(
        const std::string &cedula, const std::string &nombre, const std::string &apellido,
        const std::string &direccion, const std::string &telefono, const std::string &email,
        const Fecha &fechaNacimiento, const std::string &username, const std::string &password,
        TipoCuenta tipoCuenta, double saldoInicial);

    // Buscar cliente por cédula (con manejo de buffer y validación)
    Cliente *buscarClienteSeguro(const std::string &cedula) const;

    // Eliminar cliente y todas sus cuentas
    bool eliminarClienteYCuentas(const std::string &cedula);

    // Crear una cuenta adicional para un cliente existente
    bool crearCuentaAdicional(const std::string &cedula, TipoCuenta tipoCuenta, double saldoInicial);

    // Verificar que un cliente tenga al menos una cuenta activa
    bool clienteTieneCuentaActiva(const std::string &cedula) const;

    // Modificar cliente con validación de datos
    bool modificarClienteSeguro(const std::string &cedula, const std::string &campo, const std::string &nuevoValor);

    // Obtener todas las cuentas de un cliente
    std::vector<Cuenta> obtenerCuentasCliente(const std::string &cedula) const;

    // Cerrar una cuenta específica si el cliente tiene más de una cuenta activa
    bool cerrarCuentaSeguro(const std::string &numeroCuenta);
    bool desactivarCuentasCliente(const std::string &cedula);
};

#endif // GESTOR_INTEGRADO_H