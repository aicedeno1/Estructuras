/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Implementación del menú del sistema bancario             *
 * Autor:                          Diaz Stiven, Cedenio Andres                              *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          03/03/2025                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "MenuBancario.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include "Validaciones.h"
#include "QrGenerator.h"
#include <limits>
#include "GestorIntegrado.h"
#include <direct.h>
#include "QrGenerator.h" // Para generarQRParaTransferencia()
#include <limits>

using namespace std;

MenuBancario::MenuBancario(ArbolCuentas &arbolCuentas, GestorClientes &gestorClientes,
                           BackupManager &backupManager, EstadisticasBancarias &estadisticas)
    : arbolCuentas(arbolCuentas), gestorClientes(gestorClientes),
      backupManager(backupManager), estadisticas(estadisticas), usuarioActual(nullptr) {}

bool MenuBancario::iniciarSesion()
{
    string username, password;
    int intentos = 0;
    const int MAX_INTENTOS = 3;

    while (intentos < MAX_INTENTOS)
    {
        system("cls");
        cout << "=====================================================" << endl;
        cout << "           SISTEMA BANCARIO ESPE - LOGIN             " << endl;
        cout << "=====================================================" << endl;

        cout << "Usuario: ";
        cin >> username;

        cout << "Contraseña: ";
        // Ocultar la contraseña con asteriscos
        password.clear();
        char ch;
        while ((ch = _getch()) != '\r')
        {
            if (ch == '\b')
            { // Tecla de retroceso
                if (!password.empty())
                {
                    password.pop_back();
                    cout << "\b \b"; // Borrar el carácter de la pantalla
                }
            }
            else
            {
                password.push_back(ch);
                cout << '*';
            }
        }
        cout << endl;

        // Verificar credenciales
        usuarioActual = gestorClientes.autenticarUsuario(username, password);

        if (usuarioActual)
        {
            cout << "\nBienvenido, " << username << "!" << endl;
            cout << "Presione cualquier tecla para continuar..." << endl;
            _getch();
            return true;
        }
        else
        {
            intentos++;
            cout << "\nCredenciales incorrectas. Intento " << intentos << " de " << MAX_INTENTOS << endl;
            if (intentos < MAX_INTENTOS)
            {
                cout << "Presione cualquier tecla para intentar de nuevo..." << endl;
                _getch();
            }
        }
    }

    cout << "\nDemasiados intentos fallidos. El sistema se cerrará." << endl;
    cout << "Presione cualquier tecla para salir..." << endl;
    _getch();
    return false;
}

void MenuBancario::mostrarMenuPrincipal()
{
    if (!usuarioActual)
    {
        cout << "Error: No hay una sesión activa." << endl;
        return;
    }

    // Determinar qué tipo de menú mostrar según el rol del usuario
    if (usuarioActual->getRol() == "ADMIN")
    {
        mostrarMenuAdmin();
    }
    else
    {
        mostrarMenuCliente();
    }
}

void MenuBancario::cerrarSesion()
{
    usuarioActual = nullptr;
    cout << "Sesión cerrada correctamente." << endl;
}

void MenuBancario::mostrarMenuAdmin()
{
    ListaCircularMenu menuOpciones;
    menuOpciones.insertar("Gestionar Clientes");
    menuOpciones.insertar("Gestionar Cuentas");
    menuOpciones.insertar("Administrar Sistema");
    menuOpciones.insertar("Generar Reportes");
    menuOpciones.insertar("Cerrar Sesión");

    int seleccion = 0;

    while (true)
    {
        system("cls");
        cout << "=====================================================" << endl;
        cout << "        SISTEMA BANCARIO ESPE - ADMINISTRADOR        " << endl;
        cout << "=====================================================" << endl;
        cout << "Usuario: " << usuarioActual->getUsername() << " | Rol: Administrador" << endl;
        cout << "-----------------------------------------------------" << endl;

        NodoMenu *actual = menuOpciones.getPrimero();
        for (int i = 0; i < menuOpciones.getTamano(); i++)
        {
            if (i == seleccion)
                cout << ">> " << actual->dato << " <<" << endl;
            else
                cout << "   " << actual->dato << endl;
            actual = actual->siguiente;
        }

        char tecla = _getch();
        if (tecla == 72)
        { // Flecha Arriba
            seleccion = (seleccion - 1 + menuOpciones.getTamano()) % menuOpciones.getTamano();
        }
        else if (tecla == 80)
        { // Flecha Abajo
            seleccion = (seleccion + 1) % menuOpciones.getTamano();
        }
        else if (tecla == '\r')
        { // Enter
            string opcionSeleccionada = menuOpciones.obtenerOpcion(seleccion);

            if (opcionSeleccionada == "Gestionar Clientes")
            {
                gestionarClientes();
            }
            else if (opcionSeleccionada == "Gestionar Cuentas")
            {
                gestionarCuentas();
            }
            else if (opcionSeleccionada == "Administrar Sistema")
            {
                administrarSistema();
            }
            else if (opcionSeleccionada == "Generar Reportes")
            {
                generarReportes();
            }
            else if (opcionSeleccionada == "Cerrar Sesión")
            {
                cerrarSesion();
                break;
            }
        }
    }
}

void MenuBancario::mostrarMenuCliente()
{
    Cliente *clienteActual = gestorClientes.buscarClientePorUsuario(usuarioActual->getUsername());
    if (!clienteActual)
    {
        cout << "Error: Cliente no encontrado." << endl;
        return;
    }

    ListaCircularMenu menuOpciones;
    menuOpciones.insertar("Consultar Cuentas");
    menuOpciones.insertar("Realizar Transacciones");
    menuOpciones.insertar("Ver Historial de Movimientos");
    menuOpciones.insertar("Modificar Perfil");
    menuOpciones.insertar("Cerrar Sesión");

    int seleccion = 0;

    while (true)
    {
        system("cls");
        cout << "=====================================================" << endl;
        cout << "            SISTEMA BANCARIO ESPE - CLIENTE          " << endl;
        cout << "=====================================================" << endl;
        cout << "Cliente: " << clienteActual->getNombreCompleto() << " | Cédula: " << clienteActual->getCedula() << endl;
        cout << "-----------------------------------------------------" << endl;

        NodoMenu *actual = menuOpciones.getPrimero();
        for (int i = 0; i < menuOpciones.getTamano(); i++)
        {
            if (i == seleccion)
                cout << ">> " << actual->dato << " <<" << endl;
            else
                cout << "   " << actual->dato << endl;
            actual = actual->siguiente;
        }

        char tecla = _getch();
        if (tecla == 72)
        { // Flecha Arriba
            seleccion = (seleccion - 1 + menuOpciones.getTamano()) % menuOpciones.getTamano();
        }
        else if (tecla == 80)
        { // Flecha Abajo
            seleccion = (seleccion + 1) % menuOpciones.getTamano();
        }
        else if (tecla == '\r')
        { // Enter
            string opcionSeleccionada = menuOpciones.obtenerOpcion(seleccion);

            if (opcionSeleccionada == "Consultar Cuentas")
            {
                consultarCuentas();
            }
            else if (opcionSeleccionada == "Realizar Transacciones")
            {
                realizarTransacciones();
            }
            else if (opcionSeleccionada == "Ver Historial de Movimientos")
            {
                verHistorial();
            }
            else if (opcionSeleccionada == "Modificar Perfil")
            {
                modificarPerfil();
            }
            else if (opcionSeleccionada == "Cerrar Sesión")
            {
                cerrarSesion();
                break;
            }
        }
    }
}

void MenuBancario::consultarCuentas()
{
    Cliente *clienteActual = gestorClientes.buscarClientePorUsuario(usuarioActual->getUsername());
    if (!clienteActual)
    {
        cout << "Error: Cliente no encontrado." << endl;
        return;
    }

    vector<Cuenta> cuentasCliente = arbolCuentas.buscarCuentasPorCliente(clienteActual->getCedula());

    system("cls");
    cout << "=====================================================" << endl;
    cout << "              MIS CUENTAS BANCARIAS                 " << endl;
    cout << "=====================================================" << endl;

    if (cuentasCliente.empty())
    {
        cout << "No tiene cuentas bancarias registradas." << endl;
    }
    else
    {
        cout << left << setw(15) << "NÚMERO" << setw(15) << "TIPO" << setw(15) << "ESTADO" << "SALDO" << endl;
        cout << "-----------------------------------------------------" << endl;

        for (const auto &cuenta : cuentasCliente)
        {
            cout << left << setw(15) << cuenta.getNumeroCuenta()
                 << setw(15) << cuenta.getTipoString()
                 << setw(15) << (cuenta.isActiva() ? "Activa" : "Inactiva")
                 << "$" << fixed << setprecision(2) << cuenta.getSaldo() << endl;
        }
    }

    cout << "\nPresione cualquier tecla para volver..." << endl;
    _getch();
}
// Añade estas implementaciones al archivo MenuBancario.cpp
// (puedes colocarlas antes o después de los otros métodos de la clase)

// Función para leer solo dígitos (números)
string MenuBancario::leerSoloDigitos(const string &mensaje) {
    string entrada = "";
    char ch;
    cout << mensaje;
    
    while (true) {
        ch = _getch();
        
        // Enter termina la entrada
        if (ch == 13) { // Enter key
            if (!entrada.empty()) {
                cout << endl;
                return entrada;
            }
        }
        // Permitir borrar caracteres
        else if (ch == 8) { // Backspace key
            if (!entrada.empty()) {
                entrada.pop_back();
                cout << "\b \b"; // Borrar carácter de la pantalla
            }
        }
        // Solo aceptar dígitos
        else if (isdigit(ch)) {
            entrada += ch;
            cout << ch;
        }
        // Ignorar cualquier otro carácter (no se muestra ni se procesa)
    }
}

// Función para leer solo letras
string MenuBancario::leerSoloLetras(const string &mensaje) {
    string entrada = "";
    char ch;
    cout << mensaje;
    
    while (true) {
        ch = _getch();
        
        // Enter termina la entrada
        if (ch == 13) { // Enter key
            if (!entrada.empty()) {
                cout << endl;
                return entrada;
            }
        }
        // Permitir borrar caracteres
        else if (ch == 8) { // Backspace key
            if (!entrada.empty()) {
                entrada.pop_back();
                cout << "\b \b"; // Borrar carácter de la pantalla
            }
        }
        // Solo aceptar letras
        else if (isalpha(ch)) {
            entrada += ch;
            cout << ch;
        }
        // Ignorar cualquier otro carácter (no se muestra ni se procesa)
    }
}

