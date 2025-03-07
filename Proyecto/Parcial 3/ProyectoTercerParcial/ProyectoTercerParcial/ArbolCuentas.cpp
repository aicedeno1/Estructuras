/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación Árbol Rojo-Negro para cuentas bancarias   *
 * Autor:                          Diaz Stiven, Cedenio Andres                                             *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          03/03/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "ArbolCuentas.h"
#include "GestorClientes.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;

// Constructor
ArbolCuentas::ArbolCuentas() : raiz(nullptr), evitarGuardar(false), archivoCuentas("cuentas.txt") {}

// Destructor
ArbolCuentas::~ArbolCuentas()
{
    limpiarArbol();
}

// Método para agregar una cuenta al árbol
void ArbolCuentas::agregarCuenta(const Cuenta &cuenta)
{
    // Verificar si ya existe una cuenta con el mismo número
    if (buscarCuenta(cuenta.getNumeroCuenta()))
    {
        throw invalid_argument("Ya existe una cuenta con ese número");
    }

    // Crear un nuevo nodo para la cuenta
    NodoCuenta *nuevo = new NodoCuenta(cuenta);

    // Si el árbol está vacío, el nuevo nodo es la raíz
    if (!raiz)
    {
        nuevo->color = NEGRO; // La raíz siempre es negra
        raiz = nuevo;
    }
    else
    {
        // Buscar la posición correcta para el nuevo nodo
        NodoCuenta *actual = raiz;
        NodoCuenta *padre = nullptr;

        while (actual)
        {
            padre = actual;
            if (nuevo->cuenta.getNumeroCuenta() < actual->cuenta.getNumeroCuenta())
            {
                actual = actual->izquierdo;
            }
            else
            {
                actual = actual->derecho;
            }
        }

        // Establecer el padre del nuevo nodo
        nuevo->padre = padre;

        // Conectar el nuevo nodo al padre
        if (nuevo->cuenta.getNumeroCuenta() < padre->cuenta.getNumeroCuenta())
        {
            padre->izquierdo = nuevo;
        }
        else
        {
            padre->derecho = nuevo;
        }

        // Balancear el árbol tras la inserción
        balancearInsercion(nuevo);
    }

    // Guardar cambios en el archivo si no se está evitando la operación
    if (!evitarGuardar)
    {
        guardarCuentasEnArchivo();
    }
}

// Método para eliminar una cuenta del árbol
void ArbolCuentas::eliminarCuenta(const string &numeroCuenta)
{
    NodoCuenta *nodo = buscarCuenta(numeroCuenta);
    if (!nodo)
    {
        throw invalid_argument("No existe una cuenta con ese número");
    }

    // Lógica de eliminación del árbol rojo-negro
    // (Esta implementación es compleja y requiere mantener el balance del árbol)

    // Si el nodo a eliminar tiene dos hijos
    if (nodo->izquierdo && nodo->derecho)
    {
        // Encontrar el sucesor (el más pequeño en el subárbol derecho)
        NodoCuenta *sucesor = encontrarMinimo(nodo->derecho);

        // Copiar los datos del sucesor al nodo a eliminar
        nodo->cuenta = sucesor->cuenta;

        // Ahora eliminamos el sucesor en lugar del nodo original
        nodo = sucesor;
    }

    // El nodo a eliminar tiene a lo sumo un hijo
    NodoCuenta *hijo = (nodo->izquierdo) ? nodo->izquierdo : nodo->derecho;
    NodoCuenta *padre = nodo->padre;

    // Si el nodo a eliminar es negro y tiene un hijo, ese hijo debe ser rojo
    // (otra condición del árbol rojo-negro)
    if (nodo->color == NEGRO)
    {
        // Cambiar el color del nodo a eliminar al de su hijo (si tiene hijo)
        if (hijo)
        {
            nodo->color = hijo->color;
        }

        // Balancear el árbol tras la eliminación
        balancearEliminacion(nodo);
    }

    // Reemplazar el nodo a eliminar con su hijo (si tiene)
    // y actualizar referencias
    if (!padre)
    {
        // Si el nodo a eliminar es la raíz
        raiz = hijo;
    }
    else
    {
        // Actualizar la referencia del padre al hijo
        if (nodo == padre->izquierdo)
        {
            padre->izquierdo = hijo;
        }
        else
        {
            padre->derecho = hijo;
        }
    }

    // Si hay un hijo, actualizar su referencia al padre
    if (hijo)
    {
        hijo->padre = padre;
    }

    // Liberar memoria del nodo eliminado
    delete nodo;

    // Guardar cambios en el archivo si no se está evitando la operación
    if (!evitarGuardar)
    {
        guardarCuentasEnArchivo();
    }
}

