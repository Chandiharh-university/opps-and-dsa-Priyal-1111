/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#define SIZE 100

class Queue {
private:
    int items[SIZE], front, rear;

public:
    Queue() {
        front = -1;
        rear = -1;
    }

    
    void enqueue(int element) {
        if (rear == SIZE - 1) {
            std::cout << "Queue is full\n";
            return;
        }
        if (front == -1) 
            front = 0;
        items[++rear] = element;
        std::cout << "Inserted: " << element << "\n";
    }

    
    void dequeue() {
        if (front == -1 || front > rear) {
            std::cout << "Queue is empty\n";
            return;
        }
        std::cout << "Removed: " << items[front++] << "\n";
        if (front > rear) 
            front = rear = -1;
    }

    
    void peek() {
        if (front == -1 || front > rear) {
            std::cout << "Queue is empty\n";
            return;
        }
        std::cout << "Front: " << items[front] << "\n";
    }

    
    bool isEmpty() {
        return (front == -1);
    }
};

int main() {
    Queue q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    q.peek();

    q.dequeue();
    q.dequeue();
    q.dequeue();

    q.dequeue(); 

    return 0;
}
