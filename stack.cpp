#include "stack.h"
#include <iostream>

// Constructor, initializes a stack 
Stack::Stack(int capacity) {
    this->capacity = capacity;
    this->top = -1; // Since stack is empty, top should be -1
    this->stackArray = new VERTEX*[capacity]; // Allocate memory for the stack
}

// Destructor, free the memory allocated
Stack::~Stack() {
    delete[] stackArray;
}

// Push a vertex onto the stack
void Stack::push(VERTEX* vertex) {
    if (top == capacity - 1) { // Check for stack overflow
        std::cerr << "Stack Overflow" << std::endl;
        return;
    }
    stackArray[++top] = vertex; // Increment top and add the vertex to the stack
}

// Pop and returns the top vertex
VERTEX* Stack::pop() {
    if (isEmpty()) {
        std::cerr << "Stack Underflow" << std::endl;
        return nullptr;
    }
    return stackArray[top--]; // Return the top vertex and delete the top
}

bool Stack::isEmpty() const {
    return top == -1; // Empty if stack is -1
}