// Método para buscar una cuenta por su número
NodoCuenta *ArbolCuentas::buscarCuenta(const string &numeroCuenta) const
{
    NodoCuenta *actual = raiz;

    while (actual)
    {
        if (numeroCuenta == actual->cuenta.getNumeroCuenta())
        {
            return actual;
        }
        else if (numeroCuenta < actual->cuenta.getNumeroCuenta())
        {
            actual = actual->izquierdo;
        }
        else
        {
            actual = actual->derecho;
        }
    }

    return nullptr;
}

// Método para listar todas las cuentas
vector<Cuenta> ArbolCuentas::listarCuentas() const
{
    vector<Cuenta> cuentas;
    inorden(raiz, cuentas);
    return cuentas;
}

// Método para buscar cuentas de un cliente específico
vector<Cuenta> ArbolCuentas::buscarCuentasPorCliente(const string &cedulaCliente) const
{
    vector<Cuenta> todas = listarCuentas();
    vector<Cuenta> cuentasCliente;

    for (const auto &cuenta : todas)
    {
        if (cuenta.getTitular().getCedula() == cedulaCliente)
        {
            cuentasCliente.push_back(cuenta);
        }
    }

    return cuentasCliente;
}

// Método para guardar las cuentas en un archivo
void ArbolCuentas::guardarCuentasEnArchivo()
{
    ofstream archivo("cuentas_temp.txt");
    if (!archivo.is_open())
    {
        cerr << "Error al abrir el archivo temporal para guardar cuentas.\n";
        return;
    }

    guardarEnArchivo(raiz, archivo);
    archivo.close();

    if (remove(archivoCuentas.c_str()) != 0)
    {
        cerr << "Error al eliminar el archivo de destino: " << archivoCuentas << endl;
    }

    if (rename("cuentas_temp.txt", archivoCuentas.c_str()) != 0)
    {
        perror("Error al renombrar el archivo temporal");
    }
    else
    {
        cout << "Cuentas guardadas en el archivo: " << archivoCuentas << endl;
    }
}

// Método auxiliar para guardar las cuentas en un archivo (recorrido inorden)

// Método para cargar las cuentas desde un archivo
void ArbolCuentas::cargarCuentasDesdeArchivo(GestorClientes &gestorClientes)
{
    ifstream archivo(archivoCuentas);
    if (!archivo.is_open())
    {
        cout << "Archivo de cuentas no encontrado. Se creará uno nuevo.\n";
        return;
    }

    // Limpiar el árbol actual
    limpiarArbol();

    // No guardar en archivo durante la carga
    evitarGuardar = true;

    string linea;
    while (getline(archivo, linea))
    {
        stringstream ss(linea);
        string numeroCuenta, cedulaTitular, saldoStr, fechaStr, tipoStr, activaStr, estadoStr;

        getline(ss, numeroCuenta, ';');
        getline(ss, cedulaTitular, ';');
        getline(ss, saldoStr, ';');
        getline(ss, fechaStr, ';');
        getline(ss, tipoStr, ';');
        getline(ss, activaStr, ';');
        // Campo adicional opcional para texto de estado
        getline(ss, estadoStr);

        // Buscar el cliente titular por su cédula
        Cliente *clienteTitular = gestorClientes.buscarCliente(cedulaTitular);
        Cliente clienteTemp;

        if (clienteTitular)
        {
            clienteTemp = *clienteTitular;
        }
        else if (!cedulaTitular.empty())
        {
            // Si no se encuentra el cliente pero hay una cédula, crear un cliente temporal
            // con datos mínimos para mantener la referencia
            clienteTemp.setCedula(cedulaTitular);
            clienteTemp.setNombre("Cliente");
            clienteTemp.setApellido("Desvinculado");

            // Opcionalmente, se podría registrar este error
            cerr << "Advertencia: Cliente con cédula " << cedulaTitular
                 << " no encontrado para la cuenta " << numeroCuenta << endl;
        }

        // Convertir valores de strings a sus tipos correspondientes
        double saldo = stod(saldoStr);
        Fecha fecha = Fecha::crearDesdeCadena(fechaStr);
        TipoCuenta tipo = static_cast<TipoCuenta>(stoi(tipoStr));
        bool activa = (activaStr == "1");

        // Crear la cuenta y agregarla al árbol
        Cuenta cuenta(numeroCuenta, clienteTemp, saldo, fecha, tipo);
        cuenta.setActiva(activa);

        // Guardar el estado personalizado si existe
        if (!estadoStr.empty())
        {
            cuenta.setEstadoPersonalizado(estadoStr);
        }
        else if (!activa)
        {
            // Si está inactiva y no tiene estado personalizado, asignar "Retirado"
            cuenta.setEstadoPersonalizado("Retirado");
        }

        // Añadir la cuenta al árbol
        try
        {
            agregarCuenta(cuenta);
        }
        catch (const exception &e)
        {
            cerr << "Error al agregar cuenta desde archivo: " << e.what() << endl;
        }
    }

    archivo.close();
    evitarGuardar = false;
    cout << "Cuentas cargadas desde el archivo.\n";
}

