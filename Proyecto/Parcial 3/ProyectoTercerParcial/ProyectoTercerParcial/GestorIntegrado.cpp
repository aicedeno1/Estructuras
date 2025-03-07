/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación del gestor integrado de clientes y cuentas*
 * Autor:                              Diaz Stiven, Cedenio Andres                          *
 * Fecha de creacion:              06/03/2025                                               *
 * Fecha de modificacion:          06/03/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "GestorIntegrado.h"
#include "Validaciones.h"
#include "BackupManager.h"
#include "ArbolCuentas.h"
#include "Cliente.h"
#include <ctime>
#include <random>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <limits>

using namespace std;

// Constructor
GestorIntegrado::GestorIntegrado(GestorClientes &gestorClientes, ArbolCuentas &arbolCuentas, BackupManager &backupManager)
    : gestorClientes(gestorClientes), arbolCuentas(arbolCuentas), backupManager(backupManager) {}

// Método para limpiar el buffer de entrada
void GestorIntegrado::limpiarBuffer() const
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Método para generar un número de cuenta único
string GestorIntegrado::generarNumeroCuenta() const
{
    // Obtener fecha actual para parte del número
    time_t t = time(nullptr);
    tm *ahora = localtime(&t);
    int anio = 1900 + ahora->tm_year;

    // Generar 8 dígitos aleatorios
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 9);

    string numeroCuenta = to_string(anio);
    for (int i = 0; i < 8; i++)
    {
        numeroCuenta += to_string(dis(gen));
    }

    // Verificar que no exista una cuenta con ese número
    while (arbolCuentas.buscarCuenta(numeroCuenta))
    {
        numeroCuenta = to_string(anio);
        for (int i = 0; i < 8; i++)
        {
            numeroCuenta += to_string(dis(gen));
        }
    }

    return numeroCuenta;
}

// Método para registrar un cliente con una cuenta inicial
bool GestorIntegrado::registrarClienteConCuenta(
    const string &cedula, const string &nombre, const string &apellido,
    const string &direccion, const string &telefono, const string &email,
    const Fecha &fechaNacimiento, const string &username, const string &password,
    TipoCuenta tipoCuenta, double saldoInicial)
{
    // Validaciones básicas
    if (!Cliente::validarCedula(cedula))
    {
        cout << "Error: Cédula inválida." << endl;
        return false;
    }

    if (gestorClientes.existeCliente(cedula))
    {
        cout << "Error: Ya existe un cliente con esa cédula." << endl;
        return false;
    }

    if (gestorClientes.existeUsuario(username))
    {
        cout << "Error: Ya existe un usuario con ese nombre." << endl;
        return false;
    }

    // Crear cliente
    Cliente nuevoCliente(cedula, nombre, apellido, direccion, telefono,
                         email, fechaNacimiento, username,
                         Usuario::cifrarPassword(password));

    // Agregar cliente
    if (!gestorClientes.agregarCliente(nuevoCliente))
    {
        cout << "Error: No se pudo agregar el cliente." << endl;
        return false;
    }

    // Generar número de cuenta
    string numeroCuenta = generarNumeroCuenta();

    // Crear cuenta
    Fecha fechaActual = Fecha::obtenerFechaActual();
    Cuenta nuevaCuenta(numeroCuenta, nuevoCliente, saldoInicial, fechaActual, tipoCuenta);

    // Agregar cuenta
    try
    {
        arbolCuentas.agregarCuenta(nuevaCuenta);

        // Registrar operación en el backtracking
        backupManager.registrarOperacion("REGISTRO_CLIENTE_CUENTA",
                                         "Cédula: " + cedula +
                                             ", Nombre: " + nombre + " " + apellido +
                                             ", Cuenta: " + numeroCuenta);

        cout << "Cliente y cuenta registrados correctamente." << endl;
        cout << "Número de cuenta: " << numeroCuenta << endl;

        return true;
    }
    catch (const exception &e)
    {
        // Si falla la creación de la cuenta, eliminar el cliente también
        gestorClientes.eliminarCliente(cedula);
        cout << "Error al crear la cuenta: " << e.what() << endl;
        return false;
    }
}

