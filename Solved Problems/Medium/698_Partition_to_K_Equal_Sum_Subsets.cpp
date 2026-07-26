class Solution {
    private:
        bool dfs(vector<int>& nums, int k, vector<int>& parts, int idx, int target) {
            if(idx == nums.size()) {
                for(int i = 0; i < k; i++) {
                    if(parts[i] != target) return false;
                }
                return true;
            }
    
            for(int i = 0; i < k; i++) {
                if(i > 0 && parts[i] == parts[i - 1]) continue;
    
                if(parts[i] + nums[idx] <= target) {
                    parts[i] += nums[idx];
                    if(dfs(nums, k, parts, idx + 1, target)) return true;
                    parts[i] -= nums[idx];
                }
            }
            return false;
        }
    
    public:
        bool canPartitionKSubsets(vector<int>& nums, int k) {
            long long sum = 0;
            for(auto& x : nums) sum += x;
            if(sum % k) return false;
            sum /= k;
            vector<int> parts(k, 0);
            sort(nums.begin(), nums.end(), greater<int>());
            return dfs(nums, k, parts, 0, sum);
        }
    };

/*

Idea:
------
We are given an array of integers and must divide all
elements into exactly

k

subsets such that

the sum of every subset is identical.

Every number must belong to exactly one subset.

This is an assignment problem where every element has

k

possible choices (which subset to place it into).

Therefore,

the problem is naturally solved using

Backtracking + Depth First Search (DFS).

------------------------------------------------------------

Key Observation:
----------------

Let

Total Sum = Σ nums[i]

If

Total Sum

is not divisible by

k,

then it is impossible to divide the numbers into

k

equal-sum subsets.

Hence,

the first check is

Total Sum % k == 0.

If divisible,

each subset must have sum

Target = Total Sum / k.

Now the problem becomes

"Assign every element into one of the

k

subsets so that every subset finally equals

Target."

------------------------------------------------------------

DFS State:
----------

The recursive function

dfs(idx)

means:

"We have successfully placed the first

idx

numbers.

Can the remaining numbers also be placed so that every
subset eventually reaches the target sum?"

The vector

parts

stores the current sum of every subset.

Example

parts

=

[7,4,6,3]

means

Subset 1 currently has sum 7

Subset 2 currently has sum 4

Subset 3 currently has sum 6

Subset 4 currently has sum 3

------------------------------------------------------------

Recursive Choice:
-----------------

Suppose

Current Number

=

nums[idx]

This number can be placed into any subset

whose current sum does not exceed

Target

after insertion.

For every subset

i

If

parts[i] + nums[idx] <= Target

then

place the number there,

continue recursively,

and later remove it while backtracking if needed.

------------------------------------------------------------

Backtracking:
-------------

Whenever a number is placed,

the subset sum increases.

Example

Current subsets

[5,7,3]

Current number

= 2

Choose subset

3

↓

[5,7,5]

Now recursively solve the remaining numbers.

--------------------------------

If this choice fails,

remove the number.

↓

[5,7,3]

Try another subset.

This

Choose

↓

Explore

↓

Undo

process is exactly Backtracking.

------------------------------------------------------------

Base Case:
----------

When

idx == nums.size()

every number has already been assigned.

Now verify that every subset sum equals

Target.

If all subsets satisfy

parts[i] == Target

then a valid partition exists.

Otherwise,

return

false.

------------------------------------------------------------

Why Sorting Helps:
------------------

Before DFS,

the array is sorted in

descending order.

Largest numbers are placed first.

Example

Original

[1,1,2,5,6]

Sorted

[6,5,2,1,1]

Why?

Suppose

Target = 6.

The first element

6

immediately fills one subset.

If a large number cannot fit anywhere,

the recursion fails immediately,

avoiding exploration of many useless states.

Without sorting,

small numbers may fill subsets first,

causing many unnecessary recursive branches before
eventually discovering failure.

Thus,

placing large numbers first significantly improves
pruning.

------------------------------------------------------------

Optimization:
-------------

Inside the DFS,

the following optimization is used

if(i > 0 && parts[i] == parts[i-1]) continue;

This is one of the most important pruning techniques in
this problem.

------------------------------------------------------------

Why Is This Optimization Correct?
---------------------------------

Suppose

Current subset sums are

[5,5,2,0]

Current number

=

3

Notice that

Subset 1

and

Subset 2

currently have exactly the same sum.

If we place

3

into Subset 1,

the new state becomes

[8,5,2,0]

--------------------------------

Instead,

suppose we place

3

into Subset 2.

The state becomes

[5,8,2,0]

These two states are actually identical.

Why?

Because subsets have

no identity.

The problem never says

"First subset"

or

"Second subset"

must contain specific elements.

Only the collection of subset sums matters.

Interchanging two subsets having equal sums does not
create a different solution.

Therefore,

exploring both branches performs exactly the same search.

------------------------------------------------------------

Example:
--------

Suppose

parts

=

[4,4,0]

Current number

=

2

Choice 1

↓

[6,4,0]

Choice 2

↓

[4,6,0]

These two states are merely permutations of one another.

Every recursive call explored from

Choice 1

will also be explored from

Choice 2.

Hence,

one branch is completely redundant.

The optimization skips it.

------------------------------------------------------------

Mathematical Explanation:
-------------------------

Suppose

parts[i]

=

parts[j]

before placing the current number.

After inserting

x,

the two possible states become

State A

(..., parts[i]+x, ..., parts[j], ...)

State B

(..., parts[i], ..., parts[j]+x, ...)

Since

parts[i]

=

parts[j],

State A and State B differ only by swapping the labels of
two subsets.

Because subset labels have no meaning,

both states are equivalent.

Therefore,

exploring only one of them is sufficient.

------------------------------------------------------------

What Does This Optimization Save?
---------------------------------

Without this optimization,

many identical recursive trees are explored repeatedly.

Suppose

k = 4

Initially

parts

=

[0,0,0,0]

Current number

=

5

Without pruning,

the algorithm tries

Put into subset 1

Put into subset 2

Put into subset 3

Put into subset 4

All four produce equivalent states

[5,0,0,0]

[0,5,0,0]

[0,0,5,0]

[0,0,0,5]

These are identical except for subset numbering.

The optimization keeps only the first branch,

reducing four recursive calls to one.

As recursion progresses,

this eliminates an enormous number of duplicate states.

------------------------------------------------------------

Algorithm:
----------

Step 1

Compute the total sum.

------------------------------------------------------------

Step 2

If the total is not divisible by

k,

return

false.

------------------------------------------------------------

Step 3

Compute

Target = Total / k.

------------------------------------------------------------

Step 4

Sort the numbers in descending order.

------------------------------------------------------------

Step 5

Maintain

parts[i]

representing the current sum of every subset.

------------------------------------------------------------

Step 6

For every number,

try placing it into each subset.

Skip subsets whose sum would exceed

Target.

Also skip subsets having the same current sum as the
previous subset because they lead to identical states.

------------------------------------------------------------

Step 7

Recursively assign the next number.

------------------------------------------------------------

Step 8

Undo the placement while backtracking.

------------------------------------------------------------

Step 9

If every number is assigned and every subset equals the
target,

return

true.

Otherwise,

return

false.

------------------------------------------------------------

Example:
--------

nums

=

[4,3,2,3,5,2,1]

k

=

4

Total

=

20

Target

=

5

Sorted

↓

[5,4,3,3,2,2,1]

--------------------------------

Place

5

↓

Subsets

[5,0,0,0]

--------------------------------

Place

4

↓

[5,4,0,0]

--------------------------------

Place

3

↓

[5,4,3,0]

--------------------------------

Place

3

↓

Cannot go into subset 1

Cannot go into subset 2

Can go into subset 4

↓

[5,4,3,3]

Continue similarly until

[5,5,5,5]

Return

true.

------------------------------------------------------------

Why Does This Work?
-------------------

Every recursive call assigns exactly one number to one
subset.

A number is placed only if it does not cause the subset
sum to exceed the required target.

Thus,

every intermediate state is always valid.

Backtracking guarantees that if one placement fails,

all remaining feasible placements are explored.

The symmetry optimization removes only duplicate states
that differ merely by renaming subsets,

so no valid solution is lost.

Therefore,

the algorithm explores every unique assignment exactly
once and returns

true

iff

the array can indeed be partitioned into

k

equal-sum subsets.

------------------------------------------------------------

Time Complexity:
----------------

Let

n

be the number of elements.

Without pruning,

each element has at most

k

possible subsets.

Worst-case complexity

O(k^n)

Sorting costs

O(n log n)

which is negligible compared to the exponential search.

The symmetry pruning and descending sort dramatically
reduce the practical running time, although the
worst-case asymptotic complexity remains exponential.

------------------------------------------------------------

Space Complexity:
-----------------

The recursion depth is

n.

The vector

parts

stores

k

subset sums.

Auxiliary Space

O(n + k)

excluding the recursion output.

*/