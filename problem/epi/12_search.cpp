#include<iostream>
#include<algorithm>
#include<vector>
#include<array>
#include<random>
#include<cstring>

using namespace std;

const bool debug = false;

int bsearch(int t, const vector<int>& A){
    int L = 0, U = A.size() - 1;
    while ( L <= U ) {
        int M = ( L + U ) / 2;
        if ( A[M] < t ) {
            L = M+1;
        } else if ( A[M] == t ) {
            return M; 
        } else { 
            U = M-1; 
        }
    }
    return -1;
}

// 12.10 Find min and max simultaneously
pair<int, int> findMinMax(const vector<int>& A){
    if(A.size()<=1) return {A.front(), A.front()};

    pair<int,int> global_min_max = minmax(A[0],A[1]);
    for(int i = 2; i<A.size(); i+=2){
        pair<int,int> local_min_max = minmax(A[i],A[i+1]);
        global_min_max = {min(global_min_max.first,local_min_max.first),
                          max(global_min_max.second,local_min_max.second)};
    }

    if(A.size()&1){
        global_min_max = {min(global_min_max.first,A.back()),
                          max(global_min_max.second,A.back())};
    }
    return global_min_max;
}

// 12.11 Find K-th largest elment
int partitionAroundPivot(int left, int right, int pivot_idx, vector<int>* A){
    auto& A_ref = *A;
    int pivot_value = A_ref[pivot_idx];
    int new_pivot_idx = left;
    swap(A_ref[pivot_idx], A_ref[right]);
    for(int i=left; i<right; i++){
        if(A_ref[i] > pivot_value){ // Larger places at front
            swap(A_ref[i],A_ref[new_pivot_idx++]);
        }
    }
    swap(A_ref[right],A_ref[new_pivot_idx]);
    return new_pivot_idx;
}
int findKthLargest(vector<int> A, int k){
    int left = 0, right = A.size()-1;
    default_random_engine gen((random_device())());
    while(left <= right){
        // Generate random in int [left, right]
        uniform_int_distribution<int> dis(left,right);
        int pivot_idx = dis(gen);
        int new_pivot_idx = partitionAroundPivot(left, right, pivot_idx, &A);
        if(new_pivot_idx == k-1){
            return A[new_pivot_idx];
        } else if (new_pivot_idx > k-1){
            right = new_pivot_idx - 1;
        } else {
            left = new_pivot_idx + 1;
        }
    }
}

// 
// Quick sort
//
int partition( vector<int>& vec, int lo, int hi) { 
   int pivot = vec[(lo+hi)/2]; 

   int temp;
   while ( lo<=hi )
   {
      while ( vec[lo] < pivot ) lo++;  
      while ( pivot < vec[hi] ) hi--; 

      if ( lo<=hi ) {
          temp = vec[lo]; vec[lo] = vec[hi]; vec[hi] = temp;
          lo++, hi--;
      }
   }
   return lo;
}
void qSort(vector<int>& vec, int lo, int hi) { 
   int index = partition(vec, lo, hi);
  
   // index -1 to comply with index is return by lo+1
   if ( lo < index-1 )
      qSort( vec, lo, index-1 );

   if ( index < hi ) 
      qSort( vec, index, hi);
}

bool check_in_order(const vector<int> vec){
    for( int i=0; i<vec.size(); i++)
        if(vec[i]<vec[i-1]) 
            return false;
    return true;
}

int main(){
    vector<int> v {0,8,4,12,2,10,6,14,1,9};
    auto gmm = findMinMax(v);
    cout << gmm.first << " " << gmm.second << endl;

    vector<int> v2{1,2,3,4};
    cout << findKthLargest(v2, 2) << endl; 
    
    qSort(v, 0, v.size()-1);
    for( const int a:v)
        cout << a << " ";
    cout << endl;

    std::vector<int> v3{5, 6, 4, 3, 2, 6, 7, 9, 3};
    std::nth_element(v3.begin(), v3.begin() + v3.size()/2, v3.end());
    std::cout << "The median is " << v3[v3.size()/2] << '\n';
    for( const int a:v3)
        cout << a << " ";
    cout << endl;

    // Random
    const int NUM = 10000;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, NUM);

    vector<int> ary(NUM,0); 
    for (int& i:ary) i=dis(gen);
    qSort(ary,0,ary.size()-1);
    
    for (const int i:ary) cout << i << " ";
    cout << endl;

    cout << "Index of 527: " << bsearch(527,ary) << endl;
    cout << "In Order: " << (check_in_order?"YES":"NO") << endl;
    return 0;
}
