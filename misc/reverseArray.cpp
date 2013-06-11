#include <iostream>

using namespace std;

void reverseArray(int* A, int N){

   int* first = A, *last = A+N-1;
   while(first < last) 
      swap(*first++,*last--);
}

void reverseArrayV(int* A, int N){

   int first = 0, last = N-1;
   while(first<last)
      swap(A[first++],A[last--]);
}

int main()
{
   int A[] = { 1,2,3,4,5 };

   reverseArrayV(A,5);
   for(int i=0; i<5 ; i++)
      cout << A[i] << " ";

   return 0;
}

