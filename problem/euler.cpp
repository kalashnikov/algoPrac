
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <sys/time.h>
#include <vector>
#include <set>
#include <sstream>

using namespace std;

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

int isRightAngle(int a, int b, int c, int s){
    if(a>b){ 
        if (a>c) return s*(s-a)==(s-b)*(s-c);
        else     return s*(s-c)==(s-b)*(s-a);
    } else { 
        if (b>c) return s*(s-b)==(s-a)*(s-c);
        else     return s*(s-c)==(s-a)*(s-b);
    }
}

int flog10(unsigned int v){
    return (v >= 1000000000) ? 9 : (v >= 100000000) ? 8 : (v >= 10000000) ? 7 : 
           (v >= 1000000) ? 6 : (v >= 100000) ? 5 : (v >= 10000) ? 4 : 
           (v >= 1000) ? 3 : (v >= 100) ? 2 : (v >= 10) ? 1 : 0;
}

inline int shiftLeft(int n){
    return  (int)n%((int)pow(10,flog10(n)) );
}

inline int shiftRight(int n){
    return ( n/10 );
}

// Ref: zqguo
int divisors(int x) {
    int limit = x;
    int numberOfDivisors = 0;

    for (int i=1; i < limit; ++i) {
        if (x % i == 0) {
            limit = x / i;
            if (limit != i) {
                numberOfDivisors++;
            }
            numberOfDivisors++;
        }
    }

    return numberOfDivisors;
}

bool isPandigital(long val){
   
    int bit = flog10(val)+1;

    int nums[bit]; 
    memset(nums, 0, sizeof(int)*bit);
    
    //string s = std::to_string(val);
    string s = patch::to_string(val);
    const char *ptr = s.c_str();
    while(*ptr!='\0'){
        int tn = *ptr - '0';
        if(tn==0 || tn>bit || nums[tn-1]==1) return false;
        nums[tn-1] = 1;
        ptr++;
    }
    
    return true;
}

bool is_perfect_square(int n) {
    if (n < 0)
        return false;
    int root(round(sqrt(n)));
    return n == root * root;
}

// ========================================================= //
// ========================================================= //
// ========================================================= //
// ========================================================= //

// Find 10001 prime
void euler7(){
    long max = 500000;

    int a[max];
    memset(a, 1, sizeof(int)*max);

    for (long i = 2; i < (max >> 1); ++i) {
        if (a[i]) {
            for (long j = i << 1; j < max; j += i)
                a[j] = 0;
        }
    }

    int count = 0;
    for (long i = 2; i < max; ++i) {
        if (a[i]) { 
            ++count;
        }
        if (count == 10001) {
            printf("Answer: %ld\n", i);
            break;
        }
    }
    return ;
}

void euler12(){
    long max = 500000;
    for (int i = 0; i < max; ++i) {
        long num = (i+1)*i/2;
        int  div = divisors(num);
        if (div>500){
            printf("%ld => %d\n",num,div);
            return;
        }
    }
}

void euler14(){
    long mnum   = 0;
    long mcount = 0;
    long max = 1000000;
    for (long i = 1; i < max; ++i) {
        long n = i;
        long count = 1;
        while(n!=1){
            if(n%2==0) {
                n/=2;
            } else {
                n=3*n+1;
            }
            count++;
        }
        if ( count > mcount ){ 
            mcount = count;
            mnum   = i;
        }
    }
    printf("%ld => %ld\n", mnum, mcount);
    return;
}

void euler15(){

    int max = 21; 

    long a[max][max];
    for(int i=0; i < max ; i++){
        for(int j=0; j < max ; j++){
           a[i][j]=0; 
        }
    }

    a[0][0]=1;
    for(int i=0; i < max ; i++){
        for(int j=0; j < max ; j++){
            if ( i!=max-1 ) a[i+1][j]+=a[i][j];
            if ( j!=max-1 ) a[i][j+1]+=a[i][j];
        }
    }

    printf("%ld\n",a[max-1][max-1]);
    return; 
}

void euler16(){

    const int numiters = 1000;
    const int numdigits = numiters/3;
    int digits[numdigits];
    memset(digits, 0, sizeof(int)*numdigits);

    int size=1, sum=2;
    digits[0] = 2;

    for(int i=1; i < numiters; i++)
    {
        sum*=2;
        for(int n=0; n<size; n++)
        {
            if (digits[n] >= 5)
                sum -= 9;
            digits[n]*=2;
        }
        for(int n=0; n<size; n++)
        {
            if(digits[n]>9)
            {
                digits[n] -= 10;
                digits[n+1] += 1;
                if (n+1 == size)
                    size++;
            }
        }
    }
    printf("%d\n",sum);
}

