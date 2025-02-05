#ifndef HASHNODE_H
#define HASHNODE_H

#include <string>

struct HashNode {
    std::string data;
    HashNode *next;

    HashNode(std::string value) {
        data = value;
        next = nullptr;
    }
};

#endif