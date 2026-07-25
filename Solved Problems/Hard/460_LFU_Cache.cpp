class LFUCache {
    private: 
        // store key, val, freq
        struct ListNode {
            int key;
            int val;
            int freq;
            ListNode *next;
            ListNode *prev;
            ListNode() : key(-1), val(-1), freq(1), next(nullptr), prev(nullptr) {}
            ListNode(int k, int x, int f) : key(k), val(x), freq(f), next(nullptr), prev(nullptr) {}
        };
    
        struct DLL {
            ListNode *left;
            ListNode *right;
    
            DLL() {
                left = new ListNode();
                right = new ListNode();
    
                left->next = right;
                right->prev = left;
            }
        };
    
        // Remove node from its current frequency list
        void remove(ListNode* ptr) {
            ptr->prev->next = ptr->next;
            ptr->next->prev = ptr->prev;
        }
    
        // Insert node at the end of a frequency list
        void insert(DLL* dll, ListNode* ptr) {
            ptr->next = dll->right;
            ptr->prev = dll->right->prev;
    
            dll->right->prev->next = ptr;
            dll->right->prev = ptr;
        }
    
        unordered_map<int, ListNode*> mp; // unordered_map<key, ListNode*> mp;
        map<int, DLL*> freq; // map<freq, list_of_ListNode> freq;
        int n, curr;
    
    public:
        LFUCache(int capacity) {
            n = capacity;
            curr = 0;
        }
        
        int get(int key) {
            // Key does not exist
            if(mp.find(key) == mp.end()) return -1;
    
            // key exists
            ListNode* ptr = mp[key];
    
            // Remove from current frequency list
            remove(ptr);
    
            // check and remove old frequency list
            if(freq[ptr->freq]->left->next == freq[ptr->freq]->right) freq.erase(ptr->freq);
    
            // Increase frequency
            ptr->freq++;
    
            // Create frequency list if it doesn't exist
            if(freq.find(ptr->freq) == freq.end()) freq[ptr->freq] = new DLL();
    
            // Insert into new frequency list
            insert(freq[ptr->freq], ptr);
    
            return ptr->val;
        }
        
        void put(int key, int value) {
            // If key is not present, create a new node
            if(mp.find(key) == mp.end()) {
                // capacity is full
                if(curr == n) {
                    // Get minimum frequency list
                    int minFreq = freq.begin()->first;
    
                    DLL* dll = freq[minFreq];
    
                    // Remove LRU node from that frequency
                    ListNode* ptr = dll->left->next;
    
                    mp.erase(ptr->key);
    
                    remove(ptr);
                    delete ptr;
    
                    // Remove empty frequency list
                    if(dll->left->next == dll->right) {
                        delete dll;
                        freq.erase(minFreq);
                    }
    
                } else  curr++;
    
                // Create new node with frequency 1
                ListNode* newNode = new ListNode(key, value, 1);
    
                mp[key] = newNode;
    
                // Create frequency 1 list if needed
                if(freq.find(1) == freq.end()) freq[1] = new DLL();
    
                // Insert into frequency 1 list
                insert(freq[1], newNode);
            } else {
                // if key already exists, update value and send to right
                ListNode* ptr = mp[key];
                ptr->val = value;
    
                // Remove from current frequency list
                remove(ptr);
    
                // check and remove old frequency list
                if(freq[ptr->freq]->left->next == freq[ptr->freq]->right) freq.erase(ptr->freq);
                
                // Increase frequency
                ptr->freq++;
    
                // Create frequency list if it doesn't exist
                if(freq.find(ptr->freq) == freq.end()) freq[ptr->freq] = new DLL();
    
                // Insert into new frequency list
                insert(freq[ptr->freq], ptr);
            }
        }
    };
    
    /**
     * Your LFUCache object will be instantiated and called as such:
     * LFUCache* obj = new LFUCache(capacity);
     * int param_1 = obj->get(key);
     * obj->put(key,value);
     */

