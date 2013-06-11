
//
// [TopCode] KiloManX
// Problem Link: http://community.topcoder.com/stat?c=problem_statement&pm=2288&rd=4725
// 

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
using namespace std;

typedef vector<int>  vi;
typedef vector<vi>  vvi;
#define all(c) (c).begin(), (c).end()
#define tr(c,x) for(typeof(c).begin() x=(c).begin();x!=(c).end();x++)

class node { 

   public: 
      node(int x=0, int y=0):weapons(x),shots(y){}

      int weapons;
      int shots; 
};

bool operator<(const node& ln, const node& rn){
   return (ln.shots>rn.shots);
}

int leastShots(string[], int[]);

const bool debug = false;

int main(){

   // Answer: 218 
   string  dc[] = { "070", "500", "140" };
   int     bh[] = { 150, 150, 150 };


   // Answer: 205
   string  dc1[] = { "1542", "7935", "1139", "8882" };
   int     bh1[] = { 150, 150, 150, 150 };

   // Answer: 92
   string  dc2[] = { "02111111", "10711111", "11071111", "11104111", 
                     "41110111", "11111031", "11111107", "11111210" };
   int     bh2[] = { 28, 28, 28, 28, 28, 28, 28, 28};

   // Answer: 260445
   string  dc3[] = {"198573618294842",
                   "159819849819205",
                   "698849290010992",
                   "000000000000000",
                   "139581938009384",
                   "158919111891911",
                   "182731827381787",
                   "135788359198718",
                   "187587819218927",
                   "185783759199192",
                   "857819038188122",
                   "897387187472737",
                   "159938981818247",
                   "128974182773177",
                   "135885818282838"};

   int     bh3[] = {157, 1984, 577, 3001, 2003, 2984, 5988, 190003,
                   9000, 102930, 5938, 1000000, 1000000, 5892, 38};
   
   if ( debug ) {
      for ( int i=0; i<3; i++ ) 
         cout << dc[i] << " ";
      cout << endl;

      for ( int i=0; i<3; i++ ) 
         cout << bh[i] << " ";
      cout << endl;
   }

   cout << leastShots(dc3, bh3) << endl;

   return 0;
}

int leastShots(string damageChart[], int bossHealth[]){

   // Need 2^16 to save 2^15
   bool visited[65536]; 

   int nw = damageChart[0].size();
   int dcLen = nw;

   priority_queue<node> pq;
   pq.push(node(0,0));

   while ( !pq.empty() ) { 

      // Always got best shot of current.
      node top = pq.top(); 
      pq.pop();

      if ( debug ) cout << "Top PQ: " << top.shots << endl;
      if ( debug ) cout << "Visited Weapon:" << top.weapons << endl;

      if ( visited[top.weapons] ) continue; 
      visited[top.weapons] = true; 

      // Top's weapon is all geted ( Finished ) 
      if ( top.weapons == (1<<nw)-1 ) 
         return top.shots;

      for ( int i=0; i<dcLen ; i++ ){       // i => Boss

         // Check Boss Visited
         if ((top.weapons >> i ) & 1 )
            continue;

         int best = bossHealth[i];
         for ( int j=0; j<dcLen ; j++ ){    // j => Weapon index of current WeaponSet
            if (i==j) continue; 

            // Not kill by its own weapon & weapon's damage to this boss is not 0
            if ( ((top.weapons>>j)& 1 ) && damageChart[j][i]!='0' ){

               int shotsNeeded = bossHealth[i] / (damageChart[j][i]-'0' );
               if ( bossHealth[i]%(damageChart[j][i]-'0')!=0 ) shotsNeeded++; // Not divided, need one more shot. 

               best = min(best, shotsNeeded);

               // Use Weapon 
               if ( debug ) cout << "Use weapon [" << j << "] to kill boss[" << i << "] :" << best << " " << shotsNeeded << endl;
            }
         }

         // Put best choose based on current shots
         if ( debug ) cout << "==> PUSH : " << (top.weapons|(1<<i)) << " " << (top.shots+best) << endl;
         pq.push(node(top.weapons | (1 << i), top.shots+best));
      }
   }
}
