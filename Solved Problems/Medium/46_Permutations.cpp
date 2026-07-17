class Solution {
    private:
        vector<vector<int>> ans;
    
        void solve(vector<int>& nums, int i) {
            if(i == nums.size()) {
                ans.push_back(nums);
                return;
            }
    
            for(int j = i; j < nums.size(); j++) {
                swap(nums[i], nums[j]);
                solve(nums, i + 1);
                swap(nums[i], nums[j]);
            }
        }
    
    public:
        vector<vector<int>> permute(vector<int>& nums) {
            solve(nums, 0);
            return ans;
        }
    };

/*

Idea:
------
Generate all possible permutations using backtracking.

At every position i, choose one of the remaining unused
elements to place there.

Instead of maintaining a separate visited array, we
swap the chosen element into the current position.

After exploring all permutations starting with that
choice, swap the elements back to restore the original
array (backtracking).

------------------------------------------------------------

Algorithm:
----------

Start from index 0.

For every position i,

try placing every element from index i to the end
at position i.

------------------------------------------------------------

For every j in [i, n-1]:

1.

Swap nums[i] and nums[j].

This fixes nums[j] at the current position.

2.

Recursively generate permutations for the remaining
positions starting from i + 1.

3.

Swap the elements back.

This restores the array before trying the next choice.

------------------------------------------------------------

Base Case:
----------

When

i == nums.size()

all positions have been fixed.

The current arrangement is one valid permutation.

Store it in the answer.

------------------------------------------------------------

Example:
--------

nums = [1,2,3]

Initial:

[1,2,3]

Position 0:

Choose 1

[1,2,3]

    Position 1:

    Choose 2

    [1,2,3]

        Position 2:

        Choose 3

        [1,2,3]

        Store

    Backtrack

    Choose 3

    [1,3,2]

    Store

Backtrack to Position 0

Choose 2

[2,1,3]

Generate

[2,1,3]

[2,3,1]

Backtrack

Choose 3

[3,2,1]

Generate

[3,2,1]

[3,1,2]

Final Answer:

[1,2,3]

[1,3,2]

[2,1,3]

[2,3,1]

[3,1,2]

[3,2,1]

------------------------------------------------------------

Backtracking:
-------------

After exploring all permutations with the current
choice,

swap the elements back using

swap(nums[i], nums[j]);

This restores the original array before trying the
next element for the current position.

Without this step, future recursive calls would work
on a modified array and produce incorrect permutations.

------------------------------------------------------------

Why Swapping Works:
-------------------

When processing position i,

all positions before i have already been fixed.

Swapping brings one candidate element into position i
without requiring an additional visited array.

The recursive call then fixes the remaining positions.

Thus, every permutation is generated exactly once.

------------------------------------------------------------

Time Complexity:
----------------

O(n × n!)

There are n! permutations.

Copying each permutation of length n into the answer
takes O(n).

------------------------------------------------------------

Space Complexity:
-----------------

Auxiliary Space:

O(n)

due to the recursion stack.

The algorithm performs all swaps in-place and does not
use any extra visited array.

Output Space:

O(n × n!)

to store all generated permutations.

*/