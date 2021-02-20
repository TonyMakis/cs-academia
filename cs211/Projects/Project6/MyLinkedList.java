public class MyLinkedList<T> {
    private int numNodes;
    private Node<T> head;
    private Node<T> tail;

    // *********** MyLinkedList Constructors *************
    // Generic Constructor
    public MyLinkedList() {
        this.numNodes = 0;
        this.head = null;
        this.tail = null;
    }

    // *********** MyLinkedList Methods **************
    public int getNumNodes() {
        return this.numNodes;
    }

    public Node<T> getHeadNode() {
        return this.head;
    }

    public Node<T> getTailNode() {
        return this.tail;
    }

    public boolean isEmpty() {
        return this.numNodes == 0;
    }
    
    public boolean itemIsInList(T dataItem) {
        Node<T> cur = this.head;
        while(cur != null) {
            if(dataItem instanceof String){
                if(cur.getDataItem().equals(dataItem))
                    return true;
            } else {
                if(cur.getDataItem() == dataItem)
                    return true;
            }
            cur = cur.getNextNode();
        }
        return false;
    }

    public void append(T newDataItem) {
        Node<T> newNode = new Node<T>(newDataItem);

        if(this.isEmpty()) {
            this.head = newNode;
            this.tail = newNode;
        } else {
            this.tail.setNextNode(newNode);
            this.tail = newNode;
        }

        this.numNodes++;
    }

    private void removeNode(Node<T> prev, Node<T> cur) {
        Node<T> tmp = null;
        if(cur == this.head && cur == this.tail) {
            this.head = null;
            this.tail = null;
        } else if(cur == this.head) {
            tmp = this.head;
            this.head = this.head.getNextNode();
            tmp.setNextNode(null);
        } else if(cur == this.tail) {
            this.tail = prev;
            prev.setNextNode(null);
        } else {
            prev.setNextNode(cur.getNextNode());
            cur.setNextNode(null);
        }
        this.numNodes--;
    }

    public void delete(T dataItem) {
        if(this.isEmpty()) return;

        Node<T> prev = this.head;
        Node<T> cur = this.head;

        while(cur != null) {
            if(dataItem instanceof String){
                if(cur.getDataItem().equals(dataItem))
                    removeNode(prev, cur);
            } else {
                if(cur.getDataItem() == dataItem)
                    removeNode(prev, cur);
            }
            prev = cur;
            cur = cur.getNextNode();
        }
    }

    public void clearList() {
        if(this.isEmpty()) return;
        // Obliterate all the nodes, one at a time
        while(this.head != null) {
            removeNode(null, this.head);
        }
    }

    @Override
    public String toString() {
        String result = "Linked list is empty!";
        
        if(this.isEmpty())
            return result;
        else
            result = "";

        Node<T> cur = this.head;
        while(cur != null) {
            result += "| " + cur.getDataItem() + " | ";
            cur = cur.getNextNode();
        }
        return result;
    } 
}
