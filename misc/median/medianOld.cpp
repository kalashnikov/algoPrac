
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

const int NUM = 100;

float kth_smallest(float[] , int , int );
#define ELEM_SWAP(a,b) { int t=(a);(a)=(b);(b)=t; }
#define median(a,n) kth_smallest(a,n,(((n)&1)?((n)/2):(((n)/2)-1)))

// buggy
void quickSort3(float a[], int l, int r);

const bool debug = false;

int main(){

   srand(time(0));

   float array[NUM];

   cout << "ARRAY: ";
   for(int a=0;a<NUM;a++){
      array[a]=(rand()%NUM);
      cout << array[a] << " ";
   }
   cout << endl; 
   
   cout << "MEDIAN: " << kth_smallest( array, NUM, NUM/2) << endl; 

   cout << "ARRAY: ";
   for(int a=0;a<NUM;a++){
      array[a]=(rand()%NUM)/10.0;
      cout << array[a] << " ";
   }
   cout << endl; 

   // Insertion Sort
   /*
   int i, j, tmp = 0;
   for(i=1;i<NUM;i++){
      j = i; // i => curr, j=>comparator
      while( j>0 && array[j-1] > array[j] ){ 
         swap(array[j],array[j-1]);
         j--;
      }
   }
   */

   quickSort3(array,0,NUM-1);

   cout << "ARRAY: ";
   for(int a=0;a<NUM;a++){
      cout << array[a] << " ";
   }
   cout << endl;

   return 0;
}

float kth_smallest(float a[], int n, int k)
{
    int i,j,l,m ;
    float x;

    l=0 ; m=n-1 ;
    while (l<m) {
        x=a[k] ;
        i=l ;
        j=m ;

        // Partition of QuickSort
        do {
            while (a[i]<x) i++ ;
            while (x<a[j]) j-- ;
            if (i<=j) {
                ELEM_SWAP(a[i],a[j]) ;
                i++ ; j-- ;
            }
        } while (i<=j) ;

        if (j<k) l=i ; // Search larger  partition
        if (k<i) m=j ; // Search smaller partiiton
    }
    return a[k] ;
}

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

void quickSort3(float a[], int l, int r){
   int i = l-1, j = r;
   int p = l-1, q = r;
   int k;

   float v = a[r];

   if ( r<=l ) return;

   for(;;) 
   { 
      while( a[++i] < v ) ; 
      while( v < a[--j] ) if ( j==l ) break;
      if   ( i>=j )  break;

      swap(a[i],a[j]);
      
      if ( a[i]==v ) { p++; swap(a[p], a[i]); }
      if ( v==a[j] ) { q--; swap(a[j], a[q]); }
   }

   swap(a[i], a[r]); 

   j=i-1; i=i+1;
   for( k=l   ; k<p ; k++,j-- ) swap(a[k], a[j]);
   for( k=r-1 ; k>q ; k--,i++ ) swap(a[i], a[k]);
   
   quickSort3(a, l, j);
   quickSort3(a, i, r);
}

