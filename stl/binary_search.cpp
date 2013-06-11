
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;
#define all(c) (c).begin(), (c).end()
#define tr(c,x) for(typeof(c).begin() x=(c).begin();x!=(c).end();x++)

const bool debug = false;

// Iterated Type
int binary_search(vi& vec, int lo, int hi, int target) { 

   int index = -1; 

   int mid   =  0;

   while( lo < hi ){

      mid = (lo+hi)/2;

      if ( target==vec[mid] )
      {
         index = mid;
         cout << "GET index : " << mid << endl;
         break ;
      }
      else if ( target > vec[mid] )
         lo = mid + 1; 
      else 
         hi = mid;
   }

   return index; 
}

// Recursive Type 
int bs_recur(vi& vec, int lo, int hi, int target) { 

   int mid = (lo+hi)/2;

   if ( lo > hi ) 
      return -1;
   else if ( target==vec[mid] )
   {
      cout << "GET index : " << mid << endl;
      return mid;
   }
   else if ( target > vec[mid] )
   {
      lo = mid + 1; 
      bs_recur(vec, lo, hi, target);
   }
   else {
      hi = mid; 
      bs_recur(vec, lo, hi, target);
   }
}

bool search(vi& vec, int target){ 
//   return (binary_search(vec, 0, vec.size()-1, target)!=-1);
   return (bs_recur(vec, 0, vec.size()-1, target)!=-1);
}

// 
// Memorized !!
// ALL equal !!!! 
//
void merge( vi& vec, int lo, int mid, int hi) { 

   vi help(vec.size(),0); 
   for ( int i=lo; i<=hi; i++ )  
      help[i]=vec[i];

   if ( debug ){
      cout << "[help]" << endl;
      tr(help, x)
        cout << *x << " ";
      cout << endl;
   }

   int helplo = lo; 
   int helphi = mid+1;
   int cur    = lo;

   while( helplo<=mid && helphi<=hi )
      if ( help[helplo] <= help[helphi] ){ 
         if ( debug ) cout << "==> Put(L) " << help[helplo] << endl;
         vec[cur++]=help[helplo++];
      } else {
         if ( debug ) cout << "==> Put(H) " << help[helphi] << endl;
         vec[cur++]=help[helphi++];
      }

   if ( debug ) cout << "### mid,hlo,hhi " << mid << " " << helplo << " " << helphi << endl; 
   int res = mid - helplo;

   // 
   // Re-Put Left side remain into Vector
   // Note: i<=res , equal is NEED!!
   for (int i=0;i<=res;i++) {
      if ( debug ) cout << "==> Re-Put " << help[helplo+i] << endl;
      vec[cur+i]=help[helplo+i];   
   }

   if ( debug ){
      cout << "[vec]" << endl;
      tr(vec, x)
        cout << *x << " ";
      cout << endl << endl;
   }
}

void mergeSort(vi& vec, int lo, int hi) { 

   if ( lo < hi ){
      int mid = (lo+hi)/2; 
      mergeSort(vec,  lo,  mid);
      mergeSort(vec, mid+1, hi); // +1 at Right Side
      merge(vec, lo, mid, hi);
   }
}

int main(){

   int a[] = { 1, 2, 4, 6, 7, 9, 13, 37, 347, 843 };
   int b[] = { 43, 236, 2476, 432, 234, 275, 47, 23, 3, 44, 681, 1350, 4894, 4, 1};

   vi vec(a,a+10);
   cout << search(vec, 6) << endl;

   vi vecR(b,b+15);

   cout << "### MERGE SORT ### " << endl; 
   cout << "ORI [" << vecR.size() << "]: ";
   tr(vecR, x) 
     cout << *x << " ";
   cout << endl << endl;

   mergeSort(vecR, 0, vecR.size()-1);

   cout << "SORT[" << vecR.size() << "]: ";
   tr(vecR, x) 
     cout << *x << " ";
   cout << endl;

   cout << "#################" << endl;

   return 0;
}
