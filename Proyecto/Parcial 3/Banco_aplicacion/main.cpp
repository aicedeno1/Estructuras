#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include "Banco.h"

// Función para mostrar el menú de administrador/desarrollador
void mostrarMenuDesarrollador(Banco &banco);

// Función para mostrar el menú de cliente
void mostrarMenuCliente(Banco &banco, std::shared_ptr<Cliente> cliente);

// Función para validar entrada numérica
bool validarNumero(const std::string &str);

// Función para validar cédula (formato básico)
bool validarCedula(const std::string &cedula);

// Función para validar correo electrónico (formato básico)
bool validarCorreo(const std::string &correo);

// Función para validar número de teléfono (formato básico)
bool validarTelefono(const std::string &telefono);

// Función para crear respaldo de datos
bool crearRespaldo(const Banco &banco, const std::string &tipoArchivo);

int main()
{
    // Inicializar el banco
    Banco banco("Mi Banco");

    // Intentar cargar datos previos
    if (!banco.cargarDatos("datos_banco.dat"))
    {
        std::cout << "No se encontraron datos previos. Se iniciará con un banco vacío." << std::endl;
    }

    bool salir = false;

    while (!salir)
    {
        std::cout << "\n===== SISTEMA BANCARIO =====" << std::endl;
        std::cout << "1. Acceso como cliente" << std::endl;
        std::cout << "2. Acceso como desarrollador/administrador" << std::endl;
        std::cout << "3. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";

        std::string opcionStr;
        std::getline(std::cin, opcionStr);

        if (!validarNumero(opcionStr))
        {
            std::cout << "Error: Ingrese un número válido." << std::endl;
            continue;
        }

        int opcion = std::stoi(opcionStr);

        switch (opcion)
        {
        case 1:
        {
            // Acceso como cliente
            std::string cedula, contrasena;

            std::cout << "\nAcceso de Cliente" << std::endl;
            std::cout << "Ingrese su cédula: ";
            std::getline(std::cin, cedula);

            if (!validarCedula(cedula))
            {
                std::cout << "Error: Formato de cédula inválido." << std::endl;
                continue;
            }

            std::cout << "Ingrese su contraseña: ";
            std::getline(std::cin, contrasena);

            auto cliente = banco.autenticarCliente(cedula, contrasena);

            if (cliente)
            {
                mostrarMenuCliente(banco, cliente);
            }
            else
            {
                std::cout << "Error: Credenciales inválidas o cliente inactivo." << std::endl;
            }
            break;
        }
        case 2:
        {
            // Acceso como desarrollador/administrador
            std::string contrasenaAdmin;
            std::cout << "\nAcceso de Desarrollador/Administrador" << std::endl;
            std::cout << "Ingrese la contraseña de administrador: ";
            std::getline(std::cin, contrasenaAdmin);

            if (contrasenaAdmin == "admin123")
            { // En un sistema real, usar mecanismos más seguros
                mostrarMenuDesarrollador(banco);
            }
            else
            {
                std::cout << "Error: Contraseña de administrador incorrecta." << std::endl;
            }
            break;
        }
        case 3:
            // Guardar datos antes de salir
            banco.guardarDatos("datos_banco.dat");
            std::cout << "¡Gracias por usar el sistema bancario!" << std::endl;
            salir = true;
            break;
        default:
            std::cout << "Opción inválida. Intente nuevamente." << std::endl;
            break;
        }
    }

    return 0;
}

