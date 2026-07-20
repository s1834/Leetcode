class Solution {
    public:
        vector<vector<int>> fourSum(vector<int>& nums, int target) {
            int n = nums.size();
            set<vector<int>> st;
            sort(nums.begin(), nums.end());
            for(int i = 0; i < n - 3; i++) {
                for(int j = i + 1; j < n - 2; j++) {
                    int left = j + 1, right = n - 1;
                    long long sum = nums[i] + nums[j];
                    while(left < right) {
                        if(sum + nums[left] + nums[right] > target) right--;
                        else if(sum + nums[left] + nums[right] < target) left++;
                        else {
                            st.insert({nums[i], nums[j], nums[left], nums[right]});
                            left++;
                            right--;
                        }
                    }
                }
            }
    
            vector<vector<int>> ans;
            for(auto x : st) ans.push_back(x);
    
            return ans;
        }
    };

/*

Idea:
------
We need to find all unique quadruplets whose sum equals
the given target.

Instead of checking every combination of four elements
(O(n⁴)),

we fix the first two elements and use the Two Pointer
technique to find the remaining two elements.

Since duplicate quadruplets may be generated, we store
the answer in a set, which automatically keeps only
unique combinations.

------------------------------------------------------------

Algorithm:
----------

1.

Sort the array.

Sorting allows the Two Pointer technique to work and
ensures quadruplets are stored in sorted order.

------------------------------------------------------------

2.

Fix the first element

nums[i]

using the outer loop.

------------------------------------------------------------

3.

Fix the second element

nums[j]

using the second loop.

Now, the first two numbers of the quadruplet are fixed.

------------------------------------------------------------

4.

Use two pointers to find the remaining two numbers.

left = j + 1

right = n - 1

Compute

currentSum

=

nums[i] + nums[j] + nums[left] + nums[right]

------------------------------------------------------------

5.

If

currentSum > target,

decrease

right

to reduce the sum.

------------------------------------------------------------

6.

If

currentSum < target,

increase

left

to increase the sum.

------------------------------------------------------------

7.

If

currentSum == target,

a valid quadruplet is found.

Insert

{nums[i], nums[j], nums[left], nums[right]}

into the set.

Move both pointers inward and continue searching.

------------------------------------------------------------

8.

After processing every pair

(i, j),

copy all unique quadruplets from the set into the answer
vector.

------------------------------------------------------------

Why Does Two Pointer Work?
--------------------------

After sorting,

the array is in increasing order.

Suppose

nums[i]

and

nums[j]

are fixed.

Now only

nums[left]

and

nums[right]

need to be chosen.

Since the array is sorted,

• Moving

left

to the right always increases the sum.

• Moving

right

to the left always decreases the sum.

Therefore,

we can efficiently search for the required pair in
linear time instead of checking every possibility.

------------------------------------------------------------

Why Use a Set?
--------------

Different choices of indices may produce the same
quadruplet.

Example:

nums =

[2,2,2,2,2]

target = 8

Many different index combinations produce

[2,2,2,2]

The set stores only one copy, ensuring all returned
quadruplets are unique.

------------------------------------------------------------

Why Use long long?
------------------

The sum of four integers may exceed the range of

int.

Example:

nums =

[1000000000, 1000000000,
 1000000000, 1000000000]

The total is

4000000000,

which overflows a 32-bit integer.

Using

long long

prevents overflow during addition.

------------------------------------------------------------

Example:
--------

nums =

[1,0,-1,0,-2,2]

target = 0

After sorting

[-2,-1,0,0,1,2]

Fix

i = -2

j = -1

Need

3

Using two pointers,

0 + 2 = 2

Too small

Move left.

Next,

1 + 2 = 3

Target found.

Quadruplet

[-2,-1,1,2]

Continue searching.

Similarly,

other valid quadruplets are found.

Final Answer

[-2,-1,1,2]

[-2,0,0,2]

[-1,0,0,1]

------------------------------------------------------------

Time Complexity:
----------------

Sorting:

O(n log n)

Outer loops:

O(n²)

Two Pointer for each pair:

O(n)

Overall:

O(n³ log M)

where

M

is the number of unique quadruplets inserted into the
set.

Ignoring the logarithmic insertion cost,

the dominant complexity is approximately

O(n³).

------------------------------------------------------------

Space Complexity:
-----------------

O(M)

where

M

is the number of unique quadruplets stored in the set.

The answer vector also stores the same quadruplets.

*/