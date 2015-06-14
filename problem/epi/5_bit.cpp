#include<iostream>
#include<bitset>
#include<algorithm>
#include<random>
#include<cstring>

using namespace std;

// CCI 17.1 Swap number without temparary variables
void swap1(int& a, int& b){
    if ( b > a ) return swap1(b, a);
    cout << a << " " << b << endl;
    a = a - b;
    b = a + b;
    a = b - a;
    cout << a << " " << b << endl;
}
void swap2(int& a, int& b){ 
    cout << a << " " << b << endl;
    a = a ^ b;
    b = a ^ b;
    a = b ^ a;
    cout << a << " " << b << endl;   
}

unsigned int check_1(unsigned int b){
    int n;
    for(n=0; b; n++) b &= b-1;
    return n;
}

// 5.1 Parity Check (Brute-force)
short pp(unsigned long x){

    short result = 0;
    while(x){
        result ^= 1;
        x &= (x-1);
    }
    return result;
}

// 5.1 Parity 
const int lookTable = 0x6996; // 0b0110100110010110
short Parity(unsigned long x){
    x ^= x >> 32;
    cout << (bitset<64>) x << endl;
    x ^= x >> 16;
    cout << (bitset<64>) x << endl;
    x ^= x >> 8;
    cout << (bitset<64>) x << endl;
    x ^= x >> 4;
    cout << (bitset<64>) x << endl;
    x &= 0xf;
    cout << (bitset<64>) x << endl;
    return ( lookTable >> x ) & 1 ;
}

// 5.7 Compute x^y
double powerXY(double x, int y){
    double result = 1.0;
    long long power = y; 
    if ( y < 0 ) { 
        power = -power;
        x = 1.0 / x; 
    }
    // 1010  r    x 
    //  101  1    x^2
    //   10  x^2  x^4 
    //    1  x^2  x^8
    //    0  x^10 x^16 
    while ( power ) { 
        if ( power & 1 ) { 
            result *= x; 
        }
        x *= x, power >>= 1;
    }
    return result;
}

// 5.8
string convertBase(const string& s, int b1, int b2) { 
    bool is_negative = s.front() == '-';
    int x = 0;
    for (size_t i = (is_negative == true ? 1 : 0); i < s.size(); ++i){
        x *= b1;
        x += isdigit(s[i]) ? s[i] - '0' : s[i] - 'A' + 10; 
    }

    string result; 
    do { 
        int reminder = x % b2; 
        result.push_back(reminder > 10 ? 'A' + reminder - 10 : '0' + reminder);
        x /= b2; 
    } while (x);

    if (is_negative) {
        result.push_back('-');
    }
    reverse(result.begin(), result.end());
    return result;
}


// Random generator for 0/1
int zero_one_random(){
    // Random
    const int NUM = 10000;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, NUM);
    return (dis(gen)/5000);
}

// 5.12 Generate random integer between a, b 
// Based on random generator for 0/1
int uniform_random(int a, int b){
    int t = b - a + 1, res;
    do { 
        res = 0;
        for ( int i=0; (1<<i) < t; ++i) {
            res = (res * 2) | zero_one_random();
            cout << "res: " << res << endl;
        }
    } while ( res >= t);
    return res + a;
}

// CCI 17.11 - Implement rand7() by rand5()
int rand5(){
    // Random
    const int NUM = 10000;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 5);
}
int rand7(){
    while(true){
        int num = 5 * rand5() + rand5();
        if ( num < 21 ) {
            return num % 7;
        }
    }
}

int main(){
    unsigned long in = 232532232632532;
    cout << (bitset<64>) in << endl;
    Parity(in);

    unsigned int s = 2345;
    cout << (bitset<32>) s << endl;
    cout << pp(s) << endl;
    cout << check_1(s) << endl;

    cout << uniform_random(100,999) << endl;

    int a = 23523, b = 94725;
    swap1(a, b);
    swap2(b, a);
    return 0;
}