long euler30(){
    long i = 0, t = 0, s = 0, total = 0;
    for( long i = 2; i < 10000000; i++ ) {
       s = 0; 
       t = i;
       while(t!=0){
           s+=pow(t%10,5);
           t/=10;
       }
       if ( s==i ) 
           total += i;
    }
    return total;
}

// Ref: Exomo
int coins[8] = {200, 100, 50, 20, 10, 5,2,1};
int findposs(int money, int maxcoin)
{
    int sum = 0;
    if(maxcoin == 7) return 1;
    for(int i = maxcoin; i<8;i++)
    {
        if (money-coins[i] == 0) sum+=1;
        if (money-coins[i] > 0) sum+=findposs(money-coins[i], i);
    }
    return sum;     
}

void euler31(){
    printf("%d\n",findposs(200,0) );
    return ;
}

// Ref: grimbal
void ex31b(int m){
    int count=0;
    int a, b, c, d, e, f, g;
    for( a=m ; a>=0 ; a -= 200 )
        for( b=a ; b>=0 ; b -= 100 )
            for( c=b ; c>=0 ; c -= 50 )
                for( d=c ; d>=0 ; d -= 20 )
                    for( e=d ; e>=0 ; e -= 10 )
                        for( f=e ; f>=0 ; f -= 5 )
                            for( g=f ; g>=0 ; g -= 2 )
                                count++;
    printf("ex31b: count=%d\n", count);
}

int fac(int n){
    switch(n){
        case 1: 
            return 1;
        case 2: 
            return 2;
        case 3: 
            return 6;
        case 4: 
            return 24;
        case 5: 
            return 120;
        case 6: 
            return 720;
        case 7: 
            return 7*720;
        case 8: 
            return 8*7*720;
        case 9: 
            return 9*8*7*720;
        default:
            return 1;
    }
}

void euler34(){
    long sum = 0, n = 0, dfac = 0;
    for(long i=10;i<1000000;i++)
    {
        n = i, dfac = 0;
        while(n!=0 && dfac<=i)
        {
            dfac += fac(n%10);
            n/=10;
        }
        if ( dfac==i ) sum+=i;
    }
    printf("%ld\n",sum);
    return ;
}


void euler35(){

    /* ========================= */
    // Sieve to generate Prime array 
    long max = 1000000;
    int a[max];
    for (int i = 0; i < max; ++i) {
        a[i] = 1;
    }
    for (long i = 2; i < (max >> 1); ++i) {
        if (a[i]) {
            for (long j = i << 1; j < max; j += i)
                a[j] = 0;
        }
    }
    /* ========================= */

    int count = 0, ln = 0, n, t, tn;
    bool isCircularPrime = true;
    for (int n = 2; n < max; ++n) {
        if(a[n]==0) continue; // Check Prime only
        isCircularPrime = true;
        a[n] = 0;        // mark-off prime
        ln = flog10(n);  // log 10
        t = ln, tn = n;  // tmp variable 
        while(t--!=0){
            // Next Circular number
            int cir = ( (int)tn%(int)pow(10,ln) * 10 ) + tn/pow(10,ln); 
            if(cir==tn) { count--; break;  } // same number  
            if(a[cir]==0) {
                isCircularPrime = false;
                break; // not prime, fast break 
            } else { 
                a[cir] = 0; // mark-off prime 
                tn = cir;
            }
        }
        if(isCircularPrime) {
            count += ln+1;
        }
    }
    printf("\nAns: %d\n",count);
}

void euler37(){

    /* ========================= */
    // Sieve to generate Prime array 
    long max = 1000000;
    int a[max];
    for (int i = 0; i < max; ++i) {
        a[i] = 1;
    }
    a[1] = 0; // 1 is not prime
    for (long i = 2; i < (max >> 1); ++i) {
        if (a[i]) {
            for (long j = i << 1; j < max; j += i)
                a[j] = 0;
        }
    }
    /* ========================= */

    bool keep = false;
    int x, y, count = 0;
    for (int n = 10; n < max; n++) {
        if ( a[n]==0 ) continue;
        x = n, y = n, keep = true;
        while ( ( x = shiftLeft(x) ) !=0 )
            if ( a[x]==0 ){
                keep = false;
                break;
            }
        while ( ( y = shiftRight(y) ) !=0 )
            if ( a[y]==0 ){
                keep = false;
                break;
            }
        if ( !keep ) continue; 
        count += n;
        printf("%d\n", n);
    }
    printf("Sum: %d\n", count);
}

