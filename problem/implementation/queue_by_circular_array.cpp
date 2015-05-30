#include <iostream>

using namespace std;

class ArrayQueue{
    public:
        ArrayQueue(int size = 10):front(-1), rear(-1), capacity(size), array(new int[size]){}

        bool IsEmptyQueue(){ 
            return (front == -1);
        }

        bool IsFullQueue(){
            return ((rear + 1) % capacity == front);
        }

        int QueueSize(){
            return (capacity - front + rear + 1) % capacity;
        }

        int EnQueue(int data){
            if(IsFullQueue()) 
                cout << "Queue Overflow" << endl;
            else { 
                rear = (rear + 1) % capacity; 
                array[rear] = data;
                if(front == -1) 
                    front = rear;
            }
        }

        int DeQueue(){
            int data = 0;
            if(IsEmptyQueue()){
                cout << "Queue is Empty" << endl;
                return 0;
            } else {
                data = array[front];
                if(front == rear)
                    front = rear = -1;
                else front = (front+1) % capacity;
            }
            return data; 
        }

        void DeleteQueue(){
            if (array) delete array;
        }

    private:
        int front, rear;
        int capacity;
        int *array;
};

int main(){
    ArrayQueue aq(5);

    aq.EnQueue(5);
    aq.EnQueue(2);
    aq.EnQueue(9);
    aq.EnQueue(7);
    aq.EnQueue(4);
    
    aq.EnQueue(0); // Overflow

    cout << aq.IsFullQueue() << endl;

    cout << aq.DeQueue() << endl;
    cout << aq.DeQueue() << endl;
    cout << aq.DeQueue() << endl;
    cout << aq.DeQueue() << endl;
    cout << aq.DeQueue() << endl;

    cout << aq.IsEmptyQueue() << endl;

    return 0;
}
