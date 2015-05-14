#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

// 6.22 Spiral ordering of 2D array
void clockwise(const vector<vector<int>> &A, int offset, vector<int>* result){
    if(offset == A.size() - offset - 1){
        // odd dimension, should be at the center of matrix A 
        result->emplace_back(A[offset][offset]);
        return;
    }

    for (int j = offset; j < A.size() - offset - 1; ++j) {
        result->emplace_back(A[offset][j]);
    }
    for (int i = offset; i < A.size() - offset - 1; ++i) {
        result->emplace_back(A[i][A.size()-offset-1]);
    }
    for (int j = A.size() - offset - 1; j > offset; --j) {
        result->emplace_back(A[A.size()-offset-1][j]);
    }
    for (int i = A.size() - offset - 1; i > offset; --i) {
        result->emplace_back(A[i][offset]);
    }
}
vector<int> spiralOrder(const vector<vector<int>> &A){
   vector<int> result; 
   for ( int offset = 0; offset < ceil(0.5*A.size()); ++offset) { 
        clockwise(A, offset, &result);
   }
   return result;
}


int main(){

    // 6.22
    vector<vector<int>> A = { { 1 ,2 ,3 }, {4, 5, 6}, {7, 8, 9} } ; 
    auto result = spiralOrder(A);
    for( const int c : result) { 
        cout << c << " ";
    }
    cout << endl;

    return 0;
}