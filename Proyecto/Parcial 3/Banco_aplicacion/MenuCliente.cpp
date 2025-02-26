#include "MenuCliente.h"
#include "Validaciones.h"
#include "UIUtilidades.h"
#include <iostream>
#include <string>

void mostrarMenuCliente(Banco &banco, std::shared_ptr<Cliente> cliente)
{
    bool salir = false;

    while (!salir)
    {
        limpiarPantalla();
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
            std::cout << "Presione Enter para continuar...";
            std::cin.get();
            continue;
        }

        int opcion = std::stoi(opcionStr);

        switch (opcion)
        {
        case 1:
            limpiarPantalla();
            // Ver datos personales
            cliente->mostrarInformacion();
            std::cout << "\nPresione Enter para continuar...";
            std::cin.get();
            break;
        case 2:
            limpiarPantalla();
            // Ver cuentas
            cliente->mostrarCuentas();
            std::cout << "\nPresione Enter para continuar...";
            std::cin.get();
            break;
        case 3:
            limpiarPantalla();
            // Realizar transferencia
            gestionarTransferencia(banco, cliente);
            std::cout << "\nPresione Enter para continuar...";
            std::cin.get();
            break;
        case 4:
            limpiarPantalla();
            // Pagar servicio
            gestionarPagoServicio(banco, cliente);
            std::cout << "\nPresione Enter para continuar...";
            std::cin.get();
            break;
        case 5:
            limpiarPantalla();
            // Ver historial de transacciones
            verHistorialTransacciones(cliente);
            std::cout << "\nPresione Enter para continuar...";
            std::cin.get();
            break;
        case 6:
            limpiarPantalla();
            // Ver gráfico de estados de cuenta
            verGraficoEstadoCuenta(banco, cliente);
            std::cout << "\nPresione Enter para continuar...";
            std::cin.get();
            break;
        case 7:
            limpiarPantalla();
            // Cambiar información personal
            gestionarCambioInformacionPersonal(cliente);
            break;
        case 8:
            std::cout << "Sesión cerrada exitosamente." << std::endl;
            salir = true;
            break;
        default:
            std::cout << "Opción inválida. Intente nuevamente." << std::endl;
            std::cout << "Presione Enter para continuar...";
            std::cin.get();
            break;
        }
    }
}

void gestionarCambioInformacionPersonal(std::shared_ptr<Cliente> cliente)
{
    bool salirSubMenu = false;

    while (!salirSubMenu)
    {
        limpiarPantalla();
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
            std::cout << "Presione Enter para continuar...";
            std::cin.get();
            continue;
        }

        int subOpcion = std::stoi(subOpcionStr);

        switch (subOpcion)
        {
        case 1:
        {
            limpiarPantalla();
            std::string nuevoCorreo = solicitarEntradaValidada(
                "Ingrese nuevo correo electrónico: ",
                "Error: Formato de correo inválido. Debe ser user@dominio.com",
                validarCorreo
            );
            cliente->setCorreo(nuevoCorreo);
            std::cout << "Correo actualizado exitosamente." << std::endl;
            std::cout << "Presione Enter para continuar...";
            std::cin.get();
            break;
        }
        case 2:
        {
            limpiarPantalla();
            std::string nuevoTelefono = solicitarEntradaValidada(
                "Ingrese nuevo teléfono (exactamente 10 dígitos): ",
                "Error: El teléfono debe contener exactamente 10 dígitos sin espacios ni otros caracteres.",
                validarTelefono
            );
            cliente->setTelefono(nuevoTelefono);
            std::cout << "Teléfono actualizado exitosamente." << std::endl;
            std::cout << "Presione Enter para continuar...";
            std::cin.get();
            break;
        }
        case 3:
        {
            limpiarPantalla();
            std::string nuevaDireccion = solicitarEntradaValidada(
                "Ingrese nueva dirección (solo letras y máximo un espacio): ",
                "Error: La dirección debe contener solo letras y máximo un espacio.",
                validarDireccion
            );
            cliente->setDireccion(nuevaDireccion);
            std::cout << "Dirección actualizada exitosamente." << std::endl;
            std::cout << "Presione Enter para continuar...";
            std::cin.get();
            break;
        }
        case 4:
        {
            limpiarPantalla();
            std::string contraseniaActual;
            std::cout << "Ingrese contraseña actual: ";
            std::getline(std::cin, contraseniaActual);

            if (cliente->verificarContrasena(contraseniaActual))
            {
                std::string nuevaContrasenia = solicitarEntradaValidada(
                    "Ingrese nueva contraseña (mínimo 6 caracteres): ",
                    "Error: La contraseña debe tener al menos 6 caracteres.",
                    validarContrasena
                );
                cliente->setContrasena(nuevaContrasenia);
                std::cout << "Contraseña actualizada exitosamente." << std::endl;
            }
            else
            {
                std::cout << "Error: Contraseña actual incorrecta." << std::endl;
            }
            std::cout << "Presione Enter para continuar...";
            std::cin.get();
            break;
        }
        case 5:
            salirSubMenu = true;
            break;
        default:
            std::cout << "Opción inválida. Intente nuevamente." << std::endl;
            std::cout << "Presione Enter para continuar...";
            std::cin.get();
            break;
        }
    }
}

