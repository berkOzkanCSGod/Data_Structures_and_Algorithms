
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
BST::BST(BST& other){
    if (other.root != NULL) {
        this->size = other.size;
        this->root = new BST_Node(other.root->item);
        copy(root,other.root);
    }
}
void BST::copy(BST_Node *newTree, BST_Node*& otherNode) const{
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
    return find_execute(this->root, item);
}
BST_item_type* BST::preorder(BST_Node* node){
    BST_item_type* array = new BST_item_type[size];
    preorderTravers(node, array);
}
BST_item_type* BST::inorder(BST_Node* node){
    BST_item_type* array = new BST_item_type[size];
    inorderTravers(node, array);
}
BST_item_type* BST::postorder(BST_Node* node){
    BST_item_type* array = new BST_item_type[size];
    postorderTravers(node, array);
}
void BST::display(BST_item_type* traversMethod (BST_Node*)){
    BST_item_type* array = traversMethod(this->root);
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << "\n";
    if (size > 0)
        delete [] array;
}
void BST::display(){
    BST_item_type* array;
    preorder(this->root);
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << "\n";
    if (size > 0)
        delete [] array;
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
    if (node != NULL && item > node->item){
        insert_execute(node->right,item);
    } else if (node != NULL && item <= node->item){
        insert_execute(node->left,item);
    } else {
        node = new BST_Node(item);
        return true;
    }
    return false;
}
//remove
bool BST::remove_execute(BST_item_type item){
    BST_Node* node = find(item);
    if (node != NULL){
        remove_node(node);
        return true;
    }
    return false;
}
void BST::remove_node(BST_Node *node) {
    //cheking leaf
    if (node->right == NULL && node->left == NULL)
        delete node;

    //checking single parent
    if (node->right != NULL){
        if (node->left != NULL){
            remove_two_children(node);
        } else {
            node->item = node->right->item;            //copy right
            delete node->right;            //delete right
        }
    }
    if (node->left != NULL){
        if (node->right != NULL){
            remove_two_children(node);
        } else {
            node->item = node->left->item;            //copy left
            delete node->left;            //delete left
        }
    }

}
void BST::remove_two_children(BST_Node* node){
    BST_Node* inorderSuccessor = inorder_successor(node->right);
    node->item = inorderSuccessor->item;
    delete inorderSuccessor;
}
BST_Node* BST::inorder_successor(BST_Node* node){
    if (node != NULL && node->left != NULL)
        inorder_successor(node->left);
    return node;
}
//find
BST_Node* BST::find_execute(BST_Node* node, BST_item_type item) {
    if (node == NULL)
        return NULL;
    if (item > node->item){
        insert_execute(node->right,item);
    } else if (item < node->item){
        insert_execute(node->left,item);
    } else if(item == node->item) {
        return node;
    }
    return NULL;
}
//traversal
void BST::preorderTravers(BST_Node* node, BST_item_type* array, int index){
    if (node != NULL){
        array[index] = node->item;
        index++;
        preorderTravers(node->left, array, index);
        preorderTravers(node->right, array, index);
    }
}
void BST::inorderTravers(BST_Node* node, BST_item_type* array, int index){
    if (node != NULL){
        inorderTravers(node->left, array, index);
        array[index] = node->item;
        index++;
        inorderTravers(node->right, array, index);
    }
}
void BST::postorderTravers(BST_Node* node, BST_item_type* array, int index){
    if (node != NULL){
        postorderTravers(node->left, array, index);
        postorderTravers(node->right, array, index);
        array[index] = node->item;
        index++;
    }
}