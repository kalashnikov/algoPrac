#include<iostream>
#include<vector>
#include<random>
#include<algorithm>

using namespace std;

int search3(const vector<int> a, const vector<int> b, const vector<int> c){
  if ( a.size() > b.size() ) { 
    return search3(b, a, c);
  } else if ( a.size() > c.size() ) { 
    return search3(c, b, a);
  }

  int i = 0 , j = 0, k = 0;
  int cnt = 0;
  while(i<a.size()){
    ++cnt;

    while(b[j]<a[i]) { ++j;   ++cnt; }
    if( j>=b.size()) { ++cnt; break; }
    
    if ( a[i]!=b[j] ) { ++cnt; ++i; continue; }

    while(c[k]<a[i]) { ++k;   ++cnt; }
    if( k>=c.size()) { ++cnt;  break;}

    if ( a[i]==c[k] ){
      ++cnt;
      return a[i];
    }
    ++i;
  }

  int min_size = a.size();
  if ( b.size() < min_size ) min_size = b.size();
  if ( c.size() < min_size ) min_size = c.size();
  if ( cnt > 3*min_size ) { 
    cout << "### Too much comparsion: " << cnt << " vs " << (3*min_size) << endl; 
    cout << "### a[" << a.size() << "]:";
    for(const int i : a) cout << i << " "; 
    cout << endl;
    cout << "### b[" << b.size() << "]:";
    for(const int i : b) cout << i << " "; 
    cout << endl;
    cout << "### c[" << c.size() << "]:";
    for(const int i : c) cout << i << " "; 
    cout << endl;
  }

  return -1;
}

int search3_bad(const vector<int> a, const vector<int> b, const vector<int> c){
  int i, j, k;
  for(i=0;i<a.size();++i){
    for(j=0;j<b.size();++j){
      for(k=0;k<c.size();++k){
        if ( a[i]==b[j] && a[i]==c[k]){
          return a[i];
        }
      }
    }
  }
  return -1;
}

int search3_good(const vector<int> a, const vector<int> b, const vector<int> c){
  int i = 0, j = 0, k = 0;
  int cnt = 0;
  while(i<a.size() && j<b.size() && k<c.size()){
    if (a[i]<b[j]){
      ++cnt;
      ++i;
    } else if (b[j]<c[k]){
      ++cnt;
      ++j;
    } else if (c[k]<a[i]){
      ++cnt;
      ++k;
    } else { 
      return a[i];
    }
    cnt+=1;
  }
  
  int min_size = a.size();
  if ( b.size() < min_size ) min_size = b.size();
  if ( c.size() < min_size ) min_size = c.size();
  if ( cnt > 3*min_size ) { 
    cout << "### (GOOD) Too much comparsion: " << cnt << " vs " << (3*min_size) << endl; 
    cout << "### a: ";
    for(const int i : a) cout << i << " "; 
    cout << endl;
    cout << "### b: ";
    for(const int i : b) cout << i << " "; 
    cout << endl;
    cout << "### c: ";
    for(const int i : c) cout << i << " "; 
    cout << endl;
  }
  return -1;
}

int main(){
  bool passed = true;
  std::random_device rd;
  std::uniform_int_distribution<int> dist(1, 100);
  std::uniform_int_distribution<int> sd(20, 50);
  
  int ans1, ans2, ans3;

  for( int idx = 0; idx<1000; ++idx) {
    int a_size = sd(rd);
    int b_size = sd(rd);
    int c_size = sd(rd);

    vector<int> a(a_size,0);
    vector<int> b(b_size,0);
    vector<int> c(c_size,0);

    for(int&i : a) i = dist(rd); 
    for(int&i : b) i = dist(rd); 
    for(int&i : c) i = dist(rd); 

    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    sort(c.begin(),c.end());
      
    ans1 = search3(a,b,c);
    ans2 = search3_bad(a,b,c);
    ans3 = search3_good(a,b,c);
    
    cout << ans1 << " vs " << ans2 << " vs " << ans3 << endl;

    if ( ans1 != ans2 || ans1 != ans3 ) {
      cout << "### a: ";
      for(const int i : a) cout << i << " "; 
      cout << endl;
      cout << "### b: ";
      for(const int i : b) cout << i << " "; 
      cout << endl;
      cout << "### c: ";
      for(const int i : c) cout << i << " "; 
      cout << endl;
      passed = false;
      break;
    }
  }

  if ( passed ) cout << "### Passed Test ###" << endl;

  return 0;
}
