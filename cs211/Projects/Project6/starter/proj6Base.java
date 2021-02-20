import java.io.*;
import java.util.*;

public class Proj6Base {
 public static void main (String[] args)
 {
   // set up an instance of the BufferedReader class to read from standard input
   BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
   
   // set up the data needed for the airport adjcency list
   TravelNetwork airportData = new TravelNetwork();
   
   // call the method that reads and parses the input
   airportData.processCommandLoop(br);
   
   System.out.println("Goodbye");
 }
}
   
class TravelNetwork
{
  // Create the Data Members for the Travel Network here
  
  
  // Use a constructor to initialize the Data Members for Travel Network
  // public TravelNetwork()
  // {
  // 
  // }
  
  
  public void processCommandLoop (BufferedReader br)
  {
    try {  //try-catch clauses are needed since BufferedReader and Scanner classes
           //  throw exceptions on errors
    String inline = br.readLine();   // get a line of input
    Scanner sc;
    
   // loop until all lines are read from the input
   while (inline != null)
   {
     sc = new Scanner(inline);   // process each line of input using the Scanner iterators
     String command = sc.next();
     System.out.println("*" + command + "*");
     
     if(command.equals("q") == true)
       System.exit(1);
     
     else if(command.equals("?") == true)
       showCommands();
     
     else if(command.equals("t") == true)
       doTravel(sc);
     
     else if(command.equals("r") == true)
       doResize(sc);

     else if(command.equals("i") == true)
       doInsert(sc);

     else if(command.equals("d") == true)
       doDelete(sc);

     else if(command.equals("l") == true)
       doList(sc);

     else if(command.equals("f") == true)
       doFile(sc);

     else if(command.equals("#") == true)
       ;
     
     else
       System.out.println("Command is not known: " + command);
     
     inline = br.readLine();   // get the next line of input

   }
  }
  catch (IOException ioe)
  {
    System.out.println("Error in Reading - Assuming End of File");
  }
 }
 
 public void showCommands()
 {
   System.out.println("The commands for this project are:");
   System.out.println("  q ");
   System.out.println("  ? ");
   System.out.println("  # ");
   System.out.println("  t <int1> <int2> ");
   System.out.println("  r <int> ");
   System.out.println("  i <int1> <int2> ");
   System.out.println("  d <int1> <int2> ");
   System.out.println("  l ");
   System.out.println("  f <filename> ");
 }
 
 public void doTravel(Scanner sc)
 {
   int val1 = 0;
   int val2 = 0;
   
   if ( sc.hasNextInt() == true )
     val1 = sc.nextInt();
   else
   {
     System.out.println("Integer value expected");
     return;
   }
   
   if ( sc.hasNextInt() == true )
     val2 = sc.nextInt();
   else
   {
     System.out.println("Integer value expected");
     return;
   }
   
   System.out.println("Performing the Travel Command from " + val1 +
                       " to " + val2);
   
 }
 
 public void doResize(Scanner sc)
 {
   int val1 = 0;
   
   if ( sc.hasNextInt() == true )
     val1 = sc.nextInt();
   else
   {
     System.out.println("Integer value expected");
     return;
   }
   
    System.out.println("Performing the Resize Command with " + val1 );
 

 }
 
 public void doInsert(Scanner sc)
 {

 }
 
 public void doDelete(Scanner sc)
 {

 }
 
 public void doList(Scanner sc)
 {
   
 }
 
 public void doFile(Scanner sc)
 {
   String fname = null;
   
   if ( sc.hasNext() == true )
     fname = sc.next();
   else
   {
     System.out.println("Filename expected");
     return;
   }
   
   System.out.println("Performing the File command with file: " + fname);
   
   // next steps:  (if any step fails: print an error message and return ) 
   //  1. verify the file name is not currently in use
   //  2. open the file
   //  3. create a new instance of BufferedReader
   //        BufferedReader br = new BufferedReader (new FileReader ("MyFileReader.txt"));
   //  4. recursively call processCommandLoop() with this new instance of BufferedReader as the parameter
   //  5. close the file when processCommandLoop() returns
 }
}