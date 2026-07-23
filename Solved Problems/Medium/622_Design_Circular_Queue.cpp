class MyCircularQueue {
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
        MyCircularQueue(int k) {
            n = k;
            curr = 0;
            left = new ListNode();
            right = new ListNode();
            left->next = right;
            right->prev = left;
        }
        
        bool enQueue(int value) {
            if(isFull()) return false;
    
            ListNode* newNode = new ListNode(value);
            newNode->prev = right->prev;
            newNode->next = right;
            right->prev->next = newNode;
            right->prev = newNode;
            curr++;
    
            return true;
        }
        
        bool deQueue() {
            if(isEmpty()) return false;
            left->next = left->next->next;
            left->next->prev = left;
            curr--;
    
            return true;
        }
        
        int Front() {
            return left->next->val;
        }
        
        int Rear() {
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
     * Your MyCircularQueue object will be instantiated and called as such:
     * MyCircularQueue* obj = new MyCircularQueue(k);
     * bool param_1 = obj->enQueue(value);
     * bool param_2 = obj->deQueue();
     * int param_3 = obj->Front();
     * int param_4 = obj->Rear();
     * bool param_5 = obj->isEmpty();
     * bool param_6 = obj->isFull();
     */

/*

Idea:
------
Although the problem is called a

Circular Queue,

this implementation uses a

Doubly Linked List

with two dummy nodes.

Instead of physically connecting the last node back to
the first,

we simulate the queue behavior by maintaining

• Front pointer (left dummy)

• Rear pointer (right dummy)

along with the current number of elements.

The queue capacity is enforced using a counter.

------------------------------------------------------------

Data Structure:
---------------

Two dummy nodes are maintained.

Initially,

left <------> right

The actual queue elements are always inserted between
these two dummy nodes.

Example

Empty Queue

left <------> right

--------------------------------

After inserting

10

20

30

left <-> 10 <-> 20 <-> 30 <-> right

The first node after

left

is always the front.

The last node before

right

is always the rear.

------------------------------------------------------------

Role of Variables:
------------------

n

Maximum capacity of the queue.

--------------------------------

curr

Current number of elements stored.

Used to determine whether the queue is full.

--------------------------------

left

Dummy node before the front element.

--------------------------------

right

Dummy node after the rear element.

------------------------------------------------------------

Algorithm:
----------

enQueue(value)

1.

If the queue is already full,

return

false.

------------------------------------------------------------

2.

Create a new node.

------------------------------------------------------------

3.

Insert it just before the

right

dummy node.

Update all four pointers.

Before

left <-> ... <-> last <-> right

After

left <-> ... <-> last <-> newNode <-> right

------------------------------------------------------------

4.

Increment

curr

and return

true.

------------------------------------------------------------

deQueue()

1.

If the queue is empty,

return

false.

------------------------------------------------------------

2.

Remove the first real node

(the node immediately after

left).

Update the neighboring pointers.

Before

left <-> first <-> second

After

left <-> second

------------------------------------------------------------

3.

Decrement

curr

and return

true.

------------------------------------------------------------

Front()

Return the value of the first real node.

left->next->val

------------------------------------------------------------

Rear()

Return the value of the last real node.

right->prev->val

------------------------------------------------------------

isEmpty()

The queue is empty when

left->next == right

meaning there are no real nodes between the dummy nodes.

------------------------------------------------------------

isFull()

The queue is full when

curr == n

------------------------------------------------------------

Why Dummy Nodes?
----------------

Without dummy nodes,

special cases would be needed when

• inserting into an empty queue

• deleting the last remaining node

Using dummy nodes,

every insertion and deletion follows exactly the same
pointer updates,

making the implementation much simpler and less
error-prone.

------------------------------------------------------------

Example:
--------

Capacity = 3

Initially

left <------> right

curr = 0

--------------------------------

enQueue(10)

left <-> 10 <-> right

curr = 1

--------------------------------

enQueue(20)

left <-> 10 <-> 20 <-> right

curr = 2

--------------------------------

enQueue(30)

left <-> 10 <-> 20 <-> 30 <-> right

curr = 3

Queue is now full.

--------------------------------

deQueue()

Remove

10

left <-> 20 <-> 30 <-> right

curr = 2

--------------------------------

Front()

Returns

20

--------------------------------

Rear()

Returns

30

------------------------------------------------------------

Why Does This Work?
-------------------

The doubly linked list always stores the queue elements
between the two dummy nodes.

Insertion always occurs at the rear,

and deletion always occurs from the front,

which exactly matches the FIFO (First In, First Out)
behavior of a queue.

The

curr

variable guarantees that no more than

n

elements are inserted,

thereby satisfying the fixed-capacity requirement of the
circular queue.

------------------------------------------------------------

Time Complexity:
----------------

enQueue()

O(1)

--------------------------------

deQueue()

O(1)

--------------------------------

Front()

O(1)

--------------------------------

Rear()

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

is the queue capacity.

At most

k

nodes are stored, along with two dummy nodes.

*/