class MyCircularDeque {
    private: 
        struct ListNode {
            int val;
            ListNode *next;
            ListNode *prev;
            ListNode() : val(-1), next(nullptr), prev(nullptr) {}
            ListNode(int x) : val(x), next(nullptr), prev(nullptr) {}
        };
    
        int n, curr;
        ListNode *left, *right;
    
    public:
        MyCircularDeque(int k) {
            n = k;
            curr = 0;
            left = new ListNode();
            right = new ListNode();
            left->next = right;
            right->prev = left;
        }
        
        bool insertFront(int value) {
            if(isFull()) return false;
    
            ListNode* newNode = new ListNode(value);
            newNode->prev = left;
            newNode->next = left->next;
            newNode->next->prev = newNode;
            left->next = newNode;
            curr++;
    
            return true;
        }
        
        bool insertLast(int value) {
            if(isFull()) return false;
    
            ListNode* newNode = new ListNode(value);
            newNode->prev = right->prev;
            newNode->next = right;
            right->prev->next = newNode;
            right->prev = newNode;
            curr++;
    
            return true;
        }
        
        bool deleteFront() {
            if(isEmpty()) return false;
            left->next = left->next->next;
            left->next->prev = left;
            curr--;
    
            return true;
        }
        
        bool deleteLast() {
            if(isEmpty()) return false;
            right->prev = right->prev->prev;
            right->prev->next = right;
            curr--;
    
            return true;
        }
        
        int getFront() {
            return left->next->val;
        }
        
        int getRear() {
            return right->prev->val;
        }
        
        bool isEmpty() {
            if(left->next == right) return true;
            return false;
        }
        
        bool isFull() {
            if(curr == n) return true;
            return false;
        }
    };
    
    /**
     * Your MyCircularDeque object will be instantiated and called as such:
     * MyCircularDeque* obj = new MyCircularDeque(k);
     * bool param_1 = obj->insertFront(value);
     * bool param_2 = obj->insertLast(value);
     * bool param_3 = obj->deleteFront();
     * bool param_4 = obj->deleteLast();
     * int param_5 = obj->getFront();
     * int param_6 = obj->getRear();
     * bool param_7 = obj->isEmpty();
     * bool param_8 = obj->isFull();
     */

/*

Idea:
------
A Deque (Double Ended Queue) allows insertion and
deletion from both the front and the rear.

Although the problem is called a

Circular Deque,

this implementation uses a

Doubly Linked List

with two dummy nodes.

Instead of physically connecting the last node back to
the first,

the queue behavior is simulated using

• Front dummy node (left)

• Rear dummy node (right)

along with a counter to enforce the maximum capacity.

------------------------------------------------------------

Data Structure:
---------------

Two dummy nodes are maintained.

Initially

left <------> right

The actual deque elements are always stored between
these two dummy nodes.

Example

Empty Deque

left <------> right

--------------------------------

After inserting

10

20

30

left <-> 10 <-> 20 <-> 30 <-> right

The node immediately after

left

is the front.

The node immediately before

right

is the rear.

------------------------------------------------------------

Role of Variables:
------------------

n

Maximum capacity of the deque.

--------------------------------

curr

Current number of elements.

Used to determine whether the deque is full.

--------------------------------

left

Dummy node before the front element.

--------------------------------

right

Dummy node after the rear element.

------------------------------------------------------------

Algorithm:
----------

insertFront(value)

1.

If the deque is full,

return

false.

------------------------------------------------------------

2.

Create a new node.

------------------------------------------------------------

3.

Insert it immediately after the

left

dummy node.

Before

left <-> first

After

left <-> newNode <-> first

------------------------------------------------------------

4.

Increment

curr

and return

true.

------------------------------------------------------------

insertLast(value)

1.

If the deque is full,

return

false.

------------------------------------------------------------

2.

Create a new node.

------------------------------------------------------------

3.

Insert it immediately before the

right

dummy node.

Before

last <-> right

After

last <-> newNode <-> right

------------------------------------------------------------

4.

Increment

curr

and return

true.

------------------------------------------------------------

deleteFront()

1.

If the deque is empty,

return

false.

------------------------------------------------------------

2.

Remove the first real node

(the node immediately after

left).

Update the neighboring pointers.

------------------------------------------------------------

3.

Decrement

curr

and return

true.

------------------------------------------------------------

deleteLast()

1.

If the deque is empty,

return

false.

------------------------------------------------------------

2.

Remove the last real node

(the node immediately before

right).

Update the neighboring pointers.

------------------------------------------------------------

3.

Decrement

curr

and return

true.

------------------------------------------------------------

getFront()

Return the value of the first real node.

left->next->val

------------------------------------------------------------

getRear()

Return the value of the last real node.

right->prev->val

------------------------------------------------------------

isEmpty()

The deque is empty when

left->next == right

meaning there are no real nodes between the dummy nodes.

------------------------------------------------------------

isFull()

The deque is full when

curr == n

------------------------------------------------------------

Why Dummy Nodes?
----------------

Using dummy nodes eliminates special cases such as

• inserting into an empty deque

• deleting the last remaining node

Every insertion and deletion follows exactly the same
pointer updates,

making the implementation simpler and less error-prone.

------------------------------------------------------------

Example:
--------

Capacity = 3

Initially

left <------> right

curr = 0

--------------------------------

insertFront(10)

left <-> 10 <-> right

--------------------------------

insertLast(20)

left <-> 10 <-> 20 <-> right

--------------------------------

insertFront(5)

left <-> 5 <-> 10 <-> 20 <-> right

curr = 3

Deque is now full.

--------------------------------

deleteLast()

left <-> 5 <-> 10 <-> right

curr = 2

--------------------------------

insertLast(30)

left <-> 5 <-> 10 <-> 30 <-> right

--------------------------------

getFront()

Returns

5

--------------------------------

getRear()

Returns

30

------------------------------------------------------------

Why Does This Work?
-------------------

The doubly linked list maintains the deque elements
between the two dummy nodes.

Because every node has both

next

and

prev

pointers,

insertion and deletion at both ends require only a few
pointer updates.

The

curr

variable ensures that at most

n

elements are stored,

satisfying the fixed-capacity requirement of the circular
deque.

------------------------------------------------------------

Time Complexity:
----------------

insertFront()

O(1)

--------------------------------

insertLast()

O(1)

--------------------------------

deleteFront()

O(1)

--------------------------------

deleteLast()

O(1)

--------------------------------

getFront()

O(1)

--------------------------------

getRear()

O(1)

--------------------------------

isEmpty()

O(1)

--------------------------------

isFull()

O(1)

------------------------------------------------------------

Space Complexity:
-----------------

O(k)

where

k

is the maximum capacity of the deque.

At most

k

nodes are stored, along with two dummy nodes.

*/