/*

Idea:
------
The LFU (Least Frequently Used) Cache must support

• get(key)

• put(key, value)

while always evicting

1. The Least Frequently Used key.

2. If multiple keys have the same frequency,
   remove the Least Recently Used among them.

Thus, we need to efficiently maintain both

Frequency

and

Recency.

------------------------------------------------------------

Why Two Criteria?
-----------------

Suppose the cache capacity is

2

Operations

put(1)
put(2)

Frequency

1 -> freq = 1

2 -> freq = 1

--------------------------------

get(1)

Frequency

1 -> freq = 2

2 -> freq = 1

Now inserting another key

put(3)

must remove

2

because it has the smallest frequency.

------------------------------------------------------------

Now consider

put(1)
put(2)

Both frequencies are

1

Which one should be removed?

The problem states

Remove the Least Recently Used

among nodes having the same frequency.

Therefore,

each frequency group must itself maintain an LRU order.

------------------------------------------------------------

Data Structures:
----------------

This implementation combines

1.

Hash Map

2.

Ordered Map

3.

Multiple Doubly Linked Lists

------------------------------------------------------------

1. Hash Map

unordered_map<int, ListNode*>

Stores

key

↓

pointer to node

Purpose

Allows direct access to any key in

O(1).

------------------------------------------------------------

2. Ordered Map

map<int, DLL*>

Stores

frequency

↓

doubly linked list

Example

Frequency

1

↓

DLL

[A] [D]

--------------------------------

Frequency

2

↓

DLL

[C]

--------------------------------

Frequency

5

↓

DLL

[B]

The map automatically keeps frequencies sorted.

Therefore

freq.begin()

always points to the minimum frequency currently present.

------------------------------------------------------------

3. Doubly Linked List

Each frequency has its own linked list.

Example

Frequency = 3

left

↓

A <-> B <-> C

↓

right

Leftmost

↓

Least Recently Used

Rightmost

↓

Most Recently Used

Every time a node is accessed,

it is inserted at the end of its new frequency list.

------------------------------------------------------------

Node Structure:
---------------

Each node stores

key

Needed for deleting entries from the hash map.

--------------------------------

value

Stored cache value.

--------------------------------

frequency

Current access count.

--------------------------------

prev

next

Used for O(1) insertion and deletion.

------------------------------------------------------------

Overall Structure:
------------------

Suppose

Capacity = 5

Hash Map

1 → Node1

2 → Node2

3 → Node3

--------------------------------

Frequency Map

Freq = 1

left

↓

Node2

↓

right

--------------------------------

Freq = 2

left

↓

Node1

↓

right

--------------------------------

Freq = 5

left

↓

Node3

↓

right

Each node belongs to exactly one frequency list.

------------------------------------------------------------

Helper Function:
----------------

remove(node)

Disconnects the node from its current DLL.

Pointer updates

Prev -> Next

Next -> Prev

Time

O(1)

------------------------------------------------------------

insert(dll,node)

Always inserts the node

just before

the right dummy node.

Therefore

the newest node within a frequency list

is always at the end.

Time

O(1)

------------------------------------------------------------

GET Operation:
--------------

Suppose

get(key)

is called.

--------------------------------

Case 1

Key does not exist.

Return

-1

------------------------------------------------------------

Case 2

Key exists.

Example

Frequency

3

↓

A

B

C

Access

B

Step 1

Remove

B

from Frequency

3

list.

Frequency 3

↓

A

C

------------------------------------------------------------

Step 2

If Frequency

3

becomes empty,

remove that frequency list from the map.

This prevents empty lists from remaining.

------------------------------------------------------------

Step 3

Increase frequency.

3

↓

4

------------------------------------------------------------

Step 4

Create Frequency

4

list if it does not exist.

------------------------------------------------------------

Step 5

Insert

B

at the end of Frequency

4

list.

Now

B

is

Most Recently Used

within frequency

4.

------------------------------------------------------------

Step 6

Return its value.

------------------------------------------------------------

PUT Operation:
--------------

Case 1

Key already exists.

Only its value changes.

Since updating counts as an access,

its frequency also increases.

Exactly the same steps as

get()

are performed.

------------------------------------------------------------

Case 2

Key does not exist.

--------------------------------

If capacity is not full

Create new node.

Frequency = 1.

Insert into Frequency

1

list.

------------------------------------------------------------

If capacity is already full

Eviction is required.

------------------------------------------------------------

Eviction Process:
-----------------

Step 1

Find minimum frequency.

Since

freq

is an ordered map,

the smallest frequency is

freq.begin()->first

Time

O(1)

------------------------------------------------------------

Step 2

Among this frequency,

remove

the Least Recently Used node.

Because nodes are inserted at the end,

the

left->next

node is always

Least Recently Used.

Example

Frequency = 2

left

↓

A

B

C

↓

right

A

is removed.

------------------------------------------------------------

Step 3

Erase the node from

Hash Map

Remove it from the linked list.

Delete memory.

------------------------------------------------------------

Step 4

If the frequency list becomes empty,

delete that DLL

and erase its frequency entry.

------------------------------------------------------------

Step 5

Insert the new node into

Frequency

1

list.

------------------------------------------------------------

Why LRU Inside Same Frequency?
------------------------------

Suppose

Capacity = 2

put(1)

put(2)

Frequency

1

↓

1

2

Both have frequency

1.

--------------------------------

get(1)

Frequency

1

↓

2

Frequency

2

↓

1

--------------------------------

put(3)

Minimum frequency

=

1

Remove

2.

Correct.

------------------------------------------------------------

Now suppose

put(1)

put(2)

Frequency

1

↓

1

2

--------------------------------

get(1)

get(2)

Frequency

2

↓

1

2

--------------------------------

Now

put(3)

Both have frequency

2.

Which should be removed?

The answer is

1

because

within Frequency 2,

1

was accessed earlier,

making it the Least Recently Used.

This is exactly why every frequency maintains its own DLL.

------------------------------------------------------------

Why Ordered Map?
----------------

The problem always asks us to remove

the smallest frequency.

If frequencies were stored in an unordered map,

finding the minimum frequency would require scanning every
frequency.

Using

map

keeps frequencies sorted,

so the minimum frequency is always

freq.begin()

without any search.

------------------------------------------------------------

Why Does This Work?
-------------------

Every cache entry belongs to exactly one frequency list.

The hash map provides direct access to a node using its
key.

Whenever a node is accessed or updated,

it is removed from its current frequency list,

its frequency is incremented,

and it is inserted into the corresponding higher-frequency
list.

Within each frequency,

the doubly linked list preserves recency,

ensuring that the front node is always the Least Recently
Used.

When eviction is required,

the ordered map immediately identifies the minimum
frequency,

and the front node of that frequency list is removed,

satisfying both LFU and LRU requirements.

------------------------------------------------------------

Example:
--------

Capacity = 2

--------------------------------

put(1,10)

Freq 1

left

↓

1

↓

right

--------------------------------

put(2,20)

Freq 1

left

↓

1

2

↓

right

--------------------------------

get(1)

Remove

1

from Freq 1

Freq 1

↓

2

Freq 2

↓

1

--------------------------------

put(3,30)

Cache Full

Minimum Frequency = 1

Remove

2

Insert

3

into Frequency 1

Final

Freq 1

↓

3

Freq 2

↓

1

--------------------------------

get(3)

Move

3

to Frequency 2

Freq 2

↓

1

3

Since

3

was accessed after

1,

it is inserted at the end,

making

1

the LRU inside Frequency 2.

------------------------------------------------------------

Time Complexity:
----------------

Hash Map Lookup

O(1)

--------------------------------

Removing from DLL

O(1)

--------------------------------

Insertion into DLL

O(1)

--------------------------------

Finding Minimum Frequency

O(1)

using

freq.begin()

--------------------------------

Creating / Removing Frequency Lists

map insertion/erase

O(log F)

where

F

is the number of distinct frequencies.

Therefore

get()

=

O(log F)

put()

=

O(log F)

In practice,

F ≤ Capacity.

------------------------------------------------------------

Space Complexity:
-----------------

Hash Map

Stores one pointer per cache entry.

O(Capacity)

--------------------------------

Frequency Map

Stores one DLL per distinct frequency.

O(F)

--------------------------------

Linked Lists

Store exactly one node per cache entry.

O(Capacity)

Overall

O(Capacity)

*/