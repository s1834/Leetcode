class Solution {
    public:
        int minMoves(vector<int>& nums) {
            int n = nums.size();
            int sum = accumulate(nums.begin(), nums.end(), 0);
            int minElement = *min_element(nums.begin(), nums.end());
            return sum - (n * minElement);
        }
    };

/*
Problem: LeetCode 453 - Minimum Moves to Equal Array Elements

Approach: Mathematical Observation

Intuition:
----------
In one move, we can increment exactly n - 1 elements by 1.

Instead of thinking about incrementing n - 1 elements, we can
think of the same operation as decrementing the remaining
one element by 1.

Therefore, the problem is equivalent to finding the minimum
number of decrements required to make every element equal.

The optimal final value will be the minimum element in the
array because we can only decrease elements in this equivalent
operation.

--------------------------------------------------
1. Find the Array Size and Sum
--------------------------------------------------

int n = nums.size();

int sum = accumulate(nums.begin(), nums.end(), 0);

- n stores the number of elements.
- sum calculates the total sum of all array elements.

--------------------------------------------------
2. Find the Minimum Element
--------------------------------------------------

int minElement = *min_element(nums.begin(), nums.end());

This finds the smallest element in the array.

Since the equivalent operation only decreases elements,
the optimal target value is minElement.

--------------------------------------------------
3. Calculate the Minimum Moves
--------------------------------------------------

return sum - (n * minElement);

Every element must eventually become minElement.

The total number of decrements required is:

    (nums[0] - minElement)
  + (nums[1] - minElement)
  + ...
  + (nums[n-1] - minElement)

Expanding the expression:

    = sum - n * minElement

Hence, the answer is:

    sum - (n * minElement)

--------------------------------------------------
4. Example Walkthrough
--------------------------------------------------

Input:
nums = [1, 2, 3]

n = 3
sum = 1 + 2 + 3 = 6
minElement = 1

Minimum moves:

    6 - (3 * 1)
    = 6 - 3
    = 3

One possible sequence:

[1, 2, 3]
[1, 1, 3]
[1, 1, 2]
[1, 1, 1]

Total moves = 3.

--------------------------------------------------
5. Complexity Analysis
--------------------------------------------------

Time Complexity: O(n)

- accumulate() takes O(n).
- min_element() takes O(n).
- The remaining calculation takes O(1).

Space Complexity: O(1)

Only a few variables are used, and the input array is
not modified.

Core Idea:
----------
Incrementing n - 1 elements by 1 is equivalent to
decrementing the remaining element by 1.

Thus, we can calculate the minimum moves by bringing
every element down to the minimum array value:

    Answer = sum - n * minimum_element
*/