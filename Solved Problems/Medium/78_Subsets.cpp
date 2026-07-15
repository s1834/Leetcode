class Solution {
    private:
        vector<vector<int>> ans;
        vector<int> curr;
    
        void dfs(vector<int>& nums, int i) {
             if (i == nums.size()) {
                ans.push_back(curr);
                return;
            }
    
            // Include nums[i]
            curr.push_back(nums[i]);
            dfs(nums, i + 1);
    
            curr.pop_back();
            
            // Exclude nums[i]
            dfs(nums, i + 1);
        }
        
    public:
        vector<vector<int>> subsets(vector<int>& nums) {
            dfs(nums, 0);
            return ans;
        }
    };

/*

Idea:
------
Generate every possible subset using recursion.

For every element, there are two choices:

1.

Include the current element in the subset.

2.

Exclude the current element from the subset.

By exploring both choices recursively, every possible
subset is generated exactly once.

------------------------------------------------------------

Algorithm:
----------

At every index,

make two recursive calls.

------------------------------------------------------------

Choice 1:

Include nums[i].

Add it to the current subset.

Recursively process the next index.

After returning,

remove it (backtracking) so the next recursive call
starts from the original state.

------------------------------------------------------------

Choice 2:

Exclude nums[i].

Simply move to the next index without modifying the
current subset.

------------------------------------------------------------

Base Case:
----------

When

i == nums.size()

every element has been considered.

The current subset is complete.

Store it in the answer.

------------------------------------------------------------

Example:
--------

nums = [1,2]

Recursive Tree

                    {}
                 /        \
              +1          skip 1
             /               \
          {1}                 {}
         /   \              /    \
      +2     skip2      +2      skip2
     /          \        /          \
 {1,2}        {1}     {2}          {}

Answer:

[1,2]

[1]

[2]

[]

------------------------------------------------------------

Backtracking:
-------------

After exploring the "include" choice,

remove the last inserted element using

curr.pop_back()

This restores the subset to its previous state before
exploring the "exclude" choice.

------------------------------------------------------------

Time Complexity:
----------------

O(n × 2^n)

There are 2^n possible subsets, and copying each subset
into the answer takes O(n) time in the worst case.

------------------------------------------------------------

Space Complexity:
-----------------

Auxiliary Space:

O(n)

due to the recursion stack and the current subset.

Output Space:

O(n × 2^n)

to store all generated subsets.

*/