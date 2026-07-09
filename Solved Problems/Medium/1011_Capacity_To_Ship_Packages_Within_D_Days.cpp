class Solution {
    private:
        long long int findDays(vector<int>& weights, int capacity) {
            long long int count = 0;
            int temp = 0;
            for(int x : weights) {
                if(temp < x) {
                    count++;
                    temp = capacity;
                }
                temp -= x;
            }
            return count;
        }
        
        int binarySearch(vector<int>& weights, int days, int left, int right) {
            if(left > right) return left;
            int mid = left + (right - left) / 2;
            int count = findDays(weights, mid);
            if(count <= days) return binarySearch(weights, days, left, mid - 1);
            else return binarySearch(weights, days, mid + 1, right);
        }
    
    public:
        int shipWithinDays(vector<int>& weights, int days) {
            int mx = weights[0], total = 0;
            for(auto x : weights){
                mx = max(mx, x);
                total += x;
            }
            return binarySearch(weights, days, mx, total);
        }
    };

/*

Idea:
------
We need to find the minimum ship capacity such that all packages
can be shipped within the given number of days.

Instead of trying every possible capacity, we use Binary Search
on the answer.

------------------------------------------------------------

Observation:
------------

If a ship with capacity C can ship all packages within the
required number of days,

then every capacity greater than C can also do it.

Example:

Capacity : 10  11  12  13  14  15

Days     :  8   7   6   5   5   4

Suppose

Required Days = 5

Then

Capacity 10 -> Not Possible
Capacity 11 -> Not Possible
Capacity 12 -> Not Possible
Capacity 13 -> Possible
Capacity 14 -> Possible
Capacity 15 -> Possible

Notice the transition:

False False False True True True

Since the answer changes only once, Binary Search can be applied.

------------------------------------------------------------

Finding Days Required:
----------------------

The findDays() function simulates loading packages into the ship.

Initially, the ship has

    capacity

remaining space.

For every package:

1.

If the remaining capacity is smaller than the current package,

start a new day.

Reset the remaining capacity back to the ship's capacity.

2.

Load the current package.

Subtract its weight from the remaining capacity.

The total number of times a new day is started gives the
number of days required for the given ship capacity.

------------------------------------------------------------

Binary Search:
--------------

Search Space

Minimum possible capacity

=

Maximum package weight

(The ship must at least carry the heaviest package.)

Maximum possible capacity

=

Sum of all package weights

(In one day, the ship carries every package.)

For every middle capacity,

calculate the number of days required.

There are two possibilities.

1.

Required Days <= Given Days

Current capacity is sufficient.

Try finding a smaller valid capacity by
searching the left half.

------------------------------------------------------------

2.

Required Days > Given Days

Current capacity is too small.

Increase the capacity by searching
the right half.

------------------------------------------------------------

Base Case:
----------

When

left > right

the search space becomes empty.

At this point,

left

points to the smallest valid ship capacity,
which is the required answer.

------------------------------------------------------------

Example:
--------

weights = [1,2,3,4,5,6,7,8,9,10]

days = 5

Search Space

[10,55]

mid = 32

Days Required = 2

2 <= 5

Capacity is sufficient.

Try a smaller capacity.

----------------

mid = 20

Days Required = 4

Still valid.

Try a smaller capacity.

----------------

Eventually,

left points to the minimum capacity
that ships every package within 5 days.

------------------------------------------------------------

Time Complexity:
----------------

For every Binary Search iteration,

we traverse all packages once.

Binary Search

=

O(log(totalWeight))

Traversal

=

O(n)

Overall

O(n log(totalWeight))

------------------------------------------------------------

Space Complexity:
-----------------

O(log(totalWeight))

Due to recursive Binary Search.

*/