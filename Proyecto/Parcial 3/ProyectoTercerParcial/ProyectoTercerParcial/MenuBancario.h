

#ifndef MENU_BANCARIO_H
#define MENU_BANCARIO_H

#include "ArbolCuentas.h"
#include "GestorClientes.h"
#include "Usuario.h"
#include "ListaCircularMenu.h"
#include "BackupManager.h"
#include "EstadisticasBancarias.h"
#include "GestorIntegrado.h"

class MenuBancario
{
private:
    ArbolCuentas &arbolCuentas;
    GestorClientes &gestorClientes;
    Usuario *usuarioActual;
    BackupManager &backupManager;
    EstadisticasBancarias &estadisticas;

    // Métodos para mostrar menús según el tipo de usuario
    void mostrarMenuAdmin();
    void mostrarMenuCliente();
    void modificarDatosCliente(Cliente *cliente);
    void generarQRParaTransferencia();

    // Métodos para operaciones de administrador
    void gestionarClientes();
    void gestionarCuentas();
    void administrarSistema();
    void generarReportes();

    // Métodos para operaciones de cliente
    void consultarCuentas();
    void realizarTransacciones();
    void verHistorial();
    void modificarPerfil();

    // Métodos auxiliares para la gestión de cuentas
    void crearNuevaCuenta();
    void cerrarCuenta();
    void listarTodasLasCuentas();
    void buscarCuentaPorNumero();

    // Métodos auxiliares para gestión de clientes
    void agregarNuevoCliente();
    void editarCliente();
    void eliminarCliente();
    void listarTodosLosClientes();
    void buscarClientePorCedula();

    // Métodos auxiliares para transacciones
    void realizarDeposito();
    void realizarRetiro();
    void realizarTransferencia();

    // Método auxiliar para leer solo entrada numérica
    std::string leerSoloNumeros(bool permitirDecimal = false);

    // Métodos para validación de entrada en tiempo real
    std::string leerSoloDigitos(const std::string &mensaje);
    std::string leerSoloLetras(const std::string &mensaje);
    std::string leerLetrasYEspacios(const std::string &mensaje);
    std::string leerTelefono(const std::string &mensaje);
    std::string leerEmail(const std::string &mensaje);
    std::string leerFecha(const std::string &mensaje);
    std::string leerUsername(const std::string &mensaje);
    std::string leerPassword(const std::string &mensaje);
    std::string leerDireccion(const std::string &mensaje);

public:
    // Constructor
    MenuBancario(ArbolCuentas &arbolCuentas, GestorClientes &gestorClientes,
                 BackupManager &backupManager, EstadisticasBancarias &estadisticas);

    // Método para iniciar sesión
    bool iniciarSesion();

    // Método para mostrar el menú principal
    void mostrarMenuPrincipal();

    // Método para cerrar sesión
    void cerrarSesion();
};

#endif // MENU_BANCARIO_H