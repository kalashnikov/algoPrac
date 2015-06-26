#include<iostream>
#include<vector>
#include<random>
#include<algorithm>
#include<climits>

using namespace std;

const bool debug = true;

void find1st2nd(const vector<int> x, int &first, int &second){
  if ( x[0] < x[1] ) {
    first = x[0]; second = x[1];
  } else { 
    first = x[1]; second = x[0];
  }

  for ( int i = 2; i<x.size() ; ++i ) {
    if ( x[i] < first ) 
      second = first, first = x[i];
    else if (x[i] < second ) 
      second = x[i];
  }
}

void update(int a, int b, int &first, int &second){
  if ( a>second && b>second ) { 
    return;
  } else if ( a < b ) {
    if ( a < first && b < first ) {
      first = a, second = b;
    } else if ( a < first ) { 
      second = first, first = a; 
    } else if ( a < second ) {
      second = a;
    }
  } else { 
    if ( a < first && b < first ) { 
      first = b, second = a;
    } else if ( b < first ) { 
      second = first, first = b; 
    } else if ( b < second ) {
      second = b;
    }
  }
}

void find1st2ndRecur(const vector<int> x, int from, int to, int &first, int &second){
  if ( to - from > 1 ) {
    find1st2ndRecur(x, from, (from+to)/2, first,second);
    find1st2ndRecur(x, (from+to)/2+1, to, first,second);
  } else if ( to - from == 0 ) { 
    update(x[to], second, first, second);
  } else if ( to - from == 1 ) {
    update(x[from], x[to], first, second);
  } 
  return ;
}

void f_and_s(int x[], int left, int right, int *f, int *s){
  int mid;
  int F1, F2;
  int S1, S2;

  if ( left > right ) 
    *f = *s = INT_MAX;
  else if ( left == right ) 
    *f = x[left], *s = INT_MAX;
  else {
    mid = ( left + right ) / 2;
    f_and_s(x, left, mid, &F1, &S1);
    f_and_s(x, mid+1, right, &F2, &S2);
    if ( F1 < F2 ) 
      *f = F1, *s = ( S1 < F2 ) ? S1 : F2;
    else 
      *f = F2, *s = ( S2 < F1 ) ? S2 : F1;
  }
}

int main() {
  std::random_device rd;
  std::uniform_int_distribution<int> dist(1, 100);

  for( int idx = 0; idx<1000; ++idx) {
    vector<int> a(50,0);
    for(int&i : a) i = dist(rd); 

    int f1, s1, f2 = INT_MAX, s2 = INT_MAX;
    find1st2nd(a, f1, s1);
    find1st2ndRecur(a, 0, a.size()-1, f2, s2);

    if ( debug ) cout << "### " << idx << ": " << f1 << " vs " << f2 << " | " << s1 << " vs " << s2 << endl;

    if ( f1!=f2 || s1!=s2 ) {
      cout << endl;
      cout << "### a: ";
      for(const int i : a) cout << i << " "; 
      cout << endl;
    
      cout << "### Min:" << f1 << " " << s1 << endl;  
      cout << "### Min(Recur):" << f2 << " " << s2 << endl;  

      sort(a.begin(),a.end());
      cout << "### a: ";
      for(const int i : a) cout << i << " "; 
      cout << endl;
      break;
    }
  }

  return 0;
}