void mostrarMenuCliente(Banco &banco, std::shared_ptr<Cliente> cliente)
{
    bool salir = false;

    while (!salir)
    {
        std::cout << "\n===== MENÚ DE CLIENTE =====" << std::endl;
        std::cout << "Bienvenido, " << cliente->getNombreCompleto() << std::endl;
        std::cout << "1. Ver mis datos personales" << std::endl;
        std::cout << "2. Ver mis cuentas" << std::endl;
        std::cout << "3. Realizar transferencia" << std::endl;
        std::cout << "4. Pagar servicio" << std::endl;
        std::cout << "5. Ver historial de transacciones" << std::endl;
        std::cout << "6. Ver gráfico de estados de cuenta" << std::endl;
        std::cout << "7. Cambiar información personal" << std::endl;
        std::cout << "8. Cerrar sesión" << std::endl;
        std::cout << "Seleccione una opción: ";

        std::string opcionStr;
        std::getline(std::cin, opcionStr);

        if (!validarNumero(opcionStr))
        {
            std::cout << "Error: Ingrese un número válido." << std::endl;
            continue;
        }

        int opcion = std::stoi(opcionStr);

        switch (opcion)
        {
        case 1:
            // Ver datos personales
            cliente->mostrarInformacion();
            break;
        case 2:
            // Ver cuentas
            cliente->mostrarCuentas();
            break;
        case 3:
        {
            // Realizar transferencia
            std::string cuentaOrigen, cuentaDestino, montoStr, descripcion;

            cliente->mostrarCuentas();
            std::cout << "Ingrese número de cuenta origen: ";
            std::getline(std::cin, cuentaOrigen);

            auto cuenta = cliente->buscarCuentaPorNumero(cuentaOrigen);
            if (!cuenta)
            {
                std::cout << "Error: Cuenta no encontrada o no le pertenece." << std::endl;
                break;
            }

            std::cout << "Ingrese número de cuenta destino: ";
            std::getline(std::cin, cuentaDestino);

            std::cout << "Ingrese monto a transferir: ";
            std::getline(std::cin, montoStr);

            if (!validarNumero(montoStr))
            {
                std::cout << "Error: Monto inválido." << std::endl;
                break;
            }

            double monto = std::stod(montoStr);

            std::cout << "Ingrese descripción: ";
            std::getline(std::cin, descripcion);

            if (banco.realizarTransferencia(cuentaOrigen, cuentaDestino, monto, descripcion))
            {
                std::cout << "Transferencia realizada exitosamente." << std::endl;
            }
            break;
        }
        case 4:
        {
            // Pagar servicio
            std::string numeroCuenta, tipoServicio, montoStr, referencia;

            cliente->mostrarCuentas();
            std::cout << "Ingrese número de cuenta: ";
            std::getline(std::cin, numeroCuenta);

            auto cuenta = cliente->buscarCuentaPorNumero(numeroCuenta);
            if (!cuenta)
            {
                std::cout << "Error: Cuenta no encontrada o no le pertenece." << std::endl;
                break;
            }

            std::cout << "Ingrese tipo de servicio (Luz, Agua, Internet, etc.): ";
            std::getline(std::cin, tipoServicio);

            std::cout << "Ingrese monto a pagar: ";
            std::getline(std::cin, montoStr);

            if (!validarNumero(montoStr))
            {
                std::cout << "Error: Monto inválido." << std::endl;
                break;
            }

            double monto = std::stod(montoStr);

            std::cout << "Ingrese número de referencia: ";
            std::getline(std::cin, referencia);

            if (banco.pagarServicio(numeroCuenta, tipoServicio, monto, referencia))
            {
                std::cout << "Pago de servicio realizado exitosamente." << std::endl;
            }
            break;
        }
        case 5:
        {
            // Ver historial de transacciones
            std::string numeroCuenta;

            cliente->mostrarCuentas();
            std::cout << "Ingrese número de cuenta para ver historial: ";
            std::getline(std::cin, numeroCuenta);

            auto cuenta = cliente->buscarCuentaPorNumero(numeroCuenta);
            if (cuenta)
            {
                cuenta->mostrarHistorialTransacciones();
            }
            else
            {
                std::cout << "Error: Cuenta no encontrada o no le pertenece." << std::endl;
            }
            break;
        }
        case 6:
        {
            // Ver gráfico de estados de cuenta
            std::string numeroCuenta;

            cliente->mostrarCuentas();
            std::cout << "Ingrese número de cuenta para ver gráfico: ";
            std::getline(std::cin, numeroCuenta);

            auto cuenta = cliente->buscarCuentaPorNumero(numeroCuenta);
            if (cuenta)
            {
                banco.mostrarGraficoEstadoCuenta(numeroCuenta);
            }
            else
            {
                std::cout << "Error: Cuenta no encontrada o no le pertenece." << std::endl;
            }
            break;
        }
        case 7:
        {
            // Cambiar información personal
            bool salirSubMenu = false;

            while (!salirSubMenu)
            {
                std::cout << "\n=== CAMBIAR INFORMACIÓN PERSONAL ===" << std::endl;
                std::cout << "1. Cambiar correo electrónico" << std::endl;
                std::cout << "2. Cambiar teléfono" << std::endl;
                std::cout << "3. Cambiar dirección" << std::endl;
                std::cout << "4. Cambiar contraseña" << std::endl;
                std::cout << "5. Volver al menú principal" << std::endl;
                std::cout << "Seleccione una opción: ";

                std::string subOpcionStr;
                std::getline(std::cin, subOpcionStr);

                if (!validarNumero(subOpcionStr))
                {
                    std::cout << "Error: Ingrese un número válido." << std::endl;
                    continue;
                }

                int subOpcion = std::stoi(subOpcionStr);

                switch (subOpcion)
                {
                case 1:
                {
                    std::string nuevoCorreo;
                    std::cout << "Ingrese nuevo correo electrónico: ";
                    std::getline(std::cin, nuevoCorreo);

                    if (validarCorreo(nuevoCorreo))
                    {
                        cliente->setCorreo(nuevoCorreo);
                        std::cout << "Correo actualizado exitosamente." << std::endl;
                    }
                    else
                    {
                        std::cout << "Error: Formato de correo inválido." << std::endl;
                    }
                    break;
                }
                case 2:
                {
                    std::string nuevoTelefono;
                    std::cout << "Ingrese nuevo teléfono: ";
                    std::getline(std::cin, nuevoTelefono);

                    if (validarTelefono(nuevoTelefono))
                    {
                        cliente->setTelefono(nuevoTelefono);
                        std::cout << "Teléfono actualizado exitosamente." << std::endl;
                    }
                    else
                    {
                        std::cout << "Error: Formato de teléfono inválido." << std::endl;
                    }
                    break;
                }
                case 3:
                {
                    std::string nuevaDireccion;
                    std::cout << "Ingrese nueva dirección: ";
                    std::getline(std::cin, nuevaDireccion);

                    if (!nuevaDireccion.empty())
                    {
                        cliente->setDireccion(nuevaDireccion);
                        std::cout << "Dirección actualizada exitosamente." << std::endl;
                    }
                    else
                    {
                        std::cout << "Error: La dirección no puede estar vacía." << std::endl;
                    }
                    break;
                }
                case 4:
                {
                    std::string contraseniaActual, nuevaContrasenia;
                    std::cout << "Ingrese contraseña actual: ";
                    std::getline(std::cin, contraseniaActual);

                    if (cliente->verificarContrasena(contraseniaActual))
                    {
                        std::cout << "Ingrese nueva contraseña: ";
                        std::getline(std::cin, nuevaContrasenia);

                        if (nuevaContrasenia.length() >= 6)
                        {
                            cliente->setContrasena(nuevaContrasenia);
                            std::cout << "Contraseña actualizada exitosamente." << std::endl;
                        }
                        else
                        {
                            std::cout << "Error: La contraseña debe tener al menos 6 caracteres." << std::endl;
                        }
                    }
                    else
                    {
                        std::cout << "Error: Contraseña actual incorrecta." << std::endl;
                    }
                    break;
                }
                case 5:
                    salirSubMenu = true;
                    break;
                default:
                    std::cout << "Opción inválida. Intente nuevamente." << std::endl;
                    break;
                }
            }
            break;
        }
        case 8:
            std::cout << "Sesión cerrada exitosamente." << std::endl;
            salir = true;
            break;
        default:
            std::cout << "Opción inválida. Intente nuevamente." << std::endl;
            break;
        }
    }
}

