// Enumarated Type specifying all of the Tokens
enum TokenType { ERROR, OPERATOR, VALUE, EOLN, QUIT, HELP, EOF}

// Class to hold the Token information
public class Token {
    private TokenType type;
    private char      op;       // using '$' as undefined/error
    private int       val;      // using -999 as undefined/error
  
    // Default to initialize to the ERROR TokenType
    public Token() {
        type = TokenType.ERROR;
        op = '$'; 
        val = -999;
    }
  
    // Initialize to a specific TokenType
    public Token(TokenType t) {
        type = t;
        op = '$'; 
        val = -999;
    }
  
    // Set to a specific TokenType
    public void setToType(TokenType t) {
        type = t;
        op = '$'; 
        val = -999;
    }
  
    // Set to a OPERATOR TokenType with specific operator value
    public void setToOperator(char c) {
        type = TokenType.OPERATOR;
        op = c; 
        val = -999;
    }

    // Set to a VALUE TokenType with a specific numeric value
    public void setToValue(int v) {
        type = TokenType.VALUE;
        op = '$'; 
        val = v;
    }

    // return true if the Current Token is of the given TokenType
    public boolean equalsType(TokenType t) {
        return type == t;
    }

    // return true if the Current Token is of the OPERATOR TokenType
    //     and contains the given operator character
    public boolean equalsOperator(char c) {
        return type == TokenType.OPERATOR && op == c;
    }

    // Return the Operator for the current Token
    //   verify the current Token is of the OPERATOR TokenType
    public char getOperator() {
        // using $ to indicate an error value
        return type == TokenType.OPERATOR ? op : '$';
    }

    // Return the Value for the current Token
    //   verify the current token is of the value TokenType
    public int getValue() {
        // using -999 to indicate an error value
        return type == TokenType.VALUE ? val : -999;
    }
}