// Función para leer letras y espacios
string MenuBancario::leerLetrasYEspacios(const string &mensaje) {
    string entrada = "";
    char ch;
    cout << mensaje;
    
    while (true) {
        ch = _getch();
        
        // Enter termina la entrada
        if (ch == 13) { // Enter key
            if (!entrada.empty()) {
                cout << endl;
                return entrada;
            }
        }
        // Permitir borrar caracteres
        else if (ch == 8) { // Backspace key
            if (!entrada.empty()) {
                entrada.pop_back();
                cout << "\b \b"; // Borrar carácter de la pantalla
            }
        }
        // Aceptar letras y espacios
        else if (isalpha(ch) || ch == ' ') {
            entrada += ch;
            cout << ch;
        }
        // Ignorar cualquier otro carácter (no se muestra ni se procesa)
    }
}

// Función para leer números de teléfono (solo dígitos con formato específico)
string MenuBancario::leerTelefono(const string &mensaje) {
    string entrada = "";
    char ch;
    cout << mensaje;
    
    while (true) {
        ch = _getch();
        
        // Enter termina la entrada
        if (ch == 13) { // Enter key
            if (entrada.length() == 10 && entrada.substr(0, 2) == "09") {
                cout << endl;
                return entrada;
            } else {
                cout << "\nError: El teléfono debe tener 10 dígitos y empezar con 09. Intente nuevamente." << endl;
                cout << mensaje;
                entrada = "";
            }
        }
        // Permitir borrar caracteres
        else if (ch == 8) { // Backspace key
            if (!entrada.empty()) {
                entrada.pop_back();
                cout << "\b \b"; // Borrar carácter de la pantalla
            }
        }
        // Solo aceptar dígitos y limitar a 10 caracteres
        else if (isdigit(ch) && entrada.length() < 10) {
            entrada += ch;
            cout << ch;
        }
        // Ignorar cualquier otro carácter (no se muestra ni se procesa)
    }
}

// Función para leer correo electrónico (permite caracteres válidos para email)
string MenuBancario::leerEmail(const string &mensaje) {
    string entrada = "";
    char ch;
    cout << mensaje;
    
    while (true) {
        ch = _getch();
        
        // Enter termina la entrada
        if (ch == 13) { // Enter key
            if (!entrada.empty() && Validaciones::esEmailValido(entrada)) {
                cout << endl;
                return entrada;
            } else if (!entrada.empty()) {
                cout << "\nError: Formato de email inválido. Intente nuevamente." << endl;
                cout << mensaje;
                entrada = "";
            }
        }
        // Permitir borrar caracteres
        else if (ch == 8) { // Backspace key
            if (!entrada.empty()) {
                entrada.pop_back();
                cout << "\b \b"; // Borrar carácter de la pantalla
            }
        }
        // Aceptar caracteres válidos para email
        else if (isalnum(ch) || ch == '@' || ch == '.' || ch == '_' || ch == '-' || ch == '+') {
            entrada += ch;
            cout << ch;
        }
        // Ignorar cualquier otro carácter (no se muestra ni se procesa)
    }
}

// Función para leer fecha en formato específico DD-MM-AAAA
string MenuBancario::leerFecha(const string &mensaje) {
    string entrada = "";
    char ch;
    cout << mensaje;
    
    // Auto-formato para la fecha
    while (true) {
        ch = _getch();
        
        // Enter termina la entrada
        if (ch == 13) { // Enter key
            if (entrada.length() == 10) { // DD-MM-AAAA = 10 caracteres
                // Verificar formato
                if (entrada[2] == '-' && entrada[5] == '-') {
                    // Extraer componentes
                    string diaStr = entrada.substr(0, 2);
                    string mesStr = entrada.substr(3, 2);
                    string anioStr = entrada.substr(6, 4);
                    
                    // Verificar que sean números
                    if (Validaciones::esNumerico(diaStr) && Validaciones::esNumerico(mesStr) && Validaciones::esNumerico(anioStr)) {
                        int dia = stoi(diaStr);
                        int mes = stoi(mesStr);
                        int anio = stoi(anioStr);
                        
                        // Verificar si la fecha es válida
                        if (Fecha::esFechaValida(dia, mes, anio)) {
                            cout << endl;
                            return entrada;
                        }
                    }
                }
                
                cout << "\nError: Fecha inválida. Use formato DD-MM-AAAA con fecha válida." << endl;
                cout << mensaje;
                entrada = "";
            } else if (!entrada.empty()) {
                cout << "\nError: Formato incompleto. Use DD-MM-AAAA." << endl;
                cout << mensaje;
                entrada = "";
            }
        }
        // Permitir borrar caracteres
        else if (ch == 8) { // Backspace key
            if (!entrada.empty()) {
                entrada.pop_back();
                cout << "\b \b"; // Borrar carácter de la pantalla
            }
        }
        // Auto-formato: insertar guiones después del día y mes
        else if (isdigit(ch)) {
            if (entrada.length() < 10) { // Limitar a 10 caracteres (DD-MM-AAAA)
                entrada += ch;
                cout << ch;
                
                // Añadir guiones automáticamente
                if (entrada.length() == 2 || entrada.length() == 5) {
                    entrada += '-';
                    cout << '-';
                }
            }
        }
        // Ignorar cualquier otro carácter (no se muestra ni se procesa)
    }
}

// Función para leer nombre de usuario (solo alfanumérico)
string MenuBancario::leerUsername(const string &mensaje) {
    string entrada = "";
    char ch;
    cout << mensaje;
    
    while (true) {
        ch = _getch();
        
        // Enter termina la entrada
        if (ch == 13) { // Enter key
            if (!entrada.empty()) {
                cout << endl;
                return entrada;
            }
        }
        // Permitir borrar caracteres
        else if (ch == 8) { // Backspace key
            if (!entrada.empty()) {
                entrada.pop_back();
                cout << "\b \b"; // Borrar carácter de la pantalla
            }
        }
        // Solo aceptar caracteres alfanuméricos
        else if (isalnum(ch)) {
            entrada += ch;
            cout << ch;
        }
        // Ignorar cualquier otro carácter (no se muestra ni se procesa)
    }
}

// Función para leer contraseña (oculta con asteriscos)
string MenuBancario::leerPassword(const string &mensaje) {
    string entrada = "";
    char ch;
    cout << mensaje;
    
    while (true) {
        ch = _getch();
        
        // Enter termina la entrada
        if (ch == 13) { // Enter key
            if (entrada.length() >= 6) { // Mínimo 6 caracteres
                cout << endl;
                return entrada;
            } else if (!entrada.empty()) {
                cout << "\nError: La contraseña debe tener al menos 6 caracteres." << endl;
                cout << mensaje;
                entrada = "";
            }
        }
        // Permitir borrar caracteres
        else if (ch == 8) { // Backspace key
            if (!entrada.empty()) {
                entrada.pop_back();
                cout << "\b \b"; // Borrar carácter de la pantalla
            }
        }
        // Aceptar cualquier carácter para la contraseña
        else {
            entrada += ch;
            cout << '*'; // Mostrar asterisco en lugar del carácter
        }
    }
}

// Función para leer dirección (permite más caracteres)
string MenuBancario::leerDireccion(const string &mensaje) {
    string entrada = "";
    char ch;
    cout << mensaje;
    
    while (true) {
        ch = _getch();
        
        // Enter termina la entrada
        if (ch == 13) { // Enter key
            if (!entrada.empty()) {
                cout << endl;
                return entrada;
            }
        }
        // Permitir borrar caracteres
        else if (ch == 8) { // Backspace key
            if (!entrada.empty()) {
                entrada.pop_back();
                cout << "\b \b"; // Borrar carácter de la pantalla
            }
        }
        // Permitir caracteres razonables para una dirección
        else if (isalnum(ch) || isspace(ch) || ch == '.' || ch == ',' || ch == '#' || ch == '-') {
            entrada += ch;
            cout << ch;
        }
        // Ignorar cualquier otro carácter (no se muestra ni se procesa)
    }
}


string MenuBancario::leerSoloNumeros(bool permitirDecimal) {
    string entrada = "";
    char ch;
    bool puntoDecimalIngresado = false;
    
    while (true) {
        ch = _getch();
        
        // Enter termina la entrada
        if (ch == 13) { // Enter key
            if (!entrada.empty()) {
                cout << endl;
                return entrada;
            }
        }
        // Permitir borrar caracteres
        else if (ch == 8) { // Backspace key
            if (!entrada.empty()) {
                entrada.pop_back();
                cout << "\b \b"; // Borrar carácter de la pantalla
                
                // Si borramos el punto decimal, actualizamos la bandera
                if (permitirDecimal && entrada.find('.') == string::npos) {
                    puntoDecimalIngresado = false;
                }
            }
        }
        // Solo aceptar dígitos
        else if (isdigit(ch)) {
            entrada += ch;
            cout << ch;
        }
        // Si se permite decimal, aceptar punto (solo uno)
        else if (permitirDecimal && (ch == '.' || ch == ',') && !puntoDecimalIngresado) {
            entrada += '.'; // Siempre usamos punto como decimal internamente
            puntoDecimalIngresado = true;
            cout << ch;
        }
        // Ignorar cualquier otro carácter (no se muestra ni se procesa)
    }
}

