#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;
#define all(c) (c).begin(), (c).end()
#define tr(c,x) for(typeof((c).begin()) x=(c).begin();x!=(c).end();x++)

class DFS{ 

   public:
      DFS() { 
         N =     10;
         W = vii(10);

         int d0[] = { 1, 2 }; 
         int d1[] = { 3, 4 }; 
         int d2[] = { 9    }; 
         int d3[] = { 8    }; 
         int d4[] = { 5, 6 };
         int d5[] = { 7    };

         W[0].assign(d0,d0+2);
         W[1].assign(d1,d1+2);
         W[2].assign(d2,d2+1);
         W[3].assign(d3,d3+1);
         W[4].assign(d4,d4+2);
         W[5].assign(d5,d5+1);
      }

   int N;
   vii W;
    vi V;
    
   void dfs(int i) { 
      if(!V[i]){
         cout << "Mark " << i << endl;
         V[i]=1;
         tr(W[i], x){
            cout << "Trace " << *x << endl;
            dfs(*x);
         }
      }
   }

   bool check() { 
      int start_vertex = 0;
      V = vi(N,0);
      dfs(start_vertex);
      return (find(all(V),0) == V.end());
   }
};

int main(){

   DFS dfs;
   cout << dfs.check() << endl; 

   return 0;
}

