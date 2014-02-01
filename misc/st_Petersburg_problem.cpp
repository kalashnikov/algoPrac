// 
// St. Petersburg Paradox
// Ref: http://en.wikipedia.org/wiki/St._Petersburg_paradox
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

#define OMP 11

using namespace std;

int calResult(int i){
    if(rand()%10>4.5)
        return i;
    else 
        return calResult(i*2);
}

void Test( int n )
{
    cout << "<T:" << omp_get_thread_num() << "> - " << n << "n" << endl;
}

int main(){

    #pragma omp parallel
    {
        Test( 0 );
    }

    int max   = 0;
    int tmp   = 0;
    int total = 0;
    srand(time(NULL));

    for(int i=0;i<100000;i++) { 
        tmp    = calResult(1);
        //cout << tmp << " ";
        
        total += tmp;
        (tmp>max)?max=tmp:NULL;
    }
    cout << endl;

    cout << "### Result: " << total/1000.0 << endl; 
    cout << "### Max   : " << max << endl;

    return 0;
}