void mostrarMenuDesarrollador(Banco &banco)
{
    bool salir = false;

    while (!salir)
    {
        std::cout << "\n===== MENÚ DE DESARROLLADOR/ADMINISTRADOR =====" << std::endl;
        std::cout << "1. Registrar nuevo cliente" << std::endl;
        std::cout << "2. Listar todos los clientes" << std::endl;
        std::cout << "3. Buscar cliente por cédula" << std::endl;
        std::cout << "4. Crear cuenta para cliente" << std::endl;
        std::cout << "5. Activar/Desactivar cliente" << std::endl;
        std::cout << "6. Activar/Desactivar cuenta" << std::endl;
        std::cout << "7. Crear respaldo de datos" << std::endl;
        std::cout << "8. Estadísticas generales" << std::endl;
        std::cout << "9. Cerrar sesión" << std::endl;
        std::cout << "Seleccione una opción: ";

        std::string opcionStr;
        std::getline(std::cin, opcionStr);

        if (!validarNumero(opcionStr))
        {
            std::cout << "Error: Ingrese un número válido." << std::endl;
            continue;
        }

        int opcion = std::stoi(opcionStr);

        switch (opcion)
        {
        case 1:
        {
            // Registrar nuevo cliente
            std::string cedula, nombres, apellidos, correo, telefono, direccion, contrasena;

            std::cout << "\n=== REGISTRO DE NUEVO CLIENTE ===" << std::endl;

            std::cout << "Cédula: ";
            std::getline(std::cin, cedula);
            if (!validarCedula(cedula))
            {
                std::cout << "Error: Formato de cédula inválido." << std::endl;
                break;
            }

            std::cout << "Nombres: ";
            std::getline(std::cin, nombres);
            if (nombres.empty())
            {
                std::cout << "Error: Los nombres no pueden estar vacíos." << std::endl;
                break;
            }

            std::cout << "Apellidos: ";
            std::getline(std::cin, apellidos);
            if (apellidos.empty())
            {
                std::cout << "Error: Los apellidos no pueden estar vacíos." << std::endl;
                break;
            }

            std::cout << "Correo electrónico: ";
            std::getline(std::cin, correo);
            if (!validarCorreo(correo))
            {
                std::cout << "Error: Formato de correo inválido." << std::endl;
                break;
            }

            std::cout << "Teléfono: ";
            std::getline(std::cin, telefono);
            if (!validarTelefono(telefono))
            {
                std::cout << "Error: Formato de teléfono inválido." << std::endl;
                break;
            }

            std::cout << "Dirección: ";
            std::getline(std::cin, direccion);
            if (direccion.empty())
            {
                std::cout << "Error: La dirección no puede estar vacía." << std::endl;
                break;
            }

            std::cout << "Contraseña: ";
            std::getline(std::cin, contrasena);
            if (contrasena.length() < 6)
            {
                std::cout << "Error: La contraseña debe tener al menos 6 caracteres." << std::endl;
                break;
            }

            if (banco.registrarCliente(cedula, nombres, apellidos, correo, telefono, direccion, contrasena))
            {
                std::cout << "Cliente registrado exitosamente." << std::endl;
            }
            break;
        }
        case 2:
            // Listar todos los clientes
            banco.listarClientes();
            break;
        case 3:
        {
            // Buscar cliente por cédula
            std::string cedula;
            std::cout << "Ingrese la cédula del cliente a buscar: ";
            std::getline(std::cin, cedula);

            auto cliente = banco.buscarClientePorCedula(cedula);
            if (cliente)
            {
                cliente->mostrarInformacion();
                cliente->mostrarCuentas();
            }
            else
            {
                std::cout << "Cliente no encontrado." << std::endl;
            }
            break;
        }
        case 4:
        {
            // Crear cuenta para cliente
            std::string cedula, tipoStr, saldoInicialStr;

            std::cout << "Ingrese la cédula del cliente: ";
            std::getline(std::cin, cedula);

            auto cliente = banco.buscarClientePorCedula(cedula);
            if (!cliente)
            {
                std::cout << "Cliente no encontrado." << std::endl;
                break;
            }

            std::cout << "Tipo de cuenta (1: Ahorros, 2: Corriente): ";
            std::getline(std::cin, tipoStr);

            if (!validarNumero(tipoStr) || (stoi(tipoStr) != 1 && stoi(tipoStr) != 2))
            {
                std::cout << "Error: Tipo de cuenta inválido." << std::endl;
                break;
            }

            TipoCuenta tipo = (stoi(tipoStr) == 1) ? AHORROS : CORRIENTE;

            std::cout << "Saldo inicial: ";
            std::getline(std::cin, saldoInicialStr);

            if (!validarNumero(saldoInicialStr) || stod(saldoInicialStr) < 0)
            {
                std::cout << "Error: Saldo inicial inválido." << std::endl;
                break;
            }

            double saldoInicial = stod(saldoInicialStr);

            if (banco.crearCuenta(cedula, tipo, saldoInicial))
            {
                std::cout << "Cuenta creada exitosamente." << std::endl;
            }
            break;
        }
        case 5:
        {
            // Activar/Desactivar cliente
            std::string cedula, opcionStr;

            std::cout << "Ingrese la cédula del cliente: ";
            std::getline(std::cin, cedula);

            auto cliente = banco.buscarClientePorCedula(cedula);
            if (!cliente)
            {
                std::cout << "Cliente no encontrado." << std::endl;
                break;
            }

            std::cout << "Cliente: " << cliente->getNombreCompleto() << std::endl;
            std::cout << "Estado actual: " << (cliente->isActivo() ? "Activo" : "Inactivo") << std::endl;
            std::cout << "¿Desea " << (cliente->isActivo() ? "desactivar" : "activar") << " el cliente? (1: Sí, 2: No): ";
            std::getline(std::cin, opcionStr);

            if (!validarNumero(opcionStr) || (stoi(opcionStr) != 1 && stoi(opcionStr) != 2))
            {
                std::cout << "Opción inválida." << std::endl;
                break;
            }

            if (stoi(opcionStr) == 1)
            {
                if (cliente->isActivo())
                {
                    cliente->desactivar();
                    std::cout << "Cliente desactivado exitosamente." << std::endl;
                }
                else
                {
                    cliente->activar();
                    std::cout << "Cliente activado exitosamente." << std::endl;
                }
            }
            break;
        }
        case 6:
        {
            // Activar/Desactivar cuenta
            std::string numeroCuenta, opcionStr;

            std::cout << "Ingrese el número de cuenta: ";
            std::getline(std::cin, numeroCuenta);

            auto cuenta = banco.buscarCuentaPorNumero(numeroCuenta);
            if (!cuenta)
            {
                std::cout << "Cuenta no encontrada." << std::endl;
                break;
            }

            std::cout << "Cuenta: " << cuenta->getNumeroCuenta() << std::endl;
            std::cout << "Estado actual: " << (cuenta->isActiva() ? "Activa" : "Inactiva") << std::endl;
            std::cout << "¿Desea " << (cuenta->isActiva() ? "desactivar" : "activar") << " la cuenta? (1: Sí, 2: No): ";
            std::getline(std::cin, opcionStr);

            if (!validarNumero(opcionStr) || (stoi(opcionStr) != 1 && stoi(opcionStr) != 2))
            {
                std::cout << "Opción inválida." << std::endl;
                break;
            }

            if (stoi(opcionStr) == 1)
            {
                if (cuenta->isActiva())
                {
                    cuenta->desactivar();
                    std::cout << "Cuenta desactivada exitosamente." << std::endl;
                }
                else
                {
                    cuenta->activar();
                    std::cout << "Cuenta activada exitosamente." << std::endl;
                }
            }
            break;
        }
        case 7:
        {
            // Crear respaldo de datos
            std::string tipoArchivo;
            std::cout << "Tipo de respaldo (1: TXT, 2: CSV): ";
            std::getline(std::cin, tipoArchivo);

            if (!validarNumero(tipoArchivo) || (stoi(tipoArchivo) != 1 && stoi(tipoArchivo) != 2))
            {
                std::cout << "Opción inválida." << std::endl;
                break;
            }

            std::string extension = (stoi(tipoArchivo) == 1) ? "txt" : "csv";

            if (crearRespaldo(banco, extension))
            {
                std::cout << "Respaldo creado exitosamente." << std::endl;
            }
            break;
        }
        case 8:
            // Estadísticas generales
            banco.mostrarEstadisticas();
            break;
        case 9:
            std::cout << "Sesión cerrada exitosamente." << std::endl;
            salir = true;
            break;
        default:
            std::cout << "Opción inválida. Intente nuevamente." << std::endl;
            break;
        }
    }
}