void euler38(){

    long max = 0, cur = 0;

    bool f = false;
    int bits[9], num, ch;

    for(int i=2;i<100000000;i++){
        cur = 0;
        memset(bits, 0, sizeof(bits));
        for(int j=1;j<10;j++){
            f = false; 
            num = i*j;
            cur = cur!=0 ? cur*pow(10,flog10(num)+1) + num : num;
            //cout << i << ":" << num << endl;
            while(num!=0){
                ch   = num%10;
                num /= 10;
                if(ch == 0 || bits[ch-1]==1) {
                    f = true;
                    break;
                } else bits[ch-1]=1;
                //for ( int k=0;k<9;k++) cout << bits[k];
                //cout << endl;
            }
            if(f) break;
            for(int k=0;k<9;k++){
                if(bits[k]==0){
                    f = true;
                    break;
                }
            }
            if(!f) {
                //cout << i << ":" << cur << endl;
                if(cur>max) max = cur;
            }
        }
    }
    cout << max << endl;
}

void euler39(){

    int c = 0, s = 0, cnt = 0, max = 0, ans = 0;
    int arr[1000]; memset(arr,0,sizeof(arr));
    for(int i=10;i<1000;i++){
        if(i%2==1) continue;
        cnt = 0;
        s = i >> 1; 
        memset(arr,0,sizeof(arr));
        for(int a=1;a<i-1;a++){
            if(arr[a]==1) continue;
            for(int b=a+1;b<i-1-a;b++){
                if ( isRightAngle(a,b,i-a-b,s) ){
                    arr[a]=1; arr[b]=1; arr[i-a-b]=1;
                    cnt++; break;
                }
            }
        }
        if(cnt>max) max = cnt, ans = i;
    }
    cout << ans << endl;
}

void euler40(){

    long ans = 1;
    int cnt = 0, idx = 0, num = 1, bit = 0, tbit = 0; 
    while(cnt!=7){
        bit = flog10(num) + 1;
        if(idx+bit>=pow(10,cnt)){
            //const string s = std::to_string(num);
            const string s = patch::to_string(num);
            int dif = pow(10,cnt)-idx;
            tbit = s[dif-1]-'0';
            ans *= tbit;
            cnt++;
            printf("\n### [ %d: %d (%d) | %ld]\n", idx, tbit, num, ans);
        } 
        idx += bit;
        num++;
    }
    printf("%ld\n",ans);
}

void euler41(){
    long max = 98765432;

    vector<int> a(max,1);

    for (long i = 2; i < (max >> 1); ++i) {
        if (a[i]) {
            for (long j = i << 1; j < max; j += i)
                a[j] = 0;
        }
    }

    for (long i = max; i !=0 ; i--) {
        if (a[i] && isPandigital(i)) { 
            printf("Answer: %ld\n", i);
            break;
        }
    }
}

void euler44(){

    int max = 100000;
    vector<unsigned long> a; a.reserve(max);
    set<unsigned long> seta;

    for ( int i = 0; i<max; i++) {
        a[i] = (i+1)*(3*(i+1)-1)/2;
        seta.insert((i+1)*(3*(i+1)-1)/2);
    }

    bool find = false;
    unsigned long st, nd;
    unsigned long dif, sum;
    for ( int i = 1; i<max; i++){
        for ( int j = 0; j<i; j++){
            st  = a[j]; 
            nd  = a[i];
            if(seta.find(nd+st)!=seta.end() &&
               seta.find(nd-st)!=seta.end() ){
                printf("Answer: %ld\n", nd - st);
                find = true;
                break;
            }
        }
        if(find) break;
    }
}

void euler46(){

    // Prime table
    long max = 100000;
    int a[max];
    memset(a, 1, sizeof(int)*max);
    for (long i = 2; i < (max >> 1); ++i) {
        if (a[i]) {
            for (long j = i << 1; j < max; j += i)
                a[j] = 0;
        }
    }

    for (long i = 11; i < max ; i+=2){
        if (!a[i]) {
            bool find = false;
            for (long j = 2 ; j < i; j++){
                if(a[j] && is_perfect_square((i-j)/2)) {
                    find = true;
                    break;
                }
            }
            if (!find) {
                cout << i << endl;
                break;
            }
        }
    }
}

