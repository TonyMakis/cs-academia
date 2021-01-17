#include "queue.h"

// Command Format Checking
int cmdUsageMsg(char *cmd) {
    fprintf( stderr, "%s\n\tUsage: %s [OPTIONALS]\n\n", KYEL, cmd );
    fprintf( stderr, "\tOPTIONAL ARGUMENT:\n\n");
    fprintf( stderr, "\t\t-d, \temit debugging messages\n%s", KNRM);
    exit(-1);
}

/* Clear input until next End of Line Character - \n */
void clearToEoln() {
    int ch;
    do { 
        ch = getc(stdin);
    }
    while((ch != '\n') && (ch != EOF));
}

/* Read in until the first Non-White-Space character is Read */
/* The white space characters are:
 *      space, tab \t, newline \n, vertical tab \v, 
 *      form feed \f, and carriage return \r
 */ 
int getNextNWSChar() {
    int ch = getc(stdin);
    if(ch == EOF) return ch;
    
    while(isspace(ch)) {
        ch = getc(stdin);
        if(ch == EOF) return ch;
    }
    return ch;
}

/* read in the next Positive Integer or error:    */
/* This is based on the Mathematical definition of a Postive Integer */
/*    zero is not counted as a positive number */ 
int getPosInt() {
    int value = 0;
    /* clear white space characters */
    int ch = getc(stdin);

    while (!isdigit(ch)) {
        if('\n' == ch) return 0; // error \n ==> no integer given
        // error non white space ==> integer not given next
        if(!isspace(ch)) {
            clearToEoln();
            return 0;
        }
        ch = getc(stdin);
    }

    value = ch - '0';
    ch = getc(stdin);
    while(isdigit(ch)) {
        value = value * 10 + ch - '0';
        ch = getc(stdin);
    }

    ungetc(ch, stdin);  // put the last read character back in input stream
    /* Integer value of 0 is an error in this program */
    if(0 == value) clearToEoln();
    return value;
}

/* read in the name until the end of the input */
char *getName() {
    /* skip over the white space characters */
    int ch;
    ch = getc(stdin);
    while(isspace(ch)) {
        if('\n' == ch) return NULL; // error \n ==> no integer given
        ch = getc(stdin);
    }

    char *word;
    int size;
    size = 10;
    word = (char *)malloc(sizeof(char) * size);

    // read in character-by-character until the newline is encountered
    int count = 0;

    while(ch != '\n') {
        if(count + 1 >= size) {
            // to grow an array to make it "dynamically sized" using malloc
            char* temp;
            int i;
            size = size * 2;
            temp = (char *)malloc(sizeof(char) * size);
            
            // printf ("Growing array from size %d to size %d\n", count, size);
            // copy the characters to the new array
            for (i = 0; i < count; i++)
                temp[i] = word[i];

            free(word);
            word = temp;
        }

        word[count] = ch;
        count++;
        word[count] = '\0';

        // read next character
        ch = getc(stdin);
    }

    if(count > 30) {
        count = 30;
        word[count] = '\0';
    }
 
    /* clear ending white space characters */
    while(isspace(word[count-1])) {
        count--;
        word[count] = '\0';
    }

    return word;
}

/* Print out a list of the commands for this program */
void printCommands() {
    printf ("The commands for this program are:\n\n");
    printf ("q - to quit the program\n");
    printf ("? - to list the accepted commands\n");
    printf ("a <size> <name> - to add a group to the wait list\n");
    printf ("c <size> <name> - to add a call-ahead group to the wait list\n");
    printf ("w <name> - to specify a call-ahead group is now waiting in the restaurant\n");
    printf ("r <table-size> - to retrieve the first waiting group that can fit at the available table size\n");
    printf ("l <name> - list how many groups are ahead of the named group\n");
    printf ("d - display the wait list information\n");
        
    /* clear input to End of Line */
    clearToEoln();
}

int main(int argc, char **argv) {
    boolean debug_mode;

    if(argc == 1)
        debug_mode = FALSE;
    else if(argc == 2 && strcmp(argv[1], "-d") == 0)
        debug_mode = TRUE;
    else
        cmdUsageMsg(argv[0]);

    char *input;
    int ch;

    queue q;
    initQueue(&q, debug_mode);

    printf("Starting Restaurant Wait List Program\n\n");
    printf("Enter command: ");

    while((ch = getNextNWSChar()) != EOF) {
        /* check for the various commands */
        if('q' == ch) {
            printf ("Quitting Program\n");
            freeQueue(&q); // Ensure no mem leaks
            return (0);
        } else if('?' == ch) { printCommands();
        } else if('a' == ch) { doAdd(&q);
        } else if('c' == ch) { doCallAhead(&q);
        } else if('w' == ch) { doWaiting(&q);
        } else if('r' == ch) { doRetrieve(&q);
        } else if('l' == ch) { doList(&q);
        } else if('d' == ch) { doDisplay(&q);
        } else {
            printf("%c - in not a valid command\n", ch);
            printf("For a list of valid commands, type ?\n");
            clearToEoln();
        }
        printf ("\nEnter command: ");
    }
    freeQueue(&q); // Ensure no mem leaks
    printf ("Quiting Program - EOF reached\n");
    return 1;
}
