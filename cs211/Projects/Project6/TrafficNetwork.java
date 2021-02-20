import java.io.*;
import java.util.*;

public class TrafficNetwork {
  // Create the Data Members for the TrafficNetwork here
  public static final String ANSI_RESET = "\u001B[0m";
  public static final String ANSI_GREEN = "\u001B[32m";
  public static final String ANSI_YELLOW = "\u001B[33m";
  public static final String ANSI_CYAN = "\u001B[36m";
  public static final String ANSI_RED = "\u001B[31m";

  private MyLinkedList<String> openedFiles;
  private Airport<Integer>[] trafficNetwork;
  private int trafficNetworkSize;

  // *********** TrafficNetwork Constructors *************
  // Generic Constructor
  public TrafficNetwork() {
    this.openedFiles = new Airport<String>();
    this.trafficNetwork = null;
    this.trafficNetworkSize = 0;
  }
  
  // *********** TrafficNetwork Methods **************
  // Public Methods
  public void processCommandLoop(BufferedReader br) {
    try {
      String inline = br.readLine();
      Scanner sc;

      while (inline != null) {
        sc = new Scanner(inline);
        String command = sc.next();
        System.out.println(ANSI_GREEN + "*" + command + "*" + ANSI_RESET);
        
        if(command.equals("q") == true) System.exit(1);
        else if(command.equals("?") == true) showCommands();
        else if(command.equals("t") == true) doTravel(sc);
        else if(command.equals("r") == true) doResize(sc);
        else if(command.equals("i") == true) doInsert(sc);
        else if(command.equals("d") == true) doDelete(sc);
        else if(command.equals("l") == true) doList(sc);
        else if(command.equals("f") == true) doFile(sc);
        else if(command.equals("#") == true) ;
        else System.out.println(ANSI_YELLOW + "Command is not known: " +
                                command + ANSI_RESET);

        inline = br.readLine();
      }
    } catch (IOException ioe) {
      System.out.println(ANSI_YELLOW +
                         "Error in Reading - Assuming End of File" +
                         ANSI_RESET);
    }
  }
 
  // Private Methods
  private void showCommands() {
    System.out.println(ANSI_CYAN + "The commands for this project are:");
    System.out.println("  q ");
    System.out.println("  ? ");
    System.out.println("  # ");
    System.out.println("  t <int1> <int2> ");
    System.out.println("  r <int> ");
    System.out.println("  i <int1> <int2> ");
    System.out.println("  d <int1> <int2> ");
    System.out.println("  l ");
    System.out.println("  f <filename> " + ANSI_RESET);
  }
 
  private void markAllAirportsUnvisted() {
    for(int i = 1; i <= this.trafficNetworkSize; i++)
      this.trafficNetwork[i].setVisitedStatus(false);
  }

  private void dfs(int x, int y) {
    markAllAirportsUnvisted();
    if(_dfs(x, y))
        System.out.println(ANSI_GREEN + "You can get from airport " + x + 
              " to airport " + y + " in one or more flights" + ANSI_RESET);
    else
        System.out.println(ANSI_RED + "You can NOT get from airport " + x + 
               " to airport " + y + " in one or more flights" + ANSI_RESET);
  }

  private boolean _dfs(int a, int b) {
    Node<Integer> cur = this.trafficNetwork[a].getHeadNode();
    while(cur != null) {
      if(cur.getDataItem() == b)
        return true;
      if(!this.trafficNetwork[cur.getDataItem()].getVisitedStatus()) {
        this.trafficNetwork[cur.getDataItem()].setVisitedStatus(true);
        if(_dfs(cur.getDataItem(), b)) {
          return true;
        }
      }
      cur = cur.getNextNode();
    }
    return false;
  }

  private void doTravel(Scanner sc) {
    int air1 = 0;
    int air2 = 0;

    if(sc.hasNextInt() == true) 
      air1 = sc.nextInt();
    else {
      System.out.println(ANSI_YELLOW + "Integer value expected" + ANSI_RESET);
      return;
    }

    if(sc.hasNextInt() == true) 
      air2 = sc.nextInt();
    else {
      System.out.println(ANSI_YELLOW + "Integer value expected" + ANSI_RESET);
      return;
    }

    System.out.println(ANSI_CYAN +
                       "Performing the Travel Command from " + air1 + " to " + air2 +
                       ANSI_RESET);
    dfs(air1, air2);
  }

  @SuppressWarnings("unchecked")
  // We suppress unchecked type casting warning => to avoid this, when making
  // the array of generic Airports, this could be avoided using builtin java
  // collections; of course, that is not allowed in this project, w/ homegrown LL
  private void doResize(Scanner sc) {
    int networkSize = 0;

    if(sc.hasNextInt() == true)
      networkSize = sc.nextInt();
    else {
      System.out.println(ANSI_YELLOW + "Integer value expected" + ANSI_RESET);
      return;
    }

    if(networkSize < 1) {
      System.out.println(ANSI_YELLOW + "Integer value greater than 0 expected" + ANSI_RESET);
      return;
    }

    System.out.println(ANSI_CYAN +
                       "Performing the Resize Command with " + networkSize +
                       ANSI_RESET);

    if(this.trafficNetworkSize > 0) { // Obliterate previous travel network
      for(int i = 1; i <= this.trafficNetworkSize; i++) {
        this.trafficNetwork[i].clearList();
        this.trafficNetwork[i] = null;
      }
      this.trafficNetwork = null;
    }
    // The following type cast is why unchecked warning suppressed in this method
    // (The + 1 is to allow for direct mapping of integers -> Skipping 0th index!)
    // => Type casting from Airport[] to Airport<Integer>[]
    this.trafficNetwork = new Airport[networkSize + 1];
    this.trafficNetworkSize = networkSize;
    for(int i = 1; i <= this.trafficNetworkSize; i++) {
      this.trafficNetwork[i] = new Airport<Integer>();
    }
  }