void MenuBancario::realizarTransacciones()
{
    Cliente *clienteActual = gestorClientes.buscarClientePorUsuario(usuarioActual->getUsername());
    if (!clienteActual)
    {
        cout << "Error: Cliente no encontrado." << endl;
        cout << "Presione cualquier tecla para volver..." << endl;
        _getch();
        return;
    }

    vector<Cuenta> cuentasCliente = arbolCuentas.buscarCuentasPorCliente(clienteActual->getCedula());

    if (cuentasCliente.empty())
    {
        cout << "No tiene cuentas bancarias para realizar transacciones." << endl;
        cout << "Presione cualquier tecla para volver..." << endl;
        _getch();
        return;
    }

    ListaCircularMenu menuOpciones;
    menuOpciones.insertar("Realizar Depósito");
    menuOpciones.insertar("Realizar Retiro");
    menuOpciones.insertar("Realizar Transferencia");
    menuOpciones.insertar("Generar QR para Transferencia"); // Nueva opción
    menuOpciones.insertar("Volver al Menú Principal");

    int seleccion = 0;

    while (true)
    {
        system("cls");
        cout << "=====================================================" << endl;
        cout << "                  TRANSACCIONES                      " << endl;
        cout << "=====================================================" << endl;

        NodoMenu *actual = menuOpciones.getPrimero();
        for (int i = 0; i < menuOpciones.getTamano(); i++)
        {
            if (i == seleccion)
                cout << ">> " << actual->dato << " <<" << endl;
            else
                cout << "   " << actual->dato << endl;
            actual = actual->siguiente;
        }

        char tecla = _getch();
        if (tecla == 72)
        { // Flecha Arriba
            seleccion = (seleccion - 1 + menuOpciones.getTamano()) % menuOpciones.getTamano();
        }
        else if (tecla == 80)
        { // Flecha Abajo
            seleccion = (seleccion + 1) % menuOpciones.getTamano();
        }
        else if (tecla == '\r')
        { // Enter
            string opcionSeleccionada = menuOpciones.obtenerOpcion(seleccion);

            if (opcionSeleccionada == "Realizar Depósito")
            {
                realizarDeposito();
            }
            else if (opcionSeleccionada == "Realizar Retiro")
            {
                realizarRetiro();
            }
            else if (opcionSeleccionada == "Realizar Transferencia")
            {
                realizarTransferencia();
            }
            else if (opcionSeleccionada == "Generar QR para Transferencia")
            {
                generarQRParaTransferencia();
            }
            else if (opcionSeleccionada == "Volver al Menú Principal")
            {
                break;
            }
        }
    }
}

void MenuBancario::verHistorial()
{
    Cliente *clienteActual = gestorClientes.buscarClientePorUsuario(usuarioActual->getUsername());
    if (!clienteActual)
    {
        cout << "Error: Cliente no encontrado." << endl;
        return;
    }

    vector<Cuenta> cuentasCliente = arbolCuentas.buscarCuentasPorCliente(clienteActual->getCedula());

    if (cuentasCliente.empty())
    {
        cout << "No tiene cuentas bancarias para mostrar historial." << endl;
        cout << "Presione cualquier tecla para volver..." << endl;
        _getch();
        return;
    }

    // Mostrar las cuentas disponibles
    system("cls");
    cout << "=====================================================" << endl;
    cout << "        SELECCIONE UNA CUENTA PARA VER HISTORIAL     " << endl;
    cout << "=====================================================" << endl;

    cout << left << setw(5) << "ID" << setw(15) << "NÚMERO" << setw(15) << "TIPO" << "SALDO" << endl;
    cout << "-----------------------------------------------------" << endl;

    for (size_t i = 0; i < cuentasCliente.size(); i++)
    {
        cout << left << setw(5) << (i + 1)
             << setw(15) << cuentasCliente[i].getNumeroCuenta()
             << setw(15) << cuentasCliente[i].getTipoString()
             << "$" << fixed << setprecision(2) << cuentasCliente[i].getSaldo() << endl;
    }

    // Seleccionar cuenta con validación
    int seleccion = -1;
    bool seleccionValida = false;
    
    while (!seleccionValida) {
        cout << "\nIngrese el ID de la cuenta (o 0 para volver): ";
        string seleccionStr = leerSoloNumeros(); // Solo permite dígitos
        
        if (seleccionStr.empty()) {
            cout << "Error: Debe ingresar un número. Intente nuevamente." << endl;
            continue;
        }
        
        seleccion = stoi(seleccionStr);
        
        if (seleccion == 0) {
            return; // Volver al menú anterior
        }
        
        if (seleccion < 1 || seleccion > (int)cuentasCliente.size()) {
            cout << "Error: ID de cuenta inválido. Intente nuevamente." << endl;
            continue;
        }
        
        seleccionValida = true;
    }

    // Generar el reporte de movimientos para la cuenta seleccionada
    estadisticas.generarReporteMovimientos(cuentasCliente[seleccion - 1].getNumeroCuenta());

    cout << "\nPresione cualquier tecla para volver..." << endl;
    _getch();
}

void MenuBancario::modificarPerfil()
{
    Cliente *clienteActual = gestorClientes.buscarClientePorUsuario(usuarioActual->getUsername());
    if (!clienteActual)
    {
        cout << "Error: Cliente no encontrado." << endl;
        return;
    }

    ListaCircularMenu menuOpciones;
    menuOpciones.insertar("Cambiar Contraseña");
    menuOpciones.insertar("Editar Información Personal");
    menuOpciones.insertar("Volver al Menú Principal");

    int seleccion = 0;

    while (true)
    {
        system("cls");
        cout << "=====================================================" << endl;
        cout << "               MODIFICAR PERFIL                     " << endl;
        cout << "=====================================================" << endl;

        NodoMenu *actual = menuOpciones.getPrimero();
        for (int i = 0; i < menuOpciones.getTamano(); i++)
        {
            if (i == seleccion)
                cout << ">> " << actual->dato << " <<" << endl;
            else
                cout << "   " << actual->dato << endl;
            actual = actual->siguiente;
        }

        char tecla = _getch();
        if (tecla == 72)
        { // Flecha Arriba
            seleccion = (seleccion - 1 + menuOpciones.getTamano()) % menuOpciones.getTamano();
        }
        else if (tecla == 80)
        { // Flecha Abajo
            seleccion = (seleccion + 1) % menuOpciones.getTamano();
        }
        else if (tecla == '\r')
        { // Enter
            string opcionSeleccionada = menuOpciones.obtenerOpcion(seleccion);

            if (opcionSeleccionada == "Cambiar Contraseña")
            {
                // Validación de contraseña actual
                string passwordActual = leerPassword("Ingrese contraseña actual: ");

                if (clienteActual->validarCredenciales(clienteActual->getUsername(), passwordActual))
                {
                    // Validación de nueva contraseña y confirmación
                    string nuevaPassword = leerPassword("Ingrese nueva contraseña (mínimo 6 caracteres): ");
                    string confirmacion = leerPassword("Confirme nueva contraseña: ");

                    if (nuevaPassword == confirmacion)
                    {
                        clienteActual->setPassword(Usuario::cifrarPassword(nuevaPassword));
                        gestorClientes.guardarClientesEnArchivo();
                        cout << "Contraseña actualizada correctamente." << endl;

                        // Registrar operación en el backtracking
                        backupManager.registrarOperacion("CAMBIAR_PASSWORD",
                                                        "Usuario: " + clienteActual->getUsername());
                    }
                    else
                    {
                        cout << "Error: Las contraseñas no coinciden." << endl;
                    }
                }
                else
                {
                    cout << "Error: Contraseña actual incorrecta." << endl;
                }

                cout << "Presione cualquier tecla para continuar..." << endl;
                _getch();
            }
            else if (opcionSeleccionada == "Editar Información Personal")
            {
                // Usar la misma función editarCliente para clientes normales
                editarCliente();
            }
            else if (opcionSeleccionada == "Volver al Menú Principal")
            {
                break;
            }
        }
    }
}

void MenuBancario::listarTodosLosClientes()
{
    vector<Cliente> clientes = gestorClientes.listarClientes();

    system("cls");
    cout << "=====================================================" << endl;
    cout << "               LISTADO DE TODOS LOS CLIENTES         " << endl;
    cout << "=====================================================" << endl;

    if (clientes.empty())
    {
        cout << "No hay clientes registrados en el sistema." << endl;
    }
    else
    {
        cout << left << setw(15) << "CÉDULA" << setw(30) << "NOMBRE COMPLETO"
             << setw(15) << "TELÉFONO" << "EMAIL" << endl;
        cout << "-----------------------------------------------------" << endl;

        for (const auto &cliente : clientes)
        {
            cout << left << setw(15) << cliente.getCedula()
                 << setw(30) << cliente.getNombreCompleto()
                 << setw(15) << cliente.getTelefono()
                 << cliente.getEmail() << endl;
        }

        cout << "-----------------------------------------------------" << endl;
        cout << "Total de clientes: " << clientes.size() << endl;
    }

    cout << "\nPresione cualquier tecla para volver..." << endl;
    _getch();
}

void MenuBancario::buscarClientePorCedula()
{
    system("cls");
    cout << "=====================================================" << endl;
    cout << "            BUSCAR CLIENTE POR CÉDULA                " << endl;
    cout << "=====================================================" << endl;
    
    // Validación de cédula (solo dígitos)
    string cedula = leerSoloDigitos("Ingrese cédula del cliente a buscar: ");

    GestorIntegrado gestorIntegrado(gestorClientes, arbolCuentas, backupManager);
    Cliente *cliente = gestorIntegrado.buscarClienteSeguro(cedula);

    if (!cliente)
    {
        cout << "Presione cualquier tecla para volver..." << endl;
        _getch();
        return;
    }

    // Buscar las cuentas del cliente
    vector<Cuenta> cuentasCliente = arbolCuentas.buscarCuentasPorCliente(cedula);

    // Mostrar información del cliente
    system("cls");
    cout << "=====================================================" << endl;
    cout << "                 INFORMACIÓN DEL CLIENTE             " << endl;
    cout << "=====================================================" << endl;
    cliente->mostrar();

    cout << "\n=====================================================" << endl;
    cout << "                CUENTAS DEL CLIENTE                  " << endl;
    cout << "=====================================================" << endl;

    if (cuentasCliente.empty())
    {
        cout << "El cliente no tiene cuentas bancarias registradas." << endl;
    }
    else
    {
        cout << left << setw(15) << "NÚMERO" << setw(15) << "TIPO" << setw(15) << "ESTADO" << "SALDO" << endl;
        cout << "-----------------------------------------------------" << endl;

        for (const auto &cuenta : cuentasCliente)
        {
            cout << left << setw(15) << cuenta.getNumeroCuenta()
                 << setw(15) << cuenta.getTipoString()
                 << setw(15) << (cuenta.isActiva() ? "Activa" : "Inactiva")
                 << "$" << fixed << setprecision(2) << cuenta.getSaldo() << endl;
        }
    }

    cout << "\nPresione cualquier tecla para volver..." << endl;
    _getch();
}

