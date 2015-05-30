#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

class Heap{
    public:
        Heap(int size = 10):count(0), capacity(size), array(new int[size]){}
        ~Heap() { DestroyHeap(); }

        int Parent(int i){
            if(i<=0||i>=count)
                return -1;
            return (i-1/2);
        }

        int LeftChild(int i){
            int left = 2 * i + 1;
            if(left>=count)
                return -1;
            return left;
        }

        int RightChild(int i){
            int right = 2 * i + 2;
            if(right>=count)
                return -1;
            return right;
        }

        int GetMaximum(){
            if(count==0) 
                return -1;
            return array[0];
        }

        void PercolateDown(int i){
            int max;
            int l = LeftChild(i);
            int r = RightChild(i);
            if(l!=-1 && array[l] > array[i])
                max = l;
            else 
                max = i;
            if(r!=-1 && array[r] > array[max])
                max = r;
            if(max!=i){
                int tmp = array[i];
                array[i] = array[max];
                array[max] = tmp;
                PercolateDown(max);
            }
        }

        int DeleteMax(){
            if(count==0) 
                return -1;
            int data = array[0];
            array[0] = array[count-1];
            count--;
            PercolateDown(0);
            return data;
        }

        int Insert(int data){
            if(count==capacity) 
                ResizeHeap();
            int i = count;
            count++;
            while(i>0 && data > array[(i-1)/2]){
                array[i] = array[(i-1)/2];
                i = (i-1)/2;
            }
            array[i] = data;
        }

        void ResizeHeap(){
            int *array_old = array;
            array = new int[capacity*2];
            if(array==NULL) {
                cout << "Memory Error" << endl;
                return;
            }
            for(int i=0;i<capacity;++i)
                array[i] = array_old[i];
            capacity *= 2;
            delete array_old;
        }

        void BuildHeap(const vector<int>& A){
            int size = A.size();
            while(size > capacity)
                ResizeHeap();
            for(int i=0; i<size; ++i)
                array[i] = A[i];
            count = size;
            for(int i=(size-1)/2; i>=0; --i)
                PercolateDown(i);
        }
        
        void DestroyHeap(){
            delete array;
        }

        void Print(){
            for(int i=0;i<count;++i)
                cout << array[i] << " ";
            cout << endl;
        }

    // For HeapSort
    //private:
        int *array;
        int count;
        int capacity;
        int heap_type; // Min or Max
};

// Heap Sort
void HeapSort(const vector<int>& vec){
    vector<int> result;
    Heap h;
    h.BuildHeap(vec);
    int i, tmp;
    for(int i=vec.size()-1; i>0; --i){
        tmp = h.array[0];
        h.array[0] = h.array[h.count-1];
        h.array[h.count-1] = tmp;
        result.push_back(tmp);
        h.count--;
        h.PercolateDown(0);
    }

    result.push_back(h.array[0]);
    reverse(result.begin(), result.end());
    for(const int i:result)
        cout << i << " ";
    cout << endl;
}

int main(){

    vector<int> vec = {89,2,64,73,9,21};

    Heap h;
    h.BuildHeap(vec);
    h.Insert(236);
    h.Insert(96);
    h.Insert(44);
    h.DeleteMax();
    h.Insert(93);
    h.Print();

    HeapSort(vec);

    return 0;
}
