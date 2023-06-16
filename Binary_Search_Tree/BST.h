//
// Created by Berk Ozkan on 16.06.2023.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHMS_BST_H
#define DATA_STRUCTURES_AND_ALGORITHMS_BST_H

#include <iostream>
#include "BST_Node.h"

class BST {
public:
    //default constructors
    BST();
    BST(BST_Node* root);
    BST(BST_item_type item);
    //copy constructor & method
    BST(BST& other);
    void copy(BST_Node* newTree, BST_Node*& otherNode) const;
    //destructor
    ~BST();
    void destructor(BST_Node* node);
    //operations
    void insert(BST_item_type item);
    void remove(BST_item_type item);
    BST_Node* find(BST_item_type item);
    void display(BST_item_type* traversMethod (BST_Node*));
    void display();

    BST_item_type* preorder(BST_Node* node);
    BST_item_type* inorder(BST_Node* node);
    BST_item_type* postorder(BST_Node* node);
    bool is_in_tree(BST_item_type item);
private:
    BST_Node* root;
    int size;

    //operation helpers
    bool insert_execute(BST_Node*& node, BST_item_type item);
    bool remove_execute(BST_item_type item);
    void remove_node(BST_Node* node);
    void remove_two_children(BST_Node* node);
    BST_Node* inorder_successor(BST_Node* node);
    BST_Node* find_execute(BST_Node* node, BST_item_type item);

    void preorderTravers(BST_Node* node, BST_item_type* array, int index = 0);
    void inorderTravers(BST_Node* node, BST_item_type* array, int index = 0);
    void postorderTravers(BST_Node* node, BST_item_type* array, int index = 0);


};


#endif //DATA_STRUCTURES_AND_ALGORITHMS_BST_H
