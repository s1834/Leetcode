class Solution {
    private:
        bool divisible(int n, int t) {
            int mul = 1;
            while(n) {
                mul *= n % 10;
                n /= 10;
            }
            return (mul % t == 0) ? true : false;
        }
    
    public:
        int smallestNumber(int n, int t) {
            while(n) {
                if(divisible(n, t)) return n;
                n++;
            }
    
            return 0;
        }
    };

/*

Idea:
------

Starting from the given number

n,

check each number one by one until we find the first number
whose

product of digits

is divisible by

t.

Since we examine numbers in increasing order,

the first valid number encountered is guaranteed to be the
smallest possible answer.

------------------------------------------------------------

Key Observation:
----------------

For every candidate number,

we only need to compute the product of its digits.

If

(product of digits) % t == 0,

then the number satisfies the condition and can be returned
immediately.

Otherwise,

continue checking the next integer.

------------------------------------------------------------

Approach:
---------

1. Define a helper function

divisible(n, t)

that computes the product of all digits of

n.

2. Check whether the product is divisible by

t.

3. Starting from

n,

repeatedly call the helper function.

4. As soon as a valid number is found,

return it.

------------------------------------------------------------

Example:
--------

n = 10

t = 2

--------------------------------

Check

10

Digit Product

1 × 0 = 0

0 % 2 = 0

Condition satisfied.

Answer

10

------------------------------------------------------------

Example:
--------

n = 15

t = 8

--------------------------------

15

Product

1 × 5 = 5

5 % 8 ≠ 0

↓

16

Product

1 × 6 = 6

6 % 8 ≠ 0

↓

17

Product

1 × 7 = 7

7 % 8 ≠ 0

↓

18

Product

1 × 8 = 8

8 % 8 = 0

Answer

18

------------------------------------------------------------

Visualization:
--------------

Start

n

↓

Check Digit Product

↓

Divisible by

t

?

      Yes

       ↓

Return Number

      No

       ↓

Increment

n

↓

Repeat

------------------------------------------------------------

Why Does This Work?
-------------------

The algorithm checks every integer in increasing order.

For each number,

it correctly computes the product of its digits and verifies
whether that product is divisible by

t.

Since every possible candidate is examined sequentially,

the first number satisfying the condition is guaranteed to
be the smallest valid answer.

------------------------------------------------------------

Time Complexity:
----------------

Let

D

be the number of digits.

Computing the digit product takes

O(D).

If

K

numbers are checked before finding the answer,

the overall complexity is

O(K × D)

------------------------------------------------------------

Space Complexity:
-----------------

Only a few integer variables are used.

Overall Space Complexity

O(1)

------------------------------------------------------------

Note:
-----

This brute-force approach is sufficient because the
constraints for this problem are small.

For larger constraints,

a mathematical or digit-DP based solution would be required
to avoid checking every number individually.

*/