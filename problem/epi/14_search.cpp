#include<iostream>
#include<vector>
#include<random>
#include<cstring>

using namespace std;

const bool debug = false;

// Quick sort (From Practical Programming)
int partition( vector<int>& vec, int lo, int hi) { 
   int pivot = vec[(lo+hi)/2]; 

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
         swap(vec[lo++], vec[hi--]);
      }
   }
   return lo;
}
void qSort1(vector<int>& vec, int lo, int hi) { 

   int index = partition(vec, lo, hi);

   if ( debug ) {
       for( const int a:vec)
           cout << a << " ";
       cout << endl;
       cout << "Idx,lo,hi : " << index << " " << lo << " " << hi << endl << endl;
   }
  
   // index -1 to comply with index is return by lo+1
   if ( lo < index-1 )
      qSort1( vec, lo, index-1 );

   if ( index < hi ) 
      qSort1( vec, index, hi);
}

// Programming Pearls 11-3
void qSort2(vector<int>& vec, int lo, int hi){
    if ( lo>=hi ) return;
    swap(vec[lo], vec[(lo+hi)/2]);
    int t = vec[lo];
    int i = lo;
    int j = hi+1;
    int temp;
    for(;;) {
        do i++; while ( i<=hi && vec[i] < t );
        do j--; while ( vec[j] > t );
        if ( i > j ) break;
        temp = vec[i]; vec[i] = vec[j]; vec[j] = temp;
    }
    swap(vec[lo],vec[j]);
    qSort2(vec, lo, j-1);
    qSort2(vec, j+1, hi);
}

void select_sort(vector<int>& vec){
    int temp;
    for ( int i=0; i<vec.size()-1; ++i ){
        for ( int j=i; j<vec.size(); ++j ){
            if ( vec[j] < vec[i] ){
                temp = vec[i]; vec[i] = vec[j]; vec[j] = temp;
            }
        }
    }
}

void shell_sort(vector<int>& vec){
    int h, temp;
    for ( h=1; h<vec.size(); h=3*h+1 ) ;
    for (;;){
        h/=3;
        if ( h < 1 ) break;
        for (int i=h; i<vec.size(); ++i) {
            for (int j=i; j>=h; j-=h) {
                if (vec[j-h] < vec[j])
                    break;
                temp = vec[j-h]; vec[j-h] = vec[j]; vec[j] = temp;
            }
        }
    }
}

int main(){

    // Random
    const int NUM = 10000;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, NUM);

    vector<int> ary(NUM,0); 
    for (int& i:ary) i=dis(gen);
   
    //qSort1(ary, 0, ary.size()-1);
    //qSort2(ary, 0, ary.size()-1);
    //select_sort(ary);
    shell_sort(ary);

    for (const int i:ary) cout << i << " ";
    cout << endl;

    return 0;
}
