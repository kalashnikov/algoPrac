#include<iostream>
#include<stack>

using namespace std;

// Implement Queue by Stack
class Queue{
    public: 
        void Enqueue(int x) { A_.emplace(x); }
        int Dequeue(){
            if (B_.empty()){
                while(!A_.empty()){
                    B_.emplace(A_.top());
                    A_.pop();
                }
            }

            if (B_.empty()) {
                 //throw length_error("empty queue"); 
            }

            int ret = B_.top();
            B_.pop();
            return ret;
        }
    private:
        stack<int> A_, B_;
};

int main(){

    Queue q;
    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);
    q.Enqueue(4);
    cout << q.Dequeue() << endl;
    cout << q.Dequeue() << endl;
    cout << q.Dequeue() << endl;
    cout << q.Dequeue() << endl;

    return 0;
}