void gestionarTransferencia(Banco &banco, std::shared_ptr<Cliente> cliente)
{
    limpiarPantalla();
    cliente->mostrarCuentas();
    
    std::string cuentaOrigen = solicitarEntradaValidada(
        "Ingrese número de cuenta origen: ",
        "Error: Número de cuenta inválido.",
        validarNoVacio
    );

    auto cuenta = cliente->buscarCuentaPorNumero(cuentaOrigen);
    if (!cuenta)
    {
        std::cout << "Error: Cuenta no encontrada o no le pertenece." << std::endl;
        return;
    }

    std::string cuentaDestino = solicitarEntradaValidada(
        "Ingrese número de cuenta destino: ",
        "Error: Número de cuenta inválido.",
        validarNoVacio
    );

    std::string montoStr = solicitarEntradaValidada(
        "Ingrese monto a transferir: ",
        "Error: Monto inválido. Debe ser un número positivo.",
        validarNumero
    );

    double monto = std::stod(montoStr);

    std::string descripcion = solicitarEntradaValidada(
        "Ingrese descripción: ",
        "Error: La descripción no puede estar vacía.",
        validarNoVacio
    );

    if (banco.realizarTransferencia(cuentaOrigen, cuentaDestino, monto, descripcion))
    {
        std::cout << "Transferencia realizada exitosamente." << std::endl;
    }
}

void gestionarPagoServicio(Banco &banco, std::shared_ptr<Cliente> cliente)
{
    limpiarPantalla();
    cliente->mostrarCuentas();
    
    std::string numeroCuenta = solicitarEntradaValidada(
        "Ingrese número de cuenta: ",
        "Error: Número de cuenta inválido.",
        validarNoVacio
    );

    auto cuenta = cliente->buscarCuentaPorNumero(numeroCuenta);
    if (!cuenta)
    {
        std::cout << "Error: Cuenta no encontrada o no le pertenece." << std::endl;
        return;
    }

    std::string tipoServicio = solicitarEntradaValidada(
        "Ingrese tipo de servicio (Luz, Agua, Internet, etc.): ",
        "Error: El tipo de servicio no puede estar vacío.",
        validarNoVacio
    );

    std::string montoStr = solicitarEntradaValidada(
        "Ingrese monto a pagar: ",
        "Error: Monto inválido. Debe ser un número positivo.",
        validarNumero
    );

    double monto = std::stod(montoStr);

    std::string referencia = solicitarEntradaValidada(
        "Ingrese número de referencia: ",
        "Error: La referencia no puede estar vacía.",
        validarNoVacio
    );

    if (banco.pagarServicio(numeroCuenta, tipoServicio, monto, referencia))
    {
        std::cout << "Pago de servicio realizado exitosamente." << std::endl;
    }
}

void verHistorialTransacciones(std::shared_ptr<Cliente> cliente)
{
    limpiarPantalla();
    cliente->mostrarCuentas();
    
    std::string numeroCuenta = solicitarEntradaValidada(
        "Ingrese número de cuenta para ver historial: ",
        "Error: Número de cuenta inválido.",
        validarNoVacio
    );

    auto cuenta = cliente->buscarCuentaPorNumero(numeroCuenta);
    if (cuenta)
    {
        cuenta->mostrarHistorialTransacciones();
    }
    else
    {
        std::cout << "Error: Cuenta no encontrada o no le pertenece." << std::endl;
    }
}

void verGraficoEstadoCuenta(Banco &banco, std::shared_ptr<Cliente> cliente)
{
    limpiarPantalla();
    cliente->mostrarCuentas();
    
    std::string numeroCuenta = solicitarEntradaValidada(
        "Ingrese número de cuenta para ver gráfico: ",
        "Error: Número de cuenta inválido.",
        validarNoVacio
    );

    auto cuenta = cliente->buscarCuentaPorNumero(numeroCuenta);
    if (cuenta)
    {
        banco.mostrarGraficoEstadoCuenta(numeroCuenta);
    }
    else
    {
        std::cout << "Error: Cuenta no encontrada o no le pertenece." << std::endl;
    }
}