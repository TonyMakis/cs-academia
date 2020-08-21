#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void clearScrn() {
    printf("\e[1;1H\e[2J");
}

// Wipe the string passed into this function, making it all '\0' characters
// Also rewrites the '\0' character after the array, for good measure.
void clearString(char str[], int strSize) {
    for(int i = 0; i <= strSize; i++) {
        str[i] = '\0';
    }
}


void printGameEntryInfo() {
    clearScrn();
    printf(
        "Author: Anthony Makis\n"
        "Program: #4, DoubleDown\n\n"

        "Welcome to the game of DoubleDown, where you try to complete a set of\n"
        "four pieces that are alike. Players take turns making moves. On each\n"
        "move your OPPONENT chooses the piece, then YOU get to place it on the\n"
        "board. If you create a set of four alike when you place your piece, then\n"
        "you win! A set of four alike can be completed by using four upper case\n"
        "characters, four lower-case characters, four vowels (a,e,i,o,u) or four\n"
        "consonants.\n\n"

        "The game level determines which positions can be used in completing four\n"
        "alike pieces.  Level one checks for four alike in every row, column, and\n"
        "diagonal. Level two additionally checks for the pieces in the four corners\n"
        "as well as each cluster of four in each corner.\n\n"
        
        "When prompted for piece to use you may also:\n"                      
        "\tEnter 's' to change program level.\n"                      
        "\tEnter 'x' to exit the program.\n\n\n"
    );
}

int main() {
    printGameEntryInfo();
    return 0;
}