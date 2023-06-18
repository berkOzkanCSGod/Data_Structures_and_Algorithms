//
// Created by Berk Ozkan on 18.06.2023.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHMS_AVL_H
#define DATA_STRUCTURES_AND_ALGORITHMS_AVL_H

#include "../Binary_Search_Tree/BST.h"
typedef BST_item_type AVL_item_type;
typedef BST_Node AVL_Node;

class AVL {
public:
    //constructor
    //destructor
    //copy constructor
    AVL();
    AVL(AVL_item_type item);
    ~AVL();
    AVL(const AVL*& other);

    //insert
    //remove
    //display
    //find
    void insert(AVL_item_type item);
    void remove(AVL_item_type item);
    void display();
    AVL_Node* find(AVL_item_type item);

private:
    BST* tree;

    //retate L/R
    //balanced?
    //rebuild
    void rotateL(AVL_Node*& node);
    void rotateR(AVL_Node*& node);
    int subtreeHeight(AVL_Node*& node);
    int max(int a, int b);
    void rebuild(AVL_Node*& node, AVL_item_type);
};


#endif //DATA_STRUCTURES_AND_ALGORITHMS_AVL_H