void MenuBancario::gestionarClientes()
{
    ListaCircularMenu menuOpciones;
    menuOpciones.insertar("Agregar Nuevo Cliente");
    menuOpciones.insertar("Editar Cliente");
    menuOpciones.insertar("Desactivar Cuentas de Cliente"); // Cambiar el texto
    menuOpciones.insertar("Listar Todos los Clientes");
    menuOpciones.insertar("Buscar Cliente por Cédula");
    menuOpciones.insertar("Volver al Menú Principal");

    int seleccion = 0;

    while (true)
    {
        system("cls");
        cout << "=====================================================" << endl;
        cout << "              GESTIÓN DE CLIENTES                    " << endl;
        cout << "=====================================================" << endl;

        NodoMenu *actual = menuOpciones.getPrimero();
        for (int i = 0; i < menuOpciones.getTamano(); i++)
        {
            if (i == seleccion)
                cout << ">> " << actual->dato << " <<" << endl;
            else
                cout << "   " << actual->dato << endl;
            actual = actual->siguiente;
        }

        char tecla = _getch();
        if (tecla == 72)
        { // Flecha Arriba
            seleccion = (seleccion - 1 + menuOpciones.getTamano()) % menuOpciones.getTamano();
        }
        else if (tecla == 80)
        { // Flecha Abajo
            seleccion = (seleccion + 1) % menuOpciones.getTamano();
        }
        else if (tecla == '\r')
        { // Enter
            string opcionSeleccionada = menuOpciones.obtenerOpcion(seleccion);

            if (opcionSeleccionada == "Agregar Nuevo Cliente")
            {
                agregarNuevoCliente();
            }
            else if (opcionSeleccionada == "Editar Cliente")
            {
                editarCliente();
            }
            else if (opcionSeleccionada == "Desactivar Cuentas de Cliente")
            {
                eliminarCliente(); // Mantenemos el nombre del método aunque su función ha cambiado
            }
            else if (opcionSeleccionada == "Listar Todos los Clientes")
            {
                listarTodosLosClientes();
            }
            else if (opcionSeleccionada == "Buscar Cliente por Cédula")
            {
                buscarClientePorCedula();
            }
            else if (opcionSeleccionada == "Volver al Menú Principal")
            {
                break;
            }
        }
    }
}

void MenuBancario::gestionarCuentas()
{
    ListaCircularMenu menuOpciones;
    menuOpciones.insertar("Crear Nueva Cuenta");
    menuOpciones.insertar("Cerrar Cuenta");
    menuOpciones.insertar("Listar Todas las Cuentas");
    menuOpciones.insertar("Buscar Cuenta por Número");
    menuOpciones.insertar("Volver al Menú Principal");

    int seleccion = 0;

    while (true)
    {
        system("cls");
        cout << "=====================================================" << endl;
        cout << "              GESTIÓN DE CUENTAS                     " << endl;
        cout << "=====================================================" << endl;

        NodoMenu *actual = menuOpciones.getPrimero();
        for (int i = 0; i < menuOpciones.getTamano(); i++)
        {
            if (i == seleccion)
                cout << ">> " << actual->dato << " <<" << endl;
            else
                cout << "   " << actual->dato << endl;
            actual = actual->siguiente;
        }

        char tecla = _getch();
        if (tecla == 72)
        { // Flecha Arriba
            seleccion = (seleccion - 1 + menuOpciones.getTamano()) % menuOpciones.getTamano();
        }
        else if (tecla == 80)
        { // Flecha Abajo
            seleccion = (seleccion + 1) % menuOpciones.getTamano();
        }
        else if (tecla == '\r')
        { // Enter
            string opcionSeleccionada = menuOpciones.obtenerOpcion(seleccion);

            if (opcionSeleccionada == "Crear Nueva Cuenta")
            {
                crearNuevaCuenta();
            }
            else if (opcionSeleccionada == "Cerrar Cuenta")
            {
                cerrarCuenta();
            }
            else if (opcionSeleccionada == "Listar Todas las Cuentas")
            {
                listarTodasLasCuentas();
            }
            else if (opcionSeleccionada == "Buscar Cuenta por Número")
            {
                buscarCuentaPorNumero();
            }
            else if (opcionSeleccionada == "Volver al Menú Principal")
            {
                break;
            }
        }
    }
}

void MenuBancario::administrarSistema()
{
    ListaCircularMenu menuOpciones;
    menuOpciones.insertar("Crear Backup Completo");
    menuOpciones.insertar("Restaurar Backup de Cuentas");
    menuOpciones.insertar("Restaurar Backup de Clientes");
    menuOpciones.insertar("Ver Historial de Operaciones");
    menuOpciones.insertar("Limpiar Historial");
    menuOpciones.insertar("Volver al Menú Principal");

    int seleccion = 0;

    while (true)
    {
        system("cls");
        cout << "=====================================================" << endl;
        cout << "              ADMINISTRACIÓN DEL SISTEMA             " << endl;
        cout << "=====================================================" << endl;

        NodoMenu *actual = menuOpciones.getPrimero();
        for (int i = 0; i < menuOpciones.getTamano(); i++)
        {
            if (i == seleccion)
                cout << ">> " << actual->dato << " <<" << endl;
            else
                cout << "   " << actual->dato << endl;
            actual = actual->siguiente;
        }

        char tecla = _getch();
        if (tecla == 72)
        { // Flecha Arriba
            seleccion = (seleccion - 1 + menuOpciones.getTamano()) % menuOpciones.getTamano();
        }
        else if (tecla == 80)
        { // Flecha Abajo
            seleccion = (seleccion + 1) % menuOpciones.getTamano();
        }
        else if (tecla == '\r')
        { // Enter
            string opcionSeleccionada = menuOpciones.obtenerOpcion(seleccion);

            if (opcionSeleccionada == "Crear Backup Completo")
            {
                BackupManager::crearBackupCompleto(arbolCuentas, gestorClientes);
                cout << "Backup creado correctamente." << endl;
                cout << "Presione cualquier tecla para continuar..." << endl;
                _getch();
            }
            else if (opcionSeleccionada == "Restaurar Backup de Cuentas")
            {
                BackupManager::restaurarBackupCuentas(arbolCuentas);
                cout << "Presione cualquier tecla para continuar..." << endl;
                _getch();
            }
            else if (opcionSeleccionada == "Restaurar Backup de Clientes")
            {
                BackupManager::restaurarBackupClientes(gestorClientes);
                cout << "Presione cualquier tecla para continuar..." << endl;
                _getch();
            }
            else if (opcionSeleccionada == "Ver Historial de Operaciones")
            {
                // Solicitar fecha (formato YYYY_MM_DD)
                string fecha;
                cout << "Ingrese fecha (YYYY_MM_DD): ";
                cin >> fecha;

                vector<string> historial = BackupManager::obtenerHistorialOperaciones(fecha);

                system("cls");
                cout << "=====================================================" << endl;
                cout << "        HISTORIAL DE OPERACIONES - " << fecha << endl;
                cout << "=====================================================" << endl;

                if (historial.empty())
                {
                    cout << "No hay operaciones registradas para esta fecha." << endl;
                }
                else
                {
                    for (const auto &linea : historial)
                    {
                        cout << linea << endl;
                    }
                }

                cout << "Presione cualquier tecla para continuar..." << endl;
                _getch();
            }
            else if (opcionSeleccionada == "Limpiar Historial")
            {
                int dias;
                cout << "Eliminar historial más antiguo que (días): ";
                cin >> dias;

                BackupManager::limpiarHistorialOperaciones(dias);
                cout << "Presione cualquier tecla para continuar..." << endl;
                _getch();
            }
            else if (opcionSeleccionada == "Volver al Menú Principal")
            {
                break;
            }
        }
    }
}

void MenuBancario::generarReportes()
{
    ListaCircularMenu menuOpciones;
    menuOpciones.insertar("Generar Reporte Web Interactivo");
    menuOpciones.insertar("Ver Distribución de Tipos de Cuenta");
    menuOpciones.insertar("Ver Saldos Promedio por Tipo");
    menuOpciones.insertar("Generar Reporte de Movimientos");
    menuOpciones.insertar("Listar Clientes con Mayor Saldo");
    // Nuevas opciones de reporte
    menuOpciones.insertar("Reporte General de Usuarios y Cuentas");
    menuOpciones.insertar("Reporte de Usuarios con Cuentas Activas");
    menuOpciones.insertar("Volver al Menú Principal");

    int seleccion = 0;

    while (true)
    {
        system("cls");
        cout << "=====================================================" << endl;
        cout << "              GENERACIÓN DE REPORTES                 " << endl;
        cout << "=====================================================" << endl;

        NodoMenu *actual = menuOpciones.getPrimero();
        for (int i = 0; i < menuOpciones.getTamano(); i++)
        {
            if (i == seleccion)
                cout << ">> " << actual->dato << " <<" << endl;
            else
                cout << "   " << actual->dato << endl;
            actual = actual->siguiente;
        }

        char tecla = _getch();
        if (tecla == 72)
        { // Flecha Arriba
            seleccion = (seleccion - 1 + menuOpciones.getTamano()) % menuOpciones.getTamano();
        }
        else if (tecla == 80)
        { // Flecha Abajo
            seleccion = (seleccion + 1) % menuOpciones.getTamano();
        }
        else if (tecla == '\r')
        { // Enter
            string opcionSeleccionada = menuOpciones.obtenerOpcion(seleccion);

            if (opcionSeleccionada == "Generar Reporte Web Interactivo")
            {
                // Llamar al nuevo método que genera y abre el reporte HTML en el navegador
                estadisticas.generarAbrirReporteHTML();
                cout << "\nReporte generado y abierto en el navegador." << endl;
                cout << "\nPresione cualquier tecla para continuar..." << endl;
                _getch();
            }
            else if (opcionSeleccionada == "Ver Distribución de Tipos de Cuenta")
            {
                estadisticas.mostrarGraficoPastelDistribucionCuentas();
                cout << "\nPresione cualquier tecla para continuar..." << endl;
                _getch();
            }
            else if (opcionSeleccionada == "Ver Saldos Promedio por Tipo")
            {
                estadisticas.mostrarGraficoLineaSaldosPromedios();
                cout << "\nPresione cualquier tecla para continuar..." << endl;
                _getch();
            }
            else if (opcionSeleccionada == "Generar Reporte de Movimientos")
            {
                string numeroCuenta;
                cout << "Ingrese número de cuenta: ";
                cin >> numeroCuenta;

                estadisticas.generarReporteMovimientos(numeroCuenta);
                cout << "\nPresione cualquier tecla para continuar..." << endl;
                _getch();
            }
            else if (opcionSeleccionada == "Listar Clientes con Mayor Saldo")
            {
                int cantidad;
                cout << "Ingrese cantidad de clientes a mostrar: ";
                cin >> cantidad;

                estadisticas.generarReporteClientesMayorSaldo(cantidad);
                cout << "\nPresione cualquier tecla para continuar..." << endl;
                _getch();
            }
            else if (opcionSeleccionada == "Reporte General de Usuarios y Cuentas")
            {
                estadisticas.generarReporteGeneralUsuarios();
            }
            else if (opcionSeleccionada == "Reporte de Usuarios con Cuentas Activas")
            {
                estadisticas.generarReporteUsuariosActivos();
            }
            else if (opcionSeleccionada == "Volver al Menú Principal")
            {
                break;
            }
        }
    }
}

