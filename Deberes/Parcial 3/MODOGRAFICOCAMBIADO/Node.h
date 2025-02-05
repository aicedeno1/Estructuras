#ifndef NODE_H
#define NODE_H

struct Node
{
    int data;
    bool isRed;
    Node *left, *right, *parent;

    Node(int data)
    {
        this->data = data;
        isRed = true;
        left = right = parent = nullptr;
    }
};

#endif // NODE_H