#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <windows.h>
#include <direct.h>
#include <conio.h>
#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

#include "MenuBancario.h"
#include "GestorIntegrado.h"
#include "BackupManager.h"
#include "EstadisticasBancarias.h"
#include "Validaciones.h"

class SistemaBancario
{
private:
    ArbolCuentas arbolCuentas;
    GestorClientes gestorClientes;
    BackupManager backupManager;
    EstadisticasBancarias estadisticas;
    GestorIntegrado gestorIntegrado;

    void configurarEntorno()
    {
        // Configurar la consola para usar UTF-8
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);

        // Directorios necesarios
        std::vector<std::string> directorios = {
            "backup",
            "backup\\cuentas",
            "backup\\clientes",
            "logs"};

        // Crear directorios
        for (const auto &dir : directorios)
        {
            // Usar _mkdir para crear directorios (Windows)
            int resultado = _mkdir(dir.c_str());

            if (resultado == 0)
            {
                std::cout << "Directorio creado: " << dir << std::endl;
            }
            else
            {
                // Ignorar error si el directorio ya existe
                if (errno != EEXIST)
                {
                    std::cerr << "Error al crear directorio " << dir
                              << ". Código de error: " << errno << std::endl;
                }
            }
        }
    }

    void inicializarArchivosBasicos()
    {
        // Archivos que deben existir
        std::vector<std::string> archivosRequeridos = {
            "cuentas.txt",
            "clientes.txt"};

        for (const auto &archivo : archivosRequeridos)
        {
            std::ifstream fileCheck(archivo);
            if (!fileCheck.good())
            {
                std::ofstream crearArchivo(archivo);
                if (crearArchivo.is_open())
                {
                    std::cout << "Creado archivo base: " << archivo << std::endl;
                    crearArchivo.close();
                }
                else
                {
                    std::cerr << "No se pudo crear el archivo: " << archivo << std::endl;
                }
            }
            fileCheck.close();
        }
    }

    void crearAdminPredeterminado()
    {
        try
        {
            // Verificar si ya existe el admin
            if (!gestorClientes.buscarClientePorUsuario("admin"))
            {
                // Crear usuario administrador predeterminado
                Fecha fechaNacimiento(1, 1, 1990);
                Cliente adminDefault(
                    "9999999999",                        // Cédula
                    "Administrador",                     // Nombre
                    "Sistema",                           // Apellido
                    "Administración ESPE",               // Dirección
                    "0000000000",                        // Teléfono
                    "admin@banco.espe.edu.ec",           // Email
                    fechaNacimiento,                     // Fecha de nacimiento
                    "admin",                             // Username
                    Usuario::cifrarPassword("Admin123!") // Password
                );

                adminDefault.setRol("ADMIN");

                // Forzar guardado en archivo
                gestorClientes.setEvitarGuardar(false);

                if (gestorClientes.agregarCliente(adminDefault))
                {
                    std::cout << "Usuario administrador creado exitosamente." << std::endl;
                    std::cout << "Username: admin" << std::endl;
                    std::cout << "Password: Admin123!" << std::endl;

                    // Guardar explícitamente en archivo
                    gestorClientes.guardarClientesEnArchivo();
                }
                else
                {
                    std::cerr << "No se pudo crear el usuario administrador." << std::endl;
                }
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error al crear admin predeterminado: " << e.what() << std::endl;
        }
    }

    void cargarDatos()
    {
        try
        {
            std::cout << "Cargando clientes..." << std::endl;
            gestorClientes.cargarClientesDesdeArchivo();

            std::cout << "Cargando cuentas..." << std::endl;
            arbolCuentas.cargarCuentasDesdeArchivo(gestorClientes);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error al cargar datos: " << e.what() << std::endl;
            throw;
        }
    }

public:
    // Constructor corregido: inicializar en el orden de la declaración
    SistemaBancario()
        : arbolCuentas(),
          gestorClientes(),
          backupManager(),
          estadisticas(arbolCuentas, gestorClientes),
          gestorIntegrado(gestorClientes, arbolCuentas, backupManager)
    {
    }

    int ejecutar()
    {
        try
        {
            // Configuración inicial
            configurarEntorno();

            // Inicializar archivos básicos
            inicializarArchivosBasicos();

            // Cargar datos existentes
            cargarDatos();

            // Crear admin predeterminado si no existe
            crearAdminPredeterminado();

            // Crear menú principal
            MenuBancario menu(arbolCuentas, gestorClientes, backupManager, estadisticas);

            // Iniciar sesión
            if (menu.iniciarSesion())
            {
                menu.mostrarMenuPrincipal();
            }

            return 0;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error crítico en la aplicación: " << e.what() << std::endl;
            std::cout << "Presione cualquier tecla para salir..." << std::endl;
            _getch();
            return 1;
        }
        catch (...)
        {
            std::cerr << "Error desconocido y crítico en la aplicación." << std::endl;
            std::cout << "Presione cualquier tecla para salir..." << std::endl;
            _getch();
            return 1;
        }
    }
};

int main()
{
    try
    {
        // Crear e iniciar el sistema bancario
        SistemaBancario sistemaBancario;
        return sistemaBancario.ejecutar();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error de inicialización: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Error de inicialización desconocido" << std::endl;
        return 1;
    }
}