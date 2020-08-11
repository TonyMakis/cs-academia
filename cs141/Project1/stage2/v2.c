#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <math.h>

#define NUM_GAME_WHEELS 6
#define NUM_MATH_OPS 4
#define TRUE 1
#define FALSE 0

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

/* This ensures that any characters remaining in stdin are cleared,
 * as any chars still in stdin will affect later input prompts
 */
void clearInputBuffer() {
    while ((getchar()) != '\n');
}

void printGameEntryInfo() {
    clearScrn();
    printf("Author: Anthony Makis\n");
    printf("Program: #1, TwentyFour\n");
    printf("\n");
    printf("Welcome to the game of TwentyFour. Using each of the four numbers shown\n");
    printf("below exactly once, combine them somehow with the basic mathematical\n");
    printf("operators (+,-,*,/) to yield the value twenty-four.\n");
    printf("\n");
}

// This function is UNUSED in the program, but useful to visualize all 6
// of the hardcoded wheels
void printNumberWheels(struct NumWheel wheels[]) {
    int i = 0;

    // If I ever need to automate capturing number of wheels:
    // => size_t numWheels = sizeof(wheels)/sizeof(wheels[0]);

    printf("\n");
    for(i = 0; i < NUM_GAME_WHEELS; i++) {
        printf("  %d      ", wheels[i].top);
    }
    printf("\n");
    for(i = 0; i < NUM_GAME_WHEELS; i++) {
        printf("%d   %d    ", wheels[i].left, wheels[i].right);
    }
    printf("\n");
    for(i = 0; i < NUM_GAME_WHEELS; i++) {
        printf("  %d      ", wheels[i].bottom);
    }
    printf("\n");
}

// => @return: a random number between @lower and @upper
int rando(int lower, int upper) {
    return ( rand() % (upper - lower + 1) ) + lower;
}

// Extracts the 4 digits of a 4-digit number
// @param: num => the 4-digit number
// @param: d1, d2, d3, d4 => the four digits we extract
void extractDigits(int num, int *d1, int *d2, int *d3, int *d4) {
    *d4 = num % 10;
    num = num / 10;
    *d3 = num % 10;
    num = num / 10;
    *d2 = num % 10;
    num = num / 10;
    *d1 = num % 10;
}

// Simply ensures that there aren't any zeros in the numbers for the game
int anyDigitsZero(int n1, int n2, int n3, int n4) {
    return ( n1 == 0 || n2 == 0 || n3 == 0 || n4 == 0 );
}

// Given an operator, a float and an int, perform desired operation;
// => @return: = value calculated
float performSingleOp(float first, char op, int second) {
    float retValue = 0.0;
    if(op == '+') {
        retValue = first + second;
    } else if(op == '-') {
        retValue = first - second;
    } else if(op == '*') {
        retValue = first * second;
    } else {
        retValue = first / second;
    }
    return retValue;
}

/* A wrapper for @performSingleOp; facilitates solving of all operations of given puzzle
 * => @param printSteps: a flag, allow / repress printing operations as they occur
 * => @return: the final value as a result of the 3 operations on the 4 numbers
 */
float performAllOps(char op1, char op2, char op3, int d1, int d2, int d3, int d4, int printSteps) {
    float firstOpVal = performSingleOp(d1 * 1.0, op1, d2);
    if(printSteps) printf("%.1f %c %d is: %.1f\n", d1 * 1.0, op1, d2, firstOpVal);

    float secondOpVal = performSingleOp(firstOpVal, op2, d3);
    if(printSteps) printf("%.1f %c %d is: %.1f\n", firstOpVal, op2, d3, secondOpVal);

    float finalValue = performSingleOp(secondOpVal, op3, d4);
    if(printSteps) printf("%.1f %c %d is: %.1f\n", secondOpVal, op3, d4, finalValue);

    return finalValue;
}

