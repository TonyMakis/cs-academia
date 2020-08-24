#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

void printGameEntryInfo() {
    cout <<
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
        "\tEnter 'x' to exit the program.\n";
}

// Prints a given row of the game board
void printBoardRow(const char board[], int row) {
    cout << "| ";
    // Get the index of the start of the row using a lil' hash
    int rowIndexStart = (row - 1) * 4;
    int rowIndexEnd = rowIndexStart + 4;
    for(int i = rowIndexStart; i < rowIndexEnd; i++) {
        cout << board[i] << " ";
    }
    cout << "|";
}

// Prints available pieces for players to choose
void printPieces(const char pieces[]) {
    for(int i = 0; i < 16; i++) {
        cout << pieces[i];
        // print a space after every four characters
        if( (i + 1) % 4 == 0) {
            cout << " ";
        }
    }
}

// Use @printPieces and @printBoardRow to display the game board
void showBoardInfo(const char board[], const char pieces[]) {
    cout << endl << endl;
    cout << "|---------|   Square #" << endl;
    printBoardRow(board, 1);
    cout << "  1  2  3  4" << endl;
    printBoardRow(board, 2);
    cout << "  5  6  7  8" << endl;
    printBoardRow(board, 3);
    cout << "  9 10 11 12" << endl;
    printBoardRow(board, 4);
    cout << " 13 14 15 16" << endl;
    cout << "|---------|" << endl;
    cout << "    Pieces:  ";
    printPieces(pieces);
    cout << endl << endl;
}

// Depending on the move number, when called, shows winner
void printWinMessage(int move) {
    cout << endl << "*** Congratulations! ***  Player ";
    (move - 1) % 2 == 0 ? 
        cout << "2 wins the game!" << endl << endl :
        cout << "1 wins the game!" << endl << endl;
}

// Depending on the movie number, when called, shows the player entry info
void displayEntryPrompt(int move) {
    (move % 2 != 0) ? 
        cout << move << ". Player 2 enter piece, and Player 1 enter destination: " : 
        cout << move << ". Player 1 enter piece, and Player 2 enter destination: ";
}

// Check that the piece entered is valid in the context of the game 
bool isValidPiece(const char piece, const char pieces[]) {
    if( strchr(pieces, piece) ) {
        return 1;
    } else {
        cout << "*** " << piece << " is an invalid piece selection." << endl;
        cout << "Please retry move.";
        return 0;
    }
}

// Check that the numeric destination entered is valid in the context of the game 
bool isValidDest(const int dest, const char board[]) {
    if (dest >= 1 && dest <= 16) {
        if(board[dest - 1] == '.') {
            return 1;
        } else {
            cout << "   *** Board square " << dest << " is not empty." << endl;
            cout << "   Please retry move.";
            return 0;
        }
    } else {
        cout << "   *** Board square " << dest << " doesn't exist." << endl;
        cout << "   Please retry move.";
        return 0;
    }
}

// Use @isValidPiece and @isValidDest to check user input (piece, dest)
bool entriesAreValid(const char piece, const char pieces[], 
                     const char dest, const char board[]) {
    return isValidPiece(piece, pieces) && isValidDest(dest, board);
}

// Checks if all the pieces in board at these positions are UpperCase
bool allAreUpperCase(int i, int j, int k, int l, const char board[]) {
    return isupper(board[i]) && isupper(board[j]) && 
           isupper(board[k]) && isupper(board[l]);
}

// Checks if all the pieces in board at these positions are LowerCase
bool allAreLowerCase(int i, int j, int k, int l, const char board[]) {
    return islower(board[i]) && islower(board[j]) && 
           islower(board[k]) && islower(board[l]);
}

// Checks if all the pieces in board at these positions are Consonants
bool allAreConsonants(int i, int j, int k, int l, const char board[]) {
    char consonants[9] = "bcdfBCDF";
    return strchr(consonants, board[i]) && strchr(consonants, board[j]) && 
           strchr(consonants, board[k]) && strchr(consonants, board[l]);
}

// Checks if all pieces in board at these positions are Vowels
bool allAreVowels(int i, int j, int k, int l, const char board[]) {
    char vowels[9] = "aeioAEIO";
    return strchr(vowels, board[i]) && strchr(vowels, board[j]) && 
           strchr(vowels, board[k]) && strchr(vowels, board[l]);
}