void MenuBancario::realizarDeposito()
{
    // Obtener el cliente asociado al usuario actual
    Cliente *clienteActual = gestorClientes.buscarClientePorUsuario(usuarioActual->getUsername());
    if (!clienteActual)
    {
        cout << "Error: Cliente no encontrado." << endl;
        cout << "Presione cualquier tecla para volver..." << endl;
        _getch();
        return;
    }

    // Buscar las cuentas del cliente
    vector<Cuenta> cuentasCliente = arbolCuentas.buscarCuentasPorCliente(clienteActual->getCedula());

    if (cuentasCliente.empty())
    {
        cout << "Error: No tiene cuentas registradas." << endl;
        cout << "Presione cualquier tecla para volver..." << endl;
        _getch();
        return;
    }

    // Mostrar las cuentas disponibles
    system("cls");
    cout << "=====================================================" << endl;
    cout << "                 REALIZAR DEPÓSITO                   " << endl;
    cout << "=====================================================" << endl;
    cout << "Seleccione la cuenta para el depósito:" << endl;

    for (size_t i = 0; i < cuentasCliente.size(); i++)
    {
        cout << i + 1 << ". Cuenta " << cuentasCliente[i].getNumeroCuenta()
             << " (" << cuentasCliente[i].getTipoString() << ") - Saldo: $"
             << fixed << setprecision(2) << cuentasCliente[i].getSaldo() << endl;
    }

    cout << "0. Cancelar operación" << endl;

    // Seleccionar cuenta con validación
    int seleccion = -1;
    bool seleccionValida = false;
    
    while (!seleccionValida) {
        cout << "Ingrese opción: ";
        string seleccionStr = leerSoloNumeros(); // Solo permite dígitos
        
        if (seleccionStr.empty()) {
            cout << "Error: Debe ingresar un número. Intente nuevamente." << endl;
            continue;
        }
        
        seleccion = stoi(seleccionStr);
        
        if (seleccion == 0) {
            cout << "Operación cancelada." << endl;
            cout << "Presione cualquier tecla para volver..." << endl;
            _getch();
            return;
        }
        
        if (seleccion < 1 || seleccion > (int)cuentasCliente.size()) {
            cout << "Error: Opción inválida. Intente nuevamente." << endl;
            continue;
        }
        
        seleccionValida = true;
    }

    // Solicitar monto con validación
    double monto = 0;
    bool montoValido = false;
    
    while (!montoValido) {
        cout << "Ingrese monto a depositar: $";
        string montoStr = leerSoloNumeros(true); // Permite dígitos y punto decimal
        
        try {
            monto = stod(montoStr);
            
            if (monto <= 0) {
                cout << "Error: El monto debe ser mayor a cero. Intente nuevamente." << endl;
                continue;
            }
            
            montoValido = true;
        }
        catch (const std::exception &e) {
            cout << "Error: Monto inválido. Intente nuevamente." << endl;
        }
    }

    // Solicitar concepto
    string concepto;
    cout << "Ingrese concepto (opcional): ";
    cin.ignore();
    getline(cin, concepto);

    // Realizar el depósito
    string numeroCuenta = cuentasCliente[seleccion - 1].getNumeroCuenta();
    NodoCuenta *nodoCuenta = arbolCuentas.buscarCuenta(numeroCuenta);

    if (!nodoCuenta)
    {
        cout << "Error: No se encontró la cuenta seleccionada." << endl;
        cout << "Presione cualquier tecla para volver..." << endl;
        _getch();
        return;
    }

    if (nodoCuenta->cuenta.depositar(monto, concepto))
    {
        cout << "Depósito realizado con éxito." << endl;

        // Guardar los cambios en el árbol
        arbolCuentas.guardarCuentasEnArchivo();

        // Registrar operación en el backtracking
        backupManager.registrarOperacion(
            "DEPOSITO",
            "Cuenta: " + numeroCuenta +
                ", Monto: $" + to_string(monto) +
                ", Cliente: " + clienteActual->getNombreCompleto());
    }
    else
    {
        cout << "Error al realizar el depósito." << endl;
    }

    cout << "Presione cualquier tecla para volver..." << endl;
    _getch();
}

void MenuBancario::realizarRetiro()
{
    // Obtener el cliente asociado al usuario actual
    Cliente *clienteActual = gestorClientes.buscarClientePorUsuario(usuarioActual->getUsername());
    if (!clienteActual)
    {
        cout << "Error: Cliente no encontrado." << endl;
        cout << "Presione cualquier tecla para volver..." << endl;
        _getch();
        return;
    }

    // Buscar las cuentas del cliente
    vector<Cuenta> cuentasCliente = arbolCuentas.buscarCuentasPorCliente(clienteActual->getCedula());

    if (cuentasCliente.empty())
    {
        cout << "Error: No tiene cuentas registradas." << endl;
        cout << "Presione cualquier tecla para volver..." << endl;
        _getch();
        return;
    }

    // Mostrar las cuentas disponibles
    system("cls");
    cout << "=====================================================" << endl;
    cout << "                 REALIZAR RETIRO                     " << endl;
    cout << "=====================================================" << endl;
    cout << "Seleccione la cuenta para el retiro:" << endl;

    for (size_t i = 0; i < cuentasCliente.size(); i++)
    {
        cout << i + 1 << ". Cuenta " << cuentasCliente[i].getNumeroCuenta()
             << " (" << cuentasCliente[i].getTipoString() << ") - Saldo: $"
             << fixed << setprecision(2) << cuentasCliente[i].getSaldo() << endl;
    }

    cout << "0. Cancelar operación" << endl;

    // Seleccionar cuenta con validación
    int seleccion = -1;
    bool seleccionValida = false;
    
    while (!seleccionValida) {
        cout << "Ingrese opción: ";
        string seleccionStr = leerSoloNumeros(); // Solo permite dígitos
        
        if (seleccionStr.empty()) {
            cout << "Error: Debe ingresar un número. Intente nuevamente." << endl;
            continue;
        }
        
        seleccion = stoi(seleccionStr);
        
        if (seleccion == 0) {
            cout << "Operación cancelada." << endl;
            cout << "Presione cualquier tecla para volver..." << endl;
            _getch();
            return;
        }
        
        if (seleccion < 1 || seleccion > (int)cuentasCliente.size()) {
            cout << "Error: Opción inválida. Intente nuevamente." << endl;
            continue;
        }
        
        seleccionValida = true;
    }

    // Solicitar monto con validación
    double monto = 0;
    bool montoValido = false;
    
    while (!montoValido) {
        cout << "Ingrese monto a retirar: $";
        string montoStr = leerSoloNumeros(true); // Permite dígitos y punto decimal
        
        try {
            monto = stod(montoStr);
            
            if (monto <= 0) {
                cout << "Error: El monto debe ser mayor a cero. Intente nuevamente." << endl;
                continue;
            }
            
            // Verificar si tiene saldo suficiente
            if (monto > cuentasCliente[seleccion - 1].getSaldo()) {
                cout << "Error: Saldo insuficiente. El saldo disponible es: $" 
                     << fixed << setprecision(2) << cuentasCliente[seleccion - 1].getSaldo() 
                     << ". Intente nuevamente." << endl;
                continue;
            }
            
            montoValido = true;
        }
        catch (const std::exception &e) {
            cout << "Error: Monto inválido. Intente nuevamente." << endl;
        }
    }

    // Solicitar concepto
    string concepto;
    cout << "Ingrese concepto (opcional): ";
    cin.ignore();
    getline(cin, concepto);

    // Realizar el retiro
    string numeroCuenta = cuentasCliente[seleccion - 1].getNumeroCuenta();
    NodoCuenta *nodoCuenta = arbolCuentas.buscarCuenta(numeroCuenta);

    if (!nodoCuenta)
    {
        cout << "Error: No se encontró la cuenta seleccionada." << endl;
        cout << "Presione cualquier tecla para volver..." << endl;
        _getch();
        return;
    }

    if (nodoCuenta->cuenta.retirar(monto, concepto))
    {
        cout << "Retiro realizado con éxito." << endl;

        // Guardar los cambios en el árbol
        arbolCuentas.guardarCuentasEnArchivo();

        // Registrar operación en el backtracking
        backupManager.registrarOperacion(
            "RETIRO",
            "Cuenta: " + numeroCuenta +
                ", Monto: $" + to_string(monto) +
                ", Cliente: " + clienteActual->getNombreCompleto());
    }
    else
    {
        cout << "Error al realizar el retiro. Verifique que tenga saldo suficiente." << endl;
    }

    cout << "Presione cualquier tecla para volver..." << endl;
    _getch();
}

