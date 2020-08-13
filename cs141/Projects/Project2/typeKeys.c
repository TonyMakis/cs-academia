#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Global constant for max input line length:
 *  This is better performance than preprocessor directives (#define)
 */
const int MAX_LENGTH = 100;

/* Struct to layout keys on any keyboard:
 *  - l_* => left-hand, r_* => right-hand
 *  - all arrays are sized to a capacity of two symbols per key,
 *    plus 1 to make space for the '\0'
 */
struct KeyboardLayout { 
    // Specific home row keys, for each hand
    char l_homeRow[9], r_homeRow[9];
    char l_homeRow_midKey, r_homeRow_midKey, r_homeRow_edgeKey[3];
    // Specific bottom row keys, for each hand
    char l_bottomRow[9], r_bottomRow[11];
    char r_bottomRow_midKey;
    // Specific top row keys, for each hand
    char l_topRow[9], r_topRow[9];
    char l_topRow_midKey, r_topRow_midKey;
    // Specific number row keys, for each hand
    char l_numrow[11], r_numRow[11];
    char l_numRow_midKey[3];
};  

typedef struct KeyboardLayout keys;

// The two different keyboard layout structs we are using, as accessible constants:

const keys QWERTY = {
    // l_homeRow, r_homeRow, l_homeRow_midKey, r_homerow_midKey, r_homerow_edgeKey
    "asdf", "jkl;:", 'g','h', "\'\"",
    // l_bottomRow, r_bottomRow, r_bottomRow_midKey
    "zxcv", "nm,<.>/?", 'b',
    // l_topRow, r_topRow, l_topRow_midKey, r_topRow_midKey
    "qwer", "uiop", 't', 'y',
    // l_numrow, r_numRow, l_numRow_midKey
    "1!2@3#4$5%", "7&8*9(0)-_", "6^"
};

const keys DVORAK = {
    // l_homeRow, r_homeRow, l_homeRow_midKey, r_homerow_midKey, r_homerow_edgeKey
    "aoeu", "htns", 'i','d', "-_",
    // l_bottomRow, r_bottomRow, r_bottomRow_midKey
    ":;qjk", "bmwvz", 'x',
    // l_topRow, r_topRow, l_topRow_midKey, r_topRow_midKey
    "\'\",<.>p", "gcrl/?", 'y', 'f',
    // l_numrow, r_numRow, l_numRow_midKey
    "1!2@3#4$5%", "7&8*9(0)", "6^"
};

void verifyFileOpened(FILE *file, char fileName[]) {
    if (file == NULL) {
        printf("\nCan't open \"%s\".", fileName);
        printf(" Verify that it is in correct location.\n");
        exit(-1);
    }
}

// divide inches by 12 => feet; divide feet by 5,280 => miles
//  => 12 * 5,280 = 63,360, so inches / 63,360 = miles
float convertInchesToMiles(float inches) {
    return inches / 63360;
}

// Wipe the string passed into this function, making it all '\0' characters
// Also rewrites the '\0' character after the array, for good measure.
void clearString(char str[], int strSize) {
    for(int i = 0; i <= strSize; i++) {
        str[i] = '\0';
    }
}

// Make sure whole word is lower case, since we don't consider Shift Key
void toLowerCase(char word[]) {
    for(int i = 0; word[i]; i++){
        word[i] = tolower(word[i]);
    }
}

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

// Ensure all alphabet chars lowercase, remove punctuation on the
// start/end of the word if any and return the new string length
int massageWord(char word[], char cleanWord[], int wordLen) {
    // Directly mutate word to be lowercase
    toLowerCase(word);
    // Make a stripped version of word in cleanWord
    stripOuterPunctuation(word, cleanWord, wordLen);
    return strlen(cleanWord);
}

// Given a word and ANY 'keyboard layout' (struct), we get the number 
// of keys the word has in the home row of that keyboard.
int getNumHomeRowChars(char word[], int length, keys ANY) {
    int i, homeRowKeyCounter = 0;
    for(i = 0; i < length; i++) {
        if(strchr(ANY.l_homeRow, word[i]) || strchr(ANY.r_homeRow, word[i])) {
            homeRowKeyCounter++;
        }
    }
    return homeRowKeyCounter;
}

// Check if word can be typed without fingers leaving the home row
int isWordInHomeRow(char word[], int length, keys ANY) {
    int i;
    for(i = 0; i < length; i++) {
        if(!( strchr(ANY.l_homeRow, word[i]) || strchr(ANY.r_homeRow, word[i]) ) ) {
            return 0;
        }
    }
    return 1;
}

// Check if word is typed entirely left hand 
int isWordLeftHanded(char word[], int length, keys ANY) {
    int i;
    for(i = 0; i < length; i++) {
        if(!( strchr(ANY.l_numrow, word[i]) || strchr(ANY.l_topRow, word[i]) ||
              strchr(ANY.l_homeRow, word[i]) || strchr(ANY.l_bottomRow, word[i]) ||
              strchr(ANY.l_numRow_midKey, word[i]) || word[i] == ANY.l_topRow_midKey ||
              word[i] == ANY.l_homeRow_midKey ) ) {
            return 0;
        }  
    }
    return 1;
}

// Check if word is typed entirely right hand 
int isWordRightHanded(char word[], int length, keys ANY) {
    int i;
    for(i = 0; i < length; i++) {
        if(!( strchr(ANY.r_numRow, word[i]) || strchr(ANY.r_topRow, word[i]) ||
              strchr(ANY.r_homeRow, word[i]) || strchr(ANY.r_bottomRow, word[i]) ||
              strchr(ANY.r_homeRow_edgeKey, word[i]) || word[i] == ANY.r_topRow_midKey || 
              word[i] == ANY.r_homeRow_midKey || word[i] == ANY.r_bottomRow_midKey ) ) {
            return 0;
        }  
    }
    return 1;
}

// Check if a word is typed one handed (entirely left or right handed basically)
int isWordOneHanded(char word[], int length, keys ANY) {
    return isWordLeftHanded(word, length, ANY) || 
           isWordRightHanded(word, length, ANY);
}

// Calculate the distance (inches) fingers travel to type a word
// Since home row keys count as 0.0 inches, we don't need to check that
float getDistanceTyped(char word[], int length, keys ANY) {
    float inches = 0.0;
    int i;
    for(i = 0; i < length; i++) {
        if(word[i] == ANY.l_homeRow_midKey || word[i] == ANY.r_homeRow_midKey ||
           strchr(ANY.r_homeRow_edgeKey, word[i])) inches += 0.75;
        if(strchr(ANY.l_bottomRow, word[i]) || strchr(ANY.r_bottomRow, word[i]) || 
           strchr(ANY.l_topRow, word[i]) || strchr(ANY.r_topRow, word[i]))
            inches += 0.75;
        if(word[i] == ANY.r_bottomRow_midKey) inches += 1.25;
        if(word[i] == ANY.l_topRow_midKey || word[i] == ANY.r_topRow_midKey)
            inches += 1.0;
        if(strchr(ANY.l_numrow, word[i]) || strchr(ANY.r_numRow, word[i])) 
            inches += 1.5;
        if(strchr(ANY.l_numRow_midKey, word[i])) inches += 1.75;
    }
    return inches;
}

// Read a word at a time from the current line
void processLineWords(char line[], int *totalWords, int *totalChars, 
                      int *qwertyHomeRowChars, int *dvorakHomeRowChars,
                      int *qwertyWordsInHomeRow, int *dvorakWordsInHomeRow,
                      int *qwertyOneHandedWords, int *dvorakOneHandedWords,
                      float *qwertyDistanceTyped, float *dvorakDistanceTyped) {
  char * word;
  word = strtok (line, " \n");
  while (word != NULL)
  {
    // We need a new char[] to store the string after massaging
    int wordLen = strlen(word);
    char cleanWord[wordLen + 1]; // + 1 b/c of '\0'!
    clearString(cleanWord, wordLen + 1);
    // Massage the word, and collect word/char statistics
    int cleanWordLen = massageWord(word, cleanWord, wordLen);
    *totalChars += cleanWordLen;
    *totalWords += 1;
    // Account for number of characters typed in word that are in the home row
    *qwertyHomeRowChars += getNumHomeRowChars(cleanWord, cleanWordLen, QWERTY);
    *dvorakHomeRowChars += getNumHomeRowChars(cleanWord, cleanWordLen, DVORAK);
    // Account for this word if it is typed entirely in the home row
    if(isWordInHomeRow(cleanWord, cleanWordLen, QWERTY)) *qwertyWordsInHomeRow += 1;
    if(isWordInHomeRow(cleanWord, cleanWordLen, DVORAK)) *dvorakWordsInHomeRow += 1;
    // Account for this word if it is typed entirely with one hand, left or right
    if(isWordOneHanded(cleanWord, cleanWordLen, QWERTY)) *qwertyOneHandedWords += 1;
    if(isWordOneHanded(cleanWord, cleanWordLen, DVORAK)) *dvorakOneHandedWords += 1;
    // Account for distance travelled by fingers typing this word
    *qwertyDistanceTyped += getDistanceTyped(cleanWord, cleanWordLen, QWERTY);
    *dvorakDistanceTyped += getDistanceTyped(cleanWord, cleanWordLen, DVORAK);
    // Uncomment next line to print all the words => DEBUGGING
    // printf("<%s|%ld> ", cleanWord, strlen(cleanWord));
    // Get next word now
    word = strtok (NULL, " \n");
  }
}

// Read from the file a line at a time
void processFileLines(FILE *file, char line[], int *totalWords, int *totalChars, 
                      int *qwertyHomeRowChars, int *dvorakHomeRowChars,
                      int *qwertyWordsInHomeRow, int *dvorakWordsInHomeRow,
                      int *qwertyOneHandedWords, int *dvorakOneHandedWords,
                      float *qwertyDistanceTyped, float *dvorakDistanceTyped) {
    int curLine = 0;
    // Let's print/analyze the first 2 lines:
    printf("First two lines of the input file are:\n");
    for(curLine = 0; curLine < 2; curLine++) {
        if( fgets(line, MAX_LENGTH, file) != NULL ) {
            printf("%s", line);
            processLineWords(line, totalWords, totalChars, 
                             qwertyHomeRowChars, dvorakHomeRowChars,
                             qwertyWordsInHomeRow, dvorakWordsInHomeRow,
                             qwertyOneHandedWords, dvorakOneHandedWords,
                             qwertyDistanceTyped, dvorakDistanceTyped);
        }
    }
    // Ok, now the rest:
    while( fgets(line, MAX_LENGTH, file) != NULL ) {
        processLineWords(line, totalWords, totalChars,
                         qwertyHomeRowChars, dvorakHomeRowChars,
                         qwertyWordsInHomeRow, dvorakWordsInHomeRow,
                         qwertyOneHandedWords, dvorakOneHandedWords,
                         qwertyDistanceTyped, dvorakDistanceTyped);
    }
}

int main() {
    // Make a C string (array of char) to store filename
    char fileName[] = "20000LeaguesUnderTheSeaJulesVerne.txt";
    FILE *file;
    char line[MAX_LENGTH]; // An input line with some number of words on it
    int totalWords = 0, totalChars = 0, 
        qwertyHomeRowChars = 0, dvorakHomeRowChars = 0,
        qwertyWordsInHomeRow = 0, dvorakWordsInHomeRow = 0,
        qwertyOneHandedWords = 0, dvorakOneHandedWords = 0;
    float qwertyDistanceTyped = 0.0, dvorakDistanceTyped = 0.0;
    
    // Associate the file pointer with the actual file name and try to open it
    file = fopen(fileName, "r");        // open with "r" for "readonly" access
    verifyFileOpened(file, fileName);   // Check file opened successfully

    printf("\nAuthor: Anthony Makis\nProgram: #2, Type Keys\n\n");
    
    processFileLines(file, line, &totalWords, &totalChars, 
                     &qwertyHomeRowChars, &dvorakHomeRowChars,
                     &qwertyWordsInHomeRow, &dvorakWordsInHomeRow,
                     &qwertyOneHandedWords, &dvorakOneHandedWords,
                     &qwertyDistanceTyped, &dvorakDistanceTyped);

    printf("\n\t\tTotal words:\t%d\n", totalWords);
    printf("Total non-blank characters:\t%d\n\n", totalChars);

    printf("\t\t\t\tQwerty\tDvorak\n");
    printf("%% All Characters on home row:\t %.0f\t %.0f\n",
            qwertyHomeRowChars * 1.0 / totalChars * 100, dvorakHomeRowChars * 1.0 / totalChars * 100);  
    printf("     %% All Words on home row:\t %.0f\t %.0f\n",
            qwertyWordsInHomeRow * 1.0 / totalWords * 100, dvorakWordsInHomeRow * 1.0 / totalWords * 100); 
    printf("   %% Words typed on one hand:\t %.0f\t %.0f\n",
            qwertyOneHandedWords * 1.0 / totalWords * 100, dvorakOneHandedWords * 1.0 / totalWords * 100);
    printf("   Distance travelled(miles):\t %.3f\t %.3f\n",
            convertInchesToMiles(qwertyDistanceTyped), convertInchesToMiles(dvorakDistanceTyped));

    fclose(file);                       // close the input file
    return 0;
}
