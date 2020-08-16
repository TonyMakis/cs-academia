#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Maximum size of any word in the dictionary, + 1 for null
const int MAX_WORD_SIZE = 21 + 1;
const int MAX_LINE_SIZE = 100;

void verifyFileOpened(FILE *file, const char fileName[]) {
    if (file == NULL) {
        printf("\nCan't open \"%s\".", fileName);
        printf(" Verify that it is in correct location.\n");
        exit(-1);
    }
}

/* Compute lower case version of word, and store it in lowerWord, so
 * as NOT to mutate original word
 * @param word => what we want to see as lowered case
 * @param lowerWord => where to store the lower case version of word
 */
void storeWordAsLowerCase(const char word[], char lowerWord[]) {
    for(int i = 0; word[i]; i++){
        lowerWord[i] = tolower(word[i]);
    }
}

// Mutate word to be entirely uppercase
void toUpperCase(char word[]) {
    for(int i = 0; word[i]; i++){
        word[i] = toupper(word[i]);
    }
}

/* Wipe the string passed into this function, making it all '\0' characters
 * @param str => string to wipe
 * @param strSize => length of string to wipe
 * *** Also rewrites the terminating '\0', for good measure (<=)
 */
void clearString(char str[], int strSize) {
    for(int i = 0; i <= strSize; i++) {
        str[i] = '\0';
    }
}

/* Strips outer punctuation, like in these words:
 * - <"Kyle> (the '\"') or in <end.> (the '.')
 * @param word => word to strip punctuation from
 * @param cleanWord => word to store stripped result in
 * @param wordLen => original word's length
 */
void stripOuterPunctuation(char word[], char cleanWord[], int wordLen) {
    int i, firstAlphaIndex;
    // Find index of the 1st alphabetical char, AFTER any punctuation
    for(i = 0; i < wordLen; i++) {
        if( isalnum(word[i]) ) {
            firstAlphaIndex = i;
            break;
        }
    }
    // Copy everything from that 1st alphabetical char to the end of word
    // into cleanWord, to disregard punctuation @ the start of word
    for(i = firstAlphaIndex; i < wordLen; i++) {
        cleanWord[i - firstAlphaIndex] = word[i];
    }

    for(i = wordLen; i >= 0; i--) {
        if( isalnum(cleanWord[i]) ) break;
        if( ispunct(cleanWord[i]) ) cleanWord[i] = '\0';
    }
}

/* Read from the file a line at a time; THIS IS ONLY FOR FILES WITH 
 * ONE WORD PER LINE!!!
 * @param fileName => name of the file to extract words from
 * @param dataSet => 2D array to store words into
 * @return: number of words found in dictionary
 */
void loadFileDataToArray(const char *fileName, char dataSet[][ MAX_WORD_SIZE ]) {
    int i = 0;
    FILE *file;
    // Associate the file pointer with the actual file name and try to open it
    file = fopen(fileName, "r");        // open with "r" for "readonly" access
    verifyFileOpened(file, fileName);   // Check file opened successfully
    // Keep reading words while there are any
    while( fscanf(file, "%s", dataSet[ i ]) != EOF ) { i++; }
    // Debugging: uncomment below line for checking file reading is good
    // printf("Read in file: %s; found %d words!\n\n", fileName, i);
    fclose(file);                       // close the input file
}

/* Use binary search to look up the word in the a string (2D) array
 * @param dataSet => 2D array to store words into
 * @param numWords => number of words int the dataset we are perusing
 * @return => index of string if found, -1 otherwise
 */
int binarySearch(const char searchWord[], 
                 const char dataSet[][ MAX_WORD_SIZE ], int numWords) {
    int low, mid, high, searchResult = -1;  
    // Binary search for word
    low = 0, high = numWords - 1;
    // If there is a spread between the low and high, continue halfing,
    // Until the number is found
    while ( low <= high)  {
        mid = (low + high) / 2; // Compute the middle
        searchResult = strcmp( searchWord, dataSet[ mid ]);
        if ( searchResult == 0)  return mid;       // Word FOUND!
        else if (searchResult < 0) high = mid - 1; // Word is before middle location
        else low = mid + 1;                        // Word is after middle location
    }
    // Word NOT FOUND!
    return -1;
}

/* If a word in the Ikea Inventory happens to be an English Word, print it
 * @param ikea => ikea inventory, 2D array of product names
 * @param dict => dictionary of english words in 2D array
 * @params numIkea, numDict => lengths of each array, respectively
 */
