class Solution {
    private:
        long long int subtract(vector<int>& piles, int speed) {
            long long int count = 0;
            for(int x : piles) count += ceil((double)x / speed);
            return count;
        }
    
        int binarySearch(vector<int>& piles, int h, int left, int right) {
            if(left > right) return left;
            int mid = left + (right - left) / 2;
            long long int count = subtract(piles, mid);
            if (count <= h) return binarySearch(piles, h, left, mid - 1);
            else return binarySearch(piles, h, mid + 1, right);
        }
    
    public:
        int minEatingSpeed(vector<int>& piles, int h) {
            int mx = piles[0];
            for(auto x : piles) mx = max(mx, x);
            return binarySearch(piles, h, 1, mx);
        }
    };

/*

Idea:
------
We need to find the minimum eating speed K such that Koko can finish
all the banana piles within h hours.

Instead of trying every possible speed from 1 to the largest pile,
we use Binary Search on the answer.

------------------------------------------------------------

Observation:
------------

If Koko can finish all bananas at speed K,

then she can also finish at every speed greater than K.

Example:

Speed : 1   2   3   4   5   6

Hours :15  10   8   6   5   4

Suppose

h = 8

Then

Speed 1 -> Not Possible
Speed 2 -> Not Possible
Speed 3 -> Possible
Speed 4 -> Possible
Speed 5 -> Possible
Speed 6 -> Possible

Notice the transition:

False False False True True True

Since the answer changes only once, Binary Search can be applied.

------------------------------------------------------------

Finding Hours Required:
-----------------------

For every pile,

Hours Required

=

ceil(pile / speed)

For example,

Pile = 11

Speed = 3

Hours

=

ceil(11 / 3)

=

4

The subtract() function computes the total number of hours
required to finish every pile at the given eating speed.

------------------------------------------------------------

Binary Search:
--------------

Search Space

Minimum possible speed

=

1

Maximum possible speed

=

Largest pile

For every middle speed,

Compute the total hours needed.

There are two possibilities.

1.

Hours <= h

Current speed is valid.

Since we need the minimum possible speed,
search the left half.

------------------------------------------------------------

2.

Hours > h

Current speed is too slow.

Increase the eating speed by searching
the right half.

------------------------------------------------------------

Base Case:
----------

When

left > right

the search space becomes empty.

At this point,

left

points to the smallest valid eating speed,
which is the required answer.

------------------------------------------------------------

Example:
--------

piles = [3,6,7,11]

h = 8

Search Space

[1,11]

mid = 6

Hours

=

1 + 1 + 2 + 2

=

6

6 <= 8

Try a smaller speed.

----------------

mid = 3

Hours

=

1 + 2 + 3 + 4

=

10

10 > 8

Speed is too slow.

Increase speed.

----------------

Eventually

left = 4

Answer

4

------------------------------------------------------------

Time Complexity:
----------------

For every Binary Search iteration,

we traverse all piles once.

Binary Search

=

O(log(maxPile))

Traversal

=

O(n)

Overall

O(n log(maxPile))

------------------------------------------------------------

Space Complexity:
-----------------

O(log(maxPile))

Due to recursive Binary Search.

*/