// Modificar el método guardarEnArchivo para incluir el estado personalizado
void ArbolCuentas::guardarEnArchivo(NodoCuenta *nodo, ofstream &archivo) const
{
    if (nodo)
    {
        guardarEnArchivo(nodo->izquierdo, archivo);
        // Incluir el estado personalizado en el formato de guardado
        archivo << nodo->cuenta.toStringConEstado() << endl;
        guardarEnArchivo(nodo->derecho, archivo);
    }
}

// Método para crear un backup de las cuentas
void ArbolCuentas::crearBackup(const string &nombreArchivo)
{
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        cerr << "Error al crear el archivo de backup: " << nombreArchivo << endl;
        return;
    }

    guardarEnArchivo(raiz, archivo);
    archivo.close();
    cout << "Backup de cuentas creado en: " << nombreArchivo << endl;
}

// Método para restaurar un backup de cuentas
void ArbolCuentas::restaurarBackup(const string &nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        cerr << "Error al abrir el archivo de backup: " << nombreArchivo << endl;
        return;
    }

    // Limpiar el árbol actual
    limpiarArbol();

    // No guardar en archivo durante la restauración
    evitarGuardar = true;

    string linea;
    while (getline(archivo, linea))
    {
        stringstream ss(linea);
        string numeroCuenta, cedulaTitular, saldoStr, fechaStr, tipoStr, activaStr;

        getline(ss, numeroCuenta, ';');
        getline(ss, cedulaTitular, ';');
        getline(ss, saldoStr, ';');
        getline(ss, fechaStr, ';');
        getline(ss, tipoStr, ';');
        getline(ss, activaStr, ';');

        // Buscar el cliente titular (mismo problema que en cargarCuentasDesdeArchivo)
        Cliente clienteTemp;

        // Convertir valores de strings a sus tipos correspondientes
        double saldo = stod(saldoStr);
        Fecha fecha = Fecha::crearDesdeCadena(fechaStr);
        TipoCuenta tipo = static_cast<TipoCuenta>(stoi(tipoStr));
        bool activa = (activaStr == "1");

        // Crear la cuenta y agregarla al árbol
        Cuenta cuenta(numeroCuenta, clienteTemp, saldo, fecha, tipo);
        cuenta.setActiva(activa);

        // Añadir la cuenta al árbol
        try
        {
            agregarCuenta(cuenta);
        }
        catch (const exception &e)
        {
            cerr << "Error al restaurar cuenta desde backup: " << e.what() << endl;
        }
    }

    archivo.close();
    evitarGuardar = false;

    // Guardar los cambios en el archivo principal
    guardarCuentasEnArchivo();
    cout << "Backup de cuentas restaurado desde: " << nombreArchivo << endl;
}

// Método para limpiar el árbol (liberar memoria)
void ArbolCuentas::limpiarArbol()
{
    liberarMemoria(raiz);
    raiz = nullptr;
}

// Método auxiliar para liberar la memoria del árbol recursivamente
void ArbolCuentas::liberarMemoria(NodoCuenta *nodo)
{
    if (nodo)
    {
        liberarMemoria(nodo->izquierdo);
        liberarMemoria(nodo->derecho);
        delete nodo;
    }
}

// Método para verificar si el árbol está vacío
bool ArbolCuentas::estaVacio() const
{
    return raiz == nullptr;
}

// Método para obtener la raíz del árbol
NodoCuenta *ArbolCuentas::obtenerRaiz() const
{
    return raiz;
}

// Método para configurar si se debe evitar guardar en archivo
void ArbolCuentas::setEvitarGuardar(bool valor)
{
    evitarGuardar = valor;
}

