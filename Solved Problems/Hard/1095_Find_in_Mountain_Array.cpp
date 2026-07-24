/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */

 class Solution {
    private: 
        int binarySearch(MountainArray &mountainArr, int target, int left, int right, bool asc) {
            if (left > right) return -1;
    
            int mid = left + (right - left) / 2;
            int num = mountainArr.get(mid);
    
            if (num == target) return mid;
            else if (asc) {
                if (num > target) return binarySearch(mountainArr, target, left, mid - 1, true);
                else return binarySearch(mountainArr, target, mid + 1, right, true);
            } else {
                if (num > target) return binarySearch(mountainArr, target, mid + 1, right, false);
                else return binarySearch(mountainArr, target, left, mid - 1, false);
            }
        }
    
        int findMax(MountainArray &mountainArr, int target, int left, int right) {
            if(left == right) {
                int first = binarySearch(mountainArr, target, 0, left, true);
                int second = binarySearch(mountainArr, target, left + 1, mountainArr.length() - 1, false);
    
                if (first == -1) return second;
                if (second == -1) return first;
                return min(first, second);
            } 
    
            int mid = left + (right - left) / 2;
            int r = mountainArr.get(mid + 1), m = mountainArr.get(mid);
            if(m < r) return findMax(mountainArr, target, mid + 1, right);
            else return findMax(mountainArr, target, left, mid);
        }
    
    public:
        int findInMountainArray(int target, MountainArray &mountainArr) {
            return findMax(mountainArr, target, 0, mountainArr.length() - 1);
        }
    };

/*

Idea:
------
A Mountain Array has two sorted parts:

• Strictly increasing from the beginning to the peak.

• Strictly decreasing from the peak to the end.

Therefore,

instead of searching the entire array linearly,

we first locate the peak element and then perform Binary
Search on both halves.

Since the left half is increasing and the right half is
decreasing,

each half can be searched independently using Binary
Search.

------------------------------------------------------------

Overall Algorithm:
------------------

1.

Find the peak (maximum) element using Binary Search.

------------------------------------------------------------

2.

Search for the target in the increasing part.

------------------------------------------------------------

3.

Search for the target in the decreasing part.

------------------------------------------------------------

4.

If the target exists in both halves,

return the smaller index.

Otherwise,

return whichever index is found.

If neither search succeeds,

return

-1.

------------------------------------------------------------

Finding the Peak:
-----------------

The peak is the only element such that

arr[i] > arr[i-1]

and

arr[i] > arr[i+1]

Instead of checking both neighbors,

we compare only

arr[mid]

and

arr[mid + 1].

--------------------------------

If

arr[mid] < arr[mid + 1]

we are on the increasing slope.

The peak must lie to the right.

Search

[mid + 1, right]

--------------------------------

If

arr[mid] > arr[mid + 1]

we are on the decreasing slope or exactly at the peak.

The peak lies at

mid

or to its left.

Search

[left, mid]

This Binary Search continues until

left == right,

which is the peak index.

------------------------------------------------------------

Why Does Peak Binary Search Work?
---------------------------------

A mountain array first increases and then decreases.

Therefore,

the comparison

arr[mid]

vs

arr[mid + 1]

always tells us which side of the peak we are on.

Increasing Side

arr[mid] < arr[mid + 1]

↓

Move Right

----------------------------

Decreasing Side

arr[mid] > arr[mid + 1]

↓

Move Left

Since every comparison eliminates half of the search
space,

the peak is found in

O(log n)

time.

------------------------------------------------------------

Binary Search on Both Halves:
-----------------------------

After finding the peak,

the array becomes

Increasing Part

[0 ... peak]

Decreasing Part

[peak + 1 ... n-1]

--------------------------------

Increasing Half

Uses normal Binary Search.

If

midValue > target

search left.

Otherwise,

search right.

--------------------------------

Decreasing Half

The order is reversed.

If

midValue > target

search right.

Otherwise,

search left.

The same recursive Binary Search function is reused by
passing a flag indicating whether the current portion is
ascending or descending.

------------------------------------------------------------

Why Search Both Halves?
-----------------------

The target can appear on either side of the peak.

For example,

1 3 5 7 6 4 2

Target

4

exists only in the decreasing half.

--------------------------------

Example

1 2 3 4 5 3 1

Target

3

appears in both halves.

LeetCode requires returning the

smallest index,

so both halves are searched and the minimum valid index
is returned.

------------------------------------------------------------

Example:
--------

Mountain Array

[1,2,4,5,3,1]

Target = 3

--------------------------------

Step 1

Find Peak

Compare

4

and

5

Move Right.

Compare

5

and

3

Move Left.

Peak =

5

(index 3)

--------------------------------

Step 2

Binary Search

Increasing Half

[1,2,4,5]

Target not found.

--------------------------------

Step 3

Binary Search

Decreasing Half

[3,1]

Target found at index

4

Answer = 4

------------------------------------------------------------

Example:
--------

Mountain Array

[1,2,3,4,5,3,1]

Target = 3

Peak = 5

--------------------------------

Increasing Half

Target found at index

2

--------------------------------

Decreasing Half

Target found at index

5

--------------------------------

Return

min(2,5)

=

2

------------------------------------------------------------

Why Does This Work?
-------------------

The peak divides the mountain array into two sorted
arrays.

Binary Search works on sorted arrays.

Therefore,

after locating the peak,

the problem reduces to performing Binary Search on the
two halves.

Searching both halves guarantees that every possible
occurrence of the target is considered, and returning the
smaller index satisfies the problem requirement.

------------------------------------------------------------

Time Complexity:
----------------

Finding Peak:

O(log n)

--------------------------------

Binary Search on Increasing Half:

O(log n)

--------------------------------

Binary Search on Decreasing Half:

O(log n)

--------------------------------

Overall:

O(log n)

------------------------------------------------------------

Space Complexity:
-----------------

O(log n)

The implementation uses recursive Binary Search and
recursive peak search, so the recursion stack is

O(log n).

An iterative implementation would reduce this to

O(1).

*/