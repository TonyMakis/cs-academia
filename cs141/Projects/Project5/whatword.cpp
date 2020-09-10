#include <iostream>
#include <fstream>    // For file input and output
#include <cassert>    // For the assert statement
#include <string>
#include <chrono>

using namespace std;

unsigned long long getTimeStampInSeconds() {
    return ( 
        chrono::duration_cast<chrono::milliseconds>(
            chrono::system_clock::now().time_since_epoch()
        ).count() 
    ) / 1000;
}

string getLowerCase(string word) {
    string lowerCaseWord = word;
    int wordLen = word.length();
    for(int i = 0; i < wordLen; i++){
        lowerCaseWord[i] = tolower(word[i]);
    }
    return lowerCaseWord;
}

void processDictionary(string* dict) {
    string line;                       // Placeholder for current line in dict
    ifstream inStream;                 // Declare an input stream
    int wordRow = 0, lineLen = 0;   // Dictionary iterator, current line length

    inStream.open( "dictionary.txt");  // Open dict file
    assert( ! inStream.fail() );       // Check file opened w/o error

    // For every line of the dictionary file, get the word and store 
    // it in the array if it is between 3 and 16 characters long
    while ( getline(inStream, line) ) {
        lineLen = line.length();
        if(lineLen > 2 && lineLen < 17) {
            // Only store the word if it is WhatWord valid length (3-16 chars)
            dict[wordRow] = getLowerCase(line);
            wordRow++;
        }
    }

    inStream.close();                  // Close dict file
}

void fillWordLengths(int wordLengths[], string* dict, int numWords) {
    for(int i = 0; i < numWords; i++) {
        wordLengths[i] = dict[i].length();
    }
}

void printGameEntryInfo() {
    cout <<
        "Author: Anthony Makis\n"
        "Program: #5, WhatWord\n\n"

        "Welcome to the game of Boggle, where you play against the clock\n"  
        "to see how many words you can find using adjacent letters on the\n"  
        "board. Each letter can be used only once for a given word.\n\n"
        
        "When prompted for piece to use you may also:\n"
        "\tEnter 'r' to reset the board to user-defined values.\n"      
        "\tEnter 's' to solve the board and display all possible words.\n"
        "\tEnter 't' to toggle the timer on/off.\n"               
        "\tEnter 'x' to exit the program.\n";
}

void printGameBoard(const int seconds, const char board[][4], const int gameScore, const int moveNum) {
    cout << endl << "  " << seconds << " seconds remaining" << endl ;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << "   Score: " << gameScore << endl;
    cout << moveNum << ". Enter a word: ";
}

void printWordsFound(bool foundWords[], const string* dict, int numWords) {
    cout << "Words so far are: ";
    for(int i = 0; i < numWords; i++) {
        if(foundWords[i]) cout << dict[i] << " ";
    }
    cout << endl;
}

const double letterFreqs[26] = { // a, b, c, d, . . ., z
    0.07680, 0.09485, 0.13527, 0.16824, 0.28129, 0.29299, 0.32033,  
    0.34499, 0.43625, 0.43783, 0.44627, 0.49865, 0.52743, 0.59567,
    0.66222, 0.69246, 0.69246, 0.76380, 0.86042, 0.92666, 0.95963,
    0.96892, 0.97616, 0.97892, 0.99510, 1.00000
};

char generateRandomChar(double randToken) {
    int i = 0;
    while(randToken > letterFreqs[i]) i++;
    return i + 97; // Use offset to cast from integer index in letterFreqs to ascii chars a-z!
}

void generateRandomGameBoard(char board[][4]) {
    double randToken = 0.0;
    srand( time(NULL) );

    for (int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            // Random double: 0 < randomToken < 1
            randToken = ((double) rand() / (RAND_MAX));
            board[i][j] = generateRandomChar(randToken);
        }
    }
}

void resetGameBoard(char board[][4]) {
    string newGameBoard;
    cout << "Enter 16 characters to be used to set the board: ";
    cin >> newGameBoard;
    cout << endl;

    for(int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // Map an element of the reset string entered to the spot on 2D board!
            board[i][j] = newGameBoard[i * 4 + j];
        }
    }
}

/* Use binary search to look up the word in the a string array
 * @param searchWord => word we are searching for in @dict
 * @param dict => array of dictionary strings
 * @param numWords => number of words in the dict
 * @return => index of string if found, -1 otherwise
 */
int binarySearch(const string searchWord, 
                 const string* dict, int numWords) {
    int low, mid, high, searchResult = -1;
    low = 0, high = numWords - 1;
    // If there is a spread between the low and high
    // continue halfing, until the number is found
    while ( low <= high)  {
        mid = (low + high) / 2; // Compute the middle
        searchResult = searchWord.compare(dict[mid]);
        if ( searchResult == 0)  return mid;       // Word FOUND!
        else if (searchResult < 0) high = mid - 1; // Word is before middle location
        else low = mid + 1;                        // Word is after middle location
    }
    // Word NOT FOUND!
    return -1;
}

/* These are the codefied directions to use when traversing the board for DFS
 * An index corresponds to an x & y direction in these arrays
 * The idea is, moving right doesn't change the row we are on, but it changes the column by +1
 * and so on . . . for all 8 directions
 * 
                       Right, Left, Down, Up, DownRight, DownLeft, UpRight, UpLeft */
int xDirections[8] = {     0,    0,    1, -1,         1,        1,      -1,     -1 };
int yDirections[8] = {     1,   -1,    0,  0,         1,       -1,       1,     -1 };

// Function to check if the given index is outside board boundries
bool isOutsideGameBoard(int i, int j) {
    return (i < 0 || i >= 4 || j < 0 || j >= 4);
}