void euler47(){

    // Prime table
    long max = 700000;
    int a[max];
    memset(a, 1, sizeof(int)*max);
    for (long i = 2; i < (max >> 1); ++i) {
        if (a[i]) {
            for (long j = i << 1; j < max; j += i)
                a[j] = 0;
        }
    }

    bool debug = false;

    int cnt = 0;
    long rem, num;
    for (long i = 644; i < max ;){

        // i 
        num = rem = i; cnt = 0;
        if(debug) cout << num << ": ";
        for(long j=2;j<max;j++){
            if(a[j] && num%j==0){
                rem /= j;
                if(debug) cout << j << " ";
                cnt++;
                if(rem<max && a[rem]==1) {
                    if(debug) cout << rem << " ";
                    cnt++; 
                    break;
                }
                if(rem==1) break;
            }
        }
        if(debug) cout << endl;
        if(cnt!=4) { i++; continue; }

        // i+1
        num = rem = i+1; cnt = 0;
        if(debug) cout << num << ": ";
        for(long j=2;j<max;j++){
            if(a[j] && num%j==0){
                rem /= j;
                if(debug) cout << j << " ";
                cnt++;
                if(rem<max && a[rem]==1) {
                    if(debug) cout << rem << " ";
                    cnt++; 
                    break;
                }
                if(rem==1) break;
            }
        }
        if(debug) cout << endl;
        if(cnt!=4) { i+=2; continue; }
        
        // i+2 
        num = rem = i+2; cnt = 0;
        if(debug) cout << num << ": ";
        for(long j=2;j<max;j++){
            if(a[j] && num%j==0){
                rem /= j;
                if(debug) cout << j << " ";
                cnt++;
                if(rem<max && a[rem]==1) {
                    if(debug) cout << rem << " ";
                    cnt++; 
                    break;
                }
                if(rem==1) break;
            }
        }
        if(debug) cout << endl;
        if(cnt!=4) { i+=3; continue; }
        
        // i+3 
        num = rem = i+3; cnt = 0;
        if(debug) cout << num << ": ";
        for(long j=2;j<max;j++){
            if(a[j] && num%j==0){
                rem /= j;
                if(debug) cout << j << " ";
                cnt++;
                if(rem<max && a[rem]==1) {
                    if(debug) cout << rem << " ";
                    cnt++; 
                    break;
                }
                if(rem==1) break;
            }
        }
        if(debug) cout << endl;
        if(cnt!=4) { i+=4 ; continue; }
        else { 
            cout << "### ANS: " << i << endl;
            break;
        }
    }
}

void euler48(){

    unsigned long sum = 1, tsum = 1, last = 0;

    for( int i = 2; i != 1000 ; i++ ){
        tsum = i; 
        for ( int j = 1; j < i ; j++ ) {
            last = tsum;
            tsum = ( tsum*i ) % 10000000000;
            if ( last == tsum ) break; 
        }
        sum = sum + tsum % 10000000000;
    }
    cout << sum << endl;
}

void euler243() {
    
    long max = 700000;
    int a[max];
    memset(a, 1, sizeof(int)*max);
    for (long i = 2; i < (max >> 1); ++i) {
        if (a[i]) {
            for (long j = i << 1; j < max; j += i)
                a[j] = 0;
        }
    }

    double less = 1;

    bool flag = true;
    double pro = 0;
    const double lim = 15499.0 / 94744.0;
    cout << "lim: " << lim << endl;
   
    long i = 892371480;
    while (1) {
        flag = true;
        if (i%10000==0) cout << "### " << i << endl;

        long den = i;
        double nen = i-1;
        long rem = i;

        //
        // PhiFunction
        // http://acm.nudt.edu.cn/~twcourse/Euler%27sPhiFunction.html
        //
        for(long j=2;j<max;j++){
            if(a[j] && i%j==0){
                den = den/j*(j-1);
                rem /= j;
                if(rem<max && a[rem]==1) {
                    den = den/rem*(rem-1);
                    break;
                }
                if(rem==1) break;
            }
        }

        double pro = den / nen;
        if ( flag && pro < lim ) {
            printf("Answer: %ld (%f) \n", i, pro);
            return;
        } 
        else {
            if ( less > pro ) {
                less = pro; 
                cout << i << " => " << less << endl;
            }
        }
        i++;
    }
}

void euler477(){

    int count=0;
    long sn = 0, pre = 0, p1 = 0; 
    printf("%d ", 0);
    for(int i = 1; i < 100;i++){
        pre = (pre * pre + 45 ) % 1000000007;
        printf("%ld ",pre);
        if ( i%2==1 ) p1+=pre;
    }
    printf("\n");
    printf("%ld\n",p1);
}

// ========================================================= //
// ========================================================= //
// ========================================================= //

int main(int argc, char** argv)
{
    struct timeval start, end;
    struct timezone tz;
    gettimeofday(&start, &tz);

    int num = 1; 
    if (argc == 2 ) num = atoi(argv[1]);

    euler49();

    gettimeofday(&end, &tz);
    printf("Time: %d ms\n", (end.tv_usec - start.tv_usec) / 1000);
    return 0;
}