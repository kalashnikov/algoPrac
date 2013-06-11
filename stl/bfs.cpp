#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;
#define all(c) (c).begin(), (c).end()
#define tr(c,x) for(typeof((c).begin()) x=(c).begin();x!=(c).end();x++)

class BFS{ 

   public:
      BFS() { 
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
    
   void bfs(int i) { 

      queue<int> q;
      q.push(i);

      int now = 0;
      while( !q.empty() )
      {
         now = q.front(); 
         q.pop();

         V[now]=1;
         cout << "Mark " << now << endl;

         tr(W[now],x) {

           cout << "Enqueue " << *x << endl;
           q.push(*x);
         }
      }
   }

   bool check() { 
      int start_vertex = 0;
      V = vi(N,0);
      bfs(start_vertex);
      return (find(all(V),0) == V.end());
   }
};

int main(){

   BFS bfs;
   cout << bfs.check() << endl; 

   return 0;
}

