#include<iostream>
#include<sstream>
#include<queue>
#include<deque>

using namespace std;

void onlineMedian(istringstream* sequence){
    priority_queue<int, vector<int>, greater<int>> min_heap;
    priority_queue<int, vector<int>, less<int>> max_heap;
    int x; 
    while(*sequence >> x){
        min_heap.emplace(x);
        if ( min_heap.size() > max_heap.size()){
            max_heap.emplace(min_heap.top());
            min_heap.pop();
        }
    }

    cout << (min_heap.size()==max_heap.size() ? 0.5*(min_heap.top()+max_heap.top()) : min_heap.top()) << endl; 
}

struct Compare{ 
    bool operator()(const pair<int,int>& lhs, const pair<int,int>& rhs){
        return lhs.first < rhs.first;
    }
};

// 11.10 Implement Stack using Heap
// P-19 Stack by Heap
class Stack {
    public: 
        // Use increasing Timestamp for LIFO
        void Push(int x) { max_heap_.emplace(timestamp_++, x); }

        int Pop() {
            int val = max_heap_.top().second;
            max_heap_.pop();
            return val;
        }

        const int& Peak() const { return max_heap_.top().second; } 

    private:
        int timestamp_ = 0;
        priority_queue<pair<int,int>, vector<pair<int,int>>, Compare> max_heap_;
};

// P-20 Queue by Heap
class Queue {
    public: 
        // Use decreasing Timestamp for FIFO
        void Push(int x) { max_heap_.emplace(timestamp_--, x); } 

        int Pop() {
            int val = max_heap_.top().second;
            max_heap_.pop();
            return val;
        }

        const int& Peak() const { return max_heap_.top().second; } 

    private:
        int timestamp_ = 0;
        priority_queue<pair<int,int>, vector<pair<int,int>>, Compare> max_heap_;
};

// P-28  Maximum Sliding Window
void MaxSlidingWindow(const vector<int>& vec, int w, vector<int>& output){
    deque<int> Q;
    for(int i=0;i<w;++i){
        // Check back smaller than new value
        // If new value is smaller, do nothing
        while(!Q.empty() && vec[i] >= vec[Q.back()])
            Q.pop_back();
        Q.push_back(i);
    }
    for(int i=w;i<vec.size();++i){
        output.push_back(vec[Q.front()]);
        // Check back smaller than new value
        // If new value is smaller, do nothing
        while(!Q.empty() && vec[i] >= vec[Q.back()])
            Q.pop_back();
        // Check front out of sliding window
        while(!Q.empty() && Q.front() <= i-w)
            Q.pop_front();
        Q.push_back(i);
    }
    output.push_back(vec[Q.front()]);
}

int main(){
   
    Stack s;
    s.Push(1);
    s.Push(2);
    s.Push(3);
    s.Push(4);
    cout << s.Pop() << endl;
    cout << s.Pop() << endl;
    cout << s.Pop() << endl;
    cout << s.Pop() << endl;
    
    Queue q;
    q.Push(1);
    q.Push(2);
    q.Push(3);
    q.Push(4);
    cout << q.Pop() << endl;
    cout << q.Pop() << endl;
    cout << q.Pop() << endl;
    cout << q.Pop() << endl;

    cout << "========================" << endl;
    vector<int> vec = {1,3,-1,-3,5,3,2,1,6,7};
    vector<int> result;
    MaxSlidingWindow(vec,3,result);
    for(const int a:result)
        cout << a << " ";
    cout << endl;

    return 0;
}
