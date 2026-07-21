class MyQueue {
    private:
        stack<int> st1, st2;
    
    public:
        MyQueue() {
            
        }
        
        void push(int x) {
            st1.push(x);
        }
        
        int pop() {
            if(st2.empty()) {
                while(!st1.empty()) {
                    st2.push(st1.top());
                    st1.pop();
                }
            }
            int x = st2.top();
            st2.pop();
            return x;
        }
        
        int peek() {
            if(st2.empty()) {
                while(!st1.empty()) {
                    st2.push(st1.top());
                    st1.pop();
                }
            }
            return st2.top();
        }
        
        bool empty() {
            return st1.empty() && st2.empty();
        }
    };
    
    /**
     * Your MyQueue object will be instantiated and called as such:
     * MyQueue* obj = new MyQueue();
     * obj->push(x);
     * int param_2 = obj->pop();
     * int param_3 = obj->peek();
     * bool param_4 = obj->empty();
     */

/*

Idea:
------
A queue follows the

FIFO (First In, First Out)

principle,

while a stack follows the

LIFO (Last In, First Out)

principle.

Using two stacks,

we can reverse the order of elements twice to simulate
queue behavior efficiently.

------------------------------------------------------------

Role of the Two Stacks:
-----------------------

st1

Stores newly inserted elements.

The newest element is always on the top.

----------------------------

st2

Stores elements in queue order.

The oldest element is always on the top.

Whenever

st2

is not empty,

its top represents the front of the queue.

------------------------------------------------------------

Key Observation:
----------------

Elements only need to be transferred from

st1

to

st2

when

st2

becomes empty.

During this transfer,

the order of elements gets reversed.

This makes the oldest inserted element appear on the top
of

st2,

which is exactly the front of the queue.

------------------------------------------------------------

Algorithm:
----------

Push(x):

Simply push

x

into

st1.

This operation is always

O(1).

------------------------------------------------------------

Pop():

If

st2

is empty,

move every element from

st1

to

st2.

This reverses their order.

Then,

remove and return the top of

st2.

------------------------------------------------------------

Peek():

If

st2

is empty,

perform the same transfer from

st1

to

st2.

Return the top of

st2

without removing it.

------------------------------------------------------------

Empty():

The queue is empty only when both stacks are empty.

------------------------------------------------------------

Why Does This Work?
-------------------

Suppose we perform

push(1)

push(2)

push(3)

Initially,

st1

Top

3

↓

2

↓

1

Bottom

----------------------------

Now perform

pop().

Since

st2

is empty,

transfer every element.

After transferring,

st2

Top

1

↓

2

↓

3

Bottom

The oldest inserted element is now on top.

Removing it correctly simulates queue behavior.

The remaining elements stay inside

st2,

so future

pop()

and

peek()

operations do not require another transfer until

st2

becomes empty.

------------------------------------------------------------

Example:
--------

Operations

push(1)

push(2)

push(3)

st1

Top

3

↓

2

↓

1

----------------------------

peek()

Transfer to

st2

st2

Top

1

↓

2

↓

3

Front = 1

----------------------------

pop()

Removes

1

st2

Top

2

↓

3

----------------------------

push(4)

st1

Top

4

st2

Top

2

↓

3

No transfer is needed because

st2

still contains queue elements.

----------------------------

pop()

Returns

2

----------------------------

pop()

Returns

3

----------------------------

pop()

Now

st2

is empty,

transfer

4

from

st1

to

st2

Return

4

------------------------------------------------------------

Why Transfer Only When Needed?
------------------------------

If elements were transferred on every

pop()

or

peek(),

many elements would be moved repeatedly.

Instead,

each element is transferred from

st1

to

st2

at most once.

This makes the overall implementation much more
efficient.

------------------------------------------------------------

Time Complexity:
----------------

push()

O(1)

pop()

Amortized O(1)

peek()

Amortized O(1)

empty()

O(1)

Each element is pushed once into

st1,

transferred once to

st2,

and popped once.

Therefore,

although one operation may occasionally take

O(n),

the average cost per operation is

O(1).

------------------------------------------------------------

Space Complexity:
-----------------

O(n)

where

n

is the number of elements stored in the queue.

*/