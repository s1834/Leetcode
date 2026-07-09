class Solution {
    private:
        int binarySearch(int target, int left, int right) {
            if(left > right) return right;
    
            int mid = left + (right - left) / 2;
            long long int square = 1LL * mid * mid;
            if(square == target) return mid;
            else if(square < target) return binarySearch(target, mid + 1, right);
            else return binarySearch(target, left, mid - 1);
        }
    
    public:
        int mySqrt(int x) {
            return binarySearch(x, 0, x);
        }
    };
/*

Idea:
------
The square root of a number x is the largest integer whose square
is less than or equal to x.

Instead of checking every number from 1 to x, we use Binary Search
because the squares are monotonically increasing.

Example:

1² = 1
2² = 4
3² = 9
4² = 16
5² = 25

As the number increases, its square also increases.
Therefore, Binary Search can be applied.

------------------------------------------------------------

Observation:
------------

For every middle value:

    mid²

There are only three possibilities.

1. mid² == x

      We found the exact square root.

2. mid² < x

      mid is a valid answer, but there may exist a larger integer
      whose square is still less than or equal to x.

      Search the right half.

3. mid² > x

      mid is too large.

      Search the left half.

------------------------------------------------------------

Base Case:
----------

When

    left > right

the search space becomes empty.

At this point,

    right

is the largest integer whose square is less than or equal to x,
which is exactly the required integer square root.

Example:

x = 8

Search eventually becomes

left = 3
right = 2

Since

2² <= 8
3² > 8

the answer is

2

Therefore, return right.

------------------------------------------------------------

Overflow:
---------

Computing

    mid * mid

using int may overflow for large values of x.

Example:

mid = 50000

50000 × 50000 = 2,500,000,000

which exceeds the range of a 32-bit integer.

To avoid this, compute

    1LL * mid * mid

so the multiplication is performed using long long.

------------------------------------------------------------

Example:
--------

x = 15

Search Range:

[0,15]

mid = 7

49 > 15

Search Left

[0,6]

mid = 3

9 < 15

Search Right

[4,6]

mid = 5

25 > 15

Search Left

[4,4]

mid = 4

16 > 15

Search Left

left = 4
right = 3

Return right = 3

Answer:

√15 = 3

------------------------------------------------------------

Time Complexity:
----------------

O(log x)

Each recursive call eliminates half of the remaining search space.

------------------------------------------------------------

Space Complexity:
-----------------

O(log x)

Due to the recursive call stack.

*/