void MenuBancario::realizarTransferencia()
{
    // Obtener el cliente asociado al usuario actual
    Cliente *clienteActual = gestorClientes.buscarClientePorUsuario(usuarioActual->getUsername());
    if (!clienteActual)
    {
        cout << "Error: Cliente no encontrado." << endl;
        cout << "Presione cualquier tecla para volver..." << endl;
        _getch();
        return;
    }

    // Buscar las cuentas del cliente
    vector<Cuenta> cuentasCliente = arbolCuentas.buscarCuentasPorCliente(clienteActual->getCedula());

    if (cuentasCliente.empty())
    {
        cout << "Error: No tiene cuentas registradas." << endl;
        cout << "Presione cualquier tecla para volver..." << endl;
        _getch();
        return;
    }

    // Mostrar las cuentas origen disponibles
    system("cls");
    cout << "=====================================================" << endl;
    cout << "              REALIZAR TRANSFERENCIA                 " << endl;
    cout << "=====================================================" << endl;
    cout << "Seleccione la cuenta origen:" << endl;

    for (size_t i = 0; i < cuentasCliente.size(); i++)
    {
        cout << i + 1 << ". Cuenta " << cuentasCliente[i].getNumeroCuenta()
             << " (" << cuentasCliente[i].getTipoString() << ") - Saldo: $"
             << fixed << setprecision(2) << cuentasCliente[i].getSaldo() << endl;
    }

    cout << "0. Cancelar operación" << endl;

    // Seleccionar cuenta origen con validación
    int seleccionOrigen = -1;
    bool seleccionOrigenValida = false;
    
    while (!seleccionOrigenValida) {
        cout << "Ingrese opción: ";
        string seleccionStr = leerSoloNumeros(); // Solo permite dígitos
        
        if (seleccionStr.empty()) {
            cout << "Error: Debe ingresar un número. Intente nuevamente." << endl;
            continue;
        }
        
        seleccionOrigen = stoi(seleccionStr);
        
        if (seleccionOrigen == 0) {
            cout << "Operación cancelada." << endl;
            cout << "Presione cualquier tecla para volver..." << endl;
            _getch();
            return;
        }
        
        if (seleccionOrigen < 1 || seleccionOrigen > (int)cuentasCliente.size()) {
            cout << "Error: Opción inválida. Intente nuevamente." << endl;
            continue;
        }
        
        seleccionOrigenValida = true;
    }

    // Solicitar cuenta destino con validación
    string cuentaDestino;
    bool cuentaDestinoValida = false;
    NodoCuenta *nodoDestino = nullptr;
    
    while (!cuentaDestinoValida) {
        cout << "\nIngrese número de cuenta destino: ";
        cuentaDestino = leerSoloNumeros(); // Solo permite dígitos
        
        // Verificar que la cuenta destino exista
        nodoDestino = arbolCuentas.buscarCuenta(cuentaDestino);
        if (!nodoDestino) {
            cout << "Error: La cuenta destino no existe. Intente nuevamente." << endl;
            continue;
        }
        
        // Verificar que no sea la misma cuenta
        if (cuentasCliente[seleccionOrigen - 1].getNumeroCuenta() == cuentaDestino) {
            cout << "Error: No puede transferir a la misma cuenta. Intente nuevamente." << endl;
            continue;
        }
        
        cuentaDestinoValida = true;
    }

    // Solicitar monto con validación
    double monto = 0;
    bool montoValido = false;
    
    while (!montoValido) {
        cout << "Ingrese monto a transferir: $";
        string montoStr = leerSoloNumeros(true); // Permite dígitos y punto decimal
        
        try {
            monto = stod(montoStr);
            
            if (monto <= 0) {
                cout << "Error: El monto debe ser mayor a cero. Intente nuevamente." << endl;
                continue;
            }
            
            // Verificar si tiene saldo suficiente
            if (monto > cuentasCliente[seleccionOrigen - 1].getSaldo()) {
                cout << "Error: Saldo insuficiente. El saldo disponible es: $" 
                     << fixed << setprecision(2) << cuentasCliente[seleccionOrigen - 1].getSaldo() 
                     << ". Intente nuevamente." << endl;
                continue;
            }
            
            montoValido = true;
        }
        catch (const std::exception &e) {
            cout << "Error: Monto inválido. Intente nuevamente." << endl;
        }
    }

    // Solicitar concepto
    string concepto;
    cout << "Ingrese concepto (opcional): ";
    cin.ignore();
    getline(cin, concepto);

    // Realizar la transferencia
    string numeroCuentaOrigen = cuentasCliente[seleccionOrigen - 1].getNumeroCuenta();
    NodoCuenta *nodoOrigen = arbolCuentas.buscarCuenta(numeroCuentaOrigen);

    if (!nodoOrigen)
    {
        cout << "Error: No se encontró la cuenta de origen." << endl;
        cout << "Presione cualquier tecla para volver..." << endl;
        _getch();
        return;
    }

    if (nodoOrigen->cuenta.transferir(nodoDestino->cuenta, monto, concepto))
    {
        cout << "Transferencia realizada con éxito." << endl;

        // Guardar los cambios en el árbol
        arbolCuentas.guardarCuentasEnArchivo();

        // Registrar operación en el backtracking
        backupManager.registrarOperacion(
            "TRANSFERENCIA",
            "Cuenta Origen: " + numeroCuentaOrigen +
                ", Cuenta Destino: " + cuentaDestino +
                ", Monto: $" + to_string(monto) +
                ", Cliente: " + clienteActual->getNombreCompleto());
    }
    else
    {
        cout << "Error al realizar la transferencia. Verifique que tenga saldo suficiente." << endl;
    }

    cout << "Presione cualquier tecla para volver..." << endl;
    _getch();
}

// Método auxiliar para modificar datos de cliente
void MenuBancario::modificarDatosCliente(Cliente *cliente)
{
    if (!cliente)
        return;

    ListaCircularMenu menuOpciones;
    menuOpciones.insertar("Editar Nombre");
    menuOpciones.insertar("Editar Apellido");
    menuOpciones.insertar("Editar Dirección");
    menuOpciones.insertar("Editar Teléfono");
    menuOpciones.insertar("Editar Email");
    menuOpciones.insertar("Volver al Menú Principal");

    int seleccion = 0;

    while (true)
    {
        system("cls");
        cout << "=====================================================" << endl;
        cout << "                 EDITAR CLIENTE                      " << endl;
        cout << "=====================================================" << endl;
        cout << "Cliente: " << cliente->getNombreCompleto() << " | Cédula: " << cliente->getCedula() << endl;
        cout << "-----------------------------------------------------" << endl;

        NodoMenu *actual = menuOpciones.getPrimero();
        for (int i = 0; i < menuOpciones.getTamano(); i++)
        {
            if (i == seleccion)
                cout << ">> " << actual->dato << " <<" << endl;
            else
                cout << "   " << actual->dato << endl;
            actual = actual->siguiente;
        }

        char tecla = _getch();
        if (tecla == 72)
        { // Flecha Arriba
            seleccion = (seleccion - 1 + menuOpciones.getTamano()) % menuOpciones.getTamano();
        }
        else if (tecla == 80)
        { // Flecha Abajo
            seleccion = (seleccion + 1) % menuOpciones.getTamano();
        }
        else if (tecla == '\r')
        { // Enter
            string opcionSeleccionada = menuOpciones.obtenerOpcion(seleccion);

            if (opcionSeleccionada == "Editar Nombre")
            {
                string nuevoNombre = leerSoloLetras("Ingrese nuevo nombre (solo letras): ");
                
                if (!nuevoNombre.empty())
                {
                    cliente->setNombre(nuevoNombre);
                    gestorClientes.guardarClientesEnArchivo();
                    cout << "Nombre actualizado correctamente." << endl;

                    // Registrar operación en el backtracking
                    backupManager.registrarOperacion("EDITAR_CLIENTE",
                                                    "Cédula: " + cliente->getCedula() + ", Nuevo Nombre: " + nuevoNombre);
                }

                cout << "Presione cualquier tecla para continuar..." << endl;
                _getch();
            }
            else if (opcionSeleccionada == "Editar Apellido")
            {
                string nuevoApellido = leerSoloLetras("Ingrese nuevo apellido (solo letras): ");
                
                if (!nuevoApellido.empty())
                {
                    cliente->setApellido(nuevoApellido);
                    gestorClientes.guardarClientesEnArchivo();
                    cout << "Apellido actualizado correctamente." << endl;

                    // Registrar operación en el backtracking
                    backupManager.registrarOperacion("EDITAR_CLIENTE",
                                                    "Cédula: " + cliente->getCedula() + ", Nuevo Apellido: " + nuevoApellido);
                }

                cout << "Presione cualquier tecla para continuar..." << endl;
                _getch();
            }
            else if (opcionSeleccionada == "Editar Dirección")
            {
                string nuevaDireccion = leerDireccion("Ingrese nueva dirección: ");
                
                if (!nuevaDireccion.empty())
                {
                    cliente->setDireccion(nuevaDireccion);
                    gestorClientes.guardarClientesEnArchivo();
                    cout << "Dirección actualizada correctamente." << endl;

                    // Registrar operación en el backtracking
                    backupManager.registrarOperacion("EDITAR_CLIENTE",
                                                    "Cédula: " + cliente->getCedula() + ", Nueva Dirección");
                }

                cout << "Presione cualquier tecla para continuar..." << endl;
                _getch();
            }
            else if (opcionSeleccionada == "Editar Teléfono")
            {
                string nuevoTelefono = leerTelefono("Ingrese nuevo teléfono (debe empezar con 09): ");
                
                if (!nuevoTelefono.empty())
                {
                    // Verificar que no esté siendo usado por otro cliente
                    bool telefonoRepetido = false;
                    vector<Cliente> clientesExistentes = gestorClientes.listarClientes();
                    for (const auto &otroCliente : clientesExistentes) {
                        if (otroCliente.getCedula() != cliente->getCedula() && // Excluir al cliente actual
                            otroCliente.getTelefono() == nuevoTelefono) {
                            telefonoRepetido = true;
                            break;
                        }
                    }
                    
                    if (telefonoRepetido) {
                        cout << "Error: Este número de teléfono ya está registrado para otro cliente." << endl;
                    } else {
                        cliente->setTelefono(nuevoTelefono);
                        gestorClientes.guardarClientesEnArchivo();
                        cout << "Teléfono actualizado correctamente." << endl;

                        // Registrar operación en el backtracking
                        backupManager.registrarOperacion("EDITAR_CLIENTE",
                                                        "Cédula: " + cliente->getCedula() + ", Nuevo Teléfono: " + nuevoTelefono);
                    }
                }

                cout << "Presione cualquier tecla para continuar..." << endl;
                _getch();
            }
            else if (opcionSeleccionada == "Editar Email")
            {
                string nuevoEmail = leerEmail("Ingrese nuevo email: ");
                
                if (!nuevoEmail.empty())
                {
                    // Verificar que el email no esté siendo usado por otro cliente
                    bool emailRepetido = false;
                    vector<Cliente> clientesExistentes = gestorClientes.listarClientes();
                    for (const auto &otroCliente : clientesExistentes) {
                        if (otroCliente.getCedula() != cliente->getCedula() && // Excluir al cliente actual
                            otroCliente.getEmail() == nuevoEmail) {
                            emailRepetido = true;
                            break;
                        }
                    }
                    
                    if (emailRepetido) {
                        cout << "Error: Este email ya está registrado para otro cliente." << endl;
                    } else {
                        cliente->setEmail(nuevoEmail);
                        gestorClientes.guardarClientesEnArchivo();
                        cout << "Email actualizado correctamente." << endl;

                        // Registrar operación en el backtracking
                        backupManager.registrarOperacion("EDITAR_CLIENTE",
                                                        "Cédula: " + cliente->getCedula() + ", Nuevo Email: " + nuevoEmail);
                    }
                }

                cout << "Presione cualquier tecla para continuar..." << endl;
                _getch();
            }
            else if (opcionSeleccionada == "Volver al Menú Principal")
            {
                break;
            }
        }
    }
}

