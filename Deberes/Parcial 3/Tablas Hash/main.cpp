#include "HashTable.h"
#include "MenuValidation.h"
#include <iostream>

int main()
{
    HashTable letterTable(true);  // Tabla para letras
    HashTable numberTable(false); // Tabla para números
    int option;

    do
    {
        MenuValidation::displayMenu();
        option = MenuValidation::getMenuOption();

        switch (option)
        {
        case 1:
        {
            std::string value = MenuValidation::getValue(true);
            letterTable.insert(value);
            break;
        }
        case 2:
        {
            std::string value = MenuValidation::getValue(false);
            numberTable.insert(value);
            break;
        }
        case 3:
            letterTable.visualize();
            break;
        case 4:
            numberTable.visualize();
            break;
        case 5:
            return 0;
        }
    } while (true);

    return 0;
}