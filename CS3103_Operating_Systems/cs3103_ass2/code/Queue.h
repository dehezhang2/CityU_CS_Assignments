#ifndef QUEUE_H
#include <stdio.h>
#define QUEUE_H

// actually max number is 50
#define MAX_SIZE 51
// use template queue
template <class T>
class Queue {
private:
    int head, tail, len;
    T content[MAX_SIZE];
public:
    Queue(){head = tail = 0;}
    
    // return 0 if push failed
    bool push(const T& item) {
        if(!full()) {
            content[tail] = item;
            tail = (tail + 1) % MAX_SIZE;
            len++;
            return 1;
        }
        return 0;
    }

    // return 0 if pop failed
    bool pop() {
        if(!empty()) {
            head = (head + 1) % MAX_SIZE;
            len--;
            return 1;
        }
        return 0;
    }

    const T& front() {
        return empty() ? (const T&)NULL : content[head];
    }

    bool empty() {
        return head == tail;
    }

    bool full() {
        return (tail + 1) % MAX_SIZE == head;
    }

    int size() {
        return len;
    }

    int clear() {
        head = tail = 0;
        len = 0;
    }
};
#endif
