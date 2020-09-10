#include <iostream>   // For general IO
#include <fstream>    // For file input and output
#include <cassert>    // For the assert statement
#include <string>

using namespace std;

const int NumberOfWords = 263533;   // Number of dictionary words

int main()
{
   // Allocate space for the dictionary
   // If this causes a "Segmentation fault" then you will need to dynamically
   // allocate memory, illustrated in a separate program. 
   string* dictionary = new string[NumberOfWords];
   
   // Now read the words from the dictionary
   string line;                       // Placeholder for current line in dict
   ifstream inStream;                 // declare an input stream for my use
   int wordRow = 0;                   // Row for the current word

   inStream.open( "dictionary.txt");  // Open dict file
   assert( ! inStream.fail() );       // Check file opened w/o error

   // Keep repeating while input from the file yields a word
   while ( getline(inStream, line) ) {
      dictionary[wordRow] = line;
      wordRow++;
   }
   cout << wordRow << " words were read in." << endl;

   // show how we can access the memory 
   cout << "Enter an array index number from which to display a word: ";
   long index;
   cin >> index;
   // Display the word at that memory address 
   cout << dictionary[ index] << endl;

   inStream.close();
   
   delete []dictionary;

   return 0;
}
