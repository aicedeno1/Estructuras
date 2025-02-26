#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include "Banco.h"
#include "Validaciones.h"
#include "UIUtilidades.h"
#include "MenuCliente.h"
#include "MenuDesarrollador.h"

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
        limpiarPantalla();
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
            std::cout << "Presione Enter para continuar...";
            std::cin.get();
            continue;
        }

        int opcion = std::stoi(opcionStr);

        switch (opcion)
        {
        case 1:
        {
            limpiarPantalla();
            // Acceso como cliente
            std::string cedula = solicitarEntradaValidada(
                "\nAcceso de Cliente\nIngrese su cédula: ",
                "Error: Formato de cédula inválido.",
                validarCedula
            );

            std::string contrasena;
            std::cout << "Ingrese su contraseña: ";
            std::getline(std::cin, contrasena);

            auto cliente = banco.autenticarCliente(cedula, contrasena);

            if (cliente)
            {
                limpiarPantalla();
                mostrarMenuCliente(banco, cliente);
            }
            else
            {
                std::cout << "Error: Credenciales inválidas o cliente inactivo." << std::endl;
                std::cout << "Presione Enter para continuar...";
                std::cin.get();
            }
            break;
        }
        case 2:
        {
            limpiarPantalla();
            // Acceso como desarrollador/administrador
            std::string contrasenaAdmin;
            std::cout << "\nAcceso de Desarrollador/Administrador" << std::endl;
            std::cout << "Ingrese la contraseña de administrador: ";
            std::getline(std::cin, contrasenaAdmin);

            if (contrasenaAdmin == "admin123") // En un sistema real, usar mecanismos más seguros
            { 
                limpiarPantalla();
                mostrarMenuDesarrollador(banco);
            }
            else
            {
                std::cout << "Error: Contraseña de administrador incorrecta." << std::endl;
                std::cout << "Presione Enter para continuar...";
                std::cin.get();
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
            std::cout << "Presione Enter para continuar...";
            std::cin.get();
            break;
        }
    }

    return 0;
}