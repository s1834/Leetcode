class Solution {
    public:
        int tribonacci(int n) {
            if(n == 0) return 0;
            if(n <= 2) return 1;
    
            int t0 = 0, t1 = 1, t2 = 1, t;
    
            for(int i = 3; i <= n; i++) {
                t = t0 + t1 + t2;
                t0 = t1;
                t1 = t2;
                t2 = t;
            }
            return t;
        }
    };

/*
LeetCode 1137. N-th Tribonacci Number

Idea:
------

The Tribonacci sequence is similar to Fibonacci, but instead
of using the previous 2 values, we use the previous 3 values.

The sequence is defined as:

    T(0) = 0
    T(1) = 1
    T(2) = 1

For n >= 3:

    T(n) = T(n - 1) + T(n - 2) + T(n - 3)

So the sequence is:

    0, 1, 1, 2, 4, 7, 13, 24, 44, ...

We can calculate the sequence iteratively while keeping only
the previous three values.

------------------------------------------------------------

Base Cases:
-----------

    if(n == 0) return 0;
    if(n <= 2) return 1;

These directly handle:

    T(0) = 0
    T(1) = 1
    T(2) = 1

For example:

    tribonacci(0) -> 0
    tribonacci(1) -> 1
    tribonacci(2) -> 1

For n >= 3, we need to calculate the sequence.

------------------------------------------------------------

Keeping Track of Three Values:
------------------------------

We initialize:

    int t0 = 0;
    int t1 = 1;
    int t2 = 1;

These represent:

    t0 = T(0)
    t1 = T(1)
    t2 = T(2)

Since every new Tribonacci value depends on the previous
three values, these are the only values we need to keep.

------------------------------------------------------------

Calculating the Next Value:
---------------------------

The recurrence is:

    T(n) = T(n-1) + T(n-2) + T(n-3)

So:

    t = t0 + t1 + t2;

Here:

    t = next Tribonacci number

After calculating it, we move the three variables forward:

    t0 = t1;
    t1 = t2;
    t2 = t;

Before the update:

    t0 = T(i-3)
    t1 = T(i-2)
    t2 = T(i-1)

After the update:

    t0 = T(i-2)
    t1 = T(i-1)
    t2 = T(i)

So the variables are ready for the next iteration.

------------------------------------------------------------

Example: n = 5
--------------

Initial values:

    t0 = 0
    t1 = 1
    t2 = 1

Meaning:

    T(0) = 0
    T(1) = 1
    T(2) = 1

------------------------------------------------

i = 3:

    t = 0 + 1 + 1
      = 2

Update:

    t0 = 1
    t1 = 1
    t2 = 2

Now:

    t0 = T(1)
    t1 = T(2)
    t2 = T(3)

------------------------------------------------

i = 4:

    t = 1 + 1 + 2
      = 4

Update:

    t0 = 1
    t1 = 2
    t2 = 4

Now:

    t2 = T(4)

------------------------------------------------

i = 5:

    t = 1 + 2 + 4
      = 7

Update:

    t0 = 2
    t1 = 4
    t2 = 7

Therefore:

    T(5) = 7

and:

    return t;

returns 7.

------------------------------------------------------------

Why Do We Need Three Variables?
--------------------------------

In Fibonacci:

    F(n) = F(n-1) + F(n-2)

so we only need two previous values.

In Tribonacci:

    T(n) = T(n-1) + T(n-2) + T(n-3)

so we need three previous values.

Therefore:

    Fibonacci:
        a, b

    Tribonacci:
        t0, t1, t2

This is the same state-compression idea, just with one
additional previous state.

------------------------------------------------------------

Why Use a Temporary Variable t?
--------------------------------

We calculate:

    t = t0 + t1 + t2;

before shifting the values.

We cannot update the variables immediately because we would
lose the old values that are still needed.

For example, if:

    t0 = 1
    t1 = 2
    t2 = 4

we need:

    t = 1 + 2 + 4 = 7

before changing t0, t1, and t2.

After calculating t:

    t0 = t1;
    t1 = t2;
    t2 = t;

Now the window moves forward.

------------------------------------------------------------

Sliding Window:
---------------

The algorithm maintains a window of the last three values:

    T(0)  T(1)  T(2)
      ↓     ↓     ↓

After calculating T(3):

    T(1)  T(2)  T(3)
      ↓     ↓     ↓

After calculating T(4):

    T(2)  T(3)  T(4)
      ↓     ↓     ↓

And so on.

We never need values older than these three.

------------------------------------------------------------

Why Iteration Instead of Recursion?
------------------------------------

A direct recursive solution would repeatedly calculate the
same Tribonacci values.

For example:

    T(5)
   / | \
 T(4) T(3) T(2)

and T(4), T(3), etc. would themselves make more recursive
calls.

This causes a lot of repeated work.

The iterative solution calculates every value exactly once.

Therefore, it is much more efficient.

------------------------------------------------------------

Why Can We Return t?
--------------------

The loop runs:

    for(int i = 3; i <= n; i++)

So the final iteration calculates:

    T(n)

and stores it in:

    t

Then:

    t2 = t

as well.

Therefore:

    return t;

is correct.

You could also return:

    return t2;

because after the final iteration t2 also contains T(n).

------------------------------------------------------------

Time Complexity:
----------------

We calculate every Tribonacci number from T(3) through T(n)
exactly once.

Therefore:

    Time Complexity: O(n)

------------------------------------------------------------

Space Complexity:
-----------------

We only use four integer variables:

    t0
    t1
    t2
    t

No array or recursion is required.

Therefore:

    Space Complexity: O(1)

------------------------------------------------------------

Main Pattern to Remember:
--------------------------

This is another example of

Dynamic Programming + State Compression.

The recurrence is:

    T(n) = T(n-1) + T(n-2) + T(n-3)

Instead of storing:

    dp[0], dp[1], ..., dp[n]

we only keep the last three states:

    t0 = previous 3rd
    t1 = previous 2nd
    t2 = previous 1st

Calculate:

    t = t0 + t1 + t2;

Then shift:

    t0 = t1;
    t1 = t2;
    t2 = t;

So the general pattern is:

    Previous 3 states
          ↓
    Calculate current
          ↓
    Shift the window
          ↓
       Repeat

*/