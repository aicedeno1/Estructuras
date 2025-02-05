// RedBlackTree.cpp
#include "RedBlackTree.h"
#include "MenuValidation.h"
#include <graphics.h>
#include <cmath>
#include <queue>
#include <iostream>

RedBlackTree::RedBlackTree()
{
    root = nullptr;
}

// Los métodos rotateLeft, rotateRight, fixViolation y getHeight permanecen igual
// ya que no usan funciones de texto

void RedBlackTree::calculateNodePosition(Node *node, int x, int y, int level, int maxLevel)
{
    if (node == nullptr)
        return;

    // Ajustar el offset basado en el nivel para reducir el espaciado horizontal
    int offset = (WINDOW_WIDTH / pow(2, level + 2)) + RADIUS;

    // Dibujar conexiones con los hijos
    if (node->left != nullptr)
    {
        int childX = x - offset;
        int childY = y + VERTICAL_SPACING;
        setcolor(WHITE);
        line(x, y, childX, childY);
        calculateNodePosition(node->left, childX, childY, level + 1, maxLevel);
    }

    if (node->right != nullptr)
    {
        int childX = x + offset;
        int childY = y + VERTICAL_SPACING;
        setcolor(WHITE);
        line(x, y, childX, childY);
        calculateNodePosition(node->right, childX, childY, level + 1, maxLevel);
    }

    // Dibujar el nodo
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, node->isRed ? RED : BLACK);
    fillellipse(x, y, RADIUS, RADIUS);

    // Dibujar el número
    char num[10];
    sprintf(num, "%d", node->data);
    setcolor(node->isRed ? BLACK : WHITE);
    setbkcolor(node->isRed ? RED : BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1); // Ajustar tamaño del texto
    outtextxy(x - textwidth(num) / 2, y - textheight(num) / 2, num);
}
// Los métodos insert, visualize, y los recorridos (traversal) permanecen igual
// ya que no usan funciones de texto directamente

void RedBlackTree::preorder()
{
    system("cls");
    std::cout << "Recorrido Preorder:\n";
    std::string result = preorderTraversal(root);
    std::cout << result << "\n";
    MenuValidation::waitForEnter();
}

void RedBlackTree::inorder()
{
    system("cls");
    std::cout << "Recorrido Inorder:\n";
    std::string result = inorderTraversal(root);
    std::cout << result << "\n";
    MenuValidation::waitForEnter();
}

void RedBlackTree::postorder()
{
    system("cls");
    std::cout << "Recorrido Postorder:\n";
    std::string result = postorderTraversal(root);
    std::cout << result << "\n";
    MenuValidation::waitForEnter();
}
void RedBlackTree::rotateLeft(Node *&root, Node *&pt)
{
    Node *pt_right = pt->right;
    pt->right = pt_right->left;

    if (pt->right != nullptr)
        pt->right->parent = pt;

    pt_right->parent = pt->parent;

    if (pt->parent == nullptr)
        root = pt_right;
    else if (pt == pt->parent->left)
        pt->parent->left = pt_right;
    else
        pt->parent->right = pt_right;

    pt_right->left = pt;
    pt->parent = pt_right;
}

void RedBlackTree::rotateRight(Node *&root, Node *&pt)
{
    Node *pt_left = pt->left;
    pt->left = pt_left->right;

    if (pt->left != nullptr)
        pt->left->parent = pt;

    pt_left->parent = pt->parent;

    if (pt->parent == nullptr)
        root = pt_left;
    else if (pt == pt->parent->left)
        pt->parent->left = pt_left;
    else
        pt->parent->right = pt_left;

    pt_left->right = pt;
    pt->parent = pt_left;
}

