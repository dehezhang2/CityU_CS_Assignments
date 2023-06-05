#include <iostream>
#include "Queue.h"
using namespace std;

int main() {
    Queue<int> q;
    int n;
    while(cin >> n) {
        for(int i = 0; i < n; i++) {
            q.push(i);
            if(q.full()) {
                cout << "queue is full\n";
                break;
            }
        }
        cout << "size: " << q.size() << endl;
        while(1){
            if(q.empty()){
                cout << "queue is empty\n";
                break;
            }
            cout << q.front() << endl;
            q.pop();
        }
        cout << "size: " << q.size() << endl;
    }
    return 0;
}
