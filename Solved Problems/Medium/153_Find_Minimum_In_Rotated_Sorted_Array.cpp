// Version 1: Binary Search
// class Solution {
// public:
//     int findMin(vector<int>& nums) {
//         int ans = nums[0], l = 0, r = nums.size() - 1, m;
//         while(l <= r) {
//             if(nums[l] < nums[r]) {
//                 ans = min(ans, nums[l]);
//                 break;
//             }
            
//             m = l + (r - l) / 2;
//             ans = min(ans, nums[m]);
//             if(nums[m] >= nums[l]) l = m + 1;
//             else r = m - 1;
//         }
//         return ans;
//     }
// };

// /*
// [3, 4, 5, 1, 2]
//  l     m     r
//  since nums[m] >= nums[l]:
//     right search
//  else:
//     left search

// [3, 4, 5, 1, 2]
//  l        m  r
//  lets say for some case 1 was middle, thats why we checked the min after calculating result also, so that we can return the minimum element in case if middle is smallest
// */

// Version 2: Binary Search
class Solution {
    private:
        int binarySearch(vector<int>& nums, int left, int right) {
            if (left == right) return nums[left];
    
            if (nums[left] < nums[right]) return nums[left];
    
            int mid = left + (right - left) / 2;
    
            if (nums[mid] >= nums[left]) return binarySearch(nums, mid + 1, right);
    
            return binarySearch(nums, left, mid);
        }
    
    public:
        int findMin(vector<int>& nums) {
            return binarySearch(nums, 0, nums.size() - 1);
        }
    };

/*

Idea:
------
The original sorted array has been rotated exactly once.

Examples:

Original:

[0,1,2,4,5,6,7]

Rotated:

[4,5,6,7,0,1,2]

Notice that only one position breaks the sorted order.
The minimum element is exactly at this rotation point.

Since one half of the array is always sorted,
Binary Search can be used to locate the minimum.

------------------------------------------------------------

Observation:
------------

For every search range [left, right], there are two possibilities.

1.

The current range is already sorted.

Example:

[0,1,2,3,4]

Since the array is sorted,

    nums[left]

is the smallest element.

Return it immediately.

------------------------------------------------------------

2.

The current range is rotated.

Example:

[4,5,6,7,0,1,2]

At least one half will always remain sorted.

Compute

    mid

and determine which half is sorted.

------------------------------------------------------------

Case 1:

nums[mid] >= nums[left]

Example:

[4,5,6 | 7 | 0,1,2]

The left half

[4,5,6,7]

is completely sorted.

Since nums[left] is not the minimum of the entire array,
the rotation point (minimum element) must lie in the right half.

Search:

[mid + 1 ... right]

------------------------------------------------------------

Case 2:

nums[mid] < nums[left]

Example:

[4,5,6 | 0 | 1,2]

The rotation point lies in the left half.

Notice that

mid

itself may be the minimum.

Therefore search:

[left ... mid]

------------------------------------------------------------

Base Case:
----------

When

left == right

only one element remains.

That element must be the minimum.

Return

nums[left]

------------------------------------------------------------

Example:
--------

nums =

[4,5,6,7,0,1,2]

Search

[0,6]

mid = 3

nums[mid] = 7

7 >= 4

Minimum must be on the right.

Search

[4,6]

Current range

[0,1,2]

is already sorted.

Return

0

------------------------------------------------------------

Time Complexity:
----------------

O(log n)

Each recursive call eliminates half of the remaining search space.

------------------------------------------------------------

Space Complexity:
-----------------

O(log n)

Due to the recursive call stack.

*/