#ifndef STACK_H
#define STACK_H
#include "structures.h"

class Stack {
private:
    VERTEX** stackArray;
    int capacity;
    int top;

public:
    Stack(int capacity);
    ~Stack();
    void push(VERTEX* vertex);
    VERTEX* pop();
    bool isEmpty() const;
    
    // Method to get the top element without removing it
    VERTEX* peek() const {
        if (isEmpty()) {
            return nullptr;
        }
        return stackArray[top];
    }
};

#endif // STACK_H