  private boolean airportsExist(int air1, int air2) {
    boolean exist = true;
    if(air1 < 1 || air1 > this.trafficNetworkSize) {
      System.out.println(ANSI_YELLOW +
                         "Error: Airport " + air1 + " doesn't exist in the network" +
                         ANSI_RESET);
      exist = false;
    }
    if(air2 < 1 || air2 > this.trafficNetworkSize) {
      System.out.println(ANSI_YELLOW +
                         "Error: Airport " + air2 + " doesn't exist in the network" +
                         ANSI_RESET);
      exist = false;
    }
    return exist;
  }
 
  private boolean shouldAddEdge(int air1, int air2) {
    boolean add = true;
    if(airportsExist(air1, air2)) {
      if(this.trafficNetwork[air1].itemIsInList(air2)) {
        System.out.println(ANSI_YELLOW + 
                           "Error: Airport " + air2 + " already added to Airport " +
                           air1 + "'s' List" + ANSI_RESET);
        add = false;
      }
    } else {
      add = false;
    }
    return add;
  }

  private void doInsert(Scanner sc) {
    int air1 = 0;
    int air2 = 0;

    if(sc.hasNextInt() == true) 
      air1 = sc.nextInt();
    else {
      System.out.println(ANSI_YELLOW + "Integer value expected" + ANSI_RESET);
      return;
    }

    if(sc.hasNextInt() == true) 
      air2 = sc.nextInt();
    else {
      System.out.println(ANSI_YELLOW + "Integer value expected" + ANSI_RESET);
      return;
    }

    if(this.trafficNetworkSize > 0 && shouldAddEdge(air1, air2)) {
      System.out.println(ANSI_CYAN +
                         "Performing the Insert Command for edge from " +
                         air1 + " to " + air2 + ANSI_RESET);
      this.trafficNetwork[air1].append(air2);
    } else {
      System.out.println(ANSI_YELLOW + 
                         "\t-> Could not perform insertion, moving on" +
                         ANSI_RESET);
    }
  }
 
  private void doDelete(Scanner sc) {
    int air1 = 0;
    int air2 = 0;

    if(sc.hasNextInt() == true) 
      air1 = sc.nextInt();
    else {
      System.out.println(ANSI_YELLOW + "Integer value expected" + ANSI_RESET);
      return;
    }

    if(sc.hasNextInt() == true) 
      air2 = sc.nextInt();
    else {
      System.out.println(ANSI_YELLOW + "Integer value expected" + ANSI_RESET);
      return;
    }

    if(this.trafficNetworkSize > 0 && airportsExist(air1, air2)) {
      System.out.println(ANSI_CYAN +
                         "Performing the Delete Command for edge from " +
                         air1 + " to " + air2 + ANSI_RESET);
      this.trafficNetwork[air1].delete(air2);
    } else {
      System.out.println(ANSI_YELLOW +
                         "Could not perform deletion, moving on" +
                         ANSI_RESET);
    }
  }
 
  private void doList(Scanner sc) {
    System.out.println(ANSI_GREEN + "\tTravel Network List:\n" + ANSI_RESET);
    for(int i = 1; i <= this.trafficNetworkSize; i++) {
      System.out.println(ANSI_GREEN + "Airport " + i + ": " + ANSI_RESET +
                         this.trafficNetwork[i].toString());
    }
    System.out.println();
  }
 
  private void doFile(Scanner sc) { // Open a file to pass cmd-control to
    String fname = null;

    if(sc.hasNext() == true)
      fname = sc.next();
    else {
      System.out.println(ANSI_YELLOW +
                         "Filename expected" +
                         ANSI_RESET);
      return;
    }

    if(this.openedFiles.itemIsInList(fname)) {
      System.out.println(ANSI_YELLOW +
                         "The file given is already in use: " + fname +
                         ANSI_RESET);
      return;
    } else { // File not opened, so we start tracking it before opening it
      this.openedFiles.append(fname);
      System.out.println(ANSI_CYAN +
                         "Performing the File command with file: " + fname +
                         ANSI_RESET);
    }

    try {
      BufferedReader br = new BufferedReader(new FileReader(fname));
      this.processCommandLoop(br);
      br.close();
      this.openedFiles.delete(fname);
    } catch (Exception e) {
      System.err.format(ANSI_YELLOW +
                        "Exception occurred trying to read '%s'.\n" +
                        ANSI_RESET, fname);
    }
  }
}
