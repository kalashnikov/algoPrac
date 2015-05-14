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

int main(){

    vector<int> v {0,8,4,12,2,10,6,14,1,9};
    cout << longestNondecreasingSubseq(v) << endl;

    return 0;
}