/* Search for a word on the board using depth first search
 * @param board    -> the 2D game board
 * @param i, j     -> the source index in the board to start checking for a word
 * @param word     -> the word we are searching for on the board
 * @param position -> this is the index of the char in @word that corresponds to the
 *                    current place on the board
 * When we set a char to '-', this lets the algorithm know that spot has been visited already
 */
bool depthFirstSearch(char board[][4], int i, int j, string word, int position) {
    // Check that the current index on the board is on the board, matches the current
    // character in the word we are searching from, and make sure the char isn't visited
    if(isOutsideGameBoard(i, j) || board[i][j] != word[position] || board[i][j] == '-')
        return false;
    // We are done if we are at the end of the word
    if(position + 1 == word.length())
        return true;
    char tmpCharHolder = board[i][j];
    // Mark current char as visited
    board[i][j] = '-';
    int r = 0, c = 0;
    // Perform DFS in all 8 directions
    for(int k = 0; k < 8; k++) {
        r = xDirections[k] + i;
        c = yDirections[k] + j;
        // call dfs with position + 1, b/c we are searching for the NEXT char in word;
        // also, r and c are indeces of the next element to check
        if(depthFirstSearch(board, r, c, word, position + 1)) {
            board[i][j] = tmpCharHolder;
            return true;
        }
    }
    // Reset the character, so it isn't a '-'
    board[i][j] = tmpCharHolder;
    return false;    
}

bool checkForWordOnGameBoard(char board[][4], string searchWord) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            // When we find the first letter in the search word on the board, and
            // the DFS returns true, the word is on the board
            if(board[i][j] == searchWord[0] && depthFirstSearch(board, i, j, searchWord, 0))
                return true;
        }
    }
    // Word not found on board
    return false;
}

void incrementScore(int* score, string entry) {
    int entryLen = entry.length();
    int points = 0;
    if(entryLen < 3) points = 0;
    else if(entryLen < 4) points = 1;
    else if(entryLen < 5) points = 2;
    else if(entryLen < 6) points = 4;
    else points = entryLen;

    *score += points;
    cout << "   Worth " << points << " points." << endl;
}

void evaluateEntry(char board[][4], string entry, const string* dict, 
                   bool foundWords[], int numWords, int* moveNum, int* score) {
    int entryDictIndex = binarySearch(entry, dict, numWords);
    // Check if word is valid English (in the dictionary)
    if(entryDictIndex > -1) {
        // Check if word is also possible to make given the game board
        if(checkForWordOnGameBoard(board, entry)) {
            // Check if word was already found
            if(!foundWords[entryDictIndex]) {
                foundWords[entryDictIndex] = true;
                incrementScore(score, entry);
                (*moveNum)++;
            } else cout << "Sorry, that word was already previously found." << endl;
            printWordsFound(foundWords, dict, numWords);
        } else cout << " cannot be formed on this board." << endl;
    } else cout << " was not found in the dictionary." << endl;
}

void printSolutions(int wordLengths[], const string* dict, 
                    int numWords, char board[][4]) {
    int leftLength, rightLength;
    cout << "Enter min and max word lengths to display: ";
    cin >> leftLength; cin >> rightLength;
    cout << "Words between " << leftLength << " and " << rightLength << " are:" << endl;
    for(int len = leftLength; len < rightLength + 1; len++) {
        for(int word = 0; word < numWords; word++) {
            if(wordLengths[word] == len) {
                if(checkForWordOnGameBoard(board, dict[word])) {
                    cout << dict[word] << " ";
                }
            }
        }
    }
    cout << endl;
}

int main() {
    //**************** Dict. Preprocessing **********************
    const int numDictWords = 263533;
    string* dictionary = new string[numDictWords];
    bool wordsAlreadyEntered[numDictWords] = { false };
    int wordLengths[numDictWords];

    processDictionary(dictionary);
    fillWordLengths(wordLengths, dictionary, numDictWords);
    //************** Dict. Proprocessing Done *******************

    //**************** Game Preprocessing ***********************
    printGameEntryInfo();

    char board[4][4];
    generateRandomGameBoard(board);

    bool stillPlaying = true, stillTiming = true;
    int gameScore = 0, moveNum = 1, secondsRemaining = 60;
    string gameEntry;

    unsigned long long now;

    //************** Game Proprocessing Done ********************

    do {
        // Get Start Time Stamp
        if(stillTiming) now = getTimeStampInSeconds();
        printGameBoard((int)secondsRemaining, board, gameScore, moveNum);
        cin >> gameEntry;
        if(gameEntry.compare("r") == 0) resetGameBoard(board);  // reset board letters
        else if(gameEntry.compare("s") == 0) {                  // show solutions
            printSolutions(wordLengths, dictionary, numDictWords, board);
            break;
        }
        else if(gameEntry.compare("t") == 0) {                  // toggle timer
            stillTiming = !stillTiming;
            continue;
        }
        else if(gameEntry.compare("x") == 0) break;             // exit game
        else evaluateEntry(board, gameEntry, dictionary,        // check the word and update board
                           wordsAlreadyEntered, numDictWords, 
                           &moveNum, &gameScore);
        // Get Next Time Stamp, and use Start Time Stamp to get Elapsed Seconds
        if(stillTiming) {
            now = getTimeStampInSeconds() - now;
            secondsRemaining -= (int)now;
            // If time's up, we are done!
            if(secondsRemaining < 0) {
                cout << endl << "Time's up!!!" << endl << endl;
                break;
            }
        }
    } while(stillPlaying);

    cout << "Exiting the program." << endl << endl;

    // Clean up dynamic dictionary allocation
    delete []dictionary;

    return 0;
}
