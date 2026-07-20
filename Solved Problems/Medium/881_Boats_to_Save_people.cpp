class Solution {
    public:
        int numRescueBoats(vector<int>& people, int limit) {
            sort(people.begin(), people.end());
            int boats = 0, left = 0, right = people.size() - 1;
            while(left <= right) {
                if(left == right){
                    boats++;
                    break;
                } else if(people[left] + people[right] <= limit) {
                    boats++;
                    left++;
                    right--;
                } else {
                    boats++;
                    right--;
                }
            }
            
            return boats;
        }
    };

/*

Idea:
------
Each boat can carry at most two people, and the total
weight on the boat cannot exceed the given limit.

To minimize the number of boats, always try to pair the
heaviest remaining person with the lightest remaining
person.

If they can share a boat, it is the best possible
pairing since the heaviest person cannot be paired with
anyone heavier.

If they cannot share a boat, the heaviest person must
occupy a boat alone.

Sorting the array allows us to efficiently make this
greedy decision using two pointers.

------------------------------------------------------------

Why Does This Greedy Approach Work?
----------------------------------

Consider the heaviest remaining person.

There are only two possibilities:

1.

The lightest remaining person can fit with them.

Since everyone else is heavier than the lightest person,
pairing the heaviest person with anyone else is no
better.

So we pair them together.

------------------------------------------------------------

2.

The lightest person cannot fit with the heaviest person.

Then no other person can fit with the heaviest person
either because everyone else weighs even more.

Hence, the heaviest person must go alone.

Thus, making the greedy choice is always optimal.

------------------------------------------------------------

Algorithm:
----------

1.

Sort the array in non-decreasing order.

------------------------------------------------------------

2.

Maintain two pointers:

left

points to the lightest remaining person.

right

points to the heaviest remaining person.

------------------------------------------------------------

3.

While

left <= right

If only one person remains,

assign one boat and stop.

------------------------------------------------------------

4.

Otherwise,

if

people[left] + people[right] <= limit

both people can share a boat.

Increment

left

Decrement

right

Increment the boat count.

------------------------------------------------------------

5.

Otherwise,

the heaviest person cannot be paired with anyone.

Assign one boat only to

people[right]

Decrement

right

Increment the boat count.

------------------------------------------------------------

6.

Return the total number of boats.

------------------------------------------------------------

Example:
--------

people =

[3, 2, 2, 1]

limit = 3

After sorting

[1, 2, 2, 3]

Initially

left = 0

right = 3

----------------

1 + 3 = 4

Cannot pair.

Boat 1

(3)

right--

----------------

1 + 2 = 3

Can pair.

Boat 2

(1,2)

left++

right--

----------------

Only one person remains

Boat 3

(2)

Answer = 3

------------------------------------------------------------

Time Complexity:
----------------

Sorting:

O(n log n)

Two-pointer traversal:

O(n)

Overall:

O(n log n)

------------------------------------------------------------

Space Complexity:
-----------------

O(1)

Ignoring the space used by the sorting algorithm.

*/