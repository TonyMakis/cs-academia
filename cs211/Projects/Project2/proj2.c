#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack { 
    char* symbols;
    int size;
    int top;
};

void initStack(struct stack* s) {
    s->symbols = (char*)malloc(2 * sizeof(char));
    s->size = 2;
    s->top = 0;
}

void resetStack(struct stack* s) {
    free(s->symbols);
    initStack(s);
}

int symbolIsOpen(char symbol) { 
    return symbol == '(' || symbol == '<' || symbol == '[' || symbol == '{'; 
}

int symbolIsClose(char symbol) { 
    return symbol == ')' || symbol == '>' || symbol == ']' || symbol == '}'; 
}

int symbolsAreBalanced(char symbol, char topOfStackSymbol) {
    return (symbol == ')' && topOfStackSymbol == '(') ||
           (symbol == '>' && topOfStackSymbol == '<') ||
           (symbol == ']' && topOfStackSymbol == '[') ||
           (symbol == '}' && topOfStackSymbol == '{');
}

int stackIsEmpty(struct stack* s) { return s->top == 0; }

int stackIsFull(struct stack* s) { return s->top >= s->size; }

char getTopSymbol(struct stack* s) { return s->symbols[s->top - 1]; }

void grow(struct stack* s, int debugMode) {
    // Make new array of size 2 greater than the current size
    char *newS = (char*)malloc((s->size + 2) * sizeof(int));
    // Copy old stack array symbols to new stack array
    for (int i = 0; i < s->top; i++) newS[i] = s->symbols[i];
    // Free old stack memory, then set new size
    free(s->symbols);
    s->symbols = newS;
    s->size += 2;
    if(debugMode) 
        printf("\tStack size grew from (old) %d to (new) %d, copying %d values over!\n",
            s->size - 2, s->size, s->top);
}

void push(struct stack* s, char symbol, int debugMode) {
    if(stackIsFull(s)) grow(s, debugMode);
    s->symbols[s->top] = symbol;
    (s->top)++;
    if(debugMode) printf("\t\"%c\" just got pushed onto the stack!\n", symbol);
}

void pop(struct stack* s, int debugMode) {
    char poppedSymbol = getTopSymbol(s);
    s->symbols[s->top - 1] = '\0';
    (s->top)--;
    if(debugMode) printf("\t\"%c\" just got popped from the stack!\n", poppedSymbol);
}

char getRelatedSymbol(char symbol) {
    char openSymbols[4] = {'(', '<', '[', '{'};
    char closeSymbols[4] = {')', '>', ']', '}'};

    if(symbolIsOpen(symbol)) {
        for(int i = 0; i < 4; i++) {
            if(symbol == openSymbols[i]) return closeSymbols[i];
        }
    } else {
        for(int i =0; i < 4; i++) {
            if(symbol == closeSymbols[i]) return openSymbols[i];
        }
    }
}

void missingSymbolHandler(int problemIndex, char problemSymbol) {
    for(int i = 0; i < problemIndex; i++) printf(" ");
    printf("^ missing %c\n\n", getRelatedSymbol(problemSymbol));
}

void expectingOtherSymbolHandler(int problemIndex, char problemSymbol) {
    for(int i = 0; i < problemIndex; i++) printf(" ");
    printf("^ expecting %c\n\n", getRelatedSymbol(problemSymbol));
}

int checkExpressionBalance(struct stack* s, const char line[], int debugMode) {
    int len = strlen(line) - 1, i;
    char symbol;
    for(i = 0; i < len; i++) {
        symbol = line[i];
        if(symbolIsOpen(symbol)) push(s, symbol, debugMode);
        if(symbolIsClose(symbol)) {
            if(stackIsEmpty(s)) { // Missing opening symbol
                missingSymbolHandler(i, symbol);
                return 0;
            }
            else if(symbolsAreBalanced(symbol, getTopSymbol(s))) pop(s, debugMode);
            else {                // Closing Symbol is wrong one, expecting another
                expectingOtherSymbolHandler(i, getTopSymbol(s));
                return 0;
            }
        }
    }

    if(!stackIsEmpty(s)) { // Missing closing symbol at the end
        missingSymbolHandler(i, getTopSymbol(s));
        return 0;
    }

    return 1;
}

int main(int argc, char **argv) {
    int debugMode = argc > 1 && strcmp(argv[1], "-d") == 0; // Set debug mode
    int TRUE = 1, balanced;

    const int MAX_LENGTH = 300;
    char line[MAX_LENGTH];   // An input line with some number of symbols on it

    // Create an instance of a stack
    // At first, stack has defaults => size is 2, top is at index 0, symbols is empty
    struct stack* s = (struct stack*)malloc(sizeof(struct stack));
    initStack(s);

    printf("\nPlease enter expressions for me to assess below:\n\n");
    fgets(line, MAX_LENGTH, stdin);

    while(TRUE) {
        if(line[0] == 'q' || line[0] == 'Q') break;
        if(checkExpressionBalance(s, line, debugMode)) 
            printf("Expression is balanced\n\n");
        resetStack(s);
        fgets(line, MAX_LENGTH, stdin);
    }

    free(s->symbols);   // Clean up dynamic stack array alloc
    free(s);            // Clean up dynamic stack alloc

    return 0;
}