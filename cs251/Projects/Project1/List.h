#ifndef LIST_H
#define LIST_H

#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

template <typename T>
class List {
  private:    
    struct Node {
      T     data;
      Node *next;

      Node(const T &d = T{}, Node *n = nullptr) : data{d}, next{n} {}
    };

  public:
    /**
     * Disclaimer:  C++ conventions tell us that we should have a couple
     * of additional constructors here (a copy constructor, assignment operator
     * etc.)
     *
     * However, to keep things simple for now we will ignore that convention
     */

    // [Con/De]structor
    List() { 
      init();
    }

    ~List() {
      clear();
    }

    /**
     * DESCRIPTION:  Makes the calling list empty (but the list still exists).
     */
    void clear(){
      Node *p = front;
      Node *pnext;

      while(p != nullptr) {
        pnext = p->next;
        delete p;
        nodes--;
        p = pnext;
      }
      front = back = nullptr;
    }

    /**
     * TODO:         COMPLETED!
     *
     * DESCRIPTION:  Returns the length of the calling list
     *
     * REQUIREMENTS: This is a working implementation taking linear time.
     *
     *               Your job (todo):  make modifications so that this
     *               operation becomes constant time (O(1)).
     *
     *               This task is different from most others in that most of
     *               the "real" work you do to make this work
     *	             in O(1) time will be in _other_ functions which affect
     *	             the length of lists.
     *
     *         HINT: You are free to add data members to the List class...
     *	             maybe for "bookkeeping"??
     */
    int length() const {
      // *** OLD CODE ***
      // Node *p = front;
      // int n=0;
      // while(p != nullptr) {
      //   n++;
      //   p = p->next;
      // }
      // return n;

      // *** NEW CODE ***
      // By adding a private node count tracking variable (nodes),
      // We can always get the length of the list in O(1) time!
      return nodes;
    }


  public:

    // Return true if the list is empty, false otherwise.
    bool is_empty() const {
      return front == nullptr;
    }


    void print() const {
      Node *p = front;

      std::cout << "[ "; 
      while(p != nullptr) {
        std::cout << p->data << " ";
        p = p->next;
      }
      std::cout << "]\n";
    }

    void push_front(const T & data) {
      front = new Node(data, front);

      if(back == nullptr)
        back = front;
      nodes++;
    }

    bool pop_front(T &val) {
      Node *tmp;

      if(is_empty())
        return false;
      val = front->data;

      tmp = front;
      front = front->next;
      delete tmp;
      nodes--;
      if(front==nullptr)
        back = nullptr;
      return true;
    }

    void push_back(const T & val) {
      Node *tmp = new Node(val, nullptr);

      if(front == nullptr) {
        front = back = tmp;
      }
      else {
        back->next = tmp;
        back = tmp;
      }
      nodes++;
    }

    /**        TODO: COMPLETED!
     *    
     *  DESCRIPTION: If list is empty, we do nothing and return false 
     *               otherwise, the last element in the list is removed, its
     *               value (data field) is assigned to the reference parameter 
     *               data (so the removed element can be 'passed-back' to the
     *               caller) and true is returned.
     *
     * REQUIREMENTS: Linear runtime (O(n) where n is the length of the list)
     *
     */
    bool pop_back(T &data) {
      if(is_empty())      // No Nodes Exist
        return false;

      T dummy;
      if(front == back) { // 1 Node Exists
        data = pop_front(dummy);
        return true;
      }
                          // 2+ Nodes Exist
      Node *p = front;
      while(p->next != back)
        p = p->next;

      data = back->data;
      delete back;
      nodes--;
      back = p;
      p->next = nullptr;

      return true;
    }

    bool remove_first(const T &x) {
      Node *p, *tmp;
      T dummy;

      if(front==nullptr) return false;
      if(front->data == x) {
        pop_front(dummy);
        return true;
      }
      p = front;
      while(p->next != nullptr) {
        if(x == p->next->data) {
          tmp = p->next;
          p->next = tmp->next;
          if(tmp == back)
            back = p;
          delete tmp;
          nodes--;
          return true;
        }
        p = p->next;
      }
      return false;
    }

    int slow_remove_all(const T &x) {
      int n=0;

      while(remove_first(x))
        n++;
      return n;
    }

