// Version 1: Recursive

// class Solution {
// public:
//     int fib(int n) {
//         if (n < 2) {
//             return n;
//         }
//         return fib(n - 1) + fib(n - 2);
//     }
// };


// Version 2: Iterative
class Solution {
    public:
        int fib(int n) {
            if(n <= 1) return n;
    
            int a = 0, b = 1;
            int c;
    
            for(int i = 1; i < n; i++) {
                c = a + b;
                a = b;
                b = c;
            }
    
            return c;
        }
    };

/*
LeetCode 509. Fibonacci Number

Idea:
------

The Fibonacci sequence is defined as:

    F(0) = 0
    F(1) = 1

For every n >= 2:

    F(n) = F(n - 1) + F(n - 2)

So the sequence is:

    0, 1, 1, 2, 3, 5, 8, 13, 21, ...

Instead of using recursion, we use an iterative approach and
keep track of only the previous two Fibonacci numbers.

------------------------------------------------------------

Why Iteration?
--------------

A direct recursive solution would look like:

    fib(n) = fib(n - 1) + fib(n - 2)

but this repeatedly calculates the same Fibonacci values.

For example:

                fib(5)
               /      \
           fib(4)     fib(3)
           /   \       /   \
       fib(3) fib(2) fib(2) fib(1)

fib(3), fib(2), etc. are calculated multiple times.

That makes the simple recursive solution exponential.

Instead, we calculate the sequence from left to right:

    F(0)
    F(1)
    F(2)
    F(3)
    ...
    F(n)

This allows us to calculate each value exactly once.

------------------------------------------------------------

Base Cases:
-----------

    if(n <= 1) return n;

This handles:

    fib(0) = 0
    fib(1) = 1

We return immediately because these values are already known.

For example:

    fib(0) -> 0
    fib(1) -> 1

There is no need to enter the loop.

------------------------------------------------------------

Keeping Track of Two Values:
----------------------------

We initialize:

    int a = 0;
    int b = 1;

These represent:

    a = F(0)
    b = F(1)

So initially:

    a = 0
    b = 1

To calculate the next Fibonacci number:

    F(2) = F(0) + F(1)

Therefore:

    c = a + b;

After calculating the next value, we move forward:

    a = b;
    b = c;

So the pair

    (a, b)

always represents the two most recent Fibonacci numbers.

------------------------------------------------------------

Example: n = 5
--------------

Initial:

    a = 0
    b = 1

Meaning:

    a = F(0)
    b = F(1)

------------------------------------------------

First iteration:

    c = a + b
      = 0 + 1
      = 1

Then:

    a = b
      = 1

    b = c
      = 1

Now:

    a = F(1) = 1
    b = F(2) = 1

------------------------------------------------

Second iteration:

    c = 1 + 1
      = 2

Update:

    a = 1
    b = 2

Now:

    a = F(2)
    b = F(3)

------------------------------------------------

Third iteration:

    c = 1 + 2
      = 3

Update:

    a = 2
    b = 3

Now:

    a = F(3)
    b = F(4)

------------------------------------------------

Fourth iteration:

    c = 2 + 3
      = 5

Update:

    a = 3
    b = 5

Now:

    b = F(5)

Return:

    c = 5

Therefore:

    fib(5) = 5

------------------------------------------------------------

Why Does the Loop Start at i = 1?
----------------------------------

Your loop is:

    for(int i = 1; i < n; i++)

We already know:

    a = F(0)
    b = F(1)

So we need to calculate the remaining values until we reach
F(n).

For n = 5, the loop runs for:

    i = 1
    i = 2
    i = 3
    i = 4

which is exactly 4 iterations.

Each iteration calculates the next Fibonacci number.

------------------------------------------------------------

Why Do We Need c?
-----------------

We cannot directly do:

    a = b;
    b = a + b;

because after:

    a = b;

the old value of a is lost.

For example:

    a = 2
    b = 3

If we do:

    a = b;

we get:

    a = 3

Now if we try:

    b = a + b;

we get:

    b = 3 + 3 = 6

which is incorrect.

We need the old values of both a and b.

Therefore, we first calculate:

    c = a + b;

and then shift:

    a = b;
    b = c;

------------------------------------------------------------

The Sliding Window Idea:
------------------------

At every point, we only need the previous two values.

For example:

    F(0), F(1)
        ↓
    F(1), F(2)
        ↓
    F(2), F(3)
        ↓
    F(3), F(4)
        ↓
    F(4), F(5)

So instead of storing the entire sequence:

    vector<int> fib;

we only store:

    a
    b

This reduces the space usage.

------------------------------------------------------------

Why Can We Return c?
---------------------

After the loop finishes,

the last calculated value is stored in:

    c

For example, for n = 5:

    c = F(5)

Therefore:

    return c;

is correct.

Another way to write the solution would be to return b,
because after each iteration b is updated to the newest
Fibonacci number.

------------------------------------------------------------

Complexity:
-----------

We calculate every Fibonacci number from F(2) to F(n) once.

Therefore:

    Time Complexity: O(n)

There are no nested loops and no repeated calculations.

------------------------------------------------------------

Space Complexity:
-----------------

We only use:

    a
    b
    c

regardless of how large n is.

Therefore:

    Space Complexity: O(1)

This is better than storing the entire Fibonacci sequence,
which would require O(n) space.

------------------------------------------------------------

Comparison With Recursive Solution:
------------------------------------

Simple recursion:

    fib(n) = fib(n-1) + fib(n-2)

Time:

    O(2^n) approximately

Space:

    O(n) recursion stack

--------------------------------

Your iterative solution:

    Time = O(n)
    Space = O(1)

So the iterative solution is much more efficient.

------------------------------------------------------------

Main Pattern to Remember:
--------------------------

This is a classic

Dynamic Programming / State Compression

pattern.

The Fibonacci recurrence needs:

    previous 2 states

Therefore, we don't need to store all previous states.

Instead:

    a = previous previous value
    b = previous value
    c = current value

Then shift:

    a = b
    b = c

So the general pattern is:

    Calculate current
          ↓
    Shift previous states
          ↓
    Repeat

For Fibonacci:

    F(n) = F(n-1) + F(n-2)

        ↓

    c = a + b

        ↓

    a = b
    b = c

*/