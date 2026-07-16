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
            while(i + 1 != nums.size() && nums[i] == nums[i + 1]) i++;
            dfs(nums, i + 1);
        }
    
    
    public:
        vector<vector<int>> subsetsWithDup(vector<int>& nums) {
            sort(nums.begin(), nums.end());
            dfs(nums, 0);
            return ans;
        }
    };

/*

Idea:
------
Generate all possible subsets using backtracking.

Since the input may contain duplicate elements,

sort the array first so that duplicate values become
adjacent.

For every element, there are two choices:

1.

Include the current element in the subset.

2.

Exclude the current element.

Before exploring the exclude branch, skip all
consecutive duplicate values to avoid generating
duplicate subsets.

------------------------------------------------------------

Algorithm:
----------

Sort the array.

Sorting groups duplicate elements together, making
them easy to skip.

------------------------------------------------------------

At every index,

make two recursive calls.

------------------------------------------------------------

Choice 1:

Include nums[i].

Add it to the current subset.

Recursively process the next index.

------------------------------------------------------------

After returning,

remove the last inserted element (backtracking)
to restore the previous state.

------------------------------------------------------------

Choice 2:

Exclude nums[i].

Before moving to the next index,

skip all consecutive duplicate values.

This prevents exploring multiple recursion branches
that would generate identical subsets.

------------------------------------------------------------

Base Case:
----------

When

i == nums.size()

all elements have been considered.

The current subset is complete.

Store it in the answer.

------------------------------------------------------------

Example:
--------

nums = [1,2,2]

After sorting:

[1,2,2]

Recursive Tree

                    {}
                 /        \
              +1          -1
             /              \
          {1}               {}
         /   \             /   \
      +2      skip      +2    skip
     /                   |
 {1,2}                 {2}
   |
 +2
   |
{1,2,2}

Generated Subsets:

{}

{1}

{2}

{1,2}

{2,2}

{1,2,2}

Notice that

{2}

and

{1,2}

are generated only once because duplicate values are
skipped in the exclude branch.

------------------------------------------------------------

Backtracking:
-------------

After exploring the "include" branch,

remove the last inserted element using

curr.pop_back()

This restores the subset before exploring the
"exclude" branch.

------------------------------------------------------------

Time Complexity:
----------------

O(2^n)

Each element has two choices (include or exclude).

Skipping duplicates reduces redundant recursive calls
but does not change the worst-case complexity.

------------------------------------------------------------

Space Complexity:
-----------------

Auxiliary Space:

O(n)

due to the recursion stack and the current subset.

Output Space:

O(n × 2^n)

to store all distinct subsets.

*/