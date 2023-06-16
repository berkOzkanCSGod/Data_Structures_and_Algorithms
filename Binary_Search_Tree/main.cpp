
#include "BST.h"

int main(){

    BST* tree = new BST();
    tree->display();

    tree->insert(5);
    tree->insert(3);
    tree->insert(7);
    tree->insert(1);
    tree->insert(4);

//    tree->display();

    BST* otherTree(tree);

    tree->remove(5);
    tree->remove(3);
    tree->remove(7);
    tree->remove(1);
    tree->remove(4);

    //otherTree->display();

    return 0;
}
