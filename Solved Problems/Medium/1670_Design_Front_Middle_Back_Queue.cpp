class FrontMiddleBackQueue {
    private: 
        struct ListNode {
            int val;
            ListNode *next;
            ListNode *prev;
            ListNode() : val(-1), next(nullptr), prev(nullptr) {}
            ListNode(int x) : val(x), next(nullptr), prev(nullptr) {}
        };
    
        int curr = 0;
        ListNode *left, *right;
    
    public:
        FrontMiddleBackQueue() {
            left = new ListNode();
            right = new ListNode();
            left->next = right;
            right->prev = left;
        }
        
        void pushFront(int val) {
            ListNode* newNode = new ListNode(val);
            newNode->prev = left;
            newNode->next = left->next;
            newNode->next->prev = newNode;
            left->next = newNode;
            curr++;
        }
        
        void pushMiddle(int val) {
            ListNode* newNode = new ListNode(val);
            int i = curr / 2;
            ListNode* ptr = left;
    
            while(i--) ptr = ptr->next;
    
            newNode->prev = ptr;
            newNode->next = ptr->next;
            newNode->next->prev = newNode;
            ptr->next = newNode;
            curr++;   
        }
        
        void pushBack(int val) {
            ListNode* newNode = new ListNode(val);
            newNode->prev = right->prev;
            newNode->next = right;
            right->prev->next = newNode;
            right->prev = newNode;
            curr++;
        }
        
        int popFront() {
            if(isEmpty()) return -1;
    
            int val = left->next->val;
            left->next = left->next->next;
            left->next->prev = left;
            curr--;
    
            return val; 
        }
        
        int popMiddle() {
            if(isEmpty()) return -1;
    
            int i = (curr - 1) / 2;
            ListNode* ptr = left;
    
            while(i--) ptr = ptr->next;
            
            int val = ptr->next->val;
            ptr->next = ptr->next->next;
            ptr->next->prev = ptr;
            curr--;
    
            return val; 
        }
        
        int popBack() {
            if(isEmpty()) return -1;
    
            int val = right->prev->val;
            right->prev = right->prev->prev;
            right->prev->next = right;
            curr--;
    
            return val;
        }
            
        bool isEmpty() {
            if(left->next == right) return true;
            return false;
        }
    };
    
    /**
     * Your FrontMiddleBackQueue object will be instantiated and called as such:
     * FrontMiddleBackQueue* obj = new FrontMiddleBackQueue();
     * obj->pushFront(val);
     * obj->pushMiddle(val);
     * obj->pushBack(val);
     * int param_4 = obj->popFront();
     * int param_5 = obj->popMiddle();
     * int param_6 = obj->popBack();
     */

/*

Idea:
------
The queue supports insertion and deletion from

• Front

• Middle

• Back

This implementation uses a

Doubly Linked List

with two dummy nodes.

The doubly linked list allows

O(1)

insertion and deletion once the desired position is
known.

Since no middle pointer is maintained,

the middle node is found by traversing from the front.

------------------------------------------------------------

Data Structure:
---------------

Two dummy nodes are maintained.

Initially

left <------> right

All real elements are stored between these dummy nodes.

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

is the front.

The last node before

right

is the back.

------------------------------------------------------------

Role of Variables:
------------------

curr

Current number of elements in the queue.

It helps determine the middle position.

--------------------------------

left

Dummy node before the first element.

--------------------------------

right

Dummy node after the last element.

------------------------------------------------------------

Finding the Middle:
-------------------

For insertion,

the required middle position is

curr / 2

For deletion,

LeetCode specifies that when there are two middle
elements,

remove the

front middle.

Therefore,

the middle index becomes

(curr - 1) / 2

These formulas naturally satisfy the problem's
requirements.

------------------------------------------------------------

Algorithm:
----------

pushFront(val)

Insert the new node immediately after

left.

Increment

curr.

------------------------------------------------------------

pushBack(val)

Insert the new node immediately before

right.

Increment

curr.

------------------------------------------------------------

pushMiddle(val)

1.

Compute

middle = curr / 2

2.

Traverse from

left

until reaching the node before the middle position.

3.

Insert the new node after that node.

Increment

curr.

------------------------------------------------------------

popFront()

1.

If the queue is empty,

return

-1.

2.

Remove the first real node.

3.

Update pointers.

4.

Decrement

curr.

------------------------------------------------------------

popBack()

1.

If the queue is empty,

return

-1.

2.

Remove the last real node.

3.

Update pointers.

4.

Decrement

curr.

------------------------------------------------------------

popMiddle()

1.

If the queue is empty,

return

-1.

2.

Compute

middle = (curr - 1) / 2

This always chooses the front middle when two middle
elements exist.

3.

Traverse to the node before the middle.

4.

Remove the middle node.

5.

Update pointers.

6.

Decrement

curr.

------------------------------------------------------------

Why Do These Middle Formulas Work?
----------------------------------

Suppose the queue has

5

elements.

Indices

0 1 2 3 4

Middle index

5 / 2 = 2

Insertion happens before index

2,

which matches the problem statement.

Deletion removes index

(5 - 1) / 2 = 2.

--------------------------------

Suppose the queue has

4

elements.

Indices

0 1 2 3

There are two middle elements

1

and

2.

The problem requires removing the

front middle,

which is index

1.

Formula

(curr - 1) / 2

=

(4 - 1) / 2

=

1

Exactly the desired position.

------------------------------------------------------------

Example:
--------

Initially

left <------> right

--------------------------------

pushFront(2)

left <-> 2 <-> right

--------------------------------

pushBack(4)

left <-> 2 <-> 4 <-> right

--------------------------------

pushMiddle(3)

Current size = 2

Middle = 1

Insert before index

1

left <-> 2 <-> 3 <-> 4 <-> right

--------------------------------

pushMiddle(1)

Current size = 3

Middle = 1

Insert before index

1

left <-> 2 <-> 1 <-> 3 <-> 4 <-> right

--------------------------------

popMiddle()

Current size = 4

Front middle index =

(4 - 1) / 2 = 1

Remove

1

Queue becomes

left <-> 2 <-> 3 <-> 4 <-> right

------------------------------------------------------------

Why Does This Work?
-------------------

The doubly linked list maintains the queue in order.

Insertion and deletion at the front and back require only
constant pointer updates.

For middle operations,

the required position is first located by traversal,

after which insertion or deletion also takes constant
pointer updates.

The variable

curr

always stores the current size,

allowing the middle position to be computed correctly for
both even and odd-sized queues.

------------------------------------------------------------

Time Complexity:
----------------

pushFront()

O(1)

--------------------------------

pushBack()

O(1)

--------------------------------

popFront()

O(1)

--------------------------------

popBack()

O(1)

--------------------------------

pushMiddle()

O(n)

Traversal to the middle takes linear time.

--------------------------------

popMiddle()

O(n)

Traversal to the middle takes linear time.

------------------------------------------------------------

Space Complexity:
-----------------

O(n)

One node is stored for each queue element, along with two
dummy nodes.

*/