// Given four indeces and the board, check if there is a win!
bool groupIsWinner(int i, int j, int k, int l, const char board[]) {
    return allAreUpperCase(i, j, k, l, board) || allAreLowerCase(i, j, k, l, board) || 
           allAreConsonants(i, j, k, l, board) || allAreVowels(i, j, k, l, board);
}

// Check the game board rows for wins
bool checkRows(const char board[]) {
    int rowStart = 0;            // Index of the first element in a row on board
    for(int i = 0; i < 4; i++) { // For each of the 4 rows . . .
        // . . . check the whole row
        if(groupIsWinner(rowStart, rowStart + 1, rowStart + 2, rowStart + 3, board))
            return 1;
        rowStart += 4;
    }
    return 0;
}

// Check the game board columns for wins
bool checkCols(const char board[]) {
    for(int i = 0; i < 4; i++) { // For each of the 4 cols . . .
        // . . . check whole col
        if(groupIsWinner(i, i + 4, i + 8, i + 12, board))
            return 1;
    }
    return 0;
}

// Check game board diagonals for wins
bool checkDiags(const char board[]) {
    return groupIsWinner(0, 5, 10, 15, board) || 
           groupIsWinner(3, 6, 9, 12, board);
}

// Check game board corners for wins
bool checkCorners(const char board[]) {
    return groupIsWinner(0, 3, 12, 15, board);
}

// Check groups of four pieces on the game board for wins (i.e. clusters)
bool checkClusters(const char board[]) {
    for(int i = 0; i < 11; i++) {
        if( (i + 1 % 4) == 0) continue;
        if(groupIsWinner(i, i + 1, i + 4, i + 5, board))
            return 1;
    }
    return 0;
}

// Use all the check functions above to spot a win on the board, based on 
// gameplay level currently set
bool checkWinners(int level, const char board[]) {
    if(level == 1) {
        return checkRows(board) || checkCols(board) || checkDiags(board);
    } else {
        return checkRows(board) || checkCols(board) || checkDiags(board) ||
               checkCorners(board) || checkClusters(board);
    }
}

// Called when a piece is used by any player, to remove it from the list 
// of playable pieces
void removeUsedPiece(const char piece, char pieces[]) {
    for(int i = 0; i < 16; i++) {
        if(pieces[i] == piece) {
            pieces[i] = ' ';
            break;
        }
    }
}

int main() {
    char pieceEntry;
    int destEntry, playLevel = 1, moveNum = 1;
    bool stillPlaying = true;
    char board[17] = "................";
    char pieces[17] = "AEIOaeioBCDFbcdf";
    printGameEntryInfo();
    do {
        showBoardInfo(board, pieces);
        // If the current board has a winning sequence, print winner and exit
        if(checkWinners(playLevel, board)) {
            printWinMessage(moveNum);
            stillPlaying = false;
            break;
        }
        // No winners yet, so:
        displayEntryPrompt(moveNum);
        cin >> pieceEntry;
        if(pieceEntry == 's') {         // Change the gameplay level
            cout << endl << "What level of play would you like? ";
            cout << "1: Normal, 2: Add corners & groups --> ";
            cin >> playLevel;
            // If there is a win immediately from changing level, don't actually change it
            if(checkWinners(playLevel, board)) {
                cout << "Sorry, changing level would lead to a pre-existing win.";
                cout << endl << "Resetting the level to level 1.";
                playLevel = 1;
            }
            else
                cout << "Level of play set to " << playLevel;
        } else if(pieceEntry == 'x') {  // Exit the program
            cout << endl << "Thanks for playing! Exiting . . . " << endl << endl;
            stillPlaying = false;
        } else {                        // Play the piece entered at destination entered
            cin >> destEntry;
            if(entriesAreValid(pieceEntry, pieces, destEntry, board)) { // Are the piece/dest. valid?
                board[destEntry - 1] = pieceEntry;    // Update board with piece
                removeUsedPiece(pieceEntry, pieces);  // Piece no longer valid to use
                moveNum++;                            // Time for the next move
            }
        }
    } while(stillPlaying);
    cout << "Done." << endl << endl;
    return 0;
}