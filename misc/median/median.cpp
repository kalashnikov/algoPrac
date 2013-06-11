
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <ctime>
using namespace std;

typedef vector<int>  vi;
typedef vector<vi>  vvi;
#define all(c) (c).begin(), (c).end()
#define tr(c,x) for(typeof(c).begin() x=(c).begin();x!=(c).end();x++)

// 
// Memorize!!
//
int quickSelect(vi& vec, int k){

   int lo = 0; 
   int hi = vec.size()-1;

   int l, h;
   int pivot;
   while ( lo<hi ) {       // Check Boundary!!

      l = lo;
      h = hi;
      pivot = vec[k];

      do { 
         while( vec[l] <  pivot ) l++;
         while( pivot  < vec[h] ) h--;

         if ( l <= h ) {
            swap(vec[l],vec[h]);
            l++; h--;
         }

      } while ( l<=h ); 

      if ( h < k ) lo = l; // Search Larger  Partition
      if ( k < l ) hi = h; // Search Smaller Partition
   } 

   return vec[k];
}

int median5(int a, int b, int c, int d, int e){

 return b < a ? d < c ? b < d ? a < e ? a < d ? e < d ? e : d
                                                 : c < a ? c : a
                                         : e < d ? a < d ? a : d
                                                 : c < e ? c : e
                                 : c < e ? b < c ? a < c ? a : c
                                                 : e < b ? e : b
                                         : b < e ? a < e ? a : e
                                                 : c < b ? c : b
                         : b < c ? a < e ? a < c ? e < c ? e : c
                                                 : d < a ? d : a
                                         : e < c ? a < c ? a : c
                                                 : d < e ? d : e
                                 : d < e ? b < d ? a < d ? a : d
                                                 : e < b ? e : b
                                         : b < e ? a < e ? a : e
                                                 : d < b ? d : b
                 : d < c ? a < d ? b < e ? b < d ? e < d ? e : d
                                                 : c < b ? c : b
                                         : e < d ? b < d ? b : d
                                                 : c < e ? c : e
                                 : c < e ? a < c ? b < c ? b : c
                                                 : e < a ? e : a
                                         : a < e ? b < e ? b : e
                                                 : c < a ? c : a
                         : a < c ? b < e ? b < c ? e < c ? e : c
                                                 : d < b ? d : b
                                         : e < c ? b < c ? b : c
                                                 : d < e ? d : e
                                 : d < e ? a < d ? b < d ? b : d
                                                 : e < a ? e : a
                                         : a < e ? b < e ? b : e
                                                 : d < a ? d : a;
}

int parti(vi& vec, int lo, int hi){

   int pivot = vec[(lo+hi)/2];
   while (lo<=hi){
      while( vec[lo]<pivot ) lo++;
      while( pivot<vec[hi] ) hi--;

      if ( lo<=hi ) 
         swap(vec[lo++],vec[hi--]);
   }

   return lo;
}

void quickSort(vi& vec, int lo, int hi){
   int index = parti(vec, lo, hi);

   if ( lo<index-1 )
      quickSort(vec, lo, index-1);

   if ( index < hi )
      quickSort(vec, index, hi );
}

const int NUM = 50;

int main(){

   srand(time(0));

   int a[NUM];

   for ( int i=0 ;i<NUM; i++) a[i] = (int) (NUM * (rand() / (RAND_MAX + 1.0)));

   vi vec(a,a+NUM);

   cout << "MEDIAN: " << quickSelect(vec, NUM/2) << endl; 
   
   tr(vec, it) cout << *it << " ";
   cout << endl << endl; 

//   vi vec2(a,a+NUM);

   quickSort(vec, 0, NUM-1);
   
   tr(vec, it) cout << *it << " ";
   cout << endl; 

   cout << "MEDIAN: " << vec[NUM/2] << endl; 

   return 0;
}