// Método para buscar cliente con validación de buffer y cédula
Cliente *GestorIntegrado::buscarClienteSeguro(const string &cedula) const
{
    // Validar formato de cédula
    if (!Cliente::validarCedula(cedula))
    {
        cout << "Error: Formato de cédula no válido." << endl;
        return nullptr;
    }

    // Buscar el cliente
    Cliente *cliente = gestorClientes.buscarCliente(cedula);
    if (!cliente)
    {
        cout << "Error: No se encontró un cliente con esa cédula." << endl;
        return nullptr;
    }

    return cliente;
}

bool GestorIntegrado::desactivarCuentasCliente(const string &cedula)
{
    // Buscar cliente de forma segura
    Cliente *cliente = buscarClienteSeguro(cedula);
    if (!cliente)
    {
        return false;
    }

    // Obtener todas las cuentas del cliente
    vector<Cuenta> cuentasCliente = arbolCuentas.buscarCuentasPorCliente(cedula);

    // Marcar todas las cuentas como inactivas
    bool todasDesactivadas = true;
    for (const auto &cuenta : cuentasCliente)
    {
        try
        {
            NodoCuenta *nodoCuenta = arbolCuentas.buscarCuenta(cuenta.getNumeroCuenta());
            if (nodoCuenta)
            {
                nodoCuenta->cuenta.setActiva(false);
                nodoCuenta->cuenta.setEstadoPersonalizado("Desactivada por administrador");
            }
            else
            {
                todasDesactivadas = false;
                cout << "Error: No se encontró la cuenta " << cuenta.getNumeroCuenta() << endl;
            }
        }
        catch (const exception &e)
        {
            cout << "Error al desactivar cuenta " << cuenta.getNumeroCuenta() << ": " << e.what() << endl;
            todasDesactivadas = false;
        }
    }

    // Guardar los cambios
    arbolCuentas.guardarCuentasEnArchivo();

    // Registrar operación en el backtracking
    backupManager.registrarOperacion("DESACTIVAR_CUENTAS_CLIENTE",
                                     "Cédula: " + cedula +
                                         ", Nombre: " + cliente->getNombreCompleto() +
                                         ", Cuentas desactivadas: " + to_string(cuentasCliente.size()));

    if (todasDesactivadas)
    {
        cout << "Todas las cuentas del cliente fueron desactivadas correctamente." << endl;
    }
    else
    {
        cout << "Algunas cuentas no pudieron ser desactivadas." << endl;
    }
    return todasDesactivadas;
}

// Método para crear una cuenta adicional para un cliente existente
bool GestorIntegrado::crearCuentaAdicional(const string &cedula, TipoCuenta tipoCuenta, double saldoInicial)
{
    // Buscar cliente de forma segura
    Cliente *cliente = buscarClienteSeguro(cedula);
    if (!cliente)
    {
        return false;
    }

    // Generar número de cuenta
    string numeroCuenta = generarNumeroCuenta();

    // Crear la cuenta
    Fecha fechaActual = Fecha::obtenerFechaActual();
    Cuenta nuevaCuenta(numeroCuenta, *cliente, saldoInicial, fechaActual, tipoCuenta);

    // Agregar la cuenta al árbol
    try
    {
        arbolCuentas.agregarCuenta(nuevaCuenta);

        // Registrar operación en el backtracking
        backupManager.registrarOperacion("CREAR_CUENTA_ADICIONAL",
                                         "Número: " + numeroCuenta +
                                             ", Tipo: " + nuevaCuenta.getTipoString() +
                                             ", Titular: " + cliente->getNombreCompleto());

        cout << "Cuenta adicional creada correctamente." << endl;
        cout << "Número de cuenta: " << numeroCuenta << endl;

        return true;
    }
    catch (const exception &e)
    {
        cout << "Error al crear la cuenta: " << e.what() << endl;
        return false;
    }
}

// Verificar que un cliente tenga al menos una cuenta activa
bool GestorIntegrado::clienteTieneCuentaActiva(const string &cedula) const
{
    vector<Cuenta> cuentasCliente = arbolCuentas.buscarCuentasPorCliente(cedula);

    for (const auto &cuenta : cuentasCliente)
    {
        if (cuenta.isActiva())
        {
            return true;
        }
    }

    return false;
}

