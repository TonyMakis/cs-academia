#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

// @NumWheel is a struct to store numbers in an organized way
/*
 * I compared memory usage btwn. an array and a struct for this;
 * I found that they both take up same amount of apace in memory:
 * 
 * -- int n[4] = {8, 5, 8, 1}        => sizeof(n))  => 16 bytes
 * -- struct NumWheel nw = {8,5,8,1} => sizeof(nw)) => 16 bytes
 * 
 * Therefore, I chose a struct since it helps with visualizing
 * the data's physical appearance more so than an array does.
 */
struct NumWheel 
{ 
   int bottom, left, top, right;
};  

void clearScrn() {
    printf("\e[1;1H\e[2J");
}

void printGameEntryInfo() {
    clearScrn();
    printf("Author: Anthony Makis\n");
    printf("Program: #1, TwentyFour\n");
    printf("\n");
    printf("Welcome to the game of TwentyFour.  Using each of the four numbers shown\n");
    printf("below exactly once, combine them somehow with the basic mathematical\n");
    printf("operators (+,-,*,/) to yield the value twenty-four.\n");
    printf("\n");
}

// This function is UNUSED in the program, but nice to visualize all the wheels
void printNumberWheels(struct NumWheel wheels[]) {
    int i = 0;

    // If I ever need to automate capturing number of wheels:
    // => size_t numWheels = sizeof(wheels)/sizeof(wheels[0]);

    printf("\n");
    for(i = 0; i < 6; i++) {
        printf("  %d      ", wheels[i].top);
    }
    printf("\n");
    for(i = 0; i < 6; i++) {
        printf("%d   %d    ", wheels[i].left, wheels[i].right);
    }
    printf("\n");
    for(i = 0; i < 6; i++) {
        printf("  %d      ", wheels[i].bottom);
    }
    printf("\n");
}

// => @return: a random number between @lower and @upper
int rando(int lower, int upper) {
    return ( rand() % (upper - lower + 1) ) + lower;
}

// Ask user for 3 operators choice, and set them in params:
// => @params: op1, op2, op3 -> 3 empty operators to fill from user input
void promptForOperators(char *op1, char *op2, char *op3) {
    printf("\nEnter the three operators to be used (+,-,*, or /): ");
    scanf(" %c %c %c", op1, op2, op3);
}

// Given an operator, a float and an int, perform desired operation;
// => @return: the value calculated, and error check for bad operators
float performSingleOp(float first, char op, int second) {
    float retValue = 0.0;
    if(op == '+') {
        retValue = first + second;
    } else if(op == '-') {
        retValue = first - second;
    } else if(op == '*') {
        retValue = first * second;
    } else if(op == '/'){
        retValue = first / second;
    } else {
        fprintf(stderr, "\t\t\t\tFound bad operator: ^ %c\n\nExiting program . . .\n", op);
        exit(EXIT_FAILURE);
    }
    return retValue;
}

// A wrapper to facilitate the overall solution of user operations,
// printing out intermediate steps
// => @return: the final value as a result of the 3 operations on the number wheel
float performAllOps(struct NumWheel nw, char op1, char op2, char op3) {
    float currentValue = 0.0;
    currentValue = performSingleOp(nw.bottom * 1.0, op1, nw.left);
    printf("%.1f %c %d is: %.1f\n", nw.bottom * 1.0, op1, nw.left, currentValue);

    float newValue = performSingleOp(currentValue, op2, nw.top);
    printf("%.1f %c %d is: %.1f\n", currentValue, op2, nw.top, newValue);

    currentValue = newValue;
    newValue = performSingleOp(currentValue, op3, nw.right);
    printf("%.1f %c %d is: %.1f\n", currentValue, op3, nw.right, newValue);

    return newValue;
}

// Check if user was able to solve the number wheel
void printResult(float result) {
    if(result == 24.0) {
        printf("\nWell done, genius!\n");
    } else {
        printf("\nAlmost there, maybe next time!\n");
    }
}

// Ask if user would like to play again
// @param: runAgain -> a variable for stopping/continuing the while loop
//                     a 0 => done, a 1 => wants to play again
void checkToRunAgain(int *runAgain) {
    char decision;
    printf("\nWould you like to play again (Y/y or N/n): ");
    scanf(" %c", &decision);
    if(decision == 'N' || decision == 'n') {
        *runAgain = 0;
        printf("\nThanks for playing.  Exiting program...\n");
    } else {
        *runAgain = 1;
        clearScrn();
    }
}
 
int main() {
    // Setup given number wheels; 6 distinct wheels possible
    struct NumWheel nw1 = {8, 5, 8, 1};
    struct NumWheel nw2 = {6, 1, 5 ,1};
    struct NumWheel nw3 = {2, 8, 7, 8};
    struct NumWheel nw4 = {3, 9, 4, 1};
    struct NumWheel nw5 = {5, 2, 9, 2};
    struct NumWheel nw6 = {2, 6, 8, 4};

    // Array to hold all the wheels
    struct NumWheel wheels[6] = {nw1, nw2, nw3, nw4, nw5, nw6}; 

    // Keep track of user's desire to play a.k.a. run the game loop
    int runAgain = 0;

    do {
        // Seed random generator used in @rando by system time for better random effect =>
        srand(time(0)); 

        /* Use random generator to get an index of a wheel in @wheels;
         * There are only 6 wheels, so 0-5 are indeces 
         * => TODO: make it more dynamic so it runs independent
         *          of length of @wheels => take @wheels' length
        */
        int randWheel = rando(0,5);

        printGameEntryInfo();
        printf("The numbers to use are: %d, %d, %d, %d\n", wheels[randWheel].bottom,
                                                           wheels[randWheel].left,
                                                           wheels[randWheel].top,
                                                           wheels[randWheel].right);

        char op1, op2, op3; 
        promptForOperators(&op1, &op2, &op3);
        
        float endResult = performAllOps(wheels[randWheel], op1, op2, op3);
        printResult(endResult);

        checkToRunAgain(&runAgain);

        // Uncomment the following line if you would like to see the wheels, printed out:
        // printNumberWheels(wheels);
    } while(runAgain);
}
