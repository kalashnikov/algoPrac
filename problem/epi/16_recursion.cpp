#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

// 16.2 N-Queens 
vector<string> createOutput(const vector<int>& col_placement){
    vector<string> sol;
    for(int row: col_placement){
        string line(col_placement.size(), '.');
        line[row] = 'Q';
        sol.emplace_back(line);
    }
    return sol;
}
bool isFeasible(const vector<int>& col_placement, int row){
    for( int i = 0; i < row; ++i){
        int diff = abs(col_placement[i] - col_placement[row]);
        if(diff == 0 || diff == row-i){
            return false;
        }
    }
    return true;
}
void nQueensHelper(int n, int row, vector<int>* col_placement,
                    vector<vector<string>>* result){
    if(row==n){
        result->emplace_back(createOutput(*col_placement));
    } else {
        for( int col = 0; col < n; ++col){
            (*col_placement)[row] = col;
            if(isFeasible(*col_placement,row)){
                nQueensHelper(n, row+1, col_placement, result);
            }
        }
    }
}
vector<vector<string>> nQueens(int n){
    vector<int> placement(n);
    vector<vector<string>> result;
    nQueensHelper(n, 0, &placement, &result);
    return result;
}

int main(){
    auto result = nQueens(5);
    for ( const auto a : result){ 
        for( const string s : a ){ 
            cout << s << endl;  
        }
        cout << endl;
    }
    return 0;
}
