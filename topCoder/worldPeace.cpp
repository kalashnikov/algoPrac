
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

const bool debug = false;

class WorldPeace
{
   public:
      long long numGroups(int , int[]);
      int size;
};

int main(){

   int a0[] = { 4,4,4,4,4 };
   int a1[] = { 1,2,3,4,5,6 };
   int a2[] = { 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000 };
   int a3[] = { 96, 17, 32, 138, 112, 50, 7, 19,
                412, 23, 14, 50, 47, 343, 427, 22, 39 };
   int a4[] = { 638074479, 717901019, 910893151, 924124222, 991874870, 919392444, 729973192, 607898881, 
              838529741, 907090878, 632877562, 678638852, 749258866, 949661738, 784641190, 815740520, 
              689809286, 711327114, 658017649, 636727234, 871088534, 964608547, 867960437, 964911023, 
              642411618, 868318236, 793328473, 849540177, 960039699, 998262224, 775720601, 634685437, 
              743766982, 826321850, 846671921, 712570181, 676890302, 814283264, 958273130, 899003369, 
              909973864, 921987721, 978601888, 633027021, 896400011, 725078407, 662183572, 629843174, 
              617774786, 695823011 };

   WorldPeace wp;
   wp.size = sizeof(a4)/sizeof(a4[0]);
   cout << wp.numGroups(10, a4) << endl;

   return 0;
}

int part(int a[], int lo, int hi){

   int pivot = a[(lo+hi)/2];

   while( lo<=hi ){
      while( a[lo]>pivot ) lo++;  // Decreasing Order
      while( pivot>a[hi] ) hi--;  // Decreasing Order
      if( lo<=hi ){
         swap(a[lo],a[hi]);
         lo++; hi--;
      }
   }

   return lo;
}

void qSort(int a[], int lo, int hi){

   int index = part(a, lo, hi);

   if ( lo < index-1 )
      qSort(a, lo, index-1 );

   if ( index < hi   )
      qSort(a, index, hi   );
}

long long WorldPeace::numGroups(int k, int countries[]){

   long long min   = 0;
   long long group = 0;

   int   loop = 0;
   long allow = 0;

   int size = this->size;
   if ( debug ) cout << "k= " << k << " | Size: " << size << endl;

   do { 
      qSort(countries, 0, size-1);

      if ( debug ){
         for ( int i=0; i<size; i++ )
            cout << countries[i] << " ";
         cout << endl;
      }

      min = countries[k-1];      // Each set size: k  => use a[k-1] for largest num in Deceasing ordering
      if ( debug ) cout << "Min: " << min << endl << endl;

      allow = (min+999)/1000;

      //group += min;
      group += allow;
      for ( int i=0 ; i<k; i++){
         //countries[i] = countries[i] - min;
         countries[i] = countries[i] - allow;
      }

      loop++;
   } while(min!=0);

   if ( debug ) cout << endl << "Total Loop: " << loop << endl; 

   return group;
}
