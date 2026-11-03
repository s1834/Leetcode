class Solution {
    public:
        int minMoves(vector<int>& nums) {
            int maxElement = *max_element(nums.begin(), nums.end());
            int moves = 0;
            for(auto &x : nums) moves += maxElement - x;
            return moves;
        }
    };

/*
Problem: LeetCode 3736

Approach: Greedy + Maximum Element

Intuition:
----------
The solution finds the maximum element in the array and
calculates how many increments are required to make every
element equal to that maximum.

Since we can only increase elements, the maximum element
acts as the target value.

Every other element must be increased until it reaches
maxElement.

--------------------------------------------------
1. Find the Maximum Element
--------------------------------------------------

int maxElement = *max_element(nums.begin(), nums.end());

max_element() returns an iterator pointing to the largest
element in the array.

The * operator dereferences that iterator to get its value.

This maximum element becomes the target value because
we only need to increase the remaining elements.

--------------------------------------------------
2. Initialize the Move Counter
--------------------------------------------------

int moves = 0;

Stores the total number of increments required.

--------------------------------------------------
3. Calculate the Required Moves
--------------------------------------------------

for(auto &x : nums)
    moves += maxElement - x;

Traverse every element in the array.

For each element x:

    Required increments = maxElement - x

Since each increment increases the element by 1, the
difference directly represents the number of moves
required for that element.

We add these differences to moves.

Using auto& avoids creating a copy of each element,
although the elements are not modified in this loop.

--------------------------------------------------
4. Return the Answer
--------------------------------------------------

return moves;

After processing all elements, moves contains the total
number of increments required to make every element
equal to the maximum element.

--------------------------------------------------
5. Example Walkthrough
--------------------------------------------------

Input:
nums = [1, 3, 5]

Step 1:
    maxElement = 5

Step 2:
    moves = 0

Step 3:

    For x = 1:
        moves += 5 - 1 = 4

    For x = 3:
        moves += 5 - 3 = 2

    For x = 5:
        moves += 5 - 5 = 0

Total:

    moves = 4 + 2 + 0 = 6

Output:
6

--------------------------------------------------
6. Complexity Analysis
--------------------------------------------------

Time Complexity: O(n)

- max_element() takes O(n).
- The range-based loop takes O(n).

Space Complexity: O(1)

Only two additional variables are used.

Core Idea:
----------
Find the maximum element and calculate the difference
between it and every other element.

The sum of these differences gives the total number
of increments required:

    Answer = Σ (maxElement - nums[i])
*/