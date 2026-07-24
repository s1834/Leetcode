// Version 1: Linked List Messy

// class LRUCache {
//     private: 
//         struct ListNode {
//             int key;
//             int val;
//             ListNode *next;
//             ListNode *prev;
//             ListNode() : key(-1), val(-1), next(nullptr), prev(nullptr) {}
//             ListNode(int k, int x) : key(k), val(x), next(nullptr), prev(nullptr) {}
//         };
    
//         unordered_map<int, ListNode*> mp;
//         int n, curr;
//         ListNode *left, *right;
    
//     public:
//         LRUCache(int capacity) {
//             n = capacity;
//             curr = 0;
//             left = new ListNode();
//             right = new ListNode();
//             left->next = right;
//             right->prev = left;
//         }
        
//         int get(int key) {
//             if(mp.find(key) == mp.end()) return -1;
//             ListNode* ptr = mp[key];
//             ptr->prev->next = ptr->next;
//             ptr->next->prev = ptr->prev;
//             ptr->next = right;
//             ptr->prev = right->prev;
//             right->prev->next = ptr;
//             right->prev = ptr;
//             return mp[key]->val;
//         }
        
//         void put(int key, int value) {
//             if(mp.find(key) == mp.end()) {
//                 ListNode* newNode = new ListNode(key, value);
//                 newNode->next = right;
//                 newNode->prev = right->prev;
//                 right->prev->next = newNode;
//                 right->prev = newNode;
//                 mp[key] = newNode;
//                 if(curr == n) {
//                     mp.erase(left->next->key);
//                     left->next = left->next->next;
//                     left->next->prev = left;
//                 } else curr++;
//             } else {
//                 mp[key]->val = value;
//                 ListNode* ptr = mp[key];
//                 ptr->prev->next = ptr->next;
//                 ptr->next->prev = ptr->prev;
//                 ptr->next = right;
//                 ptr->prev = right->prev;
//                 right->prev->next = ptr;
//                 right->prev = ptr;
//             }      
//         }
//     };
    
//     /**
//      * Your LRUCache object will be instantiated and called as such:
//      * LRUCache* obj = new LRUCache(capacity);
//      * int param_1 = obj->get(key);
//      * obj->put(key,value);
//      */

// Version 2: Linked List Clean

class LRUCache {
    private: 
        struct ListNode {
            int key;
            int val;
            ListNode *next;
            ListNode *prev;
            ListNode() : key(-1), val(-1), next(nullptr), prev(nullptr) {}
            ListNode(int k, int x) : key(k), val(x), next(nullptr), prev(nullptr) {}
        };
    
        unordered_map<int, ListNode*> mp;
        int n, curr;
        ListNode *left, *right;
    
        // Remove Node
        void remove(ListNode* ptr) {
            ptr->prev->next = ptr->next;
            ptr->next->prev = ptr->prev;
        }
    
        // Insert node at last
        void insert(ListNode* ptr) {
            ptr->next = right;
            ptr->prev = right->prev;
            right->prev->next = ptr;
            right->prev = ptr;
        }
    
    public:
        LRUCache(int capacity) {
            n = capacity;
            curr = 0;
            left = new ListNode();
            right = new ListNode();
            left->next = right;
            right->prev = left;
        }
        
        int get(int key) {
            // key does not exist
            if(mp.find(key) == mp.end()) return -1;
    
            // move the accessed node to right
            ListNode* ptr = mp[key];
            remove(ptr);
            insert(ptr);
    
            return ptr->val;
        }
        
        void put(int key, int value) {
            // If key is not present, create a new node
            if(mp.find(key) == mp.end()) {
                ListNode* newNode = new ListNode(key, value);
                insert(newNode);
                mp[key] = newNode;
                
                // If cache exceeds capacity, remove LRU node
                if(curr == n) {
                    ListNode* ptr = left->next;
                    mp.erase(ptr->key);
                    remove(ptr);
                    delete ptr;
                } 
                else curr++;
            } else {
                // if key already exists, update value and send to right
                ListNode* ptr = mp[key];
                ptr->val = value;
    
                remove(ptr);
                insert(ptr);
            }
        }
    };
    