    bool is_sorted() const {
      Node *p = front;

      while(p != nullptr && p->next != nullptr) {
        if(p->data > p->next->data)
          return false;
        p = p->next;
      }
      return true;
    }

    /**        TODO: COMPLETED!
     * 
     *  DESCRIPTION: Counts number of occurrences of x 
     *               in the list and returns that count.
     *
     *   REQUIRMENT: Linear runtime (O(n) where n is the length of the list)
     */
    int _count(const Node *f, const T &x, int counter) const {
      if (f == nullptr)
        return counter;
      if (f->data == x)
        counter++;
      return _count(f->next, x, counter);
    }

    int count(const T &x) const {
      int counter = 0;
      return _count(front, x, counter);
    }

    /**        TODO: COMPLETED!
     *
     *  DESCRIPTION: Returns true if calling List and parameter 
     *               List other contain exactly the same sequence of values.
     *               Returns false otherwise.
     *
     * REQUIREMENTS: Linear runtime (O(n) where n is MIN(len1,len2)
     *               and len1 and len2 are the respective lengths of the two lists.
     **/
    bool equal_to(const List<T> &other) const {
      if(length() != other.length()) // If the lists aren't same length, no point checking equality
        return false;

      if(length() == 0 && other.length() == 0) // If both lists are empty, they are technically equal
        return true;

      Node *p = front;
      Node *op = other.front;

      while(p != nullptr && op != nullptr) {
        if(p->data != op->data)
          return false;
        p = p->next;
        op = op->next;
      }

      return true;
    }

    /**        TODO: COMPLETED!
     *
     *  DESCRIPTION: Print list in reverse order
     *
     * REQUIREMENTS: Linear runtime (O(n) where n is the length of the list)
     *
     *         HINT: Try a recursive helper function
     */
    void _print_rev(const Node *f) const {
      if(f == nullptr)
        return;
      _print_rev(f->next);
      std::cout << f->data << " "; 
    }

    void print_rev() const {
      _print_rev(front);
    }

