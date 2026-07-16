class Solution {
    private:
        vector<vector<int>> ans;
        vector<int> curr;
    
        void dfs(vector<int>& candidates, int target, int i) {
            if(target == 0) {
                ans.push_back(curr);
                return;
            }
    
            // if i == candidates.size() || sum exceeded target
            if(i == candidates.size() || target < 0) return;
    
            // Include candidates[i]
            curr.push_back(candidates[i]);
            dfs(candidates, target - candidates[i], i + 1);
    
            curr.pop_back();
    
            // Exclude candidates[i]
            while(i + 1 < candidates.size() && candidates[i] == candidates[i + 1]) i++;
            dfs(candidates, target, i + 1);
        }
        
    public:
        vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
            sort(candidates.begin(), candidates.end());
            dfs(candidates, target, 0);
            return ans; 
        }
    };

/*

Idea:
------
Generate all possible combinations using backtracking.

Each candidate can be used at most once.

For every candidate, there are two choices:

1.

Include the current candidate.

Move to the next index since the same element
cannot be reused.

2.

Exclude the current candidate.

Skip all consecutive duplicate values before
moving to the next index to avoid generating
duplicate combinations.

------------------------------------------------------------

Algorithm:
----------

Sort the array first.

Sorting places duplicate values next to each other,
making it easy to skip them.

------------------------------------------------------------

At every index,

make two recursive calls.

------------------------------------------------------------

Choice 1:

Include candidates[i].

Add it to the current combination.

Reduce the remaining target.

Move to the next index.

------------------------------------------------------------

After returning,

remove the last inserted element (backtracking)
to restore the previous state.

------------------------------------------------------------

Choice 2:

Exclude candidates[i].

Before moving to the next index,

skip all consecutive duplicate values.

This ensures that duplicate combinations are not
generated.

------------------------------------------------------------

Base Cases:
-----------

1.

If

target == 0

a valid combination has been found.

Store the current combination.

------------------------------------------------------------

2.

If

i == candidates.size()

or

target < 0

no valid combination can be formed.

Return.

------------------------------------------------------------

Example:
--------

candidates = [1,1,2,5]

target = 3

Recursive Tree

                    {}
               include1 / \ exclude1
                      /       \
                   {1}      skip duplicate 1
                  /             \
          include1              { }
             |                   |
          target=1          include2
             |                   |
       include2              target=1
         target<0              ...

Valid Combination:

[1,2]

Without skipping duplicates,

both 1's would independently generate

[1,2],

resulting in duplicate answers.

The while loop skips the second duplicate in the
exclude branch, preventing this.

------------------------------------------------------------

Backtracking:
-------------

After exploring the include branch,

remove the last inserted element using

curr.pop_back()

This restores the previous state before exploring
the exclude branch.

------------------------------------------------------------

Time Complexity:
----------------

O(2^n)

Each element has two choices (include or exclude).

Duplicate skipping reduces unnecessary recursive
calls but does not change the worst-case complexity.

------------------------------------------------------------

Space Complexity:
-----------------

Auxiliary Space:

O(n)

due to the recursion stack and the current combination.

Output Space:

Depends on the number of valid combinations stored.

*/