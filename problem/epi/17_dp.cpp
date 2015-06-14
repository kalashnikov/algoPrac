#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 17.21 Find the longest nondecreasing subsequence
int longestNondecreasingSubseq(const vector<int>& A){
    vector<int> tail_values;
    for (const int& a : A){
        auto it = upper_bound(tail_values.begin(), tail_values.end(), a);
        if ( it == tail_values.end() ) {
            tail_values.emplace_back(a);
        } else {
            *it = a;
        }
    }
    return tail_values.size();
}

// CCI 17.8  
int get_max_sum(const vector<int> vec){
    int max_sum = 0;
    int current_sum = 0;
    for(const int c : vec){
        current_sum += c;
        if ( max_sum < current_sum )
            max_sum = current_sum; 
        else if ( current_sum < 0 ) 
            current_sum = 0;
    }
    return max_sum; 
}

int main(){

    vector<int> v {0,8,4,12,2,10,6,14,1,9};
    cout << longestNondecreasingSubseq(v) << endl;

    vector<int> v2{2, 3, -8, -1, 2, 4, -2, 3};
    cout << get_max_sum(v2) << endl;

    return 0;
}