/*

Idea:
------
An LRU (Least Recently Used) Cache must support

• get(key)

• put(key, value)

both in

O(1)

time.

To achieve this,

we combine two data structures:

1.

Hash Map

Maps

key -> corresponding node

allowing O(1) lookup.

2.

Doubly Linked List

Maintains the usage order of cache entries.

The

Least Recently Used (LRU)

item is kept at the front,

while the

Most Recently Used (MRU)

item is kept at the back.

------------------------------------------------------------

Data Structure:
---------------

Two dummy nodes are maintained.

Initially

left <------> right

Actual cache nodes are always stored between them.

Example

left <-> (1,10) <-> (2,20) <-> (3,30) <-> right

Here,

(1,10)

is the Least Recently Used.

(3,30)

is the Most Recently Used.

------------------------------------------------------------

Role of Variables:
------------------

mp

Hash map storing

key -> node pointer

for O(1) access.

--------------------------------

n

Maximum cache capacity.

--------------------------------

curr

Current number of cache entries.

--------------------------------

left

Dummy node before the Least Recently Used element.

--------------------------------

right

Dummy node after the Most Recently Used element.

------------------------------------------------------------

Helper Functions:
-----------------

remove(node)

Removes a node from its current position by updating its
previous and next pointers.

This operation takes

O(1).

--------------------------------

insert(node)

Inserts a node just before the

right

dummy node,

making it the

Most Recently Used

entry.

This operation also takes

O(1).

------------------------------------------------------------

Algorithm:
----------

get(key)

1.

If the key does not exist,

return

-1.

------------------------------------------------------------

2.

Otherwise,

retrieve the node using the hash map.

------------------------------------------------------------

3.

Since the key has just been accessed,

it becomes the

Most Recently Used.

Remove it from its current position and insert it at the
end of the list.

------------------------------------------------------------

4.

Return its value.

------------------------------------------------------------

put(key, value)

Case 1

Key already exists.

Update its value.

Since it has just been accessed,

move it to the end of the list,

making it the

Most Recently Used.

------------------------------------------------------------

Case 2

Key does not exist.

Create a new node.

Insert it at the end of the list.

Store its pointer in the hash map.

------------------------------------------------------------

If the cache size exceeds its capacity,

remove the node immediately after

left,

which is the

Least Recently Used

node.

Also remove its key from the hash map and free the
allocated memory.

------------------------------------------------------------

Why Move Accessed Nodes to the End?
-----------------------------------

Whenever a key is

accessed

or

updated,

it becomes the most recently used item.

Therefore,

it should be moved to the rear of the linked list.

Example

Initially

left

A

B

C

right

LRU           MRU

--------------------------------

Access

B

Remove

B

and insert it at the end.

left

A

C

B

right

Now,

A

becomes the Least Recently Used,

while

B

becomes the Most Recently Used.

------------------------------------------------------------

Why Remove the Front Node?
--------------------------

When the cache becomes full,

the least recently used entry must be evicted.

Since the linked list always stores

LRU -> MRU,

the first real node

(left->next)

is always the correct node to remove.

------------------------------------------------------------

Example:
--------

Capacity = 2

--------------------------------

put(1,1)

left <-> (1,1) <-> right

--------------------------------

put(2,2)

left <-> (1,1) <-> (2,2) <-> right

LRU = 1

MRU = 2

--------------------------------

get(1)

Move

1

to the end.

left <-> (2,2) <-> (1,1) <-> right

LRU = 2

MRU = 1

--------------------------------

put(3,3)

Insert

3

left <-> (2,2) <-> (1,1) <-> (3,3) <-> right

Capacity exceeded.

Remove

2

Final Cache

left <-> (1,1) <-> (3,3) <-> right

------------------------------------------------------------

Why Does This Work?
-------------------

The hash map provides direct access to any cache entry in

O(1)

time.

The doubly linked list maintains the usage order of
elements.

Whenever an entry is accessed or updated,

it is moved to the rear,

ensuring that the front of the list always contains the

Least Recently Used

entry.

When eviction is required,

the correct node can therefore be removed in constant
time.

------------------------------------------------------------

Time Complexity:
----------------

get()

O(1)

--------------------------------

put()

O(1)

Both hash map operations and linked list updates take
constant time.

------------------------------------------------------------

Space Complexity:
-----------------

O(capacity)

The hash map stores one pointer per cache entry,

and the doubly linked list stores one node per cached
key-value pair.

*/