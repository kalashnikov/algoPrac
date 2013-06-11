
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

typedef vector<int>  vi;
typedef vector<vi>  vvi;
#define all(c) (c).begin(), (c).end()
#define tr(c,x) for(typeof(c).begin() x=(c).begin();x!=(c).end();x++)

class Heap{

   public:
      Heap():num(0){}
      vi vec;
      int num;

      int top(){
         return vec[0];
      }

      int pop(){
         vec[0]=vec[num-1];
         vec.erase(vec.end()-1);
         num--;
         int count = 0;
         while((2*count+1)<num && (
                vec[count]<vec[2*count+1] ||
                vec[count]<vec[2*count+2] )){

            if ( vec[count]<vec[2*count+1] && 
                 vec[2*count+1] > vec[2*count+2] ) {
               swap(vec[count],vec[2*count+1]);
               count=2*count+1;
            } else if ( vec[count]<vec[2*count+2]) {
               swap(vec[count],vec[2*count+2]);
               count=2*count+2;
            }
         }
      }

      void insert(int i){ 
         vec.push_back(i);
         num++;
         maxheapify();
      }

      // Reverse Check ( one-time check & bubble up to ROOT(Max steps) )
      void maxheapify(){
         int count = num-1;
         while( count>0&&vec[count]>vec[(count-1)/2] ){
            swap(vec[count],vec[(count-1)/2]);
            count=(count-1)/2;
         }
      }

      void traverse(){
         cout << "Heap: ";
         tr(vec, it)
           cout << *it << " ";
         cout << endl;
      }
};

int main(){

   Heap heap;
   heap.insert(1);
   heap.insert(2);
   heap.insert(3);
   heap.insert(4);
   heap.insert(5);
   heap.insert(6);
   heap.insert(7);
   heap.insert(8);
   heap.insert(9);
   heap.insert(10);
   heap.insert(11);
   heap.insert(12);
   heap.insert(13);

   heap.traverse();
   heap.pop();
   heap.traverse();
   return 0;
}