void MenuBancario::listarTodasLasCuentas()
{
    vector<Cuenta> cuentas = arbolCuentas.listarCuentas();

    system("cls");
    cout << "=====================================================" << endl;
    cout << "              LISTADO DE TODAS LAS CUENTAS           " << endl;
    cout << "=====================================================" << endl;

    if (cuentas.empty())
    {
        cout << "No hay cuentas registradas en el sistema." << endl;
    }
    else
    {
        cout << left << setw(15) << "NÚMERO" << setw(15) << "TIPO"
             << setw(20) << "TITULAR" << setw(15) << "ESTADO" << "SALDO" << endl;
        cout << "-----------------------------------------------------" << endl;

        for (const auto &cuenta : cuentas)
        {
            cout << left << setw(15) << cuenta.getNumeroCuenta()
                 << setw(15) << cuenta.getTipoString()
                 << setw(20) << cuenta.getTitular().getNombreCompleto()
                 << setw(15) << (cuenta.isActiva() ? "Activa" : "Inactiva")
                 << "$" << fixed << setprecision(2) << cuenta.getSaldo() << endl;
        }

        cout << "-----------------------------------------------------" << endl;
        cout << "Total de cuentas: " << cuentas.size() << endl;
    }

    cout << "\nPresione cualquier tecla para volver..." << endl;
    _getch();
}

void MenuBancario::buscarCuentaPorNumero()
{
    system("cls");
    cout << "=====================================================" << endl;
    cout << "              BUSCAR CUENTA POR NÚMERO               " << endl;
    cout << "=====================================================" << endl;

    // Solo permitir números en el número de cuenta
    string numeroCuenta = leerSoloDigitos("Ingrese número de cuenta: ");

    // Buscar la cuenta
    NodoCuenta *nodoCuenta = arbolCuentas.buscarCuenta(numeroCuenta);
    if (!nodoCuenta)
    {
        cout << "Error: No se encontró una cuenta con ese número." << endl;
        cout << "Presione cualquier tecla para volver..." << endl;
        _getch();
        return;
    }

    // Mostrar información detallada de la cuenta
    system("cls");
    nodoCuenta->cuenta.mostrarDetalles();

    cout << "\nHistorial de Transacciones:" << endl;
    cout << "-----------------------------------------------------" << endl;

    vector<Transaccion> transacciones = nodoCuenta->cuenta.getHistorialTransacciones();

    if (transacciones.empty())
    {
        cout << "No hay transacciones registradas para esta cuenta." << endl;
    }
    else
    {
        cout << left << setw(12) << "FECHA" << setw(15) << "TIPO"
             << setw(12) << "MONTO" << "CONCEPTO" << endl;
        cout << "-----------------------------------------------------" << endl;

        for (const auto &trans : transacciones)
        {
            cout << left << setw(12) << trans.getFecha().mostrar()
                 << setw(15) << trans.getTipoString()
                 << "$" << setw(11) << fixed << setprecision(2) << trans.getMonto()
                 << trans.getConcepto() << endl;
        }
    }

    cout << "\nPresione cualquier tecla para volver..." << endl;
    _getch();
}
void MenuBancario::agregarNuevoCliente()
{
    string cedula, nombre, apellido, direccion, telefono, email;
    string username, password;
    int tipoInt;
    double saldoInicial;

    system("cls");
    cout << "=====================================================" << endl;
    cout << "              AGREGAR NUEVO CLIENTE                  " << endl;
    cout << "=====================================================" << endl;

    // Validación de cédula en tiempo real (solo dígitos)
    bool cedulaValida = false;
    while (!cedulaValida) {
        cedula = leerSoloDigitos("Ingrese cédula (solo números): ");

        // Verificar si ya existe un cliente con esa cédula
        if (gestorClientes.existeCliente(cedula)) {
            cout << "Error: Ya existe un cliente con esa cédula. Intente nuevamente." << endl;
            continue;
        }

        // Validar cédula ecuatoriana
        if (!Cliente::validarCedula(cedula)) {
            cout << "Error: La cédula ingresada no es válida. Debe tener 10 dígitos y cumplir con la validación de cédulas ecuatorianas. Intente nuevamente." << endl;
            continue;
        }
        
        cedulaValida = true;
    }

    // Validación de nombre (solo letras)
    nombre = leerSoloLetras("Ingrese nombre (solo letras): ");
    
    // Validación de apellido (solo letras)
    apellido = leerSoloLetras("Ingrese apellido (solo letras): ");
    
    // Validación de dirección (alfanumérico y algunos caracteres especiales)
    direccion = leerDireccion("Ingrese dirección: ");
    
    // Validación de teléfono (solo números y formato específico)
    telefono = leerTelefono("Ingrese teléfono (debe empezar con 09): ");
    
    // Validación de email (formato correcto)
    bool emailValido = false;
    while (!emailValido) {
        email = leerEmail("Ingrese email: ");
        
        // Verificar que el email no esté siendo usado por otro cliente
        bool emailRepetido = false;
        vector<Cliente> clientesExistentes = gestorClientes.listarClientes();
        for (const auto &cliente : clientesExistentes) {
            if (cliente.getEmail() == email) {
                emailRepetido = true;
                break;
            }
        }
        
        if (emailRepetido) {
            cout << "Error: Este email ya está registrado para otro cliente. Intente nuevamente." << endl;
            continue;
        }
        
        emailValido = true;
    }

    // Validación de fecha de nacimiento con formato DD-MM-AAAA
    string fechaStr = leerFecha("Ingrese fecha de nacimiento (DD-MM-AAAA): ");
    
    // Extraer componentes de la fecha
    int dia = stoi(fechaStr.substr(0, 2));
    int mes = stoi(fechaStr.substr(3, 2));
    int anio = stoi(fechaStr.substr(6, 4));
    Fecha fechaNacimiento(dia, mes, anio);

    // Validación de nombre de usuario (alfanumérico)
    bool usernameValido = false;
    while (!usernameValido) {
        username = leerUsername("Ingrese nombre de usuario (solo letras y números): ");

        // Verificar si ya existe un usuario con ese nombre
        if (gestorClientes.existeUsuario(username)) {
            cout << "Error: Ya existe un usuario con ese nombre. Intente nuevamente." << endl;
            continue;
        }
        
        usernameValido = true;
    }

    // Validación de contraseña (mínimo 6 caracteres)
    password = leerPassword("Ingrese contraseña (mínimo 6 caracteres): ");

    // Validación de tipo de cuenta
    bool tipoValido = false;
    TipoCuenta tipo;
    while (!tipoValido) {
        cout << "\n--- Información de la cuenta inicial ---" << endl;
        cout << "Seleccione tipo de cuenta:" << endl;
        cout << "1. Cuenta de Ahorro" << endl;
        cout << "2. Cuenta Corriente" << endl;
        cout << "3. Cuenta a Plazo Fijo" << endl;
        
        string tipoStr = leerSoloDigitos("Opción: ");
        
        try {
            tipoInt = stoi(tipoStr);

            if (tipoInt < 1 || tipoInt > 3) {
                cout << "Error: Tipo de cuenta no válido. Intente nuevamente." << endl;
                continue;
            }

            tipo = static_cast<TipoCuenta>(tipoInt - 1); // Convertir a enum
            tipoValido = true;
        }
        catch (const exception &e) {
            cout << "Error: Opción inválida. Intente nuevamente." << endl;
        }
    }

    // Validación de saldo inicial
    bool saldoValido = false;
    while (!saldoValido) {
        cout << "Ingrese saldo inicial: $";
        string saldoStr = leerSoloNumeros(true); // Usa la función ya existente que permite decimales
        
        try {
            saldoInicial = stod(saldoStr);

            if (saldoInicial < 0) {
                cout << "Error: El saldo inicial no puede ser negativo. Intente nuevamente." << endl;
                continue;
            }
            
            saldoValido = true;
        }
        catch (const exception &e) {
            cout << "Error: Saldo inválido. Debe ingresar un número. Intente nuevamente." << endl;
        }
    }

    // Registrar cliente con cuenta usando el gestor integrado
    GestorIntegrado gestorIntegrado(gestorClientes, arbolCuentas, backupManager);

    if (gestorIntegrado.registrarClienteConCuenta(
            cedula, nombre, apellido, direccion, telefono, email,
            fechaNacimiento, username, password, tipo, saldoInicial)) {

        cout << "Cliente y cuenta creados exitosamente." << endl;
    }
    else {
        cout << "Error al registrar el cliente y crear la cuenta." << endl;
    }

    cout << "Presione cualquier tecla para volver..." << endl;
    _getch();
}

// Reemplazar el método editarCliente() con esta versión:
void MenuBancario::editarCliente()
{
    // Si es un cliente normal, editar su propio perfil
    if (usuarioActual->getRol() != "ADMIN")
    {
        Cliente *cliente = gestorClientes.buscarClientePorUsuario(usuarioActual->getUsername());
        if (!cliente)
        {
            cout << "Error: Cliente no encontrado." << endl;
            cout << "Presione cualquier tecla para volver..." << endl;
            _getch();
            return;
        }
        modificarDatosCliente(cliente);
        return;
    }

    // Si es administrador, solicitar la cédula del cliente a editar
    system("cls");
    cout << "=====================================================" << endl;
    cout << "                   EDITAR CLIENTE                    " << endl;
    cout << "=====================================================" << endl;
    
    // Validación de cédula (solo dígitos)
    string cedula = leerSoloDigitos("Ingrese cédula del cliente a editar: ");

    GestorIntegrado gestorIntegrado(gestorClientes, arbolCuentas, backupManager);
    Cliente *cliente = gestorIntegrado.buscarClienteSeguro(cedula);

    if (cliente)
    {
        modificarDatosCliente(cliente);
    }
    else
    {
        cout << "Presione cualquier tecla para volver..." << endl;
        _getch();
    }
}

