public class Node<T> { // Generic Node Class
    private T dataItem;
    private Node<T> prev;

    // *********** Node Constructors *************
    // Generic Constructor
    public Node(T dataItem) {
        this.dataItem = dataItem;
        this.prev = null;
    }

    // Generic Constructor; default values required
    public Node(T dataItem, Node<T> prev) {
        this.dataItem = dataItem;
        this.prev = prev;
    }

    // *********** Node Functions **************
    // Getters
    public T getDataItem() {
        return this.dataItem;
    }

    public Node<T> getPrevNode() {
        return this.prev;
    }
    // Setters
    public void setDataItem(T newDataItem) {
        this.dataItem = newDataItem;
    }

    public void setPrevNode(Node<T> newPrevNode) {
        this.prev = newPrevNode;
    }
}