void printSolutions(int chosenSolution,
                        char *opChoice1, char *opChoice2, char *opChoice3,
                        int *dChoice1, int*dChoice2, int *dChoice3, int *dChoice4) {
    char ops[NUM_MATH_OPS] = {'+', '-', '*', '/'};
    int d1, d2, d3, d4;
    int solutionNum = 1;
    float finalResult;

    printf("All possible solutions are:\n");
    // We loop through all possible number combos . . .
    //      And then all possibilities for the first operand . . .
    //          And then all possibilities for the second operand . . .
    //              And finally all possiblilities for the third operand
    for(int curNum = 1111; curNum <= 9999; curNum++) {
        for(int outerOp = 0; outerOp < NUM_MATH_OPS; outerOp++) {
            for(int midOp = 0; midOp < NUM_MATH_OPS; midOp++) {
                for(int innerOp = 0; innerOp < NUM_MATH_OPS; innerOp++) {
                    extractDigits(curNum, &d1, &d2, &d3, &d4);
                    if(anyDigitsZero(d1, d2, d3, d4)) {
                        // We only want to use solutions w/ numbers in the range 1-9 
                        // => NOT 0, so skip this curNum 
                        continue;
                    }
                    finalResult = performAllOps(ops[outerOp], ops[midOp], ops[innerOp], 
                                  d1, d2, d3, d4, FALSE);
                    // If the curNum happens to be the randomly chosen solution, get its info.
                    if(solutionNum == chosenSolution) {
                        *opChoice1 = ops[outerOp];
                        *opChoice2 = ops[midOp];
                        *opChoice3 = ops[innerOp];
                        *dChoice1 = d1;
                        *dChoice2 = d2;
                        *dChoice3 = d3; 
                        *dChoice4 = d4;
                    }
                    
                    if(finalResult == 24.0) {
                        printf("%d: %d%c%d%c%d%c%d\n", 
                               solutionNum, d1, ops[outerOp], d2, ops[midOp], d3, ops[innerOp], d4);
                        // On to finding the next solution!
                        solutionNum = solutionNum + 1;
                    }
                }
            }
        }
    }
}

// Check if op matches one of our desired ops
int isOpValidChar(char op) {
    return ( op == '+' || op == '-' || op == '*' || op == '/' );
}

// Check if 3 operators are all valid
int areAllOpsValidChars(char op1, char op2, char op3) {
    return ( isOpValidChar(op1) && isOpValidChar(op2) && isOpValidChar(op3) );
}

// Input checking, and handling of bad input
void validateOps(char *op1, char *op2, char *op3, int *verified, int numOpsEntered) {
    if(numOpsEntered == 3) {
        if(!areAllOpsValidChars(*op1, *op2, *op3)) {
            printf("*** Sorry, invalid characters in input.  Please retry. ***");
            *verified = FALSE;
        } else {
            *verified = TRUE;
        }
    } else {
        printf("*** Sorry, that input is the wrong length.  Please retry. ***");
        *verified = FALSE;
    }
}

// Ask user for 3 operators choice, and set them in params:
// => @param: op1, op2, op3 -> 3 empty operators to fill from user input
// => @param: verified -> set whether or not all the ops entered are valid
void promptForOperators(char *op1, char *op2, char *op3, int *verified) {
    char in;
    int numOpsEntered = 0;
    printf("\nEnter the three operators to be used (+,-,*, or /): ");
    while( in = getchar() ) {   
        if(in == '\n'|| in == '\0' || in == '\r') {
            break;
        } else {
            // Found a user-entered operator
            numOpsEntered = numOpsEntered + 1;
            if(numOpsEntered == 1)
                *op1 = in;
            else if(numOpsEntered == 2)
                *op2 = in;
            else 
                *op3 = in;
        }
    }
    validateOps(op1, op2, op3, verified, numOpsEntered);
}

// Show user the puzzle, get their input, verify their input, and play out the puzzle
float playGame(char op1, char op2, char op3, int n1, int n2, int n3, int n4) {
    printf("The numbers to use are: %d, %d, %d, %d\n", n1, n2, n3, n4);
    // Flag to ensure ops are valid
    int opsVerified;
    do {
        promptForOperators(&op1, &op2, &op3, &opsVerified);
    } while(!opsVerified);
    return performAllOps(op1, op2, op3, n1, n2, n3, n4, TRUE);
}

