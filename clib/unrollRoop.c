
// 
// Unrolling a loop in C.
//
// AKA: Duff's device
// Ref: http://www.azillionmonkeys.com/qed/case2.html
// Ref: http://www.lysator.liu.se/c/duffs-device.html 
//

#include <stdio.h>

void InnerLoop(int i)
{
    printf("%d ",i);
}

void Procedure1(unsigned int Len) {
    int i;
    for (i = 0; i < Len; i++) {
        InnerLoop (i);
    }
    printf("\n");
}

void Procedure2(unsigned int Len) {
    int i;
    if (Len == 0) return;

    i = ((Len - 1) & 7) - 7;

//    printf("[i:%d]",i);
    switch (-i) {
        do {
            case 0: InnerLoop (i + 0);
            case 1: InnerLoop (i + 1);
            case 2: InnerLoop (i + 2);
            case 3: InnerLoop (i + 3);
            case 4: InnerLoop (i + 4);
            case 5: InnerLoop (i + 5);
            case 6: InnerLoop (i + 6);
            case 7: InnerLoop (i + 7);
                    i += 8;
//                    printf("\n[i:%d]",i);
        } while (i < Len);
    }
    printf("\n");
}

int main(int argc, char** argv)
{
    if(argc==1) return 1;

    int len;
    sscanf(argv[1], "%d", &len);

    Procedure1(len);        
    Procedure2(len);        

    return 0;
}
