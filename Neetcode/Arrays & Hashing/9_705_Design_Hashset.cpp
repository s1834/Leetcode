class MyHashSet {
    private:
        struct ListNode {
            int val;
            ListNode *next;
            ListNode(int x) : val(x), next(nullptr) {}
        };
        ListNode *head;
    
    public:
        MyHashSet() {
            head = nullptr;
        }
        
        void add(int key) {
            if (!head) {
                head = new ListNode(key);
                return;
            }
    
            if(contains(key)) return;
    
            ListNode *ptr = head;
            while(ptr && ptr->next) ptr = ptr->next;
            ListNode *newNode = new ListNode(key);
            ptr->next= newNode;
        }
        
        void remove(int key) {
            if (!head) return;
    
            if (head->val == key) {
                head = head->next;
                return;
            }
            
            ListNode *ptr1 = head, *ptr2 = head;
            while(ptr1 && ptr2) {
                if(ptr2->val == key) ptr1->next = ptr2->next;
                ptr1 = ptr2;
                ptr2 = ptr1->next;
            }
        }
        
        bool contains(int key) {
            ListNode *ptr = head;
            while(ptr) {
                if(ptr->val == key) return true;
                ptr = ptr->next;
            }
            return false;
        }
    };
    
    /**
     * Your MyHashSet object will be instantiated and called as such:
     * MyHashSet* obj = new MyHashSet();
     * obj->add(key);
     * obj->remove(key);
     * bool param_3 = obj->contains(key);
     */

/*
    LeetCode 705: Design HashSet

    Approach: Singly Linked List

    Intuition:
    A HashSet is a data structure that stores unique elements.

    It supports three main operations:
    1. add(key): Insert the key if it does not already exist.
    2. remove(key): Delete the key if it exists.
    3. contains(key): Check whether the key is present.

    Instead of using a built-in set or hash table, this implementation
    maintains all elements in a singly linked list.

    Each node stores:
    - val: The integer value.
    - next: Pointer to the next node.

    The `head` pointer represents the beginning of the linked list.

    Since a HashSet does not allow duplicate elements, we call
    `contains()` before inserting a new key.

    Step-by-Step Explanation:

    1. ListNode Structure:

       struct ListNode {
           int val;
           ListNode *next;
       };

       Each node stores one key and a pointer to the next node.

       The constructor initializes the node with the given value
       and sets its next pointer to nullptr.

    2. Constructor:

       MyHashSet() {
           head = nullptr;
       }

       Initially, the HashSet is empty, so the head pointer is null.

    3. add(int key):

       This function inserts a key into the linked list.

       - If the list is empty:
         Create a new node and make it the head.

       - Otherwise, check whether the key already exists using
         `contains(key)`.

         If it exists, return without inserting anything.
         This maintains the uniqueness property of a HashSet.

       - If the key does not exist:
         Traverse the linked list until reaching the last node.

         Create a new node and attach it to the last node's next pointer.

       Example:
           Initially: 10 -> 20

           add(30)

           Result: 10 -> 20 -> 30

           add(20)

           Since 20 already exists, the list remains unchanged.

    4. remove(int key):

       This function deletes a key from the linked list.

       - If the list is empty, return immediately.

       - If the head node contains the key:
         Move head to head->next.
         This removes the first node from the list.

       - Otherwise, use two pointers:
         `ptr1`: Tracks the previous node.
         `ptr2`: Tracks the current node.

         Traverse the list until the key is found or the end is reached.

         If `ptr2` contains the key:
             ptr1->next = ptr2->next;

         This skips the current node and disconnects it from the list.

       Example:
           Before:
               10 -> 20 -> 30 -> 40

           remove(30)

           After:
               10 -> 20 -> 40

    5. contains(int key):

       This function checks whether a key exists.

       - Start traversal from head.
       - Compare every node's value with the given key.
       - If a match is found, return true.
       - If the traversal reaches nullptr, return false.

       Example:
           List: 10 -> 20 -> 30

           contains(20) -> true
           contains(40) -> false

    Complexity Analysis:

    Let n be the number of elements currently stored.

    - add():
      O(n) time
      `contains()` may traverse the entire list, and finding the
      last node also requires traversal.

    - remove():
      O(n) time
      In the worst case, we traverse the entire linked list.

    - contains():
      O(n) time
      We may need to inspect every node.

    - Space Complexity:
      O(n)
      Each stored key requires one linked-list node.

    Important Implementation Notes:

    1. This implementation behaves like a HashSet, but it is not
       an actual hash table. A real HashSet uses hashing and buckets
       to achieve average O(1) operations.

    2. In `remove()`, after finding the node, the code updates the
       links but does not call `delete` on the removed node.
       This causes a memory leak.

    3. In `add()`, insertion at the end requires traversing the list.
       Insertion at the head could be O(1), but would not change the
       overall O(n) complexity because duplicate checking is still
       required.

    4. The class does not define a destructor to free all remaining
       nodes when the HashSet is destroyed.

    Core Idea:
    Represent the HashSet as a singly linked list. Check for duplicates
    before insertion, traverse to locate elements, and update pointers
    to remove nodes.
*/