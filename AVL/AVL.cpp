#include "AVL.h"

AVL::AVL(){
    tree = new BST();
}

AVL::AVL(AVL_item_type item){
    tree = new BST(item);
}

AVL::~AVL(){
    delete tree;
    tree = NULL;
}

AVL::AVL(const AVL*& other){
    BST* tree = new BST(other->tree);
}

void AVL::insert(AVL_item_type item){
    tree->insert(item);
    AVL_Node* root = tree->getRoot();
    rebuild(root, item);
}


void AVL::remove(AVL_item_type item){
    tree->remove(item);
}
void AVL::display(){
    tree->display(&BST::preorder);
}
AVL_Node* AVL::find(AVL_item_type item){
    return tree->find(item);
}

void AVL::rotateL(AVL_Node*& node){
    AVL_Node* Lsubtree = node->right;
    node->right = Lsubtree->left;
    Lsubtree->left = node;
    *node = *Lsubtree;
}
void AVL::rotateR(AVL_Node*& node){
    AVL_Node* Lsubtree = node->left;
    node->left = Lsubtree->right;
    Lsubtree->right = node;
    node = Lsubtree;
}
void AVL::rebuild(AVL_Node*& node, AVL_item_type item){
    static bool found = false;
    int difference;

    if (item < node->item){
        rebuild(node->left, item);
    } else if (item > node->item){
        rebuild(node->right, item);
    } else if (item == node->item){
        found = true;
    }

    if (found){
        difference = subtreeHeight(node->left) - subtreeHeight(node->right);

        if (difference == 0){
            return;
        } else if (difference < -1){
            rotateL(node);
        } else if (difference > 1){
            rotateR(node);
        }
    }

}

int AVL::subtreeHeight(AVL_Node*& treePtr) {
    if (treePtr == NULL)
        return 0;
    return max(subtreeHeight(treePtr->left), subtreeHeight(treePtr->right)) + 1;
}

int AVL::max(int a, int b){
    if (a >= b)
        return a;
    return b;
}