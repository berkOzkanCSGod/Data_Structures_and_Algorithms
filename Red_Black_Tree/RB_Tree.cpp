//
// Created by Berk Ozkan on 19.06.2023.
//

#include "RB_Tree.h"

RB_Tree::RB_Tree() {
    tree = new BST();
}

RB_Tree::RB_Tree(RB_item_type item) {
    tree = new BST(item);
}

RB_Tree::RB_Tree(const RB_Tree& other){
    this->tree = new BST(other.tree);
}

RB_Tree::~RB_Tree(){
    delete tree;
}

void RB_Tree::insert(RB_item_type item){
    this->tree->insert(item);
    RB_Node* node = find(item);
    if (node != NULL)
        node->color = RED;
    recolorAdded(this->tree->root, node);
}
void RB_Tree::remove(RB_item_type item){
    this->tree->remove(item);
}
void RB_Tree::display(){
    this->tree->display();
}
RB_Node* RB_Tree::find(RB_item_type item){
    return this->tree->find(item);
}

void RB_Tree::recolorAdded(RB_Node*& node, RB_Node*& addedNode){
    if (node == NULL){
        return;
    }
    //find
    if (addedNode->item < node->item){
        recolorAdded(node->left, addedNode);
    } else if (addedNode->item > node->item){
        recolorAdded(node->right, addedNode);
    } else {
        RB_Node* grandParent = NULL;
        findGrandParent(tree->root, addedNode, grandParent);
        RB_Node* uncle = NULL;
        findUncle(addedNode, uncle);
        RB_Node* parent = NULL;
        findParent(tree->root, addedNode, parent);

        if (addedNode == tree->root){
            addedNode->color = BLACK;
        } else if (parent->color == RED && uncle != NULL && uncle->color == RED) {
            RB_Node* uncle2 = NULL;
            RB_Node* parent2 = NULL;
            RB_Node* grandParent2 = NULL;
            findUncle(addedNode, uncle2);
            findParent(tree->root, addedNode, parent2);
            findGrandParent(tree->root, addedNode, grandParent2);
            do{
                findUncle(addedNode, uncle2);
                findParent(tree->root, addedNode, parent2);
                parent2->color = BLACK;
                uncle2->color = BLACK;
                grandParent2->color = RED;
                addedNode = grandParent;
                findGrandParent(tree->root, addedNode, grandParent2);
            } while (parent2->color == RED && uncle2 != NULL && uncle2->color == RED);
            if (addedNode == tree->root){
                addedNode->color = BLACK;
            }
        } else if (parent->color == RED && (uncle == NULL || uncle->color == BLACK)){
                if (isLL(addedNode)){
                    rotateR(parent);
                } else if (isRR(addedNode)){
                    rotateL(grandParent);
                } else if (isLR(addedNode)){
                    rotateR(addedNode);
                    rotateL(parent);
                } else if (isRL(addedNode)){
                    rotateL(addedNode);
                    rotateR(parent);
                }
        }

        //case 1: if node == root
            // node->color = BLACK;
        //case 2: while (parent & uncle == RED)
            // parent & uncle = BLACK;
            // grandParent = RED;
            //x = grandParent;
        //case 3:
            //parent = red & uncle = black & x is left and parent is left
            // rotate on parent to right
        //case 4:
            //parent = red & uncle = black & x is left and parent is right
            //rotate on x right, on parent left
    }
}


void RB_Tree::rotateL(RB_Node*& node){
    RB_Node* Rsubtree = node->right;
    node->right = Rsubtree->left;
    Rsubtree->left = node;
    if (node == this->tree->getRoot()) {
        this->tree->setRoot(Rsubtree);
    }
    node = Rsubtree;
}
void RB_Tree::rotateR(RB_Node*& node){
    RB_Node* Lsubtree = node->left;
    node->left = Lsubtree->right;
    Lsubtree->right = node;
    if (node == this->tree->getRoot()) {
        this->tree->setRoot(Lsubtree);
    }
    node = Lsubtree;
}
void RB_Tree::rotateRL(RB_Node* &treePtr){
    rotateL(treePtr->left);
    rotateR(treePtr);
}
void RB_Tree::rotateLR(RB_Node* &treePtr){
    rotateR(treePtr->right);
    rotateL(treePtr);
}

