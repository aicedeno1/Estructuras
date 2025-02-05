#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include "Node.h"
#include <string>
#include <windows.h>

class RedBlackTree {
private:
    Node *root;
    const int RADIUS = 15;
    const int VERTICAL_SPACING = 40;
    const int WINDOW_WIDTH = 800;         // Ancho fijo más pequeño
    const int WINDOW_HEIGHT = 600;        // Alto fijo más pequeño
    const int INITIAL_Y = 30; 

    void rotateLeft(Node *&root, Node *&pt);
    void rotateRight(Node *&root, Node *&pt);
    void fixViolation(Node *&root, Node *&pt);
    int getHeight(Node *node);
    void calculateNodePosition(Node* node, int x, int y, int level, int maxLevel);
    std::string preorderTraversal(Node* node);
    std::string inorderTraversal(Node* node);
    std::string postorderTraversal(Node* node);

public:
    RedBlackTree();
    void insert(int data);
    void visualize();
    void preorder();
    void inorder();
    void postorder();
};
#endif