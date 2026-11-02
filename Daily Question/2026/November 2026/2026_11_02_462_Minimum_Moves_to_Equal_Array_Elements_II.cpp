class Solution {
    public:
        int minMoves2(vector<int>& nums) {
            int n = nums.size();
    
            sort(nums.begin(), nums.end());
            
            int mid = nums[n / 2], operations = 0;
            for(int i = 0; i < n; i++) operations += (abs(mid - nums[i]));
    
            return operations;
        }
    };

/*
Problem: LeetCode 462 - Minimum Moves to Equal Array Elements II

Approach: Sorting + Median

Intuition:
----------
We need to make all elements of the array equal.

In one move, we can increment or decrement any element by 1.

If we choose a target value x, the total number of moves required
is the sum of absolute differences between every element and x:

    operations = |nums[0] - x| + |nums[1] - x| + ...

The key mathematical observation is that the median minimizes
the sum of absolute differences.

Therefore, we sort the array and choose its middle element
as the target value.

--------------------------------------------------
1. Get the Array Size
--------------------------------------------------

int n = nums.size();

Stores the number of elements in the array.

--------------------------------------------------
2. Sort the Array
--------------------------------------------------

sort(nums.begin(), nums.end());

Sorts the elements in non-decreasing order.

After sorting, the median can be accessed directly
using index n / 2.

--------------------------------------------------
3. Select the Median
--------------------------------------------------

int mid = nums[n / 2];

The median is the middle element of the sorted array.

For an odd-sized array, it is the exact middle element.

For an even-sized array, this selects the upper middle
element. Both middle elements lie within the range of
optimal target values, so either can be used.

Why does the median work?

Choosing a value smaller than the median increases the
total distance contributed by elements on the right.

Choosing a value greater than the median increases the
total distance contributed by elements on the left.

Hence, a median minimizes the sum of absolute differences.

--------------------------------------------------
4. Calculate the Total Operations
--------------------------------------------------

int operations = 0;

for(int i = 0; i < n; i++)
    operations += abs(mid - nums[i]);

For every element, calculate its absolute difference
from the selected median.

Each unit of difference represents one increment or
decrement operation required to make that element equal
to the target.

Adding all these differences gives the minimum total
number of moves.

--------------------------------------------------
5. Return the Answer
--------------------------------------------------

return operations;

Returns the total number of operations required to
make all elements equal.

--------------------------------------------------
6. Example Walkthrough
--------------------------------------------------

Input:
nums = [1, 2, 3]

After sorting:
[1, 2, 3]

Median:
mid = nums[3 / 2] = nums[1] = 2

Operations:

    |2 - 1| = 1
    |2 - 2| = 0
    |2 - 3| = 1

Total:

    operations = 1 + 0 + 1 = 2

Output:
2

--------------------------------------------------
7. Complexity Analysis
--------------------------------------------------

Time Complexity: O(n log n)

- Sorting takes O(n log n).
- Calculating absolute differences takes O(n).

Space Complexity:
- O(1) auxiliary space if the sorting implementation
  uses constant auxiliary space.
- The sorting implementation may use additional stack
  space depending on the implementation.

Core Idea:
----------
The median minimizes the sum of absolute differences.

Sort the array, select nums[n / 2] as the target, and
sum the absolute differences between every element
and that median.
*/