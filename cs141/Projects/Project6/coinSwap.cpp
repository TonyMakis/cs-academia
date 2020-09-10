/* coinswap.cpp
 Make moves to solve the puzzle where the objective is to swap the place of
 the pieces on either side of the board.  X can only move to the right into
 an empty square, or can jump to the right over an O into an empty square.
 Conversely O can only move to the left into an empty square, or can jump
 to the left over an X into an empty square.
 */
#include <iostream>
using namespace std;

// Global constants
const int BoardSize=5;


//--------------------------------------------------------------------------------
// Display name and program information
void displayIdentifyingInformation()
{
    printf("\n");
    printf("Author: Dale Reed          \n");
    printf("Program: #6, Coin Swap     \n");
    printf("TA: Claude Shannon, Th 4-5 \n");
    printf("Nov 17, 2016               \n");
    printf("\n");
}//end displayIdentifyingInformation()


//--------------------------------------------------------------------------------
// Display instructions
void displayInstructions()
{
    cout << "Welcome to the coin swap puzzle.                                  \n"
         << "Make moves to solve the puzzle where the objective is to swap the \n"
         << "place of the pieces on either side of the board.  X can only move \n"
         << "to the right into an empty square, or can jump to the right over  \n"
         << "an O into an empty square. Conversely O can only move to the left \n"
         << "into an empty square, or can jump to the left over an X into an   \n"
         << "empty square.  \n"
         << " \n"
         << "For each move enter the source (1..5) and destination (1..5).     \n"
         << "Enter 0 to exit the program. \n";
}//end displayInstructions()


//--------------------------------------------------------------------------------
// See if board pieces have finished being swapped.  This is the case when
// the left-most two pieces are both 'O' and the right-most two pieces are 'X'
bool notDone( char board[])
{
    return board[0]!='O' || board[1]!='O' || board[3]!='X' || board[4]!='X';
}


//--------------------------------------------------------------------------------
void displayBoard( char board[])
{
    cout << endl;
    cout << "   1 2 3 4 5\n";
    cout << "   ";
    for( int i=0; i<BoardSize; i++) {
        cout << board[ i] << " ";
    }
    cout << endl;
}


//--------------------------------------------------------------------------------
void promptForAndGetMove( char board[], int &moveNumber, int &source, int &destination)
{
    char userInput;
    
    // Infinite loop to handle possible multiple undo of moves
    while( true) {
        cout << moveNumber << ". Enter source and destination: ";
        cin >> userInput;
        // See if user input of 0 was given to exit the program
        if( userInput == 'x') {
            cout << "\n";
            cout << "Exiting program...\n";
            exit( 0);
        }
        if( userInput == 'u') {
            // undo move
            // ..
            displayBoard( board);
            continue;   // Prompt to retry move
        }
        // Input is likely numeric and is not 'x' or 'u'.  Convert to a number.
        source = userInput - '0';
        
        // Also get destination portion of user input
        cin >> destination;
        
        // Adjust user entry to compensate for 0-based indexing, rather than 1-based
        source--;
        destination--;
        
        // break out of enclosing loop, as we don't need to undo a move
        break;
    }
}//end promptForAndGetMove()


//--------------------------------------------------------------------------------
bool moveNotValid(
        char board[],
        int source,
        int destination)
{
    // Move validation code should go here...
    
    return false;
}


//--------------------------------------------------------------------------------
int main()
{
    char board[ BoardSize + 1] = "XX OO";  // extra character for the NULL
    int source, destination;
    int moveNumber = 1;
    
    // Display identifying information, the instructions, and the initial board
    displayIdentifyingInformation();
    displayInstructions();
    displayBoard( board);
    
    // Game play loop
    while( notDone( board) ) {
        promptForAndGetMove( board, moveNumber, source, destination);
        
        if( moveNotValid( board, source, destination)) {
            cout << "Invalid move, please retry. \n";
            continue;
        }
        
        // Make move.  Note that no move validation is being done.
        board[ destination] = board[ source];
        board[ source] = ' ';
        moveNumber++;
        
        displayBoard( board);
    }
    
    cout << "Congratulations, you did it! \n"
         << "\n"
         << "Exiting program ...\n";
    return 0;         // return value to keep C++ happy
}//end main()