/* readFromFileAndParseWords.c
 *
 *    Sample program to illustrate reading from a file into an array
 *    using fgets(...) so that spaces are captured.
 *
 *    Then pull out each word one at a time and print it.
 *
 *    The datafile words.txt contains:
 *
 *        The best,
 *          and the worst.
 *
 *    Running the program gives:

         Whole line: The best,
         Individual words:
         The
         best,
         
         Whole line:   and the worst.
         Individual words:
         and
         the
         worst.

 */
#include <stdio.h>
#include <stdlib.h>      // For file input and output

// Global constant
const int MAX_LENGTH = 81;   // global constant for max input line length


// Parse allWords to find the next word, updating the current index in allWords
// and returning the new word in the newWord array.
void extractNextWordFromLine(
            char allWords[],    // The line of all words
            int *wordsIndex,    // The current index postion in allWords, with changes reflected back
            char newWord[])     // The new word is placed in this array, to be returned and used
{
    int j = 0;     // Set the index within the newWord array to start at the beginning
    char c='\0';   // Temporary storage for each character as we read it
    
    // Initialize c to be the first character, if there is one
    if( allWords[ *wordsIndex] != '\0') {
        c = allWords[ *wordsIndex];     // Get first character
        (*wordsIndex)++;                // Advance index to the next character
    }
    
    // Skip leading spaces if there are any
    while( c==' ') {
        c = allWords[ *wordsIndex];   // advance to the next character
        (*wordsIndex)++;              // Advance index to the next character
    }
    
    // Copy characters into the word until we hit a space or null
    while( c!=' ' && c!='\0') {
        newWord[ j++] = c;
        // Get the next character
        c = allWords[ *wordsIndex];
        // advance to the next character if we're not at the end of the list
        if( c!='\0') {
            (*wordsIndex)++;          // Advance index to the next character
        }
    }//end while(...
    
    // NULL terminate the word so that we can use string functions
    newWord[ j] = '\0';
}


int main()
{
    char fileName[] = "20000LeaguesUnderTheSeaJulesVerne.txt";  // Make a C string (array of char) to store filename
    FILE *pInputFile;               // file pointer
    char inputLine[ MAX_LENGTH];    // An input line with some number of words on it
    int i=0;                        // Current index position in inputLine
    char aWord[ MAX_LENGTH];        // A single word
    
    // Associate the file pointer with the actual file name and try to open it
    pInputFile = fopen(fileName, "r");   // open with "r" for "read" access
    // verify that file open worked
    if (pInputFile == NULL) {
        printf("Can't open %s. Verify it is in correct location\n", fileName);
        exit(-1);
    }
    
    // Read a line at a time from the file and echo it as output.
    // Then process each line and print out each word, one at a time.
    while( fgets(inputLine, MAX_LENGTH, pInputFile) != NULL) {
        
        // Display the entire input line that was just read
        printf("Whole line: %s", inputLine);
        
        // Extract and display each word from the input line, one at a time
        printf("Individual words: \n");
        i=0;        // This must be reset each time a new line is processed
        while( inputLine[ i] != '\0') {
            extractNextWordFromLine( inputLine, &i, aWord);
            printf("%s\n", aWord);
        }
    }
    
    fclose( pInputFile);         // close the input file
    return 0;
}//end main()
