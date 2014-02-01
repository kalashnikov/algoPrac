// 
// St. Petersburg Paradox
// Ref: http://en.wikipedia.org/wiki/St._Petersburg_paradox
//

#include <omp.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

#define NUM 100000000

using namespace std;

int calResult(int i){
    if(rand()%10>4.5)
        return i;
    else 
        return calResult(i*2);
}

int main(){

    int max   = 0;
    int tmp   = 0;
    long total = 0;
    srand(time(NULL));

    #pragma omp parallel
    {
        for(int i=0;i<NUM;i++) { 
            tmp    = calResult(1);

            total += tmp;
            (tmp>max)?max=tmp:NULL;
        }
    }
    cout << endl;

    cout << "### Result: " << total/NUM << endl; 
    cout << "### Max   : " << max << endl;

    return 0;
}
