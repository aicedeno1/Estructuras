/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación del gestor de clientes                    *
 * Autor:                           Diaz Stiven, Cedenio Andres                             *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          03/03/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "GestorClientes.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "BackupManager.h"

using namespace std;

GestorClientes::GestorClientes() : archivoClientes("clientes.txt"), evitarGuardar(false) {}

bool GestorClientes::agregarCliente(const Cliente &cliente)
{
    // Verificar si ya existe un cliente con la misma cédula
    if (existeCliente(cliente.getCedula()))
    {
        cout << "Error: Ya existe un cliente con la cédula " << cliente.getCedula() << endl;
        return false;
    }

    // Verificar si ya existe un usuario con el mismo nombre de usuario
    if (existeUsuario(cliente.getUsername()))
    {
        cout << "Error: Ya existe un usuario con el nombre " << cliente.getUsername() << endl;
        return false;
    }

    clientes.push_back(cliente);

    // Guardar en archivo si no se está evitando la operación de guardar
    if (!evitarGuardar)
    {
        guardarClientesEnArchivo();
    }

    return true;
}

bool GestorClientes::eliminarCliente(const string &cedula)
{
    for (auto it = clientes.begin(); it != clientes.end(); ++it)
    {
        if (it->getCedula() == cedula)
        {
            clientes.erase(it);

            // Guardar cambios en el archivo
            if (!evitarGuardar)
            {
                guardarClientesEnArchivo();
            }

            return true;
        }
    }

    cout << "Error: No se encontró un cliente con la cédula " << cedula << endl;
    return false;
}

Cliente *GestorClientes::buscarCliente(const string &cedula)
{
    for (auto &cliente : clientes)
    {
        if (cliente.getCedula() == cedula)
        {
            return &cliente;
        }
    }
    return nullptr;
}

Cliente *GestorClientes::buscarClientePorUsuario(const string &username)
{
    for (auto &cliente : clientes)
    {
        if (cliente.getUsername() == username)
        {
            return &cliente;
        }
    }
    return nullptr;
}

vector<Cliente> GestorClientes::listarClientes() const
{
    return clientes;
}

bool GestorClientes::existeCliente(const string &cedula)
{
    return buscarCliente(cedula) != nullptr;
}

bool GestorClientes::existeUsuario(const string &username)
{
    return buscarClientePorUsuario(username) != nullptr;
}

Usuario *GestorClientes::autenticarUsuario(const string &username, const string &password)
{
    Cliente *cliente = buscarClientePorUsuario(username);
    if (cliente && cliente->validarCredenciales(username, password))
    {
        return cliente;
    }
    return nullptr;
}

void GestorClientes::guardarClientesEnArchivo()
{
    ofstream archivo("clientes_temp.txt");
    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo temporal para guardar clientes.\n";
        return;
    }

    for (const auto &cliente : clientes)
    {
        archivo << cliente.toString() << endl;
    }

    archivo.close();

    if (remove(archivoClientes.c_str()) != 0)
    {
        cout << "Error al eliminar el archivo de destino: " << archivoClientes << endl;
    }

    if (rename("clientes_temp.txt", archivoClientes.c_str()) != 0)
    {
        perror("Error al renombrar el archivo temporal");
    }
    else
    {
        cout << "Clientes guardados en el archivo: " << archivoClientes << endl;
    }
}

void GestorClientes::cargarClientesDesdeArchivo()
{
    ifstream archivo(archivoClientes);
    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo para cargar los clientes.\n";
        return;
    }

    clientes.clear();
    evitarGuardar = true;

    string linea;
    while (getline(archivo, linea))
    {
        stringstream ss(linea);
        string cedula, nombre, apellido, direccion, telefono, email, fechaNacStr;
        string username, password, rol;

        getline(ss, cedula, ';');
        getline(ss, nombre, ';');
        getline(ss, apellido, ';');
        getline(ss, direccion, ';');
        getline(ss, telefono, ';');
        getline(ss, email, ';');
        getline(ss, fechaNacStr, ';');
        getline(ss, username, ';');
        getline(ss, password, ';');
        getline(ss, rol, ';');

        Fecha fechaNacimiento = Fecha::crearDesdeCadena(fechaNacStr);

        Cliente cliente(cedula, nombre, apellido, direccion, telefono,
                        email, fechaNacimiento, username, password);

        if (!rol.empty())
        {
            cliente.setRol(rol);
        }

        clientes.push_back(cliente);
    }

    archivo.close();
    evitarGuardar = false;
    cout << "Clientes cargados desde el archivo.\n";
}

void GestorClientes::crearBackup(const string &nombreArchivo)
{
    BackupManager::crearCarpetaSiNoExiste("backup");
    BackupManager::crearCarpetaSiNoExiste("backup/clientes");

    string rutaCompleta = nombreArchivo;

    ofstream archivo(rutaCompleta);
    if (!archivo.is_open())
    {
        cout << "Error al crear el archivo de backup en la ruta: " << rutaCompleta << endl;
        return;
    }

    for (const auto &cliente : clientes)
    {
        archivo << cliente.toString() << endl;
    }

    archivo.close();
    cout << "Backup de clientes creado correctamente en: " << rutaCompleta << endl;
}

void GestorClientes::restaurarBackup(const string &nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo de backup de clientes.\n";
        return;
    }

    cout << "Cargando backup desde: " << nombreArchivo << endl;

    clientes.clear();
    evitarGuardar = true;

    string linea;
    while (getline(archivo, linea))
    {
        stringstream ss(linea);
        string cedula, nombre, apellido, direccion, telefono, email, fechaNacStr;
        string username, password, rol;

        getline(ss, cedula, ';');
        getline(ss, nombre, ';');
        getline(ss, apellido, ';');
        getline(ss, direccion, ';');
        getline(ss, telefono, ';');
        getline(ss, email, ';');
        getline(ss, fechaNacStr, ';');
        getline(ss, username, ';');
        getline(ss, password, ';');
        getline(ss, rol, ';');

        Fecha fechaNacimiento = Fecha::crearDesdeCadena(fechaNacStr);

        Cliente cliente(cedula, nombre, apellido, direccion, telefono,
                        email, fechaNacimiento, username, password);

        clientes.push_back(cliente);
    }

    archivo.close();
    evitarGuardar = false;

    guardarClientesEnArchivo();
    cout << "Backup de clientes restaurado: " << nombreArchivo << endl;
}

void GestorClientes::setEvitarGuardar(bool valor)
{
    evitarGuardar = valor;
}