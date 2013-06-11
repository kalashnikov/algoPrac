
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std;

typedef vector<int>  vi;
typedef vector<vi>  vvi;
#define all(c) (c).begin(), (c).end()
#define tr(c,x) for(typeof(c).begin() x=(c).begin();x!=(c).end();x++)

const int NUM=100;

int part(int v[], int lo, int hi){
   int pivot = v[(lo+hi)/2]; // Pivot is value!!

   while(lo<=hi){
      while( v[lo] < pivot ) lo++;
      while( pivot < v[hi] ) hi--;
      if(lo<=hi){
         swap(v[lo++],v[hi--]);
      }
   }

   return lo; // Important!!!
}

void qSort(int v[], int lo, int hi){

   int index = part(v,lo,hi); // Once!!

   if(lo<index-1)
      qSort(v,lo,index-1);

   if(index<hi)
      qSort(v,index,hi);

   return;
}

int main(){

   srand(time(0));
   int array[NUM];

   for(int i=0;i<NUM;i++) array[i]=rand()%100;

   qSort(array,0,NUM-1);

   for(int i=0;i<NUM;i++) cout << array[i] << " ";
   cout << endl;

   return 0;
}
