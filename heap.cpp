#include "heap.h"
#include <iostream>
#include <algorithm>

// Constructor, initializes a minheap
MinHeap::MinHeap(int capacity) {
    this->capacity = capacity;
    this->heapSize = 0;
    this->heapArray = new VERTEX*[capacity];
}

// Destructor, free the memory allocated for the array
MinHeap::~MinHeap() {
    delete[] heapArray;
}

// Build the heap using an array of vertex
void MinHeap::buildHeap(VERTEX** vertices, int size) {
    if (size > capacity) { // Make sure the size does not exceed the capacity of the heap
        std::cerr << "Size exceeds heap capacity." << std::endl;
        return;
    }

    // Copy the vertex pointers into the array and set the size of the heap
    heapSize = size;
    for (int i = 0; i < size; ++i) {
        heapArray[i] = vertices[i];
    }

    // Convert the heap array into a valid minheap
    for (int i = (heapSize - 2) / 2; i >= 0; --i) {
        minHeapify(i);
    }
}

// Modify the minHeapify starting from a given index
void MinHeap::minHeapify(int index) {
    int smallest = index;
    int left = 2 * index + 1; // Left child 
    int right = 2 * index + 2; // Right child

    // Find the smallest node
    if (left < heapSize && heapArray[left]->key < heapArray[smallest]->key) {
        smallest = left;
    }

    if (right < heapSize && heapArray[right]->key < heapArray[smallest]->key) {
        smallest = right;
    }

    // if it is not a smallest, swap and continue executing minHeapify
    if (smallest != index) {
        std::swap(heapArray[index], heapArray[smallest]);
        minHeapify(smallest);
    }
}

// Extracts and return the min value from the heap array
VERTEX* MinHeap::extractMin() {
    // Return null if it is empty
    if (isEmpty()) {
        return nullptr;
    }
    
    // Set the root as the minimum value
    VERTEX* root = heapArray[0];
    // Replace the root with the last value and decrease the heap size
    heapArray[0] = heapArray[heapSize - 1];
    heapSize--;
    minHeapify(0);

    return root;
}

void MinHeap::decreaseKey(VERTEX* vertex, float newKey) {
    // Find the vertex in the heap
    int i = 0;
    for (; i < heapSize; ++i) {
        if (heapArray[i] == vertex) {
            break;
        }
    }
    if (i == heapSize) { // Vertex not found
        return;
    }

    heapArray[i]->key = newKey;
    while (i != 0 && heapArray[(i - 1) / 2]->key > heapArray[i]->key) {
        std::swap(heapArray[i], heapArray[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

bool MinHeap::isEmpty() const {
    return heapSize == 0;
}
