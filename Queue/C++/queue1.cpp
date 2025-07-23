/*
    Queue Data Structure:

    A queue is a fundamental data structure that follows the First-In-First-Out (FIFO) principle. 
    Think of it like a line of people waiting - the first person to join the line is the first one to be served.
    

Important Terminologies:

1. Queue: A FIFO (First-In-First-Out) data structure
2. Enqueue: Operation to add an element to the back of queue
3. Dequeue: Operation to remove an element from the front of queue
4. Front/Head: First element in the queue
5. Rear/Tail: Last element in the queue
6. Deque: Double-ended queue allowing operations at both ends
7. Priority Queue: Queue where elements have priorities
8. Circular Queue: Fixed-size queue implemented circularly
   

Time Complexity Analysis;

Operation	Average Case	Worst Case
Enqueue	       O(1)	          O(1)
Dequeue	       O(1)	          O(1)
Peek	       O(1)	          O(1)
Search	       O(n)	          O(n)
isEmpty	       O(1)	          O(1)


Space Complexity:

Basic Queue: O(n) where n is number of elements
Circular Queue: O(n) where n is fixed size
Priority Queue: O(n) for binary heap implementation



Practice Problems by Difficulty::Leetcode

Easy:
Implement Queue using Stacks (LC #232)
Number of Recent Calls (LC #933)
First Unique Character in a String (LC #387)

Medium:
Design Circular Queue (LC #622)
Perfect Squares (LC #279)
Number of Islands (LC #200)
Rotting Oranges (LC #994)

Hard:
Sliding Window Maximum (LC #239)
Find Median from Data Stream (LC #295)
Maximum Performance of a Team (LC #1383)



Use Cases of Queue::

->CPU scheduling (Round Robin)
->Breadth-First Search (BFS) in graphs/trees
->IO Buffers, Printers
->Producer-Consumer problems
->Simulation systems


******************* Implementation *********************************/

// 1. Basic Queue Implementation
/****************************************/
#include <bits/stdc++.h>
using namespace std;
class Queue {
private:
    vector<int> items;

public:
    // Enqueue (insert at rear)
    void enqueue(int item) {
        items.push_back(item);
    }

    // Dequeue (remove from front)
    int dequeue() {
        if (!is_empty()) {
            int frontItem = items.front();
            items.erase(items.begin());  // costly: O(n)
            return frontItem;
        }
        throw out_of_range("Dequeue from empty queue");
    }

    // Get front element
    int front() const {
        if (!is_empty()) {
            return items.front();
        }
        throw out_of_range("Front from empty queue");
    }

    // Check if queue is empty
    bool is_empty() const {
        return items.empty();
    }

    // Get queue size
    int size() const {
        return items.size();
    }
};



// 2. Circular Queue Implementation
/************************************************
---A Circular Queue connects the end of the queue back to the front — like a circle — to efficiently use storage.

✅ Advantages:
-> Prevents memory wastage in fixed-size queues.
-> Efficient use of space compared to a linear queue where front keeps moving forward.
*/
#include <bits/stdc++.h>
using namespace std;

class CircularQueue {
private:
    vector<int> queue;
    int size;
    int front;
    int rear;

public:
    CircularQueue(int k) : size(k), queue(k), front(-1), rear(-1) {}

    // Enqueue element
    void enqueue(int item) {
        if (is_full()) {
            throw overflow_error("Queue is full");
        }

        if (front == -1) {
            front = 0;
        }
        rear = (rear + 1) % size;
        queue[rear] = item;
    }

    // Dequeue element
    int dequeue() {
        if (is_empty()) {
            throw underflow_error("Queue is empty");
        }
        int item = queue[front];
        if (front == rear) {
            // Only one element was present
            front = rear = -1;
        } else {
            front = (front + 1) % size;
        }
        return item;
    }

    // Check if queue is empty
    bool is_empty() const {
        return front == -1;
    }

    // Check if queue is full
    bool is_full() const {
        return (rear + 1) % size == front;
    }

    // Optional: Get front element
    int get_front() const {
        if (is_empty()) {
            throw underflow_error("Queue is empty");
        }
        return queue[front];
    }

    // Optional: Print queue
    void display() const {
        if (is_empty()) {
            cout << "Queue is empty\n";
            return;
        }
        cout << "Queue elements: ";
        int i = front;
        while (true) {
            cout << queue[i] << " ";
            if (i == rear) break;
            i = (i + 1) % size;
        }
        cout << "\n";
    }
};




// 3. Deque Implementation
/***************************************
A Deque (Double-Ended Queue) is a data structure where elements can be:
-> Added/removed from both ends — front and rear.
-> More flexible than a queue or stack.*/

#include <bits/stdc++.h>
using namespace std;
class Deque {
private:
    deque<int> items;

public:
    // Add element to the front
    void add_front(int item) {
        items.push_front(item);
    }

    // Add element to the rear
    void add_rear(int item) {
        items.push_back(item);
    }

    // Remove element from the front
    int remove_front() {
        if (is_empty()) throw out_of_range("Deque is empty");
        int val = items.front();
        items.pop_front();
        return val;
    }

    // Remove element from the rear
    int remove_rear() {
        if (is_empty()) throw out_of_range("Deque is empty");
        int val = items.back();
        items.pop_back();
        return val;
    }

    // Check if deque is empty
    bool is_empty() const {
        return items.empty();
    }

    // Optional: Get front and rear values
    int front() const {
        if (is_empty()) throw out_of_range("Deque is empty");
        return items.front();
    }

    int rear() const {
        if (is_empty()) throw out_of_range("Deque is empty");
        return items.back();
    }
};


