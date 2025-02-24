#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <iomanip>
#include <memory>
#include "Banco.h"
#include "Cliente.h"
#include "Cuenta.h"
#include "Transaccion.h"

using namespace std;

// Definición de constantes de colores ANSI para mejorar la interfaz
const string COLOR_RESET = "\033[0m";
const string COLOR_TITULO = "\033[1;36m";  // Cian brillante
const string COLOR_MENU = "\033[1;33m";    // Amarillo brillante
const string COLOR_EXITO = "\033[1;32m";   // Verde brillante
const string COLOR_ERROR = "\033[1;31m";   // Rojo brillante
const string COLOR_INFO = "\033[1;34m";    // Azul brillante
const string COLOR_PROMPT = "\033[1;35m";  // Magenta brillante

// Función para limpiar la pantalla
void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Función para pausar y esperar entrada del usuario
void pausar() {
    cout << COLOR_PROMPT << "\nPresione Enter para continuar..." << COLOR_RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Función para limpiar el buffer de entrada
void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Función para mostrar línea decorativa
void mostrarLinea(char caracter = '=', int longitud = 80) {
    cout << string(longitud, caracter) << endl;
}

// Función para mostrar el título del banco
void mostrarTituloBanco(const string& nombreBanco) {
    limpiarPantalla();
    mostrarLinea('*');
    cout << COLOR_TITULO << setw(40 + nombreBanco.length()/2) << nombreBanco << COLOR_RESET << endl;
    cout << COLOR_TITULO << setw(46) << "SISTEMA DE BANCA EN LÍNEA" << COLOR_RESET << endl;
    mostrarLinea('*');
    cout << endl;
}

// Función para mostrar el menú principal
int mostrarMenuPrincipal() {
    int opcion;
    cout << COLOR_MENU << "===== MENÚ PRINCIPAL =====" << COLOR_RESET << endl;
    cout << "1. Iniciar sesión" << endl;
    cout << "2. Registrarse como nuevo cliente" << endl;
    cout << "3. Información del banco" << endl;
    cout << "0. Salir" << endl;
    cout << COLOR_PROMPT << "Seleccione una opción: " << COLOR_RESET;
    cin >> opcion;
    
    if (cin.fail()) {
        limpiarBuffer();
        return -1;
    }
    
    return opcion;
}

// Función para mostrar el menú del cliente
int mostrarMenuCliente(const string& nombreCliente) {
    int opcion;
    cout << COLOR_MENU << "===== MENÚ DE CLIENTE: " << nombreCliente << " =====" << COLOR_RESET << endl;
    cout << "1. Ver mis cuentas" << endl;
    cout << "2. Ver detalles de una cuenta" << endl;
    cout << "3. Realizar depósito" << endl;
    cout << "4. Realizar retiro" << endl;
    cout << "5. Realizar transferencia" << endl;
    cout << "6. Pagar servicio" << endl;
    cout << "7. Solicitar nueva cuenta" << endl;
    cout << "8. Actualizar información personal" << endl;
    cout << "0. Cerrar sesión" << endl;
    cout << COLOR_PROMPT << "Seleccione una opción: " << COLOR_RESET;
    cin >> opcion;
    
    if (cin.fail()) {
        limpiarBuffer();
        return -1;
    }
    
    return opcion;
}

// Función para registrar un nuevo cliente
void registrarNuevoCliente(Banco& banco) {
    string cedula, nombres, apellidos, correo, telefono, direccion, contrasena;
    
    limpiarPantalla();
    cout << COLOR_TITULO << "===== REGISTRO DE NUEVO CLIENTE =====" << COLOR_RESET << endl;
    
    cout << "Ingrese su número de cédula: ";
    cin >> cedula;
    limpiarBuffer();
    
    cout << "Ingrese sus nombres: ";
    getline(cin, nombres);
    
    cout << "Ingrese sus apellidos: ";
    getline(cin, apellidos);
    
    cout << "Ingrese su correo electrónico: ";
    getline(cin, correo);
    
    cout << "Ingrese su número de teléfono: ";
    getline(cin, telefono);
    
    cout << "Ingrese su dirección: ";
    getline(cin, direccion);
    
    cout << "Ingrese una contraseña: ";
    getline(cin, contrasena);
    
    if (banco.registrarCliente(cedula, nombres, apellidos, correo, telefono, direccion, contrasena)) {
        // Crear automáticamente una cuenta de ahorros con saldo inicial
        cout << COLOR_INFO << "\nAhora crearemos su primera cuenta de ahorros." << COLOR_RESET << endl;
        double saldoInicial;
        cout << "Ingrese el saldo inicial para su cuenta de ahorros: $";
        cin >> saldoInicial;
        
        if (cin.fail()) {
            limpiarBuffer();
            cout << COLOR_ERROR << "Monto inválido. Se creará la cuenta con saldo 0." << COLOR_RESET << endl;
            saldoInicial = 0.0;
        }
        
        if (banco.crearCuenta(cedula, AHORROS, saldoInicial)) {
            cout << COLOR_EXITO << "\n¡Registro completado con éxito! Puede iniciar sesión con su cédula y contraseña." << COLOR_RESET << endl;
        } else {
            cout << COLOR_ERROR << "\nError al crear la cuenta, pero su registro como cliente fue exitoso." << COLOR_RESET << endl;
        }
    } else {
        cout << COLOR_ERROR << "\nError en el registro. Intente nuevamente más tarde." << COLOR_RESET << endl;
    }
    
    pausar();
}

// Función para iniciar sesión
shared_ptr<Cliente> iniciarSesion(Banco& banco) {
    string cedula, contrasena;
    
    limpiarPantalla();
    cout << COLOR_TITULO << "===== INICIO DE SESIÓN =====" << COLOR_RESET << endl;
    
    cout << "Ingrese su número de cédula: ";
    cin >> cedula;
    limpiarBuffer();
    
    cout << "Ingrese su contraseña: ";
    getline(cin, contrasena);
    
    auto cliente = banco.autenticarCliente(cedula, contrasena);
    
    if (cliente) {
        cout << COLOR_EXITO << "\n¡Bienvenido/a, " << cliente->getNombreCompleto() << "!" << COLOR_RESET << endl;
        pausar();
        return cliente;
    } else {
        cout << COLOR_ERROR << "\nCredenciales incorrectas o cliente inactivo." << COLOR_RESET << endl;
        pausar();
        return nullptr;
    }
}

// Función para ver las cuentas del cliente
void verCuentasCliente(shared_ptr<Cliente> cliente) {
    limpiarPantalla();
    cout << COLOR_TITULO << "===== MIS CUENTAS =====" << COLOR_RESET << endl;
    
    cliente->mostrarCuentas();
    
    pausar();
}

// Función para ver detalles de una cuenta específica
void verDetallesCuenta(shared_ptr<Cliente> cliente) {
    string numeroCuenta;
    
    limpiarPantalla();
    cout << COLOR_TITULO << "===== DETALLES DE CUENTA =====" << COLOR_RESET << endl;
    
    cliente->mostrarCuentas();
    
    cout << "\nIngrese el número de cuenta para ver detalles: ";
    cin >> numeroCuenta;
    
    auto cuenta = cliente->buscarCuentaPorNumero(numeroCuenta);
    
    if (cuenta) {
        limpiarPantalla();
        cout << COLOR_TITULO << "===== DETALLES DE CUENTA " << numeroCuenta << " =====" << COLOR_RESET << endl;
        cuenta->mostrarDetalles();
        
        cout << "\n¿Desea ver el historial de transacciones? (s/n): ";
        char respuesta;
        cin >> respuesta;
        
        if (tolower(respuesta) == 's') {
            cuenta->mostrarHistorialTransacciones();
        }
    } else {
        cout << COLOR_ERROR << "Cuenta no encontrada o no le pertenece." << COLOR_RESET << endl;
    }
    
    pausar();
}

// Función para realizar un depósito
void realizarDeposito(shared_ptr<Cliente> cliente) {
    string numeroCuenta;
    double monto;
    string descripcion;
    
    limpiarPantalla();
    cout << COLOR_TITULO << "===== REALIZAR DEPÓSITO =====" << COLOR_RESET << endl;
    
    cliente->mostrarCuentas();
    
    cout << "\nIngrese el número de cuenta para el depósito: ";
    cin >> numeroCuenta;
    
    auto cuenta = cliente->buscarCuentaPorNumero(numeroCuenta);
    
    if (cuenta) {
        cout << "Ingrese el monto a depositar: $";
        cin >> monto;
        
        if (cin.fail()) {
            limpiarBuffer();
            cout << COLOR_ERROR << "Monto inválido." << COLOR_RESET << endl;
            pausar();
            return;
        }
        
        limpiarBuffer();
        cout << "Ingrese una descripción para el depósito: ";
        getline(cin, descripcion);
        
        if (cuenta->depositar(monto, descripcion)) {
            cout << COLOR_EXITO << "\nDepósito realizado con éxito. Nuevo saldo: $" 
                 << fixed << setprecision(2) << cuenta->getSaldo() << COLOR_RESET << endl;
        } else {
            cout << COLOR_ERROR << "\nError al realizar el depósito." << COLOR_RESET << endl;
        }
    } else {
        cout << COLOR_ERROR << "Cuenta no encontrada o no le pertenece." << COLOR_RESET << endl;
    }
    
    pausar();
}

// Función para realizar un retiro
void realizarRetiro(shared_ptr<Cliente> cliente) {
    string numeroCuenta;
    double monto;
    string descripcion;
    
    limpiarPantalla();
    cout << COLOR_TITULO << "===== REALIZAR RETIRO =====" << COLOR_RESET << endl;
    
    cliente->mostrarCuentas();
    
    cout << "\nIngrese el número de cuenta para el retiro: ";
    cin >> numeroCuenta;
    
    auto cuenta = cliente->buscarCuentaPorNumero(numeroCuenta);
    
    if (cuenta) {
        cout << "Saldo disponible: $" << fixed << setprecision(2) << cuenta->getSaldo() << endl;
        cout << "Ingrese el monto a retirar: $";
        cin >> monto;
        
        if (cin.fail()) {
            limpiarBuffer();
            cout << COLOR_ERROR << "Monto inválido." << COLOR_RESET << endl;
            pausar();
            return;
        }
        
        limpiarBuffer();
        cout << "Ingrese una descripción para el retiro: ";
        getline(cin, descripcion);
        
        if (cuenta->retirar(monto, descripcion)) {
            cout << COLOR_EXITO << "\nRetiro realizado con éxito. Nuevo saldo: $" 
                 << fixed << setprecision(2) << cuenta->getSaldo() << COLOR_RESET << endl;
        } else {
            cout << COLOR_ERROR << "\nError al realizar el retiro." << COLOR_RESET << endl;
        }
    } else {
        cout << COLOR_ERROR << "Cuenta no encontrada o no le pertenece." << COLOR_RESET << endl;
    }
    
    pausar();
}

// Función para realizar una transferencia
void realizarTransferencia(Banco& banco, shared_ptr<Cliente> cliente) {
    string cuentaOrigen, cuentaDestino;
    double monto;
    string descripcion;
    
    limpiarPantalla();
    cout << COLOR_TITULO << "===== REALIZAR TRANSFERENCIA =====" << COLOR_RESET << endl;
    
    cliente->mostrarCuentas();
    
    cout << "\nIngrese el número de su cuenta origen: ";
    cin >> cuentaOrigen;
    
    auto cuenta = cliente->buscarCuentaPorNumero(cuentaOrigen);
    
    if (!cuenta) {
        cout << COLOR_ERROR << "Cuenta origen no encontrada o no le pertenece." << COLOR_RESET << endl;
        pausar();
        return;
    }
    
    cout << "Saldo disponible: $" << fixed << setprecision(2) << cuenta->getSaldo() << endl;
    cout << "Ingrese el número de cuenta destino: ";
    cin >> cuentaDestino;
    
    if (cuentaOrigen == cuentaDestino) {
        cout << COLOR_ERROR << "No puede transferir a la misma cuenta." << COLOR_RESET << endl;
        pausar();
        return;
    }
    
    cout << "Ingrese el monto a transferir: $";
    cin >> monto;
    
    if (cin.fail()) {
        limpiarBuffer();
        cout << COLOR_ERROR << "Monto inválido." << COLOR_RESET << endl;
        pausar();
        return;
    }
    
    limpiarBuffer();
    cout << "Ingrese una descripción para la transferencia: ";
    getline(cin, descripcion);
    
    if (banco.realizarTransferencia(cuentaOrigen, cuentaDestino, monto, descripcion)) {
        cout << COLOR_EXITO << "\nTransferencia realizada con éxito. Nuevo saldo: $" 
             << fixed << setprecision(2) << cuenta->getSaldo() << COLOR_RESET << endl;
    } else {
        cout << COLOR_ERROR << "\nError al realizar la transferencia." << COLOR_RESET << endl;
    }
    
    pausar();
}

// Función para pagar servicios
void pagarServicio(Banco& banco, shared_ptr<Cliente> cliente) {
    string numeroCuenta, tipoServicio, referencia;
    double monto;
    
    limpiarPantalla();
    cout << COLOR_TITULO << "===== PAGO DE SERVICIOS =====" << COLOR_RESET << endl;
    
    cliente->mostrarCuentas();
    
    cout << "\nIngrese el número de cuenta para el pago: ";
    cin >> numeroCuenta;
    
    auto cuenta = cliente->buscarCuentaPorNumero(numeroCuenta);
    
    if (!cuenta) {
        cout << COLOR_ERROR << "Cuenta no encontrada o no le pertenece." << COLOR_RESET << endl;
        pausar();
        return;
    }
    
    cout << "Saldo disponible: $" << fixed << setprecision(2) << cuenta->getSaldo() << endl;
    
    limpiarBuffer();
    cout << "Tipos de servicios disponibles:" << endl;
    cout << "1. Agua" << endl;
    cout << "2. Luz" << endl;
    cout << "3. Teléfono" << endl;
    cout << "4. Internet" << endl;
    cout << "5. Otro" << endl;
    
    int opcionServicio;
    cout << "Seleccione el tipo de servicio: ";
    cin >> opcionServicio;
    
    switch (opcionServicio) {
        case 1: tipoServicio = "Agua"; break;
        case 2: tipoServicio = "Luz"; break;
        case 3: tipoServicio = "Teléfono"; break;
        case 4: tipoServicio = "Internet"; break;
        case 5: 
            limpiarBuffer();
            cout << "Ingrese el tipo de servicio: ";
            getline(cin, tipoServicio);
            break;
        default:
            cout << COLOR_ERROR << "Opción inválida." << COLOR_RESET << endl;
            pausar();
            return;
    }
    
    if (opcionServicio >= 1 && opcionServicio <= 4) {
        limpiarBuffer();
    }
    
    cout << "Ingrese el número de referencia o factura: ";
    getline(cin, referencia);
    
    cout << "Ingrese el monto a pagar: $";
    cin >> monto;
    
    if (cin.fail()) {
        limpiarBuffer();
        cout << COLOR_ERROR << "Monto inválido." << COLOR_RESET << endl;
        pausar();
        return;
    }
    
    if (banco.pagarServicio(numeroCuenta, tipoServicio, monto, referencia)) {
        cout << COLOR_EXITO << "\nPago de servicio realizado con éxito. Nuevo saldo: $" 
             << fixed << setprecision(2) << cuenta->getSaldo() << COLOR_RESET << endl;
    } else {
        cout << COLOR_ERROR << "\nError al realizar el pago de servicio." << COLOR_RESET << endl;
    }
    
    pausar();
}

// Función para solicitar una nueva cuenta
void solicitarNuevaCuenta(Banco& banco, shared_ptr<Cliente> cliente) {
    int tipoCuenta;
    double saldoInicial;
    
    limpiarPantalla();
    cout << COLOR_TITULO << "===== SOLICITUD DE NUEVA CUENTA =====" << COLOR_RESET << endl;
    
    cout << "Tipos de cuenta disponibles:" << endl;
    cout << "1. Cuenta de Ahorros" << endl;
    cout << "2. Cuenta Corriente" << endl;
    cout << "Seleccione el tipo de cuenta: ";
    cin >> tipoCuenta;
    
    if (cin.fail() || (tipoCuenta != 1 && tipoCuenta != 2)) {
        limpiarBuffer();
        cout << COLOR_ERROR << "Opción inválida." << COLOR_RESET << endl;
        pausar();
        return;
    }
    
    TipoCuenta tipo = (tipoCuenta == 1) ? AHORROS : CORRIENTE;
    
    cout << "Ingrese el saldo inicial para la nueva cuenta: $";
    cin >> saldoInicial;
    
    if (cin.fail()) {
        limpiarBuffer();
        cout << COLOR_ERROR << "Monto inválido." << COLOR_RESET << endl;
        pausar();
        return;
    }
    
    if (banco.crearCuenta(cliente->getCedula(), tipo, saldoInicial)) {
        cout << COLOR_EXITO << "\nCuenta creada exitosamente." << COLOR_RESET << endl;
    } else {
        cout << COLOR_ERROR << "\nError al crear la cuenta." << COLOR_RESET << endl;
    }
    
    pausar();
}

// Función para actualizar información personal
void actualizarInformacionPersonal(shared_ptr<Cliente> cliente) {
    int opcion;
    
    limpiarPantalla();
    cout << COLOR_TITULO << "===== ACTUALIZAR INFORMACIÓN PERSONAL =====" << COLOR_RESET << endl;
    
    cliente->mostrarInformacion();
    
    cout << "\n¿Qué información desea actualizar?" << endl;
    cout << "1. Correo electrónico" << endl;
    cout << "2. Número de teléfono" << endl;
    cout << "3. Dirección" << endl;
    cout << "4. Contraseña" << endl;
    cout << "0. Volver al menú anterior" << endl;
    cout << COLOR_PROMPT << "Seleccione una opción: " << COLOR_RESET;
    cin >> opcion;
    
    if (cin.fail()) {
        limpiarBuffer();
        cout << COLOR_ERROR << "Opción inválida." << COLOR_RESET << endl;
        pausar();
        return;
    }
    
    limpiarBuffer();
    
    string nuevoValor;
    bool actualizado = false;
    
    switch (opcion) {
        case 1:
            cout << "Ingrese el nuevo correo electrónico: ";
            getline(cin, nuevoValor);
            cliente->setCorreo(nuevoValor);
            actualizado = true;
            break;
            
        case 2:
            cout << "Ingrese el nuevo número de teléfono: ";
            getline(cin, nuevoValor);
            cliente->setTelefono(nuevoValor);
            actualizado = true;
            break;
            
        case 3:
            cout << "Ingrese la nueva dirección: ";
            getline(cin, nuevoValor);
            cliente->setDireccion(nuevoValor);
            actualizado = true;
            break;
            
        case 4:
            cout << "Ingrese la nueva contraseña: ";
            getline(cin, nuevoValor);
            cliente->setContrasena(nuevoValor);
            actualizado = true;
            break;
            
        case 0:
            return;
            
        default:
            cout << COLOR_ERROR << "Opción inválida." << COLOR_RESET << endl;
            break;
    }
    
    if (actualizado) {
        cout << COLOR_EXITO << "\nInformación actualizada exitosamente." << COLOR_RESET << endl;
    }
    
    pausar();
}

// Función para mostrar información del banco
void mostrarInformacionBanco(const string& nombreBanco) {
    limpiarPantalla();
    cout << COLOR_TITULO << "===== INFORMACIÓN DEL BANCO =====" << COLOR_RESET << endl;
    
    cout << "Nombre: " << nombreBanco << endl;
    cout << "Dirección: Av. Principal 123, Quito, Ecuador" << endl;
    cout << "Teléfono: (02) 123-4567" << endl;
    cout << "Email: info@" << nombreBanco << ".com.ec" << endl;
    cout << "Horario de atención: Lunes a Viernes de 9:00 a 17:00" << endl;
    cout << "Página web: www." << nombreBanco << ".com.ec" << endl;
    
    pausar();
}

// Función principal
int main() {
    // Crear instancia del banco
    Banco miBanco("BANCO PICHINCHA VIRTUAL");
    
    // Variables para el flujo de programa
    int opcion;
    shared_ptr<Cliente> clienteActual = nullptr;
    
    // Crear algunos datos de prueba
    miBanco.registrarCliente("1234567890", "Juan", "Pérez", "juan@ejemplo.com", "0987654321", "Quito", "12345");
    miBanco.crearCuenta("1234567890", AHORROS, 1000.0);
    miBanco.crearCuenta("1234567890", CORRIENTE, 500.0);
    
    miBanco.registrarCliente("0987654321", "María", "López", "maria@ejemplo.com", "0912345678", "Guayaquil", "12345");
    miBanco.crearCuenta("0987654321", AHORROS, 2000.0);
    
    // Bucle principal del programa
    while (true) {
        if (clienteActual == nullptr) {
            // Mostrar menú principal si no hay sesión iniciada
            mostrarTituloBanco(miBanco.nombre);
            opcion = mostrarMenuPrincipal();
            
            switch (opcion) {
                case 1: // Iniciar sesión
                    clienteActual = iniciarSesion(miBanco);
                    break;
                    
                case 2: // Registrarse como nuevo cliente
                    registrarNuevoCliente(miBanco);
                    break;
                    
                case 3: // Información del banco
                    mostrarInformacionBanco(miBanco.nombre);
                    break;
                    
                case 0: // Salir
                    limpiarPantalla();
                    cout << COLOR_EXITO << "¡Gracias por utilizar el sistema de banca en línea!" << COLOR_RESET << endl;
                    return 0;
                    
                default:
                    cout << COLOR_ERROR << "Opción inválida. Intente nuevamente." << COLOR_RESET << endl;
                    pausar();
                    break;
            }
        } else {
            // Mostrar menú del cliente si hay sesión iniciada
            mostrarTituloBanco(miBanco.nombre);
            opcion = mostrarMenuCliente(clienteActual->getNombreCompleto());
            
            switch (opcion) {
                case 1: // Ver mis cuentas
                    verCuentasCliente(clienteActual);
                    break;
                    
                case 2: // Ver detalles de una cuenta
                    verDetallesCuenta(clienteActual);
                    break;
                    
                case 3: // Realizar depósito
                    realizarDeposito(clienteActual);
                    break;
                    
                case 4: // Realizar retiro
                    realizarRetiro(clienteActual);
                    break;
                    
                case 5: // Realizar transferencia
                    realizarTransferencia(miBanco, clienteActual);
                    break;
                    
                case 6: // Pagar servicio
                    pagarServicio(miBanco, clienteActual);
                    break;
                    
                case 7: // Solicitar nueva cuenta
                    solicitarNuevaCuenta(miBanco, clienteActual);
                    break;
                    
                case 8: // Actualizar información personal
                    actualizarInformacionPersonal(clienteActual);
                    break;
                    
                case 0: // Cerrar sesión
                    cout << COLOR_INFO << "Sesión cerrada correctamente." << COLOR_RESET << endl;
                    clienteActual = nullptr;
                    pausar();
                    break;
                    
                default:
                    cout << COLOR_ERROR << "Opción inválida. Intente nuevamente." << COLOR_RESET << endl;
                    pausar();
                    break;
            }
        }
    }
    
    return 0;
}