bool RB_Tree::isLL(RB_Node* node){
    RB_Node* grandParent;
    findGrandParent(tree->root, node, grandParent);
    if (grandParent == NULL)
        return false;
    if (grandParent->left == NULL)
        return false;
    if (grandParent->left->left == NULL)
        return false;
    if (grandParent->left->left == node)
        return true;
    return false;
}
bool RB_Tree::isRR(RB_Node* node){
    RB_Node* grandParent;
    findGrandParent(tree->root, node, grandParent);
    if (grandParent == NULL)
        return false;
    if (grandParent->right == NULL)
        return false;
    if (grandParent->right->right == NULL)
        return false;
    if (grandParent->right->right == node)
        return true;
    return false;
}
bool RB_Tree::isLR(RB_Node* node){
    RB_Node* grandParent;
    findGrandParent(tree->root, node, grandParent);
    if (grandParent == NULL)
        return false;
    if (grandParent->left == NULL)
        return false;
    if (grandParent->left->right == NULL)
        return false;
    if (grandParent->left->right == node)
        return true;
    return false;
}
bool RB_Tree::isRL(RB_Node* node){
    RB_Node* grandParent;
    findGrandParent(tree->root, node, grandParent);
    if (grandParent == NULL)
        return false;
    if (grandParent->right == NULL)
        return false;
    if (grandParent->right->left == NULL)
        return false;
    if (grandParent->right->left == node)
        return true;
    return false;
}

RB_Node* RB_Tree::findGrandParent(RB_Node* grandParent, RB_Node* node){
    if (grandParent != NULL){
        if (grandParent->left != NULL){
            if (grandParent->left->left != NULL) {
                if (grandParent->left->left == node) {
                    return grandParent;
                }
            }
            if (grandParent->left->right != NULL) {
                if (grandParent->left->right == node) {
                    return grandParent;
                }
            }
        }
        if (grandParent->right != NULL){
            if (grandParent->right->left != NULL) {
                if (grandParent->right->left == node) {
                    return grandParent;
                }
            }
            if (grandParent->right->right != NULL) {
                if (grandParent->right->right == node) {
                    return grandParent;
                }
            }
        } else {
            return NULL;
        }

        if (node->item < grandParent->item){
            findGrandParent(grandParent->left, node);
        } else if (node->item > grandParent->item){
            findGrandParent(grandParent->right, node);
        }
    }
    return NULL;
}
RB_Node* RB_Tree::findUncle(RB_Node *node) {
    RB_Node* grandParent = findGrandParent(tree->root, node);
    RB_Node* parent;
    findParent(tree->root,node, parent);
    if (grandParent != NULL) {
        if (grandParent->left != NULL && grandParent->left == parent){
            return grandParent->right;
        } else if (grandParent->right != NULL && grandParent->right == parent){
            return grandParent->left;
        }
    }
}
RB_Node* RB_Tree::findParent(RB_Node* parent, RB_Node *node) {
    if (parent != NULL && node != NULL){

        if (parent->left != NULL && (parent->left == node)){
            return parent;
        } else if (parent->right != NULL && parent->right == node) {
            return parent;
        }

        if (node->item < parent->item){
            findParent(parent->left, node);
        } else if (node->item > parent->item){
            findParent(parent->right, node);
        }

    } else {
        return NULL;
    }
}

void RB_Tree::findParent(RB_Node* parent, RB_Node *node, RB_Node*& newParent) {
    if (parent != NULL && node != NULL){

        if (parent->left != NULL && (parent->left == node)){
            newParent = parent;
        } else if (parent->right != NULL && parent->right == node) {
            newParent = parent;
        }

        if (node->item < parent->item){
            findParent(parent->left, node, newParent);
        } else if (node->item > parent->item){
            findParent(parent->right, node, newParent);
        }

    } else {
        newParent = NULL;
    }
}
void RB_Tree::findUncle(RB_Node* node, RB_Node*& newParent){
    RB_Node* grandParent;
    findGrandParent(tree->root, node, grandParent);
    RB_Node* parent;
    findParent(tree->root, node, parent);
    if (grandParent != NULL) {
        if (grandParent->left != NULL && grandParent->left == parent){
            newParent = grandParent->right;
        } else if (grandParent->right != NULL && grandParent->right == parent){
            newParent = grandParent->left;
        }
    }
}
void RB_Tree::findGrandParent(RB_Node* grandParent, RB_Node* node,  RB_Node*& newParent){
    if (grandParent != NULL){
        if (grandParent->left != NULL){
            if (grandParent->left->left != NULL) {
                if (grandParent->left->left == node) {
                    newParent = grandParent;
                }
            }
            if (grandParent->left->right != NULL) {
                if (grandParent->left->right == node) {
                    newParent = grandParent;
                }
            }
        }
        if (grandParent->right != NULL){
            if (grandParent->right->left != NULL) {
                if (grandParent->right->left == node) {
                    newParent = grandParent;
                }
            }
            if (grandParent->right->right != NULL) {
                if (grandParent->right->right == node) {
                    newParent = grandParent;
                }
            }
        }

        if (node->item < grandParent->item){
            findGrandParent(grandParent->left, node,newParent);
        } else if (node->item > grandParent->item){
            findGrandParent(grandParent->right, node,newParent);
        }
    }
}