void RedBlackTree::fixViolation(Node *&root, Node *&pt)
{
    Node *parent_pt = nullptr;
    Node *grand_parent_pt = nullptr;

    while ((pt != root) && (pt->isRed) && (pt->parent->isRed))
    {
        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;

        if (parent_pt == grand_parent_pt->left)
        {
            Node *uncle_pt = grand_parent_pt->right;

            if (uncle_pt != nullptr && uncle_pt->isRed)
            {
                grand_parent_pt->isRed = true;
                parent_pt->isRed = false;
                uncle_pt->isRed = false;
                pt = grand_parent_pt;
            }
            else
            {
                if (pt == parent_pt->right)
                {
                    rotateLeft(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                rotateRight(root, grand_parent_pt);
                bool temp = parent_pt->isRed;
                parent_pt->isRed = grand_parent_pt->isRed;
                grand_parent_pt->isRed = temp;
                pt = parent_pt;
            }
        }
        else
        {
            Node *uncle_pt = grand_parent_pt->left;

            if ((uncle_pt != nullptr) && (uncle_pt->isRed))
            {
                grand_parent_pt->isRed = true;
                parent_pt->isRed = false;
                uncle_pt->isRed = false;
                pt = grand_parent_pt;
            }
            else
            {
                if (pt == parent_pt->left)
                {
                    rotateRight(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                rotateLeft(root, grand_parent_pt);
                bool temp = parent_pt->isRed;
                parent_pt->isRed = grand_parent_pt->isRed;
                grand_parent_pt->isRed = temp;
                pt = parent_pt;
            }
        }
    }

    root->isRed = false;
}

void RedBlackTree::insert(int data)
{
    Node *pt = new Node(data);

    if (root == nullptr)
    {
        pt->isRed = false;
        root = pt;
    }
    else
    {
        Node *current = root;
        Node *parent = nullptr;

        while (current != nullptr)
        {
            parent = current;
            if (pt->data < current->data)
                current = current->left;
            else
                current = current->right;
        }

        pt->parent = parent;

        if (pt->data < parent->data)
            parent->left = pt;
        else
            parent->right = pt;

        fixViolation(root, pt);
    }
}

std::string RedBlackTree::preorderTraversal(Node *node)
{
    if (node == nullptr)
        return "";

    std::string result = std::to_string(node->data) + " ";
    result += preorderTraversal(node->left);
    result += preorderTraversal(node->right);

    return result;
}

std::string RedBlackTree::inorderTraversal(Node *node)
{
    if (node == nullptr)
        return "";

    std::string result = inorderTraversal(node->left);
    result += std::to_string(node->data) + " ";
    result += inorderTraversal(node->right);

    return result;
}

std::string RedBlackTree::postorderTraversal(Node *node)
{
    if (node == nullptr)
        return "";

    std::string result = postorderTraversal(node->left);
    result += postorderTraversal(node->right);
    result += std::to_string(node->data) + " ";

    return result;
}

void RedBlackTree::visualize()
{
    HWND console = GetConsoleWindow();
    ShowWindow(console, SW_MINIMIZE);
    
    closegraph();
    
    int gd = DETECT, gm;
    initwindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Visualizacion de Arbol Rojo-Negro", 
              (GetSystemMetrics(SM_CXSCREEN) - WINDOW_WIDTH) / 2,    // Centrar horizontalmente
              (GetSystemMetrics(SM_CYSCREEN) - WINDOW_HEIGHT) / 2);  // Centrar verticalmente
    
    cleardevice();
    setbkcolor(BLACK);
    cleardevice();
    
    if (root != nullptr)
    {
        int height = getHeight(root);
        calculateNodePosition(root, WINDOW_WIDTH/2, INITIAL_Y, 0, height);
    }
    else
    {
        setcolor(WHITE);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2, "Arbol vacio");
    }
    
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(10, WINDOW_HEIGHT - 30, "Presione cualquier tecla para volver al menu...");
    
    while (!kbhit())
    {
        delay(100);
    }
    getch();
    
    closegraph();
    ShowWindow(console, SW_RESTORE);
}

int RedBlackTree::getHeight(Node *node)
{
    if (node == nullptr)
        return 0;

    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    return std::max(leftHeight, rightHeight) + 1;
}