// Modificar cliente con validación de datos
bool GestorIntegrado::modificarClienteSeguro(const string &cedula, const string &campo, const string &nuevoValor)
{
    // Buscar cliente de forma segura
    Cliente *cliente = buscarClienteSeguro(cedula);
    if (!cliente)
    {
        return false;
    }

    // Validar y aplicar la modificación según el campo
    if (campo == "nombre")
    {
        if (nuevoValor.empty() || !Validaciones::soloLetrasYEspacios(nuevoValor))
        {
            cout << "Error: Nombre inválido. Debe contener solo letras y espacios." << endl;
            return false;
        }
        cliente->setNombre(nuevoValor);
    }
    else if (campo == "apellido")
    {
        if (nuevoValor.empty() || !Validaciones::soloLetrasYEspacios(nuevoValor))
        {
            cout << "Error: Apellido inválido. Debe contener solo letras y espacios." << endl;
            return false;
        }
        cliente->setApellido(nuevoValor);
    }
    else if (campo == "direccion")
    {
        if (nuevoValor.empty())
        {
            cout << "Error: Dirección inválida. No puede estar vacía." << endl;
            return false;
        }
        cliente->setDireccion(nuevoValor);
    }
    else if (campo == "telefono")
    {
        if (!Validaciones::esTelefonoValido(nuevoValor))
        {
            cout << "Error: Teléfono inválido. Debe contener 10 dígitos." << endl;
            return false;
        }
        cliente->setTelefono(nuevoValor);
    }
    else if (campo == "email")
    {
        if (!Validaciones::esEmailValido(nuevoValor))
        {
            cout << "Error: Email inválido. Formato incorrecto." << endl;
            return false;
        }
        cliente->setEmail(nuevoValor);
    }
    else
    {
        cout << "Error: Campo desconocido." << endl;
        return false;
    }

    // Guardar cambios
    gestorClientes.guardarClientesEnArchivo();

    // Registrar operación en el backtracking
    backupManager.registrarOperacion("MODIFICAR_CLIENTE",
                                     "Cédula: " + cedula + ", Campo: " + campo + ", Nuevo valor: " + nuevoValor);

    cout << "Cliente modificado correctamente." << endl;
    return true;
}

// Obtener todas las cuentas de un cliente
vector<Cuenta> GestorIntegrado::obtenerCuentasCliente(const string &cedula) const
{
    return arbolCuentas.buscarCuentasPorCliente(cedula);
}

// Cerrar una cuenta específica si el cliente tiene más de una cuenta activa
bool GestorIntegrado::cerrarCuentaSeguro(const string &numeroCuenta)
{
    // Buscar la cuenta
    NodoCuenta *nodoCuenta = arbolCuentas.buscarCuenta(numeroCuenta);
    if (!nodoCuenta)
    {
        cout << "Error: No se encontró una cuenta con ese número." << endl;
        return false;
    }

    // Verificar que la cuenta esté activa
    if (!nodoCuenta->cuenta.isActiva())
    {
        cout << "Error: La cuenta ya está cerrada." << endl;
        return false;
    }

    // Verificar que la cuenta tenga saldo cero
    if (nodoCuenta->cuenta.getSaldo() > 0)
    {
        cout << "Error: La cuenta tiene saldo pendiente ($"
             << fixed << setprecision(2) << nodoCuenta->cuenta.getSaldo()
             << "). Debe retirar todo el saldo antes de cerrar la cuenta." << endl;
        return false;
    }

    // Obtener el titular de la cuenta
    string cedulaTitular = nodoCuenta->cuenta.getTitular().getCedula();

    // Verificar que el cliente tenga más de una cuenta activa
    vector<Cuenta> cuentasCliente = arbolCuentas.buscarCuentasPorCliente(cedulaTitular);

    int cuentasActivas = 0;
    for (const auto &cuenta : cuentasCliente)
    {
        if (cuenta.isActiva())
        {
            cuentasActivas++;
        }
    }

    if (cuentasActivas <= 1)
    {
        cout << "Error: No se puede cerrar la única cuenta activa del cliente." << endl;
        cout << "El cliente debe tener al menos una cuenta activa en todo momento." << endl;
        return false;
    }

    // Cerrar la cuenta
    nodoCuenta->cuenta.setActiva(false);

    // Guardar cambios
    arbolCuentas.guardarCuentasEnArchivo();

    // Registrar operación en el backtracking
    backupManager.registrarOperacion("CERRAR_CUENTA",
                                     "Número: " + numeroCuenta +
                                         ", Titular: " + nodoCuenta->cuenta.getTitular().getNombreCompleto());

    cout << "Cuenta cerrada correctamente." << endl;
    return true;
}