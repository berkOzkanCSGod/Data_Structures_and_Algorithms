#ifndef DATA_STRUCTURES_AND_ALGORITHMS_BST_NODE_H
#define DATA_STRUCTURES_AND_ALGORITHMS_BST_NODE_H

typedef int BST_item_type;

enum Color {RED, BLACK};

struct BST_Node {

    BST_Node() {}
    BST_Node(BST_item_type item): item(item), left(NULL), right(NULL) {}
    BST_item_type item;
    BST_Node* left;
    BST_Node* right;
    Color color;
};


#endif //DATA_STRUCTURES_AND_ALGORITHMS_BST_NODE_H
