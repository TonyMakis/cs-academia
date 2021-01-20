public class MyStack<T> {
    private int numNodes;
    private Node<T> top;  // Repurposed name for the head of a linked list of Nodes

    // *********** MyStack Constructors *************
    // Generic Constructor
    public MyStack() {
        this.numNodes = 0;
        this.top = null;
    }

    // *********** MyStack Functions **************
    public int getNumNodes() {
        return this.numNodes;
    }

    public T top() {
        return this.top.getDataItem();
    }

    public boolean isEmpty() {
        return this.numNodes == 0;
    }

    public void push(T newDataItem) {
        Node<T> newNode = new Node<T>(newDataItem);
        newNode.setPrevNode(this.top);
        this.top = newNode;
        this.numNodes++;
    }

    public void pop() {
        Node<T> tmp = this.top;
        this.top = this.top.getPrevNode();
        tmp.setPrevNode(null);
        this.numNodes--;
    }

    public T topPop() {
        T ret = this.top();
        this.pop();
        return ret;
    }

    public void clearStack() {
        Node<T> cur = this.top;
        Node<T> tmp = null;
        while(cur != null) {
            tmp = cur.getPrevNode();
            this.pop();
            cur = tmp;
        }
    }

    @Override
    public String toString() {  // TODO: NEED TO REVERSE PRINTING W/ ANOTHER STACK
        String result = "Stack is empty!";
        
        if(this.isEmpty())
            return result;
        else
            result = "";

        Node<T> cur = this.top;
        while(cur != null) {
            result += "| " + cur.getDataItem() + " | ";
            cur = cur.getPrevNode();
        }
        return result;
    } 
}
