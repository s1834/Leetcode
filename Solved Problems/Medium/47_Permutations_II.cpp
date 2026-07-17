class Solution {
    private:
        vector<vector<int>> ans;
    
        void solve(vector<int>& nums, int i) {
            if(i == nums.size()) {
                ans.push_back(nums);
                return;
            }
            
            unordered_set<int> st;
    
            for(int j = i; j < nums.size(); j++) {
                if(st.find(nums[j]) != st.end()) continue;
                st.insert(nums[j]);
                swap(nums[i], nums[j]);
                solve(nums, i + 1);
                swap(nums[i], nums[j]);
            }
        }
    
    public:
        vector<vector<int>> permuteUnique(vector<int>& nums) {
            solve(nums, 0);
            return ans;  
        }
    };

/*

Idea:
------
Generate all unique permutations using backtracking.

At every position i, choose one of the remaining
elements to place at that position.

Since duplicate values may exist, multiple indices can
contain the same value.

Trying all of them would generate identical
permutations.

To avoid this, maintain a hash set at every recursion
level.

The set stores the values that have already been placed
at the current position.

If the same value appears again at this level, skip it.

------------------------------------------------------------

Algorithm:
----------

Start from index 0.

For every position i,

try placing every remaining element from index i to
the end.

------------------------------------------------------------

For every j in [i, n-1]:

1.

Check whether nums[j] has already been used for the
current position.

If yes,

skip this iteration.

------------------------------------------------------------

2.

Otherwise,

insert nums[j] into the hash set.

This ensures that the same value is never chosen twice
for the current position.

------------------------------------------------------------

3.

Swap nums[i] and nums[j].

This fixes nums[j] at position i.

------------------------------------------------------------

4.

Recursively generate permutations for the remaining
positions starting from i + 1.

------------------------------------------------------------

5.

Swap the elements back.

This restores the original array before trying the
next candidate.

------------------------------------------------------------

Base Case:
----------

When

i == nums.size()

all positions have been fixed.

The current arrangement is one unique permutation.

Store it in the answer.

------------------------------------------------------------

Example:
--------

nums = [1,1,2]

Position 0

Remaining Elements

1 1 2

Hash Set = {}

------------------------------------------------------------

j = 0

Value = 1

Not present in the set.

Insert 1.

Swap.

Generate all permutations beginning with

1 _ _

------------------------------------------------------------

Backtrack.

j = 1

Value = 1

Already present in the set.

Skip.

This avoids generating duplicate permutations that
would also begin with

1 _ _

------------------------------------------------------------

j = 2

Value = 2

Not present.

Insert 2.

Swap.

Generate all permutations beginning with

2 _ _

------------------------------------------------------------

Final Answer

[1,1,2]

[1,2,1]

[2,1,1]

------------------------------------------------------------

Why the Hash Set Works:
-----------------------

The hash set is recreated for every recursive call.

Therefore,

it only tracks which values have already been used for
the current position.

Duplicate values appearing later in the array are
ignored for the current level, preventing duplicate
permutations.

At deeper recursion levels, a new hash set is created,
allowing the same value to be used again at different
positions.

------------------------------------------------------------

Backtracking:
-------------

After exploring all permutations for one choice,

swap the elements back using

swap(nums[i], nums[j]);

This restores the array before trying the next
candidate.

Without this step, future recursive calls would work on
an incorrect array.

------------------------------------------------------------

Time Complexity:
----------------

Worst Case (all elements distinct):

O(n × n!)

There are n! permutations, and copying each
permutation into the answer takes O(n).

When duplicate values exist, fewer unique permutations
are generated, so the actual running time is smaller.

------------------------------------------------------------

Space Complexity:
-----------------

Auxiliary Space:

O(n)

due to the recursion stack.

Each recursion level also maintains an unordered_set
whose maximum size is at most n.

Output Space:

O(U × n)

where U is the number of unique permutations.

*/ 