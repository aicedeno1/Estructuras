#include <iostream>
#include <string>
#include "Banco.h"
#include "Validaciones.h"
#include "UIUtilidades.h"

void mostrarMenuDesarrollador(Banco &banco) {
    bool salir = false;

    while (!salir) {
        limpiarPantalla();
        std::cout << "\n===== MENÚ DE DESARROLLADOR =====" << std::endl;
        std::cout << "1. Registrar nuevo cliente" << std::endl;
        std::cout << "2. Listar todos los clientes" << std::endl;
        std::cout << "3. Crear cuenta para cliente" << std::endl;
        std::cout << "4. Buscar cliente" << std::endl;
        std::cout << "5. Activar/Desactivar cliente" << std::endl;
        std::cout << "6. Generar respaldo de datos" << std::endl;
        std::cout << "7. Mostrar estadísticas" << std::endl;
        std::cout << "8. Volver al menú principal" << std::endl;
        std::cout << "Seleccione una opción: ";

        std::string opcionStr;
        std::getline(std::cin, opcionStr);

        if (!validarNumero(opcionStr)) {
            std::cout << "Error: Ingrese un número válido." << std::endl;
            std::cout << "Presione Enter para continuar...";
            std::cin.get();
            continue;
        }

        int opcion = std::stoi(opcionStr);

        switch (opcion) {
        case 1:
            limpiarPantalla();
            solicitarDatosNuevoCliente(banco);
            std::cout << "Presione Enter para continuar...";
            std::cin.get();
            break;
        case 2:
            limpiarPantalla();
            banco.listarClientes();
            std::cout << "\nPresione Enter para continuar...";
            std::cin.get();
            break;
        case 3: {
            limpiarPantalla();
            auto cliente = solicitarBusquedaCliente(banco);
            if (cliente) {
                std::string tipoStr = solicitarEntradaValidada(
                    "Tipo de cuenta (1: Ahorros, 2: Corriente): ", 
                    "Error: Ingrese 1 para Ahorros o 2 para Corriente.",
                    [](const std::string &str) -> bool {
                        return str == "1" || str == "2";
                    }
                );

                TipoCuenta tipo = (tipoStr == "1") ? AHORROS : CORRIENTE;

                std::string saldoStr = solicitarEntradaValidada(
                    "Saldo inicial: ", 
                    "Error: El saldo debe ser un número positivo.",
                    validarNumero
                );

                double saldo = std::stod(saldoStr);
                banco.crearCuenta(cliente->getCedula(), tipo, saldo);
            } else {
                std::cout << "Cliente no encontrado." << std::endl;
            }
            std::cout << "Presione Enter para continuar...";
            std::cin.get();
            break;
        }
        case 4: {
            limpiarPantalla();
            auto cliente = solicitarBusquedaCliente(banco);
            if (cliente) {
                cliente->mostrarInformacion();
                cliente->mostrarCuentas();
            } else {
                std::cout << "Cliente no encontrado." << std::endl;
            }
            std::cout << "\nPresione Enter para continuar...";
            std::cin.get();
            break;
        }
        case 5: {
            limpiarPantalla();
            auto cliente = solicitarBusquedaCliente(banco);
            if (cliente) {
                std::cout << "El cliente está actualmente " 
                          << (cliente->isActivo() ? "ACTIVO" : "INACTIVO") << std::endl;
                
                std::string opcionActivacion = solicitarEntradaValidada(
                    cliente->isActivo() ? 
                    "¿Desea desactivar el cliente? (S/N): " : 
                    "¿Desea activar el cliente? (S/N): ",
                    "Error: Ingrese S para Sí o N para No.",
                    [](const std::string &str) -> bool {
                        return str == "S" || str == "s" || str == "N" || str == "n";
                    }
                );
                
                if (opcionActivacion == "S" || opcionActivacion == "s") {
                    if (cliente->isActivo()) {
                        cliente->desactivar();
                        std::cout << "Cliente desactivado exitosamente." << std::endl;
                    } else {
                        cliente->activar();
                        std::cout << "Cliente activado exitosamente." << std::endl;
                    }
                }
            } else {
                std::cout << "Cliente no encontrado." << std::endl;
            }
            std::cout << "Presione Enter para continuar...";
            std::cin.get();
            break;
        }
        case 6: {
            limpiarPantalla();
            std::string tipoArchivo = solicitarEntradaValidada(
                "Tipo de archivo para respaldo (txt/csv): ", 
                "Error: Ingrese 'txt' o 'csv'.",
                [](const std::string &str) -> bool {
                    return str == "txt" || str == "csv";
                }
            );
            
            if (crearRespaldo(banco, tipoArchivo)) {
                std::cout << "Respaldo creado exitosamente." << std::endl;
            }
            std::cout << "Presione Enter para continuar...";
            std::cin.get();
            break;
        }
        case 7:
            limpiarPantalla();
            banco.mostrarEstadisticas();
            std::cout << "\nPresione Enter para continuar...";
            std::cin.get();
            break;
        case 8:
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