class Solution {
    private:
        vector<vector<int>> ans;
        vector<int> curr;
    
        void dfs(int n, int k, int i) {
            if(!k) {
                ans.push_back(curr);
                return;
            }
    
            if(i > n) return;
    
            curr.push_back(i);
            dfs(n, k - 1, i + 1);
            curr.pop_back();
    
            dfs(n, k, i + 1);
        }
    
    public:
        vector<vector<int>> combine(int n, int k) {
            dfs(n, k, 1);
            return ans;
        }
    };

/*

Idea:
------
Generate all possible combinations using backtracking.

For every number from 1 to n, there are two choices:

1.

Include the current number in the combination.

2.

Exclude the current number and move to the next one.

A combination is complete once exactly k numbers have
been selected.

------------------------------------------------------------

Algorithm:
----------

Start from the number 1.

At every number,

make two recursive calls.

------------------------------------------------------------

Choice 1:

Include the current number.

Add it to the current combination.

Since one number has been selected,

decrease k by 1.

Move to the next number.

------------------------------------------------------------

After returning,

remove the last inserted number (backtracking)
to restore the previous state.

------------------------------------------------------------

Choice 2:

Exclude the current number.

Do not modify the current combination.

Move to the next number while keeping k unchanged.

------------------------------------------------------------

Base Cases:
-----------

1.

If

k == 0

exactly the required number of elements have been
selected.

Store the current combination.

------------------------------------------------------------

2.

If

i > n

all numbers have been considered but a valid
combination was not formed.

Return.

------------------------------------------------------------

Example:
--------

n = 4

k = 2

Recursive Tree

                    {}
                 include1 / \ exclude1
                        /       \
                     {1}         {}
                    /   \       /   \
               +2 {1,2}  {1}  {2}   {}
                  /         ...
             Store {1,2}

Continuing the recursion generates

{1,3}

{1,4}

{2,3}

{2,4}

{3,4}

------------------------------------------------------------

Backtracking:
-------------

After exploring the "include" branch,

remove the last inserted number using

curr.pop_back()

This restores the combination before exploring
the "exclude" branch.

------------------------------------------------------------

Time Complexity:
----------------

O(2^n)

Each number has two choices (include or exclude).

Only combinations of size k are stored.

------------------------------------------------------------

Space Complexity:
-----------------

Auxiliary Space:

O(n)

due to the recursion stack and the current combination.

Output Space:

O(C(n, k) × k)

to store all valid combinations.

*/