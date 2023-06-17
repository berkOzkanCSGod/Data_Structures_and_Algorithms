
#include "BST.h"

int main() {

    BST* tree = new BST();
    tree->insert(5);
    tree->insert(2);
    tree->insert(4);
    tree->insert(6);

    delete tree;

    return 0;
}