// Métodos auxiliares para el árbol rojo-negro

// Realizar rotación izquierda en el nodo dado
void ArbolCuentas::rotarIzquierda(NodoCuenta *nodo)
{
    if (!nodo || !nodo->derecho)
        return;

    NodoCuenta *derecho = nodo->derecho;
    nodo->derecho = derecho->izquierdo;

    if (derecho->izquierdo)
    {
        derecho->izquierdo->padre = nodo;
    }

    derecho->padre = nodo->padre;

    if (!nodo->padre)
    {
        raiz = derecho;
    }
    else if (nodo == nodo->padre->izquierdo)
    {
        nodo->padre->izquierdo = derecho;
    }
    else
    {
        nodo->padre->derecho = derecho;
    }

    derecho->izquierdo = nodo;
    nodo->padre = derecho;
}

// Realizar rotación derecha en el nodo dado
void ArbolCuentas::rotarDerecha(NodoCuenta *nodo)
{
    if (!nodo || !nodo->izquierdo)
        return;

    NodoCuenta *izquierdo = nodo->izquierdo;
    nodo->izquierdo = izquierdo->derecho;

    if (izquierdo->derecho)
    {
        izquierdo->derecho->padre = nodo;
    }

    izquierdo->padre = nodo->padre;

    if (!nodo->padre)
    {
        raiz = izquierdo;
    }
    else if (nodo == nodo->padre->derecho)
    {
        nodo->padre->derecho = izquierdo;
    }
    else
    {
        nodo->padre->izquierdo = izquierdo;
    }

    izquierdo->derecho = nodo;
    nodo->padre = izquierdo;
}

// Balancear el árbol después de una inserción
void ArbolCuentas::balancearInsercion(NodoCuenta *nodo)
{
    NodoCuenta *padre = nullptr;
    NodoCuenta *abuelo = nullptr;

    while (nodo != raiz && nodo->color == ROJO && nodo->padre && nodo->padre->color == ROJO)
    {
        padre = nodo->padre;
        abuelo = padre->padre;

        // Caso 1: El padre es hijo izquierdo del abuelo
        if (padre == abuelo->izquierdo)
        {
            NodoCuenta *tio = abuelo->derecho;

            // Caso 1.1: El tío es rojo -> recolorear
            if (tio && tio->color == ROJO)
            {
                abuelo->color = ROJO;
                padre->color = NEGRO;
                tio->color = NEGRO;
                nodo = abuelo;
            }
            else
            {
                // Caso 1.2: El nodo es hijo derecho -> rotación izquierda en el padre
                if (nodo == padre->derecho)
                {
                    rotarIzquierda(padre);
                    nodo = padre;
                    padre = nodo->padre;
                }

                // Caso 1.3: El nodo es hijo izquierdo -> rotación derecha en el abuelo
                rotarDerecha(abuelo);
                swap(padre->color, abuelo->color);
                nodo = padre;
            }
        }
        // Caso 2: El padre es hijo derecho del abuelo
        else
        {
            NodoCuenta *tio = abuelo->izquierdo;

            // Caso 2.1: El tío es rojo -> recolorear
            if (tio && tio->color == ROJO)
            {
                abuelo->color = ROJO;
                padre->color = NEGRO;
                tio->color = NEGRO;
                nodo = abuelo;
            }
            else
            {
                // Caso 2.2: El nodo es hijo izquierdo -> rotación derecha en el padre
                if (nodo == padre->izquierdo)
                {
                    rotarDerecha(padre);
                    nodo = padre;
                    padre = nodo->padre;
                }

                // Caso 2.3: El nodo es hijo derecho -> rotación izquierda en el abuelo
                rotarIzquierda(abuelo);
                swap(padre->color, abuelo->color);
                nodo = padre;
            }
        }
    }

    // La raíz siempre debe ser negra
    raiz->color = NEGRO;
}

