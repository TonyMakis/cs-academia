/* recall the name of the public class in the file MUST match the filename
 * (without the file extention)                                            */
public class InfixExpressionRunner {
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_YELLOW = "\u001B[33m";

    // Command Format Checking
    public static void cmdUsageMsg(String cmd) {
        System.out.print(ANSI_YELLOW + "\n\tUsage: " + cmd + " [OPTIONALS]\n\n");
        System.out.print("\tOPTIONAL ARGUMENT:\n\n");
        System.out.print("\t\t-d, \temit debugging messages\n" + ANSI_RESET);
    }

    public static void printCommands() {
        System.out.print("The commands for this program are:\n\n");
        System.out.print("q - to quit the program\n");
        System.out.print("? - to list the accepted commands\n");
        System.out.print("or any infix mathematical expression using operators of (), *, /, +, -\n");
    }

    public static boolean isMathOperator(char op) {
        return op == '*' || op == '/' || op == '+' || op == '-';
    }

    public static boolean isPriorityOperator(char op) {
        return op == '*' || op == '/';
    }

    public static int canReturnTop(MyStack<Integer> valStack) {
        int ret = -999;
        if(valStack.isEmpty()) {
            System.out.println("Error: Attempted getting top of empty value stack.");
        } else {
            ret = valStack.top();
            valStack.pop();
        }
        return ret;
    }

    public static int eval(int val1, char op, int val2) {
        int ret = -999;
        if(op == '*') {
            ret = val1 * val2;
        } else if(op == '/') {
            ret = val1 / val2;
        } else if(op == '+') {
            ret = val1 + val2;
        } else if(op == '-') {
            ret = val1 - val2;
        } else {
            System.out.println("Error: Operator is not \'*\', \'/\', \'+\', or \'-\'.");
        }
        return ret;
    }

    public static void popAndEval(
        MyStack<Character> opStack, MyStack<Integer> valStack
    ) {
        char op = opStack.topPop();
        int v2 = canReturnTop(valStack);
        int v1 = canReturnTop(valStack);
        int v3 = eval(v1, op, v2);
        valStack.push(v3);
    }

    public static void processExpression(
        Token inputToken, TokenReader tr, boolean debug
    ) {
        MyStack<Integer> values = new MyStack<Integer>();
        MyStack<Character> operators = new MyStack<Character>();
        int val; char op;
        values.clearStack();
        operators.clearStack();

        /* Loop until the expression reaches its End */
        while(!inputToken.equalsType(TokenType.EOLN)) {
            if(inputToken.equalsType(TokenType.VALUE)) {
                val = inputToken.getValue();
                if(debug) System.out.print ("Val: " + val + ", "); 
                values.push(val);
            } else if(inputToken.equalsType(TokenType.OPERATOR)) {
                op = inputToken.getOperator();
                if(debug) System.out.print ("OP: " + op + ", ");
                if(op == '(')
                    operators.push(op);
                if(inputToken.getOperator() == '+' || op == '-') {
                    while(!operators.isEmpty() && isMathOperator(operators.top()))
                        popAndEval(operators, values);
                    operators.push(op);
                }
                if(op == '*' || op == '/') {
                    while(!operators.isEmpty() && isPriorityOperator(operators.top()))
                        popAndEval(operators, values);
                    operators.push(op);
                }
                if(op == ')') {
                    while(!operators.isEmpty() && operators.top() != '(')
                        popAndEval(operators, values);
                    if(operators.isEmpty())
                        System.out.println("\nOps. stack empty; where is other \'(\'?");
                    else
                        operators.pop();
                }
            }
            /* get next token from input */
            inputToken = tr.getNextToken ();
        } /* The expression has reached its end */

        while(!operators.isEmpty())
            popAndEval(operators, values);

        int solution = values.topPop();
        if(values.isEmpty())
            System.out.println("\nThe solution is " + solution + ".");
        else
            System.out.println("\nValue stack not empty, unknown error encountered!");

        System.out.println();
    }

    // The error statements in this program should only occur 
    // if an invalid infix expression is given as input. We are
    // not required to check for any other errors in the input.
    public static void main (String[] args) {
        boolean debug_mode;
        int argc = args.length;

        if(argc < 1) {
            debug_mode = false;
        } else if(argc == 1 && args[0].equals("-d"))
            debug_mode = true;
        else {
            cmdUsageMsg("java InfixExpression");
            return;
        }
        
        Token inputToken;
        TokenReader tr = new TokenReader();
        
        System.out.print("Starting Expression Evaluation Program\n\n");
        System.out.print("Enter Expression: ");

        inputToken = tr.getNextToken();
        
        while(!inputToken.equalsType(TokenType.QUIT)) {
            if(inputToken.equalsType(TokenType.HELP)) {
                printCommands();
                tr.clearToEoln();
            } else if(inputToken.equalsType(TokenType.ERROR)) {
                System.out.print("Invalid Input - For a list of valid commands, type ?\n");
                tr.clearToEoln();
            } else if(inputToken.equalsType(TokenType.EOLN)) {
                System.out.print("Blank Line - Do Nothing\n");
            } else {
                processExpression(inputToken, tr, debug_mode);
            } 
            System.out.print("\nEnter Expression: ");
            inputToken = tr.getNextToken();
        }
        System.out.print("Quitting Program\n");
        return;
    }
}