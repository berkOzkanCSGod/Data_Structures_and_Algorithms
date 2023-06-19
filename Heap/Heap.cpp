//
// Created by Berk Ozkan on 19.06.2023.
//

//
// Created by Berk Ozkan on 18.04.2023.
//
#include "Heap.h"

Heap::Heap() : size(0){

}

bool Heap::heapIsEmpty() const{
    return size == 0;
}
void Heap::heapInsert(const HeapItemType& newItem){
    if (this->size+1 <= MAX_HEAP){
        items[this->size] = newItem;

        //trickle up:
        int place = size;
        int parent = (place - 1)/2;
        while (place > 0 && items[place] > items[parent]) {
            HeapItemType temp = items[parent];
            items[parent] = items[place];
            items[place] = temp;

            place = parent;
            parent = (place - 1)/2;
        }


        this->size++;

    } else {
        std::cout << "Heap is full. \n";
    }
}

void Heap::heapDelete(HeapItemType& rootItem){
    rootItem = items[0];
    items[0] = items[this->size-1];
    items[this->size-1] = 0;
    this->size--;
    heapRebuild(0);
}

void Heap::heapRebuild(int root){
    int child = 2 * root + 1;
    if ( child < size ) {
        
        int rightChild = child + 1;
        if ((rightChild < size) && (items[rightChild] > items[child]))
            child = rightChild;

        // If root’s item is smaller than larger child, swap values
        if (items[root] < items[child]) {
            HeapItemType temp = items[root];
            items[root] = items[child];
            items[child] = temp;

            heapRebuild(child);
        }
    }
}

void Heap::print() const{
    for (int i = 0; i < size; i++) {
        std::cout << items[i] << " ";
    }
}

