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
    AVL_Node* root = tree->getRoot();
    findImbalance(root);
}
void AVL::findImbalance(AVL_Node* node){
    int difference = 0;
    if (node != NULL){
        difference = subtreeHeight(node->left) - subtreeHeight(node->right);

        if (difference == 0){
            return;
        } else if (isLRCase(node)){
            rotateRL(node);
        } else if (isRLCase(node)){
            rotateLR(node);
        } else if (difference < -1){
            rotateL(node);
        } else if (difference > 1){
            rotateR(node);
        }

        findImbalance(node->left);
        findImbalance(node->right);
    }
}
void AVL::display(){
    tree->display(&BST::preorder);
}
AVL_Node* AVL::find(AVL_item_type item){
    return tree->find(item);
}

void AVL::rotateL(AVL_Node*& node){
    AVL_Node* Rsubtree = node->right;
    node->right = Rsubtree->left;
    Rsubtree->left = node;
    if (node == this->tree->getRoot()) {
        this->tree->setRoot(Rsubtree);
    }
    node = Rsubtree;
}
void AVL::rotateR(AVL_Node*& node){
    AVL_Node* Lsubtree = node->left;
    node->left = Lsubtree->right;
    Lsubtree->right = node;
    if (node == this->tree->getRoot()) {
        this->tree->setRoot(Lsubtree);
    }
    node = Lsubtree;
}
void AVL::rotateRL(AVL_Node* &treePtr){
    rotateL(treePtr->left);
    rotateR(treePtr);
}
void AVL::rotateLR(AVL_Node* &treePtr){
    rotateR(treePtr->right);
    rotateL(treePtr);
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
        } else if (isLRCase(node)){
            rotateRL(node);
        } else if (isRLCase(node)){
            rotateLR(node);
        } else if (difference < -1){
            rotateL(node);
        } else if (difference > 1){
            rotateR(node);
        }
    }

}

bool AVL::isRLCase(AVL_Node* node) {
    if (node != NULL){
        if (node->right != NULL){
            if (node->right->left != NULL){
                int LL = subtreeHeight(node->right->left->left);
                int LR = subtreeHeight(node->right->left->right);
                if (LL >= LR){
                    return true;
                }
            }
        }
    }
    return false;
}
bool AVL::isLRCase(AVL_Node* node) {
    if (node != NULL){
        if (node->left != NULL){
            if (node->left->right != NULL){
                int RL = subtreeHeight(node->left->right->left);
                int RR = subtreeHeight(node->left->right->right);
                if (RL >= RR){
                    return true;
                }
            }
        }
    }
    return false;
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