#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Maximum size of any word in the dictionary, + 1 for null
const int MAX_WORD_SIZE = 21 + 1;

void verifyFileOpened(FILE *file, const char fileName[]) {
    if (file == NULL) {
        printf("\nCan't open \"%s\".", fileName);
        printf(" Verify that it is in correct location.\n");
        exit(-1);
    }
}

/* Compute lower case version of a word
 * @param word => what we want to see as lowered case
 * @param lowerWord => where to store the lower case version of word
 */
void toLowerCase(const char word[], char lowerWord[]) {
    for(int i = 0; word[i]; i++){
        lowerWord[i] = tolower(word[i]);
    }
}

/* Read from the file a line at a time
 * @param fileName => name of the file to extract words from
 * @param dataSet => 2D array to store words into
 * @return: number of words found in dictionary
 */
void processFileWords(const char *fileName, char dataSet[][ MAX_WORD_SIZE ]) {
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
        toLowerCase(ikea[i], lowerWord);
        // Print if Ikea product is an english word
        if(binarySearch(lowerWord, dict, numDict) >= 0) 
            printf("%s\n", ikea[i]);
    }
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
    // Number of words in the dictionary / Ikea Inventory; known beforehand
    const int numDictWords = 40437;
    const int numIkeaProducts = 1764;
    // 2D array declaratoins; AKA an a array of chars.
    char dictionary[ numDictWords ][ MAX_WORD_SIZE ];
    char ikeaInventory[ numIkeaProducts ][ MAX_WORD_SIZE ];

    printf("\nAuthor: Anthony Makis\nProgram: #3, IKEA Words, Stage 1\n\n");
    // iterate files and store their string data in arrays
    processFileWords(dictionaryFileName, dictionary);
    processFileWords(ikeaFileName, ikeaInventory);

    // Debugging: uncomment next two lines to check strings stored correctly
    // printDataSet(numDictWords, dictionary);
    // printDataSet(numIkeaProducts, ikeaInventory);

    printIkeaWordsAlsoInDictionary(ikeaInventory, dictionary,
                                   numIkeaProducts, numDictWords);

    return 0;
}
