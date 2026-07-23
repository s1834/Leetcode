/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
    public:
        Node* copyRandomList(Node* head) {
            unordered_map<Node*, Node*> mp;
            Node* ptr = head;
    
            // Create Copy
            while(ptr) {
                mp[ptr] = new Node(ptr->val);
                ptr = ptr->next;
            }
    
            // Connect next and random
            ptr = head;
            while(ptr) {
                mp[ptr]->next = mp[ptr->next];
                mp[ptr]->random = mp[ptr->random];
                ptr = ptr->next;
            }
    
            return mp[head];
        }
    };

/*

Idea:
------
Each node contains two pointers:

• next

• random

The challenge is that the

random

pointer can point to any node in the list (or be NULL).

Therefore,

while creating a copy of a node,

we may not yet have created the node pointed to by its
random pointer.

To solve this,

we use a hash map that stores the mapping

Original Node  →  Copied Node.

This allows us to connect both

next

and

random

pointers in constant time.

------------------------------------------------------------

Data Structure:
---------------

unordered_map<Node*, Node*>

The map stores

Original Node

↓

Copied Node

Example

Original List

A → B → C

Map

A → A'

B → B'

C → C'

Once every node has its copy,

all pointers can be reconstructed easily.

------------------------------------------------------------

Algorithm:
----------

Pass 1:

Create a copy of every node.

Traverse the original list.

For every node,

create a new node having the same value.

Store the mapping

original node

→

copied node

inside the hash map.

At the end of this pass,

every original node has its corresponding copy,

but none of the pointers are connected yet.

------------------------------------------------------------

Pass 2:

Reconnect the pointers.

Traverse the original list again.

For every original node,

Connect

next

copy->next = map[original->next]

Connect

random

copy->random = map[original->random]

Since every copied node already exists in the hash map,

both pointers can be assigned directly.

------------------------------------------------------------

Pass 3:

Return the copied head.

The copied head is simply

map[head]

------------------------------------------------------------

Why Does This Work?
-------------------

After the first traversal,

every original node already has a unique copied node.

Therefore,

during the second traversal,

whenever we encounter

original->next

or

original->random,

their copied versions are immediately available through
the hash map.

Thus,

every pointer in the copied list points only to copied
nodes,

producing a completely independent deep copy.

------------------------------------------------------------

Example:
--------

Original List

A → B → C

Random

A → C

B → A

C → B

--------------------------------

Pass 1

Create

A'

B'

C'

Store

A → A'

B → B'

C → C'

--------------------------------

Pass 2

A'->next = B'

A'->random = C'

----------------

B'->next = C'

B'->random = A'

----------------

C'->next = NULL

C'->random = B'

--------------------------------

Return

A'

The copied list has the exact same structure as the
original,

but all pointers refer only to copied nodes.

------------------------------------------------------------

Why Use a Hash Map?
-------------------

Without the hash map,

when assigning

random

or

next,

we would need to search for the copied node every time,
leading to

O(n²)

time.

The hash map provides direct access to the copied node
for every original node in

O(1)

average time.

------------------------------------------------------------

Time Complexity:
----------------

Pass 1:

O(n)

Pass 2:

O(n)

Overall:

O(n)

------------------------------------------------------------

Space Complexity:
-----------------

O(n)

The hash map stores one copied node for every original
node.

*/