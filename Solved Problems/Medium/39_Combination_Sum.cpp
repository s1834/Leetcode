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
            dfs(candidates, target - candidates[i], i);
    
            curr.pop_back();
    
            // Exclude candidates[i]
            dfs(candidates, target, i + 1);
        }
        
    public:
        vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
            dfs(candidates, target, 0);
            return ans;
        }
    };

/*

Idea:
------
Generate all possible combinations using backtracking.

For every candidate, there are two choices:

1.

Include the current candidate.

Since a candidate can be chosen unlimited times,
continue recursion with the same index.

2.

Exclude the current candidate.

Move to the next candidate.

Whenever the remaining target becomes 0,
the current combination is valid.

------------------------------------------------------------

Algorithm:
----------

At every index,

make two recursive calls.

------------------------------------------------------------

Choice 1:

Include candidates[i].

Add it to the current combination.

Reduce the remaining target by its value.

Since the same element can be reused,

continue recursion with the same index.

------------------------------------------------------------

After returning,

remove the last inserted element (backtracking)
to restore the previous state.

------------------------------------------------------------

Choice 2:

Exclude candidates[i].

Move to the next candidate.

------------------------------------------------------------

Base Cases:
-----------

1.

If

target == 0

a valid combination has been found.

Store it in the answer.

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

candidates = [2,3,6,7]

target = 7

Recursive Tree

                    target = 7
                   /          \
             include 2      exclude 2
              target=5        target=7
             /      \
      include2    exclude2
      target=3     target=5
       /    \
 include2  exclude2
 target=1   target=3
    |          |
 target<0   include3
              |
          target=0

Combination Found:

[2,2,3]

Another valid path:

exclude 2

exclude 3

exclude 6

include 7

target = 0

Combination Found:

[7]

------------------------------------------------------------

Backtracking:
-------------

After exploring the "include" branch,

remove the last inserted element using

curr.pop_back()

This restores the combination before exploring the
"exclude" branch.

------------------------------------------------------------

Time Complexity:
----------------

O(2^T)

where T depends on the target and candidate values.

The exact number of recursive calls depends on how many
valid combinations can be formed.

------------------------------------------------------------

Space Complexity:
-----------------

Auxiliary Space:

O(target / minCandidate)

due to the recursion stack and the current combination.

Output Space:

Depends on the number of valid combinations stored.

*/