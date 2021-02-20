public class Node<T> { // Generic Node Class
    private T dataItem;
    private Node<T> next;

    // *********** Node Constructors *************
    // Generic Constructor
    public Node(T dataItem) {
        this.dataItem = dataItem;
        this.next = null;
    }

    // Generic Constructor; default values required
    public Node(T dataItem, Node<T> next) {
        this.dataItem = dataItem;
        this.next = next;
    }

    // *********** Node Functions **************
    // Getters
    public T getDataItem() {
        return this.dataItem;
    }

    public Node<T> getNextNode() {
        return this.next;
    }
    // Setters
    public void setDataItem(T newDataItem) {
        this.dataItem = newDataItem;
    }

    public void setNextNode(Node<T> newNextNode) {
        this.next = newNextNode;
    }
}
