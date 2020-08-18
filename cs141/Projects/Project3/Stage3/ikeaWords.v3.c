#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Some functions are recycled from Project 2:
 * 1. verifyFileOpened
 * 2. clearString
 * 3. stripOuterPunctuation
 * 
 * Other functions are modified and borrow from Project 2:
 * 1. toUpperCase / storeWordsAsLowerCase
 * 2. processFileLines / processLineWords
 * 3. massageWords
 */

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

// Direclty mutate word to be entirely uppercase
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
        if(binarySearch(lowerWord, dict, numDict) >= 0) {
            if(i)
                printf(", ");
            printf("%s", ikea[i]);
        }
    }
    printf("\n\n");
}

// Try matching substrings of the word, by removing one char at a time
// i.e. if word = [open] => try: [pen], [oen], [opn], and [ope]
int checkRemovingLetter(char word[], int wordLen, 
                        char ikea[][ MAX_WORD_SIZE ], int numIkea) {
    // tryWord is one char shorter than word
    char tryWord[wordLen];
    int tryWordIndex = 0;
    clearString(tryWord, wordLen);

    // Extract every version of word with one less char
    for(int i = 0; i < wordLen; i++) {
        for(int j = 0; j < wordLen; j++) {
            if(j != i) {
                tryWord[tryWordIndex] = word[j];
                tryWordIndex++;
            }
        }
        // Check if we can find this similar word in Ikea Inventory
        if(binarySearch(tryWord, ikea, numIkea) >= 0) {
            printf("%s ", tryWord);
            return 1;
        }
        tryWordIndex = 0;
    }
    return 0;
}

// Try matching variations of the word, by subbin one char at a time for some A-Z
// i.e. if word = [car] => try: [aar], [bar], [car], ... [zar],
//                              [car], [cbr], [ccr], ... [czr],
//                              [caa], [cab], [cac], ... [caz]
int checkSubstitutingLetter(char word[], int wordLen, 
                            char ikea[][ MAX_WORD_SIZE ], int numIkea) {
    // +1 b/c of the '\0' we need to terminate; tryWord is same size as word
    char tryWord[wordLen + 1];
    clearString(tryWord, wordLen + 1);
    strncpy(tryWord, word, wordLen);

    // Try every version of word, with an A-Z replaceing each char in it iteratively
    for(int i = 0; i < wordLen; i++) { // Now, chars A-Z in ascii are 65-90
        for(char asciiAlpha = 65; asciiAlpha < 91; asciiAlpha++) {
            tryWord[i] = asciiAlpha;
            if(binarySearch(tryWord, ikea, numIkea) >= 0) {
                printf("%s ", tryWord);
                return 1;
            }
        }
        strncpy(tryWord, word, wordLen);
    }

    return 0;
}

/* Put one word into another, where destination string has one char in 
 * it already
 * @param result => the string containg one char
 * @param word => the string providing chars that need to file into result;
 *                they should be put into result in order, skipping the 
 *                already existing character in the array, replacing only '\0's
 */
void insertWordAroundLetter(char result[], char word[], int wordLen) {
    int wordIndex = 0;
    for(int i = 0; i < wordLen + 1; i++) {
        if(!result[i]) {
            result[i] = word[wordIndex];
            wordIndex++;
        }
    }
}

// Try matching variations of the word, by adding one char at a time for some A-Z
// i.e. if word = [car] => try: [acar], [bcar], [ccar], ... [zcar],
//                              [caar], [cbar], [ccar], ... [czar],
//                              [caar], [cabr], [cacr], ... [cazr],
//                              [cara], [carb], [carc], ... [carz]
int checkAddingLetter(char word[], int wordLen, 
                      char ikea[][ MAX_WORD_SIZE ], int numIkea) {
    // +2 b/c of the '\0' we need to terminate, and b/c tryWord is 1 char bigger than word
    char tryWord[wordLen + 2];
    clearString(tryWord, wordLen + 2);

    // Try every version of word, with an A-Z inserted in it iteratively
    for(int i = 0; i < wordLen + 1; i++) { // chars A-Z in ascii are 65-90
        for(char asciiAlpha = 65; asciiAlpha < 91; asciiAlpha++) {
            tryWord[i] = asciiAlpha;
            insertWordAroundLetter(tryWord, word, wordLen);
            if(binarySearch(tryWord, ikea, numIkea) >= 0) {
                printf("%s ", tryWord);
                return 1;
            }
            clearString(tryWord, wordLen + 1);
        }
    }
    return 0;
}

