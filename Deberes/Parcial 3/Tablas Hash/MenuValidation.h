#ifndef MENUVALIDATION_H
#define MENUVALIDATION_H

#include <iostream>
#include <limits>

class MenuValidation
{
public:
    static void displayMenu()
    {
        system("cls");
        std::cout << "Programa de Tablas Hash\n";
        std::cout << "1. Insertar en tabla de letras\n";
        std::cout << "2. Insertar en tabla de numeros\n";
        std::cout << "3. Visualizar tabla de letras\n";
        std::cout << "4. Visualizar tabla de numeros\n";
        std::cout << "5. Salir\n";
        std::cout << "Elija una opcion (1-5): ";
    }

    static int getMenuOption()
    {
        int option;
        std::cin >> option;
        while (option < 1 || option > 5)
        {
            std::cout << "Opcion invalida. Intente nuevamente: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> option;
        }
        return option;
    }

    static std::string getValue(bool isLetterMode)
    {
        system("cls");
        std::string value;
        if (isLetterMode)
        {
            std::cout << "Ingrese una letra: ";
        }
        else
        {
            std::cout << "Ingrese un numero: ";
        }
        std::cin >> value;
        return value;
    }
};

#endif