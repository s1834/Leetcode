// Version 1: Binary Search
// class Solution {
// public:
//     int search(vector<int>& nums, int target) {
//         int  l = 0, r = nums.size() - 1, m;
//         while(l <= r) {
//             m = l + (r - l) / 2;
//             if(nums[m] == target) return m;
//             if(nums[l] <= nums[m]) {
//                 if(target > nums[m] || target < nums[l]) l = m + 1;
//                 else r = m - 1;
//             } else {
//                 if(target < nums[m] || target > nums[r]) r = m - 1;
//                 else l = m + 1;
//             }
//         }
//         return -1;
//     }
// };

// /*
// 1) The function searches for a target value in a rotated sorted array.
// 2) It uses a modified binary search algorithm to find the target efficiently.
//     a) The algorithm checks the middle element and determines whether we are in the left or right sorted half of the array.
//     b) if nums[l] <= nums[m], it means the left half is sorted.
//         i) If the target is in the left half (between nums[l] and nums[m]), it narrows down the search space to that half.
//         ii) If the target is not in the left half, it narrows down the search space to the right half.
//     c) If nums[l] > nums[m], it means the right half is sorted.
//         i) If the target is in the right half (between nums[m] and nums[r]), it narrows down the search space to that half.
//         ii) If the target is not in the right half, it narrows down the search space to the left half.
// 3) The search continues until the target is found or the search space is exhausted.
// 4) If the target is found, it returns the index of the target; otherwise, it  returns -1.

// [4, 5, 6, 7, 0, 1, 2]

// The time complexity of this algorithm is O(log n), where n is the number of elements in the array.
// */

// Version 2: Binary Search
class Solution {
    private:
        int rotatedIndex(vector<int>& nums, int left, int right) {
            if (left == right) return left;
    
            if (nums[left] < nums[right]) return left;
    
            int mid = left + (right - left) / 2;
    
            if (nums[mid] >= nums[left]) return rotatedIndex(nums, mid + 1, right);
    
            return rotatedIndex(nums, left, mid);
        }
    
        int binarySearch(vector<int>& nums, int target, int left, int right) {
            if(left > right) return -1;
    
            int mid = left + (right - left) / 2;
            if(nums[mid] == target) return mid;
            else if (nums[mid] < target) return binarySearch(nums, target, mid + 1, right);
            else return binarySearch(nums, target, left, mid - 1);
        }
    
    public:
        int search(vector<int>& nums, int target) {
            int rotation = rotatedIndex(nums, 0, nums.size() - 1);
            if (rotation == 0) return binarySearch(nums, target, 0, nums.size() - 1);
            else if(target >= nums[0]) return binarySearch(nums, target, 0, rotation);
            else return binarySearch(nums, target, rotation, nums.size() - 1);
        }
    };

/*

Idea:
------
The array was originally sorted in increasing order and then rotated.

Example:

Original:

[0,1,2,4,5,6,7]

Rotated:

[4,5,6,7,0,1,2]

The rotation divides the array into two individually sorted halves.

Instead of performing Binary Search on a rotated array directly,
we first locate the rotation point (minimum element) and then
perform a normal Binary Search on the appropriate half.

------------------------------------------------------------

Step 1 : Find the Rotation Index
--------------------------------

The rotation index is the position of the smallest element.

Observation:

1.

If the current range is already sorted,

    nums[left] < nums[right]

then

left

is the rotation index.

------------------------------------------------------------

2.

Otherwise,

compute

mid

There are two possibilities.

Case 1:

nums[mid] >= nums[left]

The left half is sorted.

Therefore, the rotation point must lie
in the right half.

Search

[mid + 1 ... right]

------------------------------------------------------------

Case 2:

nums[mid] < nums[left]

The rotation point lies in the left half.

Notice that

mid

itself may be the minimum.

Therefore search

[left ... mid]

------------------------------------------------------------

Step 2 : Decide which half contains the target
----------------------------------------------

After finding the rotation index,

the array becomes

Left Half

[0 ... rotation - 1]

Right Half

[rotation ... n - 1]

Both halves are individually sorted.

If

target >= nums[0]

the target belongs to the left sorted half.

Otherwise,

it belongs to the right sorted half.

A normal Binary Search is then performed
on the corresponding half.

------------------------------------------------------------

Binary Search:
--------------

Standard Binary Search.

For every middle element,

1.

nums[mid] == target

Target found.

------------------------------------------------------------

2.

nums[mid] < target

Search right half.

------------------------------------------------------------

3.

nums[mid] > target

Search left half.

------------------------------------------------------------

Example:
--------

nums

[4,5,6,7,0,1,2]

target = 6

Rotation Index

=

4

Array is divided into

Left

[4,5,6,7]

Right

[0,1,2]

Since

6 >= 4

search the left half.

Binary Search returns index 2.

------------------------------------------------------------

Time Complexity:
----------------

Finding Rotation Index

O(log n)

Binary Search

O(log n)

Overall

O(log n)

------------------------------------------------------------

Space Complexity:
-----------------

O(log n)

Due to recursive Binary Search calls.

*/