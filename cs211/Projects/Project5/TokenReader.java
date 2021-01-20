import java.io.*;

public class TokenReader {
    private BufferedReader br;
    private String inline;
    private boolean needline;
    private int pos;
  
    // initialize the TokenReader class to read from Standard Input
    public TokenReader() {
        // set to read from Standard Input
        br = new BufferedReader(new InputStreamReader(System.in));
        inline = "";
        pos = 0;
        needline = true;
    }
  
    // Force the next getNextToken to read in a line of input
    public void clearToEoln() {
        needline = true;
    }
  
    // Return the next Token from the input line
    public Token getNextToken() {
        // get a new line of input from user
        if(needline) {
            try {
                inline = br.readLine();
            } catch(IOException ioe) {
                System.out.println ("Error in reading");
                return new Token(TokenType.EOF);
            }
            if(inline == null) {
                // End of File Encoutered - Should never be the case when reading 
                //   from standard input: System.in
                return new Token(TokenType.EOF);
            }
            // add a space at end to help deal with digit calculation
            inline = inline + " ";
            needline = false;
            pos = 0;
        }

        // skip over any white space characters in the beginning of the input
        while(pos < inline.length() && Character.isWhitespace(inline.charAt(pos)))
            pos++;

        // check for the end of the current line of input
        if(pos >= inline.length()) {  // at end of line
            needline = true;
            return new Token(TokenType.EOLN);
        }

        // Get the next character from the input line
        char ch = inline.charAt(pos); pos++;

        // check if 'q' or 'Q' was entered ==> QUIT Token
        if('q' == ch || 'Q' == ch)
            return new Token (TokenType.QUIT);

        // check if "?" was entered ==> HELP Token
        if('?' == ch)
            return new Token (TokenType.HELP);

        // check for Operator values of: + - * / ( )  ==> OPERATOR Token
        if (('+' == ch) || ('-' == ch) || ('*' == ch) || 
            ('/' == ch) || ('(' == ch) || (')' == ch)) {
            Token t = new Token();
            t.setToOperator(ch);
            return t;
        }

        // check for a number  ==> VALUE Token
        if (Character.isDigit(ch)) {
            int number = Character.digit(ch, 10);
            ch = inline.charAt(pos); pos++;
            while (Character.isDigit(ch)) {
                number = number * 10 + Character.digit(ch, 10);
                ch = inline.charAt(pos); pos++;
            }
            pos--; // since number calcuation checks one character after the last digit
            Token t = new Token();
            t.setToValue(number);
            return t; 
        }

        // Input in not valid if code get to this part ==> ERROR Token
        return new Token(TokenType.ERROR);
    }
    
}