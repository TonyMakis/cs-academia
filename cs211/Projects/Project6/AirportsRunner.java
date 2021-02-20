import java.io.*;

public class AirportsRunner {
    public static void main (String[] args) {
   // set up an instance of the BufferedReader class to read from standard input
   BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
   
   // set up the data needed for the airport adjcency list
   TrafficNetwork airportsData = new TrafficNetwork();
   
   // call the method that reads and parses the input
   airportsData.processCommandLoop(br);
   
   System.out.println("\nGoodbye!\n");
 }
}