// Implementación de funciones auxiliares

bool validarNumero(const std::string &str)
{
    if (str.empty())
    {
        return false;
    }

    size_t i = 0;
    if (str[0] == '-' || str[0] == '+')
    {
        i = 1;
        if (str.size() == 1)
        {
            return false;
        }
    }

    bool puntoEncontrado = false;

    for (; i < str.size(); ++i)
    {
        if (str[i] == '.' && !puntoEncontrado)
        {
            puntoEncontrado = true;
        }
        else if (!isdigit(str[i]))
        {
            return false;
        }
    }

    return true;
}

bool validarCedula(const std::string &cedula)
{
    // Validación básica: solo números y longitud adecuada
    if (cedula.empty() || cedula.length() < 5 || cedula.length() > 15)
    {
        return false;
    }

    for (char c : cedula)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }

    return true;
}

bool validarCorreo(const std::string &correo)
{
    // Validación básica: debe contener @ y un punto después
    size_t posArroba = correo.find('@');
    if (posArroba == std::string::npos || posArroba == 0)
    {
        return false;
    }

    size_t posPunto = correo.find('.', posArroba);
    if (posPunto == std::string::npos || posPunto == correo.length() - 1)
    {
        return false;
    }

    return true;
}

bool validarTelefono(const std::string &telefono)
{
    // Validación básica: solo números y longitud adecuada
    if (telefono.empty() || telefono.length() < 7 || telefono.length() > 15)
    {
        return false;
    }

    for (char c : telefono)
    {
        if (!isdigit(c) && c != '+' && c != '-' && c != ' ')
        {
            return false;
        }
    }

    return true;
}

bool crearRespaldo(const Banco &banco, const std::string &tipoArchivo)
{
    std::string nombreArchivo = "respaldo_" + std::to_string(time(nullptr)) + "." + tipoArchivo;

    return banco.guardarRespaldo(nombreArchivo, tipoArchivo);
}