// Balancear el árbol después de una eliminación
void ArbolCuentas::balancearEliminacion(NodoCuenta *nodo)
{
    if (!nodo)
        return;

    // Si el nodo es la raíz, simplemente lo coloreamos negro y terminamos
    if (nodo == raiz)
    {
        nodo->color = NEGRO;
        return;
    }

    // Implementación del balanceo tras eliminación
    // (Esta parte es compleja y requiere manejar múltiples casos)
    // Por simplicidad, esta implementación es básica

    NodoCuenta *padre = nodo->padre;
    NodoCuenta *hermano = nodo->obtenerHermano();

    // Si el hermano es rojo
    if (hermano && hermano->color == ROJO)
    {
        padre->color = ROJO;
        hermano->color = NEGRO;

        if (nodo == padre->izquierdo)
        {
            rotarIzquierda(padre);
        }
        else
        {
            rotarDerecha(padre);
        }

        hermano = nodo->obtenerHermano();
    }

    // Si el padre, el hermano y los hijos del hermano son negros
    if (padre->color == NEGRO && hermano && hermano->color == NEGRO &&
        (!hermano->izquierdo || hermano->izquierdo->color == NEGRO) &&
        (!hermano->derecho || hermano->derecho->color == NEGRO))
    {

        hermano->color = ROJO;
        balancearEliminacion(padre);
    }
    // Si el padre es rojo y el hermano y los hijos del hermano son negros
    else if (padre->color == ROJO && hermano && hermano->color == NEGRO &&
             (!hermano->izquierdo || hermano->izquierdo->color == NEGRO) &&
             (!hermano->derecho || hermano->derecho->color == NEGRO))
    {

        hermano->color = ROJO;
        padre->color = NEGRO;
    }
    // Si el hermano es negro
    else if (hermano && hermano->color == NEGRO)
    {
        // Si el nodo es hijo izquierdo y el hijo derecho del hermano es rojo
        if (nodo == padre->izquierdo &&
            (!hermano->derecho || hermano->derecho->color == NEGRO) &&
            (hermano->izquierdo && hermano->izquierdo->color == ROJO))
        {

            hermano->color = ROJO;
            hermano->izquierdo->color = NEGRO;
            rotarDerecha(hermano);
            hermano = nodo->obtenerHermano();
        }
        // Si el nodo es hijo derecho y el hijo izquierdo del hermano es rojo
        else if (nodo == padre->derecho &&
                 (!hermano->izquierdo || hermano->izquierdo->color == NEGRO) &&
                 (hermano->derecho && hermano->derecho->color == ROJO))
        {

            hermano->color = ROJO;
            hermano->derecho->color = NEGRO;
            rotarIzquierda(hermano);
            hermano = nodo->obtenerHermano();
        }

        // Ajustes finales
        hermano->color = padre->color;
        padre->color = NEGRO;

        if (nodo == padre->izquierdo)
        {
            if (hermano->derecho)
                hermano->derecho->color = NEGRO;
            rotarIzquierda(padre);
        }
        else
        {
            if (hermano->izquierdo)
                hermano->izquierdo->color = NEGRO;
            rotarDerecha(padre);
        }
    }
}

// Encontrar el nodo con el valor mínimo en un subárbol
NodoCuenta *ArbolCuentas::encontrarMinimo(NodoCuenta *nodo)
{
    if (!nodo)
        return nullptr;

    while (nodo->izquierdo)
    {
        nodo = nodo->izquierdo;
    }

    return nodo;
}

// Encontrar el sucesor de un nodo (el nodo con el valor siguiente)
NodoCuenta *ArbolCuentas::encontrarSucesor(NodoCuenta *nodo)
{
    if (!nodo)
        return nullptr;

    // Si tiene hijo derecho, el sucesor es el mínimo en el subárbol derecho
    if (nodo->derecho)
    {
        return encontrarMinimo(nodo->derecho);
    }

    // Si no tiene hijo derecho, buscamos un ancestro que sea hijo izquierdo
    NodoCuenta *padre = nodo->padre;
    while (padre && nodo == padre->derecho)
    {
        nodo = padre;
        padre = nodo->padre;
    }

    return padre;
}

// Método auxiliar para realizar un recorrido inorden
void ArbolCuentas::inorden(NodoCuenta *nodo, vector<Cuenta> &cuentas) const
{
    if (nodo)
    {
        inorden(nodo->izquierdo, cuentas);
        cuentas.push_back(nodo->cuenta);
        inorden(nodo->derecho, cuentas);
    }
}

void ArbolCuentas::cargarCuentasDesdeArchivo()
{
    // Crea un gestor vacío para compatibilidad
    GestorClientes gestorTemp;
    cargarCuentasDesdeArchivo(gestorTemp);

    // Mensaje de advertencia sobre uso de método obsoleto
    cerr << "Advertencia: Usando cargarCuentasDesdeArchivo() sin GestorClientes. "
         << "Las cuentas se cargarán con clientes temporales." << endl;
}