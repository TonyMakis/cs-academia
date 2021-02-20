public class Airport<T> extends MyLinkedList<T> {
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_RED = "\u001B[31m";
    public static final String ANSI_PURPLE = "\u001B[35m";

    private boolean visited;

    // *********** Airport Constructors *************
    // Generic Constructor
    public Airport() {
        super();
        this.visited = false;
    }

    public boolean getVisitedStatus() {
        return this.visited;
    }

    public void setVisitedStatus(boolean newStatus) {
        this.visited = newStatus;
    }

    @Override
    public String toString() {
        String result = ANSI_RED + "Airport has no connections!" + ANSI_RESET;
        
        if(this.isEmpty())
            return result;
        else
            result = "";

        Node<T> cur = this.getHeadNode();
        while(cur != null) {
            if(cur == this.getTailNode())
                result += " " + ANSI_PURPLE + cur.getDataItem() + ANSI_RESET;
            else
                result += " " + ANSI_PURPLE + cur.getDataItem() + ANSI_RESET + " , ";
            cur = cur.getNextNode();
        }
        return result;
    } 
}