// Reemplazar el método eliminarCliente() con esta versión:
void MenuBancario::eliminarCliente()
{
    // Cambiar nombre del método a desactivarCuentasCliente
    system("cls");
    cout << "=====================================================" << endl;
    cout << "           DESACTIVAR CUENTAS DE CLIENTE             " << endl;
    cout << "=====================================================" << endl;
    
    // Validación de cédula (solo dígitos)
    string cedula = leerSoloDigitos("Ingrese cédula del cliente cuyas cuentas desea desactivar: ");

    GestorIntegrado gestorIntegrado(gestorClientes, arbolCuentas, backupManager);
    Cliente *cliente = gestorIntegrado.buscarClienteSeguro(cedula);

    if (!cliente)
    {
        cout << "Presione cualquier tecla para volver..." << endl;
        _getch();
        return;
    }

    // Verificar si el cliente tiene cuentas
    vector<Cuenta> cuentasCliente = arbolCuentas.buscarCuentasPorCliente(cedula);

    if (cuentasCliente.empty())
    {
        cout << "Este cliente no tiene cuentas activas para desactivar." << endl;
        cout << "Presione cualquier tecla para volver..." << endl;
        _getch();
        return;
    }

    // Confirmar desactivación
    cout << "==============================================" << endl;
    cout << "Cliente: " << cliente->getNombreCompleto() << endl;
    cout << "Este cliente tiene " << cuentasCliente.size() << " cuenta(s)." << endl;
    cout << "Todas serán marcadas como inactivas, pero se mantendrán en el sistema." << endl;
    cout << "==============================================" << endl;

    char confirmar;
    cout << "¿Está seguro de desactivar todas las cuentas de este cliente? (S/N): ";
    confirmar = _getch();
    cout << confirmar << endl; // Mostrar la tecla presionada

    if (toupper(confirmar) == 'S')
    {
        if (gestorIntegrado.desactivarCuentasCliente(cedula))
        {
            cout << "Cuentas desactivadas correctamente. El cliente permanece en el sistema." << endl;
        }
        else
        {
            cout << "Error al desactivar algunas cuentas del cliente." << endl;
        }
    }
    else
    {
        cout << "Operación cancelada." << endl;
    }

    cout << "Presione cualquier tecla para volver..." << endl;
    _getch();
}

// Reemplazar el método cerrarCuenta() con esta versión:
void MenuBancario::cerrarCuenta()
{
    system("cls");
    cout << "=====================================================" << endl;
    cout << "                 CERRAR CUENTA                       " << endl;
    cout << "=====================================================" << endl;

    // Solo permitir números en el número de cuenta
    string numeroCuenta = leerSoloDigitos("Ingrese número de cuenta a cerrar: ");

    GestorIntegrado gestorIntegrado(gestorClientes, arbolCuentas, backupManager);

    if (gestorIntegrado.cerrarCuentaSeguro(numeroCuenta))
    {
        cout << "Cuenta cerrada correctamente." << endl;
    }

    cout << "Presione cualquier tecla para volver..." << endl;
    _getch();
}

// Reemplazar el método crearNuevaCuenta() con esta versión:
void MenuBancario::crearNuevaCuenta()
{
    string cedula;
    int tipoInt;
    double saldoInicial;

    system("cls");
    cout << "=====================================================" << endl;
    cout << "              CREAR NUEVA CUENTA                     " << endl;
    cout << "=====================================================" << endl;

    // Validación de cédula (solo dígitos)
    cedula = leerSoloDigitos("Ingrese cédula del titular (solo números): ");

    GestorIntegrado gestorIntegrado(gestorClientes, arbolCuentas, backupManager);

    // Verificar si existe el cliente
    Cliente *cliente = gestorIntegrado.buscarClienteSeguro(cedula);
    if (!cliente)
    {
        cout << "Presione cualquier tecla para volver..." << endl;
        _getch();
        return;
    }

    // Seleccionar tipo de cuenta
    bool tipoValido = false;
    TipoCuenta tipo;
    while (!tipoValido) {
        cout << "Seleccione tipo de cuenta:" << endl;
        cout << "1. Cuenta de Ahorro" << endl;
        cout << "2. Cuenta Corriente" << endl;
        cout << "3. Cuenta a Plazo Fijo" << endl;
        
        string tipoStr = leerSoloDigitos("Opción: ");
        
        try {
            tipoInt = stoi(tipoStr);

            if (tipoInt < 1 || tipoInt > 3) {
                cout << "Error: Tipo de cuenta no válido. Intente nuevamente." << endl;
                continue;
            }

            tipo = static_cast<TipoCuenta>(tipoInt - 1); // Convertir a enum
            tipoValido = true;
        }
        catch (const exception &e) {
            cout << "Error: Opción inválida. Intente nuevamente." << endl;
        }
    }

    // Validación de saldo inicial
    bool saldoValido = false;
    while (!saldoValido) {
        cout << "Ingrese saldo inicial: $";
        string saldoStr = leerSoloNumeros(true); // Permite dígitos y punto decimal
        
        try {
            saldoInicial = stod(saldoStr);

            if (saldoInicial < 0) {
                cout << "Error: El saldo inicial no puede ser negativo. Intente nuevamente." << endl;
                continue;
            }
            
            saldoValido = true;
        }
        catch (const exception &e) {
            cout << "Error: Saldo inválido. Debe ingresar un número. Intente nuevamente." << endl;
        }
    }

    // Crear la cuenta adicional
    if (gestorIntegrado.crearCuentaAdicional(cedula, tipo, saldoInicial))
    {
        cout << "Cuenta adicional creada correctamente." << endl;
    }
    else
    {
        cout << "Error al crear la cuenta adicional." << endl;
    }

    cout << "Presione cualquier tecla para volver..." << endl;
    _getch();
}
void MenuBancario::generarQRParaTransferencia()
{
#ifdef _WIN32
    _mkdir("qr_codes");
#else
    mkdir("qr_codes", 0777); // Para sistemas Unix-like
#endif
    // Obtener el cliente asociado al usuario actual
    Cliente *clienteActual = gestorClientes.buscarClientePorUsuario(usuarioActual->getUsername());
    if (!clienteActual)
    {
        cout << "Error: Cliente no encontrado." << endl;
        cout << "Presione cualquier tecla para volver..." << endl;
        _getch();
        return;
    }

    // Buscar las cuentas del cliente
    vector<Cuenta> cuentasCliente = arbolCuentas.buscarCuentasPorCliente(clienteActual->getCedula());

    if (cuentasCliente.empty())
    {
        cout << "Error: No tiene cuentas registradas para generar QR." << endl;
        cout << "Presione cualquier tecla para volver..." << endl;
        _getch();
        return;
    }

    // Mostrar las cuentas disponibles
    system("cls");
    cout << "=====================================================" << endl;
    cout << "           GENERAR QR PARA TRANSFERENCIA             " << endl;
    cout << "=====================================================" << endl;
    cout << "Seleccione la cuenta para generar el código QR:" << endl;

    for (size_t i = 0; i < cuentasCliente.size(); i++)
    {
        cout << i + 1 << ". Cuenta " << cuentasCliente[i].getNumeroCuenta()
             << " (" << cuentasCliente[i].getTipoString() << ") - Saldo: $"
             << fixed << setprecision(2) << cuentasCliente[i].getSaldo() << endl;
    }

    cout << "0. Cancelar operación" << endl;

    // Seleccionar cuenta con validación
    int seleccion = -1;
    bool seleccionValida = false;
    
    while (!seleccionValida) {
        cout << "Ingrese opción: ";
        string seleccionStr = leerSoloNumeros(); // Solo permite dígitos
        
        if (seleccionStr.empty()) {
            cout << "Error: Debe ingresar un número. Intente nuevamente." << endl;
            continue;
        }
        
        seleccion = stoi(seleccionStr);
        
        if (seleccion == 0) {
            cout << "Operación cancelada." << endl;
            cout << "Presione cualquier tecla para volver..." << endl;
            _getch();
            return;
        }
        
        if (seleccion < 1 || seleccion > (int)cuentasCliente.size()) {
            cout << "Error: Opción inválida. Intente nuevamente." << endl;
            continue;
        }
        
        seleccionValida = true;
    }

    // Solicitar monto sugerido con validación
    double monto = 0;
    bool montoValido = false;
    
    while (!montoValido) {
        cout << "Ingrese monto sugerido para la transferencia (0 para que el remitente decida): $";
        string montoStr = leerSoloNumeros(true); // Permite dígitos y punto decimal
        
        try {
            monto = stod(montoStr);
            
            if (monto < 0) {
                cout << "Error: El monto no puede ser negativo. Intente nuevamente." << endl;
                continue;
            }
            
            montoValido = true;
        }
        catch (const std::exception &e) {
            cout << "Error: Monto inválido. Intente nuevamente." << endl;
        }
    }

    // Solicitar concepto
    string concepto;
    cout << "Ingrese concepto para la transferencia: ";
    cin.ignore();
    getline(cin, concepto);

    // Generar el QR
    string numeroCuenta = cuentasCliente[seleccion - 1].getNumeroCuenta();
    string nombreTitular = clienteActual->getNombreCompleto();

    // Crear la carpeta qr_codes si no existe
    _mkdir("qr_codes");

    // Generar nombre de archivo único
    string nombreArchivo = "qr_codes/transferencia_" + numeroCuenta + ".html";

    QRGenerator qrGenerator;
    bool exito = qrGenerator.generarQRTransferencia(
        numeroCuenta, nombreTitular, monto, concepto, nombreArchivo);

    if (exito)
    {
        cout << "Código QR generado exitosamente." << endl;
        cout << "Archivo: " << nombreArchivo << endl;

        // Registrar operación en el backtracking
        backupManager.registrarOperacion(
            "GENERAR_QR_TRANSFERENCIA",
            "Cuenta: " + numeroCuenta +
                ", Monto Sugerido: $" + to_string(monto) +
                ", Cliente: " + nombreTitular);

        // Abrir el QR automáticamente en el navegador
        string comando = "start " + nombreArchivo;
        system(comando.c_str());
    }
    else
    {
        cout << "Error al generar el código QR." << endl;
    }

    cout << "Presione cualquier tecla para volver..." << endl;
    _getch();
}