// Search ikea inventory for substrings of words, instead of whole words
// => not a binary search, since you can't "sort" words for substring matching
int checkSubstring(char word[], int wordLen, 
                   char ikea[][ MAX_WORD_SIZE ], int numIkea) {
    for(int i = 0; i < numIkea; i++) {
        if( strstr(ikea[i], word) ) {
            printf("%s ", ikea[i]);
            return 1;
        }
    }
    return 0;
}

/* If we are running this, likely the word is not a perfect match with an IKEA word,
 * so we are trying to find any similar words, differing by just one character
 * @param cleanWord => the word that we want to to try to match
 * @param cleanWordLen => length of the word
 * @param ikea => the ikea inventory we are searching through
 * @param numIkea => the number of products in the Ikea Inventory
 */
int findSimilarWords(char word[], int wordLen, 
                          char ikea[][ MAX_WORD_SIZE ], int numIkea) {
    // The good thing is, this will evaluate left to right;
    // once one of them is a 1, C is optimized enought to return 1,
    // and stops evaluating the rest => called: short-circuiting :)
    return checkRemovingLetter(word, wordLen, ikea, numIkea) || 
           checkSubstitutingLetter(word, wordLen, ikea, numIkea) || 
           checkAddingLetter(word, wordLen, ikea, numIkea) || 
           checkSubstring(word, wordLen, ikea, numIkea);
}

/* Read a word at a time from the given line arg.
 * @param line => the line that was just read in, needing parsing
 * @param ikea => the ikea inventory we are searching through
 * @param numIkea => the number of products in the Ikea Inventory
 * @param findExactMatches => a value to tell how precisely to match the words to Ikea Products
 *                        |=> Only capitalize words that match EXACTLY if exactness != 0
 *                        |=> ALSO print ikea words that are CLOSE to match if exactness == 0
 */
void processLineWords(char line[], char ikea[][ MAX_WORD_SIZE ],
                      int numIkea, int findExactMatches) {
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
    if(findExactMatches) {
        // Check if the word is an ikeaWord, if so, capitalize it
        if(binarySearch(cleanWord, ikea, numIkea) >= 0) toUpperCase(word);
        printf("%s ", word);
    } else { // findExactMatches == 0; try to find exact match, if can't, find similar
        if(binarySearch(cleanWord, ikea, numIkea) >= 0) {
            toUpperCase(word);
            printf("%s ", word);
        } else {
            if(!findSimilarWords(cleanWord, cleanWordLen, ikea, numIkea)) {
                printf("%s ", word);
            };
        }
    }
    // Get next word now
    word = strtok (NULL, " \n");
  }
}

// Read from the file a line at a time, this is mainly meant for files
// that have full lines containing more than 1 word. If files have one word
// per line, use @loadFileDataToArray() above, to load them into an array
void processFileLines(FILE *file, char line[], char ikea[][ MAX_WORD_SIZE ], 
                      int numIkea, int findExactMatches) {
    while( fgets(line, MAX_LINE_SIZE, file) != NULL ) {
        processLineWords(line, ikea, numIkea, findExactMatches);
    }
}

/* If a word in the input file happens to be in the Ikea Inventory, print it
 * @param fileName => name of input file
 * @param ikea => ikea inventory, 2D array of product names
 * @param numIkea => length of Ikea array, respectively
 * @param findExactMatches => a value to tell how precisely to match the words to Ikea Products
 */
void showIkeaWordsInFile(const char *fileName, char line[],
                         char ikea[][ MAX_WORD_SIZE ],
                         int numIkea, int findExactMatches) {
    FILE *file;
    // Associate the file pointer with the actual file name and try to open it
    file = fopen(fileName, "r");        // open with "r" for "readonly" access
    verifyFileOpened(file, fileName);   // Check file opened successfully
    processFileLines(file, line, ikea, numIkea, findExactMatches);
    printf("\n\n");
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
    // Stage 2 Output => the 1 as an argument means match words EXACTLY
    printf(" * * * Stage 2 Ouput * * * \n\n");
    showIkeaWordsInFile(inputFileName, line, ikeaInventory, numIkeaProducts, 1);

    // Stage 3 Output => the 0 as an argument means match words SIMILARLY
    printf(" * * * Stage 3 Output * * * \n\n");
    showIkeaWordsInFile(inputFileName, line, ikeaInventory, numIkeaProducts, 0);

    return 0;
}
