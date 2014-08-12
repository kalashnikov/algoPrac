#include<stdio.h>

int main(){
    int c;
    system("stty raw");
    c = getchar();
    system("stty cooked");
    printf("\nget:%c\n",c);
    return 0;
}
