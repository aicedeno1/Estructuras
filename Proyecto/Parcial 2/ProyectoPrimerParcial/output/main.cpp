/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Archivo principal de ayuda                               *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/


#include <iostream>
#include <conio.h>

using namespace std;

void mostrarAyuda() {
    system("cls");

    // Encabezado
    cout << "=======================================" << endl;
    cout << "              Uso Basico              " << endl;
    cout << "=======================================" << endl;

    // Sección de uso básico
    cout << "\n1. Registrar un libro:" << endl;
    cout << "   Para registrar un nuevo libro, seleccione la opcion" << endl;
    cout << "   'Agregar libro' desde el menu principal. Ingrese los" << endl;
    cout << "   datos requeridos como titulo, autor, ano de publicacion" << endl;
    cout << "   y genero, y haga clic en 'GUARDAR'."<< endl;

    cout << "\n2. Buscar un libro:" << endl;
    cout << "   Utilice la opcion 'Buscar libro' e ingrese los parametros" << endl;
    cout << "   de busqueda (como titulo o autor) para encontrar un libro en el registro." << endl;

    cout << "\n3. Eliminar un libro:" << endl;
    cout << "   Seleccione el libro que desea eliminar de la lista de libros" << endl;
    cout << "   y haga clic en 'ELIMINAR'. Confirme la accion para borrar el libro del registro." << endl;

    cout << "\n4. Imprimir lista de libros:" << endl;
    cout << "   Puede imprimir la lista de libros registrados seleccionando" << endl;
    cout << "   la opcion 'IMPRIMIR' en el menu principal." << endl;

    // Separador
    cout << "\n=======================================" << endl;
    cout << "           Funciones Avanzadas         " << endl;
    cout << "=======================================" << endl;

    // Sección de funciones avanzadas
    cout << "\n1. Realizar un Backup:" << endl;
    cout << "   Para realizar un backup de los datos, seleccione la" << endl;
    cout << "   opción 'BACKUP' desde el menú. El sistema guardara" << endl;
    cout << "   una copia de seguridad de los datos en formato de fecha y hora" << endl;
    cout << "   (ano-mes-dia-hora-minuto-segundo)." << endl;

    cout << "\n2. Restaurar desde un Backup:" << endl;
    cout << "   Para restaurar un backup, seleccione 'RESTAURAR BACKUP'" << endl;
    cout << "   desde el menu y elija el archivo de backup correspondiente." << endl;
    cout << "   El sistema recuperara los datos a partir de esa copia de seguridad." << endl;

    // Instrucción para continuar
    cout << "\n=============================================" << endl;
    cout << "Presione 'Enter' dos veces para continuar..." << endl;
    cout << "=============================================" << endl;

    // Pausa para el usuario
cin.ignore(); // Limpia el buffer de entrada
    cin.get();    // Espera Enter
}

int main() {
    mostrarAyuda();
    return 0; // Cierra el programa inmediatamente
}
