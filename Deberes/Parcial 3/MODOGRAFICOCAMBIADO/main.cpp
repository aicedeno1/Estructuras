#include "RedBlackTree.h"
#include "MenuValidation.h"
#include <iostream>
#include <graphics.h>

int main()
{
    RedBlackTree tree;
    int valor, opcion;

    do
    {
        MenuValidation::displayMenu();
        opcion = MenuValidation::getMenuOption();

        switch (opcion)
        {
        case 1:
        {
            char seguirInsertando;
            do
            {
                valor = MenuValidation::getNumberInput();
                tree.insert(valor);
                seguirInsertando = MenuValidation::getContinueOption();
            } while (seguirInsertando == 's');
            break;
        }
        case 2:
            tree.visualize();
            MenuValidation::waitForEnter();
            break;
        case 3:
            tree.preorder();
            MenuValidation::waitForEnter();
            break;
        case 4:
            tree.inorder();
            MenuValidation::waitForEnter();
            break;
        case 5:
            tree.postorder();
            MenuValidation::waitForEnter();
            break;
        case 6:
            closegraph();
            return 0;
        }
    } while (true);

    return 0;
}