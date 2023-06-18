
#include "BST.h"

//constructor
BST::BST() {
    root = NULL;
    size = 0;
}
BST::BST(BST_Node* root){
    this->root = root;
    size = 1;
}
BST::BST(BST_item_type item){
    if (root == NULL){
        this->root = new BST_Node(item);
        size = 1;
    } else {
        std::cout << "Could not add " << item << " to tree because root is full.\n";
    }
}
//copy consrtructor & method
BST::BST(const BST* other){
    if (other != NULL && other->root != NULL) {
        this->size = other->size;
//        this->root = new BST_Node(other->root->item);
        copy(root,other->root);
    }
}
void BST::copy(BST_Node*& newTree, const BST_Node* otherNode) {
    if (otherNode != NULL){
        newTree = new BST_Node(otherNode->item);
        copy(newTree->left, otherNode->left);
        copy(newTree->right, otherNode->right);
    } else {
        newTree = NULL;
    }
}
//destructor
BST::~BST(){
    destructor(this->root);
}
void BST::destructor(BST_Node* node){
    if (node != NULL){
        destructor(node->left);
        destructor(node->right);
        delete node;
    }
}
//operations
void BST::insert(BST_item_type item) {
    if (insert_execute(this->root, item)) {
        this->size++;
        std::cout << "Successfuly inserted " << item << ".\n";
    } else {
        std::cout << "Could not insert " << item << ".\n";
    }
}
void BST::remove(BST_item_type item) {
    if (remove_execute(item)) {
        this->size--;
        std::cout << "Successfuly removed " << item << ".\n";
    } else {
        std::cout << "Could not remove " << item << ".\n";
    }
}
BST_Node* BST::find(BST_item_type item) {
    BST_Node* newNode = NULL;
    find_execute(this->root, newNode,item);
    return newNode;
}
BST_item_type* BST::preorder(BST_Node* node){
    BST_item_type* array = new BST_item_type[this->size];
    preorderTravers(node, array);
    return array;
}
BST_item_type* BST::inorder(BST_Node* node){
    BST_item_type* array = new BST_item_type[this->size];
    inorderTravers(node, array);
    return array;

}
BST_item_type* BST::postorder(BST_Node* node){
    BST_item_type* array = new BST_item_type[this->size];
    postorderTravers(node, array);
    return array;
}
void BST::display(BST_item_type* (BST::*traversMethod)(BST_Node*)){
    globalIndex = 0;
    BST_item_type* array = (this->*traversMethod)(this->root);
            //traversMethod(this->root);
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << "\n";
    if (size > 0)
        delete [] array;
}
void BST::display(){

}
bool BST::is_in_tree(BST_item_type item){
    BST_item_type* array = inorder(this->root);
    for (int i = 0; i < size; ++i) {
        if (array[i] == item)
            return true;
    }
    return true;
}
//operation helpers
//insert
bool BST::insert_execute(BST_Node*& node, BST_item_type item){
    static bool inserted = false;
    if (node != NULL && item > node->item){
        insert_execute(node->right,item);
    } else if (node != NULL && item <= node->item){
        insert_execute(node->left,item);
    } else {
        node = new BST_Node(item);
        inserted = true;
    }
    return inserted;
}
//remove
bool BST::remove_execute(BST_item_type item){
    static bool removed = false;
    if (this->root != NULL){
        remove_node(this->root, item);
        removed = true;
    }
    return removed;
}
void BST::remove_node(BST_Node*& node, BST_item_type item) {
    if (node == NULL){
        return;
    }
    BST_Node* delPtr;
    BST_item_type replacementItem;
    if (size == 1){
        delete this->root;
        this->root = NULL;
        return;
    }

    if (item < node->item){
        remove_node(node->left, item);
    } else if (item > node->item) {
        remove_node(node->right, item);
    } else if (item == node->item) {
        if (node->left == NULL && node->right == NULL){
            delPtr = node;
            node = NULL;
            delete delPtr;
        } else if (node->left != NULL && node->right == NULL){
            delPtr = node;
            node = node->left;
            delPtr->left = NULL;
            if (node == this->root) {
                delPtr = this->root;
            }
            delete delPtr;
            delPtr = node;
        } else if (node->left == NULL && node->right != NULL){
            delPtr = node;
            node = node->right;
            delPtr->right = NULL;
            if (node == this->root) {
                delPtr = this->root;
            }
            delete delPtr;
            delPtr = node;
        } else if (node->left != NULL && node->right != NULL){
            inorder_successor(node->right,replacementItem);
            node->item = replacementItem;
        }
    }

}
void BST::remove_two_children(BST_Node*& node, BST_item_type& item){
    inorder_successor(node->right, item);
}
void BST::inorder_successor(BST_Node*& node, BST_item_type& item) {
    if (node->left == NULL) {
        item = node->item;
        BST_Node *delPtr = node;
        node = node->right;
        delPtr->right = NULL;
        delete delPtr;
    } else {
        inorder_successor(node->left, item);
    }
}
//find
BST_Node* BST::find_execute(BST_Node*& node, BST_Node*& newNode, BST_item_type item) {
    if (node == NULL) {
        newNode = NULL;
    } else if (item > node->item){
        find_execute(node->right,newNode,item);
    } else if (item < node->item){
        find_execute(node->left,newNode,item);
    } else if(item == node->item) {
        newNode = node;
    }
}
//traversal
void BST::preorderTravers(BST_Node* node, BST_item_type* array){
    if (node != NULL){
        array[globalIndex] = node->item;
        globalIndex++;
        preorderTravers(node->left, array);
        preorderTravers(node->right, array);
    }
}
void BST::inorderTravers(BST_Node* node, BST_item_type* array){
    if (node != NULL){
        inorderTravers(node->left, array);
        array[globalIndex] = node->item;
        globalIndex++;
        inorderTravers(node->right, array);
    }
}
void BST::postorderTravers(BST_Node* node, BST_item_type* array){
    if (node != NULL){
        postorderTravers(node->left, array);
        postorderTravers(node->right, array);
        array[globalIndex] = node->item;
        globalIndex++;
    }
}