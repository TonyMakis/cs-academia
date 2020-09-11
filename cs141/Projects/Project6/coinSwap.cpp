#include <iostream>
#include <string>

using namespace std;

// Global constants
const int BOARD_SIZE = 5;

/* Struct to layout a game move
 *  - moveNum   => The number of this move when displayed
 *  - movePiece => The piece used to make this move
 *  - nextMove  => Pointer to the next move made after this one
 *  - priorMove  => Pointer to the previous move made before this one
 */
struct move { 
    int     moveNum;
    string    board;
    move* priorMove;
};

void addNewMove(int moveNum, string board, struct move* &currentMove) {
    struct move* newMove = new struct move;
    newMove->moveNum = moveNum;
    newMove->board = board;
    newMove->priorMove = currentMove;
    currentMove = newMove;
}

void undoLatestMove(struct move* &currentMove) {
    struct move* delCurMove = currentMove;
    currentMove = currentMove->priorMove;
    delete delCurMove; 
}

void displayIdentifyingInformation() {
    cout << endl << "Author: Anthony Makis" << endl;
    cout << "Program: #6, CoinSwap Undo" << endl << endl;
}

void displayInstructions() {
    cout << "Welcome to the coin swap puzzle." << endl
         << "Make moves to solve the puzzle where the objective is to swap the" << endl
         << "place of the pieces on either side of the board.  X can only move" << endl
         << "to the right into an empty square, or can jump to the right over" << endl
         << "an O into an empty square. Conversely O can only move to the left" << endl
         << "into an empty square, or can jump to the left over an X into an" << endl
         << "empty square." << endl << endl
         << "For each move enter the source (1..5) and destination (1..5)." << endl
         << "Enter x to exit the program." << endl;
}

void printMoveList(struct move* latestMove) {
    struct move* iter = latestMove;
    while(iter != nullptr) {
        cout << iter->moveNum;
        if(iter->moveNum != 1) cout << "->";
        iter = iter->priorMove;
    }
}

void displayBoard(struct move* latestMove) {
    cout << endl << "   1 2 3 4 5\n" << "   ";
    for(int i = 0; i < BOARD_SIZE; i++) { cout << latestMove->board[i] << " ";}
    cout << "\tList: ";
    printMoveList(latestMove);
    cout << endl << endl;
}

// See if board pieces have finished being swapped.  This is the case when
// the left-most two pieces are both 'O' and the right-most two pieces are 'X'
bool notDone(string board) {
    return board[0]!='O' || board[1]!='O' || board[3]!='X' || board[4]!='X';
}

void promptForAndGetMove(string &board, int &moveNumber, int &source, 
                         int &destination, struct move* &currentMove) {
    char userInput;
    // Infinite loop to handle possible multiple undo of moves
    while(true) {
        cout << currentMove->moveNum << ". Enter source and destination: ";
        cin >> userInput;
        // See if user input of 0 was given to exit the program
        if( userInput == 'x') {
            cout << "\n";
            cout << "Exiting program...\n";
            exit(0);
        }
        if( userInput == 'u') {
            if(currentMove->moveNum > 1) {
                undoLatestMove(currentMove);
                board = currentMove->board;
                moveNumber = currentMove->moveNum;
                cout << "* Undoing move *" << endl;
            } else {
                cout << "*** You cannot undo past the beginning of the game. ";
                cout << "Please retry. " << endl;
            }
            displayBoard(currentMove);
            continue;   // Prompt to retry move
        }
        // Input is likely numeric and is not 'x' or 'u'.  Convert to a number.
        source = userInput - '0';
        // Also get destination portion of user input
        cin >> destination;
        // Adjust user entry to compensate for 0-based indexing, rather than 1-based
        source--;
        destination--;
        // We don't need to undo a move
        break;
    }
}

bool moveNotValid(string board, int source, int destination) {
    if(source < 0 || source > 4 || destination < 0 || destination > 4) {
        cout << "*** You can't refer to a position off the board. ";
        return true;
    } 
    if(board[destination] != ' ') {
        cout << "*** Destination square is not empty. ";
        return true;
    }
    if(board[source] == 'X') {
        if(source > destination) {
            cout << "*** You can't move that piece that direction. ";
            return true;
        }
    } else if(board[source] == 'O') {
        if(source < destination) {
            cout << "*** You can't move that piece that direction. ";
            return true;
        }
    }
    if(source - destination > 2 || source - destination < -2) {
        cout << "*** Destination is too far away. ";
        return true;
    }
    if(source - destination == 2) {
        if( board[(source + destination) / 2] ==  ' ') {
            cout << "*** A jumped square must have an opponent. ";
            return true;
        }
    }
    if(source - destination == -2) {
        if( board[(source + destination) / 2] ==  ' ') {
            cout << "*** A jumped square must have an opponent. ";
            return true;
        }
    }
    return false;
}

int main() {
    // Initial Board Setup
    string board = "XX OO";
    int source, destination;
    int moveNumber = 1;

    // Setup the intial board state, as a "move" that we can return to
    struct move* currentMove = new struct move;
    currentMove->moveNum = moveNumber;
    currentMove->board = board;
    currentMove->priorMove = nullptr;
    
    // Display identifying information, the instructions, and the initial board
    displayIdentifyingInformation();
    displayInstructions();    
    displayBoard(currentMove);

    // Game play loop
    while(notDone(board)) {
        promptForAndGetMove(board, moveNumber, source, destination, currentMove);
        
        if( moveNotValid(board, source, destination)) {
            cout << "Invalid move, please retry. \n";
            continue;
        }
        
        // Make move.  Note that no move validation is being done.
        board[destination] = board[source];
        board[source] = ' ';
        moveNumber++;

        addNewMove(moveNumber, board, currentMove);
        
        displayBoard(currentMove);
    }

    // freeMovesMemory(currentMove);

    cout << "Congratulations, you did it!" << endl << endl;
    cout << "Exiting program ...\n";
    return 0;
}