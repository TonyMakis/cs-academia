#include "WinChecker.h"
#include <string>

WinChecker::WinChecker(int gameLevel, char gameBoard[]) {
    level = gameLevel;
    strncpy_s(board, gameBoard, 17);
}

// Checks if all the pieces in board at these positions are UpperCase
bool allAreUpperCase(int i, int j, int k, int l, char board[]) {
    return isupper(board[i]) && isupper(board[j]) &&
        isupper(board[k]) && isupper(board[l]);
}

// Checks if all the pieces in board at these positions are LowerCase
bool allAreLowerCase(int i, int j, int k, int l, char board[]) {
    return islower(board[i]) && islower(board[j]) &&
        islower(board[k]) && islower(board[l]);
}

// Checks if all the pieces in board at these positions are Consonants
bool allAreConsonants(int i, int j, int k, int l, char board[]) {
    char consonants[9] = "bcdfBCDF";
    return strchr(consonants, board[i]) && strchr(consonants, board[j]) &&
        strchr(consonants, board[k]) && strchr(consonants, board[l]);
}

// Checks if all pieces in board at these positions are Vowels
bool allAreVowels(int i, int j, int k, int l, char board[]) {
    char vowels[9] = "aeioAEIO";
    return strchr(vowels, board[i]) && strchr(vowels, board[j]) &&
        strchr(vowels, board[k]) && strchr(vowels, board[l]);
}

// Given four indeces and the board, check if there is a win!
bool groupIsWinner(int i, int j, int k, int l, char board[]) {
    return allAreUpperCase(i, j, k, l, board) || allAreLowerCase(i, j, k, l, board) ||
        allAreConsonants(i, j, k, l, board) || allAreVowels(i, j, k, l, board);
}

// Check the game board rows for wins
bool checkRows(char board[], int winIndeces[]) {
    int rowStart = 0;            // Index of the first element in a row on board
    for (int i = 0; i < 4; i++) { // For each of the 4 rows . . .
        // . . . check the whole row
        if (groupIsWinner(rowStart, rowStart + 1, rowStart + 2, rowStart + 3, board)) {
            winIndeces[0] = rowStart;
            winIndeces[1] = rowStart + 1;
            winIndeces[2] = rowStart + 2;
            winIndeces[3] = rowStart + 3;
            return 1;
        }
        rowStart += 4;
    }
    return 0;
}

// Check the game board columns for wins
bool checkCols(char board[], int winIndeces[]) {
    for (int i = 0; i < 4; i++) { // For each of the 4 cols . . .
        // . . . check whole col
        if (groupIsWinner(i, i + 4, i + 8, i + 12, board)) {
            winIndeces[0] = i;
            winIndeces[1] = i + 4;
            winIndeces[2] = i + 8;
            winIndeces[3] = i + 12;
            return 1;
        }
           
    }
    return 0;
}

// Check game board diagonals for wins
bool checkDiags(char board[], int winIndeces[]) {
    if (groupIsWinner(0, 5, 10, 15, board)) {
        winIndeces[0] = 0;
        winIndeces[1] = 5;
        winIndeces[2] = 10;
        winIndeces[3] = 15;
        return 1;
    }
    if (groupIsWinner(3, 6, 9, 12, board)) {
        winIndeces[0] = 3;
        winIndeces[1] = 6;
        winIndeces[2] = 9;
        winIndeces[3] = 12;
        return 1;
    }

    return 0;
}

// Check game board corners for wins
bool checkCorners(char board[], int winIndeces[]) {
    if (groupIsWinner(0, 3, 12, 15, board)) {
        winIndeces[0] = 0;
        winIndeces[1] = 3;
        winIndeces[2] = 12;
        winIndeces[3] = 15;
        return 1;
    }
    return 0;
}

// Check groups of four pieces on the game board for wins (i.e. clusters)
bool checkClusters(char board[], int winIndeces[]) {
    for (int i = 0; i < 11; i++) {
        if ((i + 1 % 4) == 0) continue;
        if (groupIsWinner(i, i + 1, i + 4, i + 5, board)) {
            winIndeces[0] = i;
            winIndeces[1] = i + 1;
            winIndeces[2] = i + 4;
            winIndeces[3] = i + 5;
            return 1;
        }
    }
    return 0;
}

// Use all the check functions above to spot a win on the board, based on 
// gameplay level currently set
bool WinChecker::checkWinners() {
    if (level == 1) {
        return checkRows(board, winningIndeces) || checkCols(board, winningIndeces) || checkDiags(board, winningIndeces);
    }
    else {
        return checkRows(board, winningIndeces) || checkCols(board, winningIndeces) || checkDiags(board, winningIndeces) ||
            checkCorners(board, winningIndeces) || checkClusters(board, winningIndeces);
    }
}
