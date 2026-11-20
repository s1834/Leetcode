
class MyHashMap {
    private:
        struct ListNode {
            int key;
            int val;
            ListNode *next;
            ListNode(int x, int y): key(x), val(y), next(nullptr) {}
        };
        ListNode* head;
    
    public:
        MyHashMap() {
            head = nullptr;
        }
        
        void put(int key, int value) {
            if (!head) {
                head = new ListNode(key, value);
                return;
            }
    
            ListNode* ptr = head;
            while(ptr) {
                if(ptr->key == key) {
                    ptr->val = value;
                    return;
                }
                ptr = ptr->next;
            }
    
            ptr = head;
            while(ptr && ptr->next) ptr = ptr->next;
            ListNode *newNode = new ListNode(key, value);
            ptr->next = newNode;
        }
        
        int get(int key) {
            if(!head) return -1;
    
            ListNode* ptr = head;
            while(ptr) {
                if(ptr->key == key) return ptr->val;
                ptr = ptr->next;
            }
    
            return -1;
        }
        
        void remove(int key) {
            if(!head) return;
            
            if(head->key == key) {
                head = head->next;
                return;
            }
    
            ListNode *ptr1 = head;
            ListNode *ptr2 = head->next;
            while(ptr2) {
                if(ptr2->key == key) {
                    ptr1->next = ptr2->next;
                    return;
                }
    
                ptr1 = ptr2;
                ptr2 = ptr2->next;
            }
        }
    };
    
    /**
     * Your MyHashMap object will be instantiated and called as such:
     * MyHashMap* obj = new MyHashMap();
     * obj->put(key,value);
     * int param_2 = obj->get(key);
     * obj->remove(key);
     */

/*
    LeetCode 706: Design HashMap

    Approach: Singly Linked List

    Intuition:
    We need to implement a HashMap that supports three operations:

    1. put(key, value): Insert a key-value pair or update the value
       if the key already exists.
    2. get(key): Return the value associated with the key.
    3. remove(key): Remove the key-value pair if the key exists.

    Instead of using a built-in unordered_map, this implementation
    stores all key-value pairs in a singly linked list.

    Each node contains:
    - key: The key used to identify the entry.
    - val: The value associated with that key.
    - next: Pointer to the next node.

    The `head` pointer represents the beginning of the linked list.

    Since a HashMap must contain at most one entry for each key,
    the `put()` operation first checks whether the key already exists.
    If it does, we update its value instead of inserting a duplicate.

    Step-by-Step Explanation:

    1. ListNode Structure:

       struct ListNode {
           int key;
           int val;
           ListNode *next;
       };

       Each node stores one key-value pair and a pointer to the
       next node.

       The constructor initializes the key, value, and next pointer.

    2. Constructor:

       MyHashMap() {
           head = nullptr;
       }

       Initially, the HashMap is empty, so the head pointer is null.

    3. put(int key, int value):

       This function inserts a new key-value pair or updates an
       existing entry.

       Case 1: The list is empty.

           if (!head) {
               head = new ListNode(key, value);
               return;
           }

       Create the first node and make it the head.

       Case 2: The key already exists.

       Traverse the linked list and compare every node's key
       with the given key.

           if(ptr->key == key) {
               ptr->val = value;
               return;
           }

       If the key is found, update its value and return immediately.

       This prevents duplicate keys from being inserted.

       Case 3: The key does not exist.

       After completing the search, traverse the list again to
       reach the last node.

       Create a new node and attach it to the end:

           ptr->next = newNode;

       Example:

           Initial:
               (1, 10) -> (2, 20)

           put(2, 25):
               (1, 10) -> (2, 25)

           put(3, 30):
               (1, 10) -> (2, 25) -> (3, 30)

       The existing key 2 gets updated, while key 3 is inserted.

    4. get(int key):

       This function searches for a key and returns its associated
       value.

       - If the list is empty, return -1.
       - Start traversal from head.
       - Compare each node's key with the requested key.
       - If a match is found, return its value.
       - If traversal reaches nullptr, the key does not exist,
         so return -1.

       Example:

           List:
               (1, 10) -> (2, 20) -> (3, 30)

           get(2) -> 20
           get(5) -> -1

    5. remove(int key):

       This function removes the node associated with the given key.

       Case 1: The list is empty.

           if(!head) return;

       Nothing needs to be removed.

       Case 2: The head node contains the key.

           if(head->key == key) {
               head = head->next;
               return;
           }

       Move the head pointer to the next node.
       This removes the first node from the linked list.

       Case 3: The key is somewhere after the head.

       Use two pointers:

       - ptr1: Points to the previous node.
       - ptr2: Points to the current node.

       Initially:
           ptr1 = head;
           ptr2 = head->next;

       Traverse the list while ptr2 is not null.

       If the current node contains the required key:

           ptr1->next = ptr2->next;

       This skips the current node and connects the previous node
       directly to the next node.

       Otherwise, move both pointers forward:

           ptr1 = ptr2;
           ptr2 = ptr2->next;

       Example:

           Before:
               (1, 10) -> (2, 20) -> (3, 30)

           remove(2)

           After:
               (1, 10) -> (3, 30)

    Why It Works:

    - `put()` searches for an existing key before inserting, ensuring
      that every key has only one associated value.
    - `get()` traverses the list and returns the value of the matching
      key.
    - `remove()` correctly handles both head deletion and deletion
      of a node from the middle or end of the list.

    Together, these operations maintain the required key-value
    mapping.

    Complexity Analysis:

    Let n be the number of key-value pairs stored in the HashMap.

    - put():
      O(n) time
      We may traverse the entire list to check whether the key exists.
      If it does not exist, we traverse again to reach the last node.

    - get():
      O(n) time
      In the worst case, we search through the entire linked list.

    - remove():
      O(n) time
      In the worst case, the key is at the last node.

    - Space Complexity:
      O(n)
      Each key-value pair requires one linked-list node.

    Important Implementation Notes:

    1. This implementation behaves like a HashMap but does not use
       hashing or buckets. A typical HashMap uses a hash function
       to distribute keys across buckets and achieve average O(1)
       operations.

    2. In `remove()`, the node is disconnected from the linked list
       but is not explicitly deleted using `delete ptr2`.
       This causes a memory leak.

    3. The implementation does not define a destructor to free all
       remaining nodes when the HashMap object is destroyed.

    4. The `put()` function traverses the list twice when inserting
       a new key: once to check for an existing key and again to
       reach the last node.

    Core Idea:
    Store key-value pairs as nodes in a singly linked list.
    Search by key for updates and lookups, append new keys at the end,
    and modify pointers to remove existing entries.
*/