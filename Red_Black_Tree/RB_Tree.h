//
// Created by Berk Ozkan on 19.06.2023.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHMS_RB_TREE_H
#define DATA_STRUCTURES_AND_ALGORITHMS_RB_TREE_H

#include "../Binary_Search_Tree/BST.h"

typedef BST_item_type RB_item_type;
typedef BST_Node RB_Node;

class RB_Tree {
public:
    RB_Tree();
    RB_Tree(RB_item_type item);
    RB_Tree(const RB_Tree& other); //copy
    ~RB_Tree();

    void insert(RB_item_type item);
    void remove(RB_item_type item);
    void display();
    RB_Node* find(RB_item_type item);



private:
    BST* tree;

    void recolorAdded(RB_Node*& node, RB_Node*& addedNode);
    RB_Node* findGrandParent(RB_Node* grandParent, RB_Node* node);
    RB_Node* findUncle(RB_Node* node);
    RB_Node* findParent(RB_Node* parent, RB_Node* node);
    void findParent(RB_Node* parent, RB_Node* node, RB_Node*& newParent);
    void findUncle(RB_Node* node, RB_Node*& newParent);
    void findGrandParent(RB_Node* grandParent, RB_Node* node,  RB_Node*& newParent);

    void rotateL(RB_Node*& node);
    void rotateR(RB_Node*& node);
    void rotateRL(RB_Node* &treePtr);
    void rotateLR(RB_Node* &treePtr);

    bool isLL(RB_Node* node);
    bool isRR(RB_Node* node);
    bool isLR(RB_Node* node);
    bool isRL(RB_Node* node);

};


#endif //DATA_STRUCTURES_AND_ALGORITHMS_RB_TREE_H
