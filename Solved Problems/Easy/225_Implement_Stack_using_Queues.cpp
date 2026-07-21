class MyStack {
    private:
        queue<int> q;
    
    public:
        MyStack() {
            
        }
        
        void push(int x) {
            q.push(x);
            int n = q.size() - 1;
            while(n--) {
                q.push(q.front());
                q.pop();
            }
        }
        
        int pop() {
            int x = q.front();
            q.pop();
            return x;
        }
        
        int top() {
            return q.front();
        }
        
        bool empty() {
            return q.empty();
        }
    };
    
    /**
     * Your MyStack object will be instantiated and called as such:
     * MyStack* obj = new MyStack();
     * obj->push(x);
     * int param_2 = obj->pop();
     * int param_3 = obj->top();
     * bool param_4 = obj->empty();
     */

/*

Idea:
------
A stack follows the

LIFO (Last In, First Out)

principle,

while a queue follows the

FIFO (First In, First Out)

principle.

Since only one queue is allowed,

we simulate stack behavior by rearranging the queue
after every insertion.

The goal is to always keep the most recently inserted
element at the front of the queue.

Then,

both

pop()

and

top()

become simple front operations.

------------------------------------------------------------

Key Observation:
----------------

After every

push(),

rotate all previously inserted elements behind the new
element.

This ensures that the newest element is always at the
front of the queue, exactly like the top of a stack.

------------------------------------------------------------

Algorithm:
----------

Push(x):

1.

Insert

x

at the back of the queue.

------------------------------------------------------------

2.

Suppose the queue now contains

n

elements.

Rotate the first

n - 1

elements.

For each rotation,

• Remove the front element.

• Push it back into the queue.

------------------------------------------------------------

3.

After all rotations,

the newly inserted element moves from the back to the
front.

------------------------------------------------------------

Pop():

Simply remove and return the front element.

Since the newest element is always at the front,

this correctly simulates stack pop.

------------------------------------------------------------

Top():

Return the front element of the queue.

------------------------------------------------------------

Empty():

Return whether the queue is empty.

------------------------------------------------------------

Why Does This Work?
-------------------

After every insertion,

the queue is rearranged so that its order matches the
order of a stack.

Example,

Push 1

Queue

[1]

----------------

Push 2

Initially

[1, 2]

Rotate once

[2, 1]

Top = 2

----------------

Push 3

Initially

[2, 1, 3]

Rotate twice

[1, 3, 2]

↓

[3, 2, 1]

Top = 3

The front of the queue always stores the most recently
inserted element.

Therefore,

every

pop()

removes the same element that a real stack would remove.

------------------------------------------------------------

Example:
--------

Operations

push(1)

Queue

[1]

----------------

push(2)

Queue after insertion

[1, 2]

Rotate

↓

[2, 1]

----------------

push(3)

Queue after insertion

[2, 1, 3]

Rotate

↓

[1, 3, 2]

↓

[3, 2, 1]

----------------

top()

Returns

3

----------------

pop()

Removes

3

Queue

[2, 1]

----------------

top()

Returns

2

------------------------------------------------------------

Time Complexity:
----------------

push()

O(n)

The queue is rotated after every insertion.

pop()

O(1)

top()

O(1)

empty()

O(1)

------------------------------------------------------------

Space Complexity:
-----------------

O(n)

Only one queue is used to store the stack elements.

*/