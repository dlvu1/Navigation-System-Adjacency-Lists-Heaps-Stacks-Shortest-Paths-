#ifndef HEAP_H
#define HEAP_H
#include "structures.h"

class MinHeap {
private:
    VERTEX** heapArray;
    int capacity;
    int heapSize;

public:
    MinHeap(int capacity);
    ~MinHeap();
    void buildHeap(VERTEX** vertices, int size);
    void minHeapify(int index);
    VERTEX* extractMin();
    void decreaseKey(VERTEX* index, float newKey);
    bool isEmpty() const;
};

#endif // HEAP_H

