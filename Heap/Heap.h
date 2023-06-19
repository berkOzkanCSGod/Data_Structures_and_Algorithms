//
// Created by Berk Ozkan on 19.06.2023.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHMS_HEAP_H
#define DATA_STRUCTURES_AND_ALGORITHMS_HEAP_H

#include <string>
#include <iostream>

const int MAX_HEAP = 10;
typedef int HeapItemType;

class Heap {
private:
    HeapItemType items[MAX_HEAP];	// array of heap items
    int          size;            	// number of heap items
public:
    Heap();				// default constructor
    // copy constructor and destructor are supplied by the compiler

    bool heapIsEmpty() const;
    void heapInsert(const HeapItemType& newItem);
    void heapDelete(HeapItemType& rootItem);
    void print() const;
    int getSize() const {return size;}

protected:
    void heapRebuild(int root);		// Converts the semiheap rooted at index root into a heap

};



#endif //DATA_STRUCTURES_AND_ALGORITHMS_HEAP_H