// Based on current debug_mode and result, we print win/loss results
void showGameResults(float result, char op1, char op2, char op3, 
                     int n1, int n2, int n3, int n4, int debug_mode) {
    if(debug_mode) { 
        if(result == 24.0) { 
            printf("\nWell done, genius!\n");
        } else {
            printf("\nSorry, that was not correct.");
            printf("The correct answer was: %d%c%d%c%d%c%d\n", 
                   n1, op1, n2, op2, n3, op3, n4);
        }
    } else {
        result == 24.0 ?
            printf("\nWell done, genius!\n") : printf("\nAlmost there, maybe next time!\n");
    }
}

int main() {
    // Setup given number wheels for non-debug mode gameplay
    struct NumWheel nw1 = {8, 5, 8, 1};
    struct NumWheel nw2 = {6, 1, 5 ,1};
    struct NumWheel nw3 = {2, 8, 7, 8};
    struct NumWheel nw4 = {3, 9, 4, 1};
    struct NumWheel nw5 = {5, 2, 9, 2};
    struct NumWheel nw6 = {2, 6, 8, 4};

    // Array to hold all the wheels
    struct NumWheel wheels[NUM_GAME_WHEELS] = {nw1, nw2, nw3, nw4, nw5, nw6}; 

    // Keep track of user's desire to play a.k.a. run the game loop
    char runAgain;
    // Change from running the game to printing it's solutions
    int debug_mode = TRUE;
    // This will store the result of user-input operation on the selected puzzle
    float endResult;
    // Seed random generator used in @rando by system time for better random effect =>
    srand(time(0)); 

    /* @randomNum will have 1 of 2 contexts, depending on the debug_mode we are in:
     * -> 1.) In Debug Mode, Random Number => one of the 3185 solutions
     * -> 2.) In NOT Debug Mode, Random Number => one of the hardcoded wheels
     */
    int randomNum;
    // Ops entered by user will be held in these:
    char userOp1, userOp2, userOp3;
    /* @num<x> will have 1 of 2 contexts, again depending on debug_mode:
     * -> 1.) In Debug Mode, nums => integers from one of the 3185 solutions
     * -> 2.) In NOT Debug Mode, nums => integers from one of the hardcoded wheels
     */
    int num1, num2, num3, num4;

    do {
        printGameEntryInfo();

        if(debug_mode) {
            printf("*** Start Debug Display ***\n");
            // Ops from randomly chosen solution will be held in these:
            char solutionOp1, solutionOp2, solutionOp3;
            randomNum = rando(1,3185);

            // While generating the possible solutions (3,185), the ops / digits 
            // that make up the randomly chosen solution will be set as well,
            // via reflecting changes to the arguments
            printSolutions(randomNum,
                           &solutionOp1, &solutionOp2, &solutionOp3,
                           &num1, &num2, &num3, &num4);
            printf("Puzzle to choose is #%d: %d%c%d%c%d%c%d\n", 
                    randomNum, 
                    num1, solutionOp1, num2, solutionOp2, num3, solutionOp3, num4);
            printf("*** End Debug Display ***\n\n");

            endResult = playGame(userOp1, userOp2, userOp3, num1, num2, num3, num4);
            showGameResults(endResult, solutionOp1, solutionOp2, solutionOp3,
                            num1, num2, num3, num4, debug_mode);
        } else {
            randomNum = rando(0,5);
            num1 = wheels[randomNum].bottom;
            num2 = wheels[randomNum].left;
            num3 = wheels[randomNum].top;
            num4 = wheels[randomNum].right;
            endResult = playGame(userOp1, userOp2, userOp3, num1, num2, num3, num4);
            showGameResults(endResult, userOp1, userOp2, userOp3,
                            num1, num2, num3, num4, debug_mode);    
        }
        // Uncomment the following line if you would like to see the wheels, printed out:
        // printNumberWheels(wheels);

        printf("\nWould you like to play again (Y/N): ");
        runAgain = getchar();
        clearInputBuffer();
    } while(runAgain == 'Y' || runAgain == 'y');

    return 0;
}
