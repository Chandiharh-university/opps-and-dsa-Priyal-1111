#include <iostream>
#define MAX 1000 // Define the maximum size of the stack

class Stack {
private:
    int top;             // Index of the top element
    int arr[MAX];        // Array to store stack elements

public:
    Stack() { top = -1; } // Constructor initializes top to -1

    // Method to push an element onto the stack
    bool push(int value) {
        if (top >= (MAX - 1)) {
            std::cout << "Stack Overflow\n";
            return false;
        } else {
            arr[++top] = value;
            std::cout << value << " pushed onto the stack\n";
            return true;
        }
    }

    // Method to pop an element from the stack
    int pop() {
        if (top < 0) {
            std::cout << "Stack Underflow\n";
            return 0;
        } else {
            int value = arr[top--];
            return value;
        }
    }

    // Method to peek at the top element of the stack
    int peek() {
        if (top < 0) {
            std::cout << "Stack is Empty\n";
            return 0;
        } else {
            return arr[top];
        }
    }

    // Method to check if the stack is empty
    bool isEmpty() {
        return (top < 0);
    }
};

int main() {
    Stack stack;

    stack.push(10);
    stack.push(20);
    stack.push(30);

    std::cout << stack.pop() << " popped from the stack\n";

    std::cout << "Top element is: " << stack.peek() << "\n";

    std::cout << "Stack is " << (stack.isEmpty() ? "empty" : "not empty") << "\n";

    return 0;
}