    /**        TODO: COMPLETED!
     *
     *  DESCRIPTION: Reverse list in-place
     *
     * REQUIREMENTS: Linear runtime (O(n) where n is the length of the list).
     *               Also, you cannot allocate any new memory!
     */
    void reverse() {
      if(front == nullptr)
        return;
      Node *prev = front, *cur = front, *next, *tmp;
      // Reverse next pointers of all nodes in List
      while(cur != nullptr) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
      }
      // Switch the front and back pointers
      tmp = front;
      front = back;
      back = tmp;
      back->next = nullptr;
    }

    /**        TODO: COMPLETED!
     * 
     *  DESCRIPTION: Same behavior/semantics as slow_remove_all. 
     *               However, this function must guarantee linear time 
     *               worst case runtime (hence, "fast").
     *
     * REQUIREMENTS: Linear runtime (O(n) where n is the length of the list)
     *
     *         NOTE: Your solution may be either recursive or iterative.
     **/
    int fast_remove_all(const T &x) {
      int numRemoved = 0;
      Node *prev = front, *cur = front;
      T dummy;
      // Reverse next pointers of all nodes in List
      while(cur != nullptr) {
        if(cur->data == x) {   // Match Found
          if(cur == front) {        // Front node needs removal
            prev = cur->next;
            cur = cur->next;
            pop_front(dummy);
          } else if(cur == back) {  // Back node needs removal
            cur = nullptr;
            pop_back(dummy);
          } else {                  // Middle node needs removal
            prev->next = cur->next;
            cur->next = nullptr;
            delete cur;
            nodes--;
            cur = prev->next;
          }
          numRemoved++;
        } else {               // No Match, continue
          prev = cur;
          cur = cur->next;
        }
      }
      return numRemoved;
    }

    /**        TODO: COMPLETED!
     *
     *  DESCRIPTION: Assumes given list is already in sorted order from
     *               smallest to largest and inserts x into the appropriate
     * 	             position retaining sorted-ness.
     *
     * REQUIREMENTS: Linear runtime (O(n) where n is the length of the list)
     * 
     *         NOTE: Duplicates are allowed, and if given list not sorted, 
     *               behavior is undefined/implementation dependent. We blame the 
     *               caller. So don't need to check ahead of time if it is sorted.
     */
    void insert_sorted(const T &x) {
      Node *prev = front, *cur = front;
      T dummy;
      // Reverse next pointers of all nodes in List
      while(cur != nullptr) {
        if(x <= cur->data) {   // Match Found
          if(cur == front) {        // Insert x in front of `front` node
            push_front(x);
            return;
          } else {                  // Insert before cur, and after prev
            Node *tmp = new Node(x, cur);
            prev->next = tmp;
            nodes++;
            return;
          }
        } else {               // No Match, continue
          prev = cur;
          cur = cur->next;
        }
      }
      // If we haven't inserted by now, then then x is greater
      // than all other elements, so push it to the back of the list
      push_back(x);
    }

    /**        TODO: COMPLETED!
     *
     *  DESCRIPTION: Assumes both list a and b are in sorted (non-descending) order 
     *               and merges them into a single sorted list with the same elements.  
     *
     * 	             This single sorted list is stored in a while b becomes empty.
     *
     * 	             If either of given lists are not sorted, we blame the caller and 
     *               the behavior is implementation dependent.
     *
     *               Condition in which both parameters are the same list (not merely
     *               "equal"), the function simply does nothing and returns. This can 
     *               be tested with simple pointer comparison.
     *
     *      EXAMPLE: Call a.merge_with(b)
     *            
     *               BEFORE:               |   AFTER:
     *            -------------------------|--------------------------------------  
     *               a: [2 3 4 9 10 30]    |   a: [2 3 4 5 8 8 9 10 11 20 30 40]
     *               b: [5 8 8 11 20 40]   |   b: []
     *
     * REQUIREMENTS: Runtime Must be linear in the length of the resulting
     *              merged list (or using variables above, O(a.length() + b.length()).
     *              
     *              It should not allocate ANY new list nodes -- it should just 
     *              re-link existing nodes.
     */
    void merge_with(List<T> &other){
      if(this == &other) { // If implicit & explicit list params point to the same List, return
        std::cerr << "Warning: List::merge_with(): calling object same as parameter";
        std::cerr << "\n          lists unchanged\n";
        return;
      }
      
      Node *b = other.front, *cur = front, *prev = front, *tmp; // b iterates List B, prev/cur iterate List A

      while(b != nullptr) {
        // Get into position in List A for an insertion in ASC sorted order
        while(cur != nullptr && b->data > cur->data) {
          prev = cur;
          cur = cur->next;
        }
        // Move the main pointer for List B to next node after its tracking original (w/ tmp)
        tmp = b;
        b = b->next;
        // If we are at front of List A, we set the new front to incoming node
        // otherwise, point current position in List A to incoming node
        if(cur == front)
          front = tmp;
        else
          prev->next = tmp;
        // Point incoming node to the rest of List A, reset List B front pointer
        tmp->next = cur;
        other.front = b;
        // Adjust lengths of List B & A, respectively
        other.nodes--;
        nodes++;
        // If we are at the end of List A, we point the current position in List A
        // to the incoming node, as well as reposition both List A & B's new back, otherwise
        // move previous pointer to incoming node
        if(cur == nullptr) {
          cur = tmp;
          back = tmp;
          if(b == nullptr)
            other.back = b;
        } else {
          prev = tmp;
        }
      }
    }

    /**        TODO: COMPLETED!
     * 
     *  DESCRIPTION: Makes a "deep copy" of the given List A and returns it (as a List pointer).
     *
     *         NOTE: This functionality would normally be folded into a "copy constructor"
     *
     */
    List<T> * clone() const {
      List<T> *ret = new List<T>();
      Node *cur = front;

      while(cur != nullptr) {
        ret->push_back(cur->data);
        cur = cur->next;
      }

      return ret;
    }

    /**        TODO: COMPLETED!
     *
     *  DESCRIPTION: Removes the first k elements from the calling list which are used 
     *               to form a new list which is then returned.
     *
     *		           If n is the length of the given list, we have the following boundary conditions:
     *
     *		           if k == 0:
     *			            Calling list unchanged and an empty list returned
     *		           if k >= n:
     *			            Calling becomes empty and a list w/ elements previously in list is returned.
     *
     *      EXAMPLE: 
     * 
     *          EX.1) Call a.prefix(3)
     *            
     *                     BEFORE:         |       AFTER:
     *            -------------------------|-----------------------
     *               a: [2 3 9 7 8]        |         a: [7 8]
     *               k: 3                  |   @return: [2 3 9]
     *
     *		      EX.2) Call a.prefix(0)     
     *              
     *                     BEFORE:         |       AFTER:
     *            -------------------------|-----------------------
     *               a: [2 3 9 7 8]        |         a: [2 3 9 7 8]
     *               k: 0                  |   @return: []
     * 
     *		      EX.3) Call a.prefix(5)     
     *              
     *                     BEFORE:         |       AFTER:
     *            -------------------------|-----------------------
     *               a: [2 3 9 7 8]        |         a: []
     *               k: 5                  |   @return: [2 3 9 7 8]
     *
     *
     * REQUIREMENTS: THETA(n) worst case where n is the length of the given list
     *
     *               Ordering of the returned prefix should be the same as in the given list
     *
     *               For full credit, no new nodes should be allocated or deallocated; you should just 
     *               "re-use" the existing nodes. However, you will need to allocate a List object for
     *               the returned prefix.
     */
    List<T> * prefix(unsigned int k) {
      List<T> *ret = new List<T>();
      Node *cur = front;

      if(this->is_empty()) return ret;
      if(k < 1) return ret;

      for(int i = 0; i < k - 1; i++)
        cur = cur->next;
      
      ret->front = front;
      ret->back = cur;
      ret->nodes = k;

      if(cur == nullptr) {
        front = nullptr;
        back = nullptr;
        nodes = 0;
      } else {
        front = cur->next;
        cur->next = nullptr;
        nodes -= k;
      }

      return ret;
    }

    /**        TODO: COMPLETED!
     *
     *  DESCRIPTION: Removes all elements of the given list which are less than or equal 
     *               to a given value (cutoff). A list containing the removed elements is returned.
     *
     *      EXAMPLE: 
     * 
     *          EX.1) Call a.filter_leq(4)
     *            
     *                     BEFORE:         |       AFTER:
     *            -------------------------|------------------------
     *               a: [4 9 2 4 8 12 7 3] |         a: [9 8 12 7]
     *               k: 4                  |   @return: [4 2 4 3]
     * 
     *          EX.2) Call a.filter_leq(6)
     *            
     *                     BEFORE:         |       AFTER:
     *            -------------------------|------------------------
     *               a: [6 5 2 1]          |         a: []
     *               k: 6                  |   @return: [6 5 2 1]
     *
     * REQUIREMENTS: THETA(n) where n is the length of the given list
     *
     *               The ordering of the returned list should be the same as in the given list
     *
     *               For full credit, no new nodes should be allocated or deallocated;
     *		           you should just "re-use" the existing nodes. However, you will
     *		           need to allocate a list structure itself (i.e., for the returned list).
     */
    List<T> * filter_leq(const T & cutoff) {
      List<T> *ret = new List<T>();
      Node *cur = front, *prev = front, *tmp;

      if(this->is_empty()) return ret;

      while(cur != nullptr) {
        if(cur->data <= cutoff) { // leq to cutoff, so move from this list to ret list
          tmp = cur;
          cur = cur->next;

          if(tmp == front) {
            prev = cur;
            front = cur;
          } else {
            prev->next = cur;
            if(tmp == back)
              back = prev;
          }
          tmp->next = nullptr;

          if(ret->is_empty())
            ret->front = tmp;
          else
            ret->back->next = tmp;
          ret->back = tmp;

          nodes--;
          ret->nodes++;
        } else {
          prev = cur;
          cur = cur->next;
        }
      }

      return ret;
    }

    /**        TODO: COMPLETED!
     *
     *  DESCRIPTION: Concatenates the implicit list param with the explicit list param. The resulting 
     *               concatenation is reflected the calling list; the explicit param list becomes empty.
     * 
     *               Condition in which both parameters are the same list (not merely
     *               "equal"), the function simply does nothing and returns. This can 
     *               be tested with simple pointer comparison.
     *
     *      EXAMPLE: Call a.concat(b)
     *            
     *               BEFORE:       |   AFTER:
     *            -----------------|--------------------- 
     *               a: [2 9 1]    |   a: [2 9 1 5 1 2]
     *               b: [5 1 2]    |   b: []
     *
     * REQUIREMENTS: The runtime should be O(1)
     */
    void concat(List<T> &other) {
      if(this == &other) { // If implicit & explicit list params point to the same List, return
        std::cerr << "Warning: List::concat(): calling object same as parameter";
        std::cerr << "\n          lists unchanged\n";
        return;
      }
      if(other.is_empty()) {
        return;
      }

      if(this->is_empty()) {
        front = other.front;
      } else {
        back->next = other.front;
      }
      
      back = other.back;
      other.front = nullptr;
      other.back = nullptr;
      nodes += other.nodes;
      other.nodes = 0;
    }


    /**        TODO: 
     *
     *  DESCRIPTION: Compares the calling list with parameter list "LEXICOGRAPHICALLY" 
     *               (essentially a generalization of dictionary ordering).
     *
     *               Link:  https://en.wikipedia.org/wiki/Lexicographical_order
     *
     *               - If the two lists are identical, 0 is returned
     *               - If the calling list is lexically before the other list, -1 is returned
     *               - Otherwise, the parameter list is lexically before the calling list, 1 is returned
     *
     *      EXAMPLE: Call a.compare_with(b)
     *
     *          EX.1) The empty list is lexically before all non-empty lists
     *
     *          EX.2) [2 5 1], [3 1 1 1 1] => return -1
     *
     *          EX.3) [4 1 3], [4 1 3 0 0 0] => return -1
     *
     *          EX.4) [4 5 6 1 2 3 9 9 9], [4 5 6 1 4 0 0] => return -1
     *                                     
     *          EX.5) ["egg", "goat"], ["egg", "globe", "apple"] => return 1
     *
     *          EX.6) ["zebra", "fun"], ["zebra", "funny"] => return -1
     */
    int compare_with(const List<T> &other) const {
      if(this == &other) { // If implicit & explicit list params point to the same List, return
        std::cerr << "Warning: List::compare_with(): calling object same as parameter";
        std::cerr << "\n          lists unchanged\n";
        return INT_MIN;
      }

      if(this->equal_to(other)) return 0;

      if(this->is_empty()) return -1;
      else if(other.is_empty()) return 1;

      Node *cur = front;
      Node *otherCur = other.front;

      while(cur != nullptr && otherCur != nullptr) {
        if(cur->data < otherCur->data) return -1;
        else if(cur->data > otherCur->data) return 1;
        cur = cur->next;
        otherCur = otherCur->next;
      }

      if(cur == nullptr) return -1;
      else if(otherCur == nullptr) return 1;
    }

    /**        TODO: COMPLETED!
     *
     *  DESCRIPTION: Constructs a new list of the same length as the calling list
     *               with the value stored at position `i` of the new list is the MAXIMUM
     *               value in the suffix (or tail) of the calling list starting from position `i`.
     *
     *               This new list is returned and the calling list is unchanged.
     *
     *      EXAMPLE: Call a.suffix_maxes()
     *            
     *                        BEFORE:             |               AFTER:
     *            --------------------------------|-------------------------------
     *               a: [6 -18 12 4 1 7 2 5 4]    |      a: [6 -18 12 4 1 7 2 5 4]
     *                                            |   @ret: [12 12 12 7 7 7 5 5 4]
     *
     *              (as a sub-example, the marked entry in the new list (marked with '^') is the max 
     *              of the marked suffix in the given list (marked with a bunch of '^'s).
     *
     * REQUIREMENTS: Linear runtime (O(n) where n is the length of the list).
     *               Calling list is unchanged.
     *
     */
    int _suffix_maxes(int sufMax, const Node *f, List<T> &ret) const {
      if(f == nullptr) return INT_MIN;

      sufMax = _suffix_maxes(sufMax, f->next, ret);

      if(f->data > sufMax) {
        ret.push_front(f->data);
        return f->data;
      } else {
        ret.push_front(sufMax);
        return sufMax;
      }

    }

    List<T> * suffix_maxes() const {
      List<T> *ret = new List<T>();
      int sufMax;
      _suffix_maxes(sufMax, front, *ret);
      return ret;
    }


  private:
    Node *front;
    Node *back;
    int  nodes; /** TODO: COMPLETED! => Added to keep track of List length */

    void init() {
      front = nullptr;
      back = nullptr;
      nodes = 0; /** TODO: COMPLETED! => New lists have length 0! */
    }
};

#endif