void printIkeaWordsAlsoInDictionary(char ikea[][ MAX_WORD_SIZE ], 
                                    char dict[][ MAX_WORD_SIZE ],
                                    int numIkea, int numDict) {
    for(int i = 0; i < numIkea; i++) {
        // Make a lowercase copy of the ikea word we need to lookup (not mutation)
        int wordLen = strlen(ikea[i]);
        char lowerWord[wordLen + 1];
        lowerWord[wordLen] = '\0';
        storeWordAsLowerCase(ikea[i], lowerWord);
        // Print if Ikea product is an english word
        if(binarySearch(lowerWord, dict, numDict) >= 0) printf("%s, ", ikea[i]);
    }
    printf("\n\n");
}

/* Ensure all alphabet chars lowercase, remove punctuation on the
 * start/end of the word if any and return the new string length
 */
int massageWord(char word[], char cleanWord[], int wordLen) {
    // Make a stripped version of word in cleanWord
    stripOuterPunctuation(word, cleanWord, wordLen);
    // Directly mutate word to be uppercase; since all words in Ikea file are 
    // uppercase, we need to do this for comparison to work accurately
    toUpperCase(cleanWord);
    return strlen(cleanWord);
}

// Read a word at a time from the given line arg.
void processLineWords(char line[], char ikea[][ MAX_WORD_SIZE ], int numIkea) {
  char * word;
  word = strtok (line, " \n");
  while (word != NULL)
  {
    // We need a new char[] to store the string after massaging
    int wordLen = strlen(word);
    char cleanWord[wordLen + 1]; // + 1 b/c of '\0'!
    clearString(cleanWord, wordLen + 1);
    // Massage the word, get the clean words length
    int cleanWordLen = massageWord(word, cleanWord, wordLen);
    // Check if the word is an ikeaWord, if so, capitalize it
    if(binarySearch(cleanWord, ikea, numIkea) >= 0)
        toUpperCase(word);
    // print word
    printf("%s ", word);
    // Get next word now
    word = strtok (NULL, " \n");
  }
}

// Read from the file a line at a time, this is mainly meant for files
// that have full lines containing more than 1 word. If files have one word
// per line, use @loadFileDataToArray() above, to load them into an array
void processFileLines(FILE *file, char line[], char ikea[][ MAX_WORD_SIZE ], int numIkea) {
    while( fgets(line, MAX_LINE_SIZE, file) != NULL ) {
        processLineWords(line, ikea, numIkea);
    }
}

/* If a word in the input file happens to be in the Ikea Inventory, print it
 * @param fileName => name of input file
 * @param ikea => ikea inventory, 2D array of product names
 * @param numIkea => length of Ikea array, respectively
 */
void showIkeaWordsInFile(const char *fileName, char line[],
                         char ikea[][ MAX_WORD_SIZE ], int numIkea) {
    FILE *file;
    // Associate the file pointer with the actual file name and try to open it
    file = fopen(fileName, "r");        // open with "r" for "readonly" access
    verifyFileOpened(file, fileName);   // Check file opened successfully
    processFileLines(file, line, ikea, numIkea);
    printf("\n");
    fclose(file);                       // close the input file
}

/* Print any 2D array of words
 * @param numWords => length of array of words
 * @param dataSet => 2D array of words
 */
void printDataSet(int numWords, char dataSet[ ][ MAX_WORD_SIZE ]) {
    for(int i = 0; i < numWords; i++) {
        printf("%d. %s\n", i, dataSet[i]);
    }
}

int main() {
    // File names for where dictionary words / Ikea products are found
    char dictionaryFileName[] = "dictionary.txt";
    char ikeaFileName[] = "inventory_ikea.txt";
    char inputFileName[] = "input.txt";
    // Number of words in the dictionary / Ikea Inventory; known beforehand
    const int numDictWords = 40437;
    const int numIkeaProducts = 1764;
    // 2D array declaratoins; AKA an a array of chars.
    char dictionary[ numDictWords ][ MAX_WORD_SIZE ];
    char ikeaInventory[ numIkeaProducts ][ MAX_WORD_SIZE ];
    // Array to hold a line read int => for reading input file!
    char line[MAX_LINE_SIZE];

    printf("\nAuthor: Anthony Makis\nProgram: #3, IKEA Words, Stage 1\n\n");
    // iterate files and store their string data in arrays
    loadFileDataToArray(dictionaryFileName, dictionary);
    loadFileDataToArray(ikeaFileName, ikeaInventory);

    // Debugging: uncomment next two lines to check strings stored correctly
    // printDataSet(numDictWords, dictionary);
    // printDataSet(numIkeaProducts, ikeaInventory);

    // Stage 1 Ouptut
    printf(" * * * Stage 1 Ouput * * * \n\n");
    printIkeaWordsAlsoInDictionary(ikeaInventory, dictionary,
                                   numIkeaProducts, numDictWords);
    // Stage 2 Output
    printf(" * * * Stage 2 Ouput * * * \n\n");
    showIkeaWordsInFile(inputFileName, line, ikeaInventory, numIkeaProducts);

    return 0;
}
