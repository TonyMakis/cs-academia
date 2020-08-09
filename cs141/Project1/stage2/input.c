#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

int main() {
    char in, op1='~', op2='~', op3='~';
    int opsInputCount = 0;
    printf("\nEnter the three operators to be used (+,-,*, or /): ");
    while( in = getchar() ) {   
        if(in == '\n'|| in == '\0' || in == '\r') {
            opsInputCount != 3 ? 
                printf("\n*** Sorry, that input is the wrong length.  Please retry. ***\n") : 
                printf("\nThanks for entering values!\n");
            break;
        }
        else {
            opsInputCount = opsInputCount + 1;
            if(opsInputCount == 1)
                op1 = in;
            else if(opsInputCount == 2)
                op2 = in;
            else 
                op3 = in;
        }
    }
    return 0;
}
