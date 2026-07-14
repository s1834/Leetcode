class Solution {
    private:
        int dfs(vector<int>& nums, int idx, int total) {
            if(nums.size() == idx) return total;
            return dfs(nums, idx + 1, total ^ nums[idx]) + dfs (nums, idx + 1, total);
        }
    
    public:
        int subsetXORSum(vector<int>& nums) {
            return dfs(nums, 0, 0);;
        }
    };

/*

Idea:
------
Generate every possible subset using recursion.

For every element, there are two choices:

1.

Include the current element in the subset.

Update the current XOR.

2.

Exclude the current element.

Keep the current XOR unchanged.

When all elements have been processed, the current XOR
represents one complete subset and is added to the answer.

------------------------------------------------------------

Algorithm:
----------

At every index,

make two recursive calls.

------------------------------------------------------------

Choice 1:

Include the current element.

Update the XOR as

currentXOR ^ nums[idx]

------------------------------------------------------------

Choice 2:

Skip the current element.

Keep the current XOR unchanged.

------------------------------------------------------------

When

idx == nums.size()

all elements have been considered.

Return the XOR value of the current subset.

The final answer is the sum of XOR values returned by
every recursive path.

------------------------------------------------------------

Example:
--------

nums = [1,3]

Recursive Tree

                    (0, XOR = 0)
                   /            \
             include           exclude
                1                 -
             XOR = 1           XOR = 0
             /     \           /      \
       include    exclude  include   exclude
          3          3         3         3
      XOR = 2    XOR = 1   XOR = 3   XOR = 0

Leaf Nodes:

Subset:

{1,3}

XOR = 2

Subset:

{1}

XOR = 1

Subset:

{3}

XOR = 3

Subset:

{}

XOR = 0

Answer:

2 + 1 + 3 + 0 = 6

------------------------------------------------------------

Time Complexity:
----------------

O(2^n)

Each element has two choices (include or exclude),
resulting in 2^n subsets.

------------------------------------------------------------

Space Complexity:
-----------------

O(n)

The recursion depth is at most n.

*/