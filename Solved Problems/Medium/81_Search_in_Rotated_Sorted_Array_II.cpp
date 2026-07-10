class Solution {
    private:
        bool binarySearch(vector<int>& nums, int target, int left, int right) {
            if (left > right) return false;
    
            int mid = left + (right - left) / 2;
    
            if (nums[mid] == target) return true;
    
             // Eliminate duplicates
            if (nums[left] == nums[mid] && nums[mid] == nums[right]) return binarySearch(nums, target, left + 1, right - 1);
    
            // Left half is sorted
            if (nums[left] <= nums[mid]) {
                if (nums[left] <= target && target < nums[mid]) return binarySearch(nums, target, left, mid - 1);
                else return binarySearch(nums, target, mid + 1, right);
            }
    
            // Right half is sorted
            if (nums[mid] < target && target <= nums[right]) return binarySearch(nums, target, mid + 1, right);
            else return binarySearch(nums, target, left, mid - 1);
        }
    
    public:
        bool search(vector<int>& nums, int target) {
            return binarySearch(nums, target, 0, nums.size() - 1);
        }
    };

/*

Idea:
------
The array was originally sorted and then rotated.

Unlike LeetCode 33, duplicate elements are allowed.

Because of duplicates, we cannot always determine which half
of the array is sorted.

Therefore, Binary Search has one additional case to handle.

------------------------------------------------------------

Observation:
------------

At every recursive call, there are three possibilities.

------------------------------------------------------------

Case 1:
--------

Target is found.

nums[mid] == target

Return true.

------------------------------------------------------------

Case 2:
--------

Duplicates hide the sorted half.

nums[left] == nums[mid] == nums[right]

Example:

1 1 1 0 1
L   M   R

or

1 0 1 1 1
L   M   R

Both arrays satisfy

nums[left] == nums[mid] == nums[right]

but the rotation lies on different sides.

Therefore, we cannot determine whether the left half
or the right half is sorted.

Since both boundary elements are duplicates, removing them
does not lose any useful information.

Search the remaining range:

[left + 1 ... right - 1]

------------------------------------------------------------

Case 3:
--------

The left half is sorted.

nums[left] <= nums[mid]

Example:

4 5 6 7 | 0 1 2
L     M

Now check whether the target lies inside this sorted range.

If

nums[left] <= target < nums[mid]

search

[left ... mid - 1]

Otherwise,

search

[mid + 1 ... right]

------------------------------------------------------------

Case 4:
--------

The right half is sorted.

Example:

6 7 0 | 1 2 4 5
      M       R

Check whether the target lies inside this sorted range.

If

nums[mid] < target <= nums[right]

search

[mid + 1 ... right]

Otherwise,

search

[left ... mid - 1]

------------------------------------------------------------

Example:
--------

nums =

[2,5,6,0,0,1,2]

target = 0

mid = 0

The left half is sorted.

Since the target does not lie inside the left half,

search the right half.

Eventually,

nums[mid] == target

Return true.

------------------------------------------------------------

Worst Case Example:
-------------------

nums =

[1,1,1,1,1,1,1]

target = 2

Every recursive call satisfies

nums[left] == nums[mid] == nums[right]

We can only shrink the search space by removing duplicates:

left++
right--

Instead of eliminating half of the array each time,
we remove only two elements.

Therefore, the worst-case complexity becomes O(n).

------------------------------------------------------------

Time Complexity:
----------------

Average Case:

O(log n)

Worst Case:

O(n)

when many duplicate elements prevent us from determining
which half is sorted.

------------------------------------------------------------

Space Complexity:
-----------------

Average Case:

O(log n)

Due to recursive Binary Search.

Worst Case:

O(n)

because duplicate elimination may recurse almost once
per element.

*/