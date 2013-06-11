
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;
#define all(c) (c).begin(), (c).end()
#define tr(c,x) for(typeof(c).begin() x=(c).begin();x!=(c).end();x++)

const bool debug = true;

// 
// Memorize!
//
int partition( vi& vec, int lo, int hi) { 

   int pivot = vec[(lo+hi)/2]; 

   if ( debug ) cout << "L,H  : " << lo << " " << hi << endl; 
   if ( debug ) cout << "PIVOT: " << pivot << " (" << ((lo+hi)/2) << ")" << endl; 

   // 
   // lo==hi will make one time self-swap
   // and will make lo=lo+1, which end this recursive loop
   //
   while ( lo<=hi )
   {
      // 
      // lo/hi approach pivot, and at the end, 
      // one of it will become index of pivot 
      // and will change pivot to correct position
      //
      while ( vec[lo] < pivot ) lo++;  
      while ( pivot < vec[hi] ) hi--; 

      if ( lo<=hi ) {
         if ( debug ) cout << lo << " " << hi << endl; 
         swap(vec[lo++], vec[hi--]);
      }
   }

   if ( debug ){
      cout << "[vec][" << vec.size() << "]"<< endl;
      tr(vec, x)
        cout << *x << " ";
      cout << endl << endl;
   }

   if ( debug ) cout << "Return : " << lo << endl << endl; 
   return lo;
}

void qSort(vi& vec, int lo, int hi) { 

   int index = partition(vec, lo, hi);

   if ( debug ) cout << "Idx,lo,hi : " << index << " " << lo << " " << hi << endl << endl;

   // index -1 to comply with index is return by lo+1
   if ( lo < index-1 )
      qSort( vec, lo, index-1 );

   if ( index < hi ) 
      qSort( vec, index, hi);
}

int main(){

   int b[] = { 43, 236, 2476, 432, 234, 275, 47, 23, 3, 44, 681, 1350, 4894, 4, 1};

   vi vecR(b,b+15);

   cout << "### QSORT SORT ### " << endl; 
   cout << "ORI [" << vecR.size() << "]: ";
   tr(vecR, x) 
     cout << *x << " ";
   cout << endl << endl;

   qSort(vecR, 0, vecR.size()-1);

   cout << "SORT[" << vecR.size() << "]: ";
   tr(vecR, x) 
     cout << *x << " ";
   cout << endl;

   cout << "#################" << endl;

   return 0;
}
