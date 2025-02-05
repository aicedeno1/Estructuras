#ifndef MENUVALIDATION_H
#define MENUVALIDATION_H

#include <iostream>
#include <limits>

class MenuValidation
{
private:
     static void clearBuffer()
    {
        std::cin.clear();
        // Limpiar solo hasta encontrar un salto de línea
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

public:
    static void displayMenu()
    {
        system("cls"); // Limpia la consola
        std::cout << "Programa de Arbol Rojo-Negro\n";
        std::cout << "1. Insertar numero\n";
        std::cout << "2. Mostrar arbol\n";
        std::cout << "3. Mostrar recorrido Preorder\n";
        std::cout << "4. Mostrar recorrido Inorder\n";
        std::cout << "5. Mostrar recorrido Postorder\n";
        std::cout << "6. Salir\n";
        std::cout << "Elija una opcion (1-6): ";
    }

    static int getMenuOption()
    {
        int option;
        bool validInput = false;

        do
        {
            if (std::cin >> option)
            {
                if (option >= 1 && option <= 6)
                {
                    if (option == 2)
                    {
                        clearBuffer();
                        return option;
                    }
                    validInput = true;
                }
                else
                {
                    std::cout << "Error: Ingrese un numero entre 1 y 6\n";
                    std::cout << "Presione Enter para continuar...";
                    clearBuffer();
                    std::cin.get();
                    displayMenu();
                }
            }
            else
            {
                std::cout << "Error: Ingrese un numero valido\n";
                std::cout << "Presione Enter para continuar...";
                clearBuffer();
                std::cin.get();
                displayMenu();
            }
        } while (!validInput);

        return option;
    }

    static void waitForEnter()
    {
        std::cout << "\nPresione Enter para continuar...";
        clearBuffer();
        std::cin.get();
    }

    static char getContinueOption()
    {
        char option;
        std::cout << "\nDesea insertar otro numero? (s/n): ";
        std::cin >> option;
        clearBuffer(); // Limpiar el buffer después de leer la opción
        return tolower(option);
    }

    static int getNumberInput()
    {
        system("cls");
        std::cout << "=== Modo Insercion ===\n";
        std::cout << "Ingrese un numero para insertar en el arbol: ";
        int number;
        std::cin >> number;
        clearBuffer(); // Limpiar el buffer después de leer el número
        return number;
    }
};

#endif