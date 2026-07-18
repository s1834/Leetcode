class NumArray {
    private:
        vector<int> prefix;
    
    public:
        NumArray(vector<int>& nums) {
            int n = nums.size();
            prefix.assign(n + 1, 0);
            for(int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + nums[i];
        }
        
        int sumRange(int left, int right) {
            return prefix[right + 1] - prefix[left];
        }
    };
    
    /**
     * Your NumArray object will be instantiated and called as such:
     * NumArray* obj = new NumArray(nums);
     * int param_1 = obj->sumRange(left,right);
     */

/*

Idea:
------
Since multiple range sum queries need to be answered,
calculating the sum by traversing the array every time
would take O(n) per query.

Instead, preprocess the array using a Prefix Sum array.

Each position in the prefix array stores the sum of all
elements from index

0

to

i-1.

Once the prefix array is built, any range sum can be
answered in O(1) time.

------------------------------------------------------------

Prefix Sum:
-----------

prefix[i]

stores the sum of the first

i

elements of the array.

That is,

prefix[0] = 0

prefix[1] = nums[0]

prefix[2] = nums[0] + nums[1]

...

Formula:

prefix[i + 1]

=

prefix[i]

+

nums[i]

------------------------------------------------------------

Why Use an Extra Element?
-------------------------

The prefix array is created with size

n + 1

where

prefix[0] = 0.

This allows every range query to use the same formula,
even when the range starts from index 0.

No special boundary checks are required.

------------------------------------------------------------

Answering Queries:
------------------

Suppose we need the sum from

left

to

right.

Visual Representation

Index

0   1   2   3   4   5

Values

2   4   6   8   10  12

If

left = 2

right = 4

Required Sum

6 + 8 + 10

------------------------------------------------------------

prefix[right + 1]

contains the sum of elements

0

to

right.

prefix[left]

contains the sum of elements

0

to

left - 1.

Subtracting them removes everything before

left,

leaving only the required range.

Formula:

Sum

=

prefix[right + 1]

-

prefix[left]

------------------------------------------------------------

Example:
--------

nums =

[1, 2, 3, 4, 5]

Prefix Array

0  1  3  6  10  15

Query

left = 1

right = 3

Answer

prefix[4] - prefix[1]

=

10 - 1

=

9

which equals

2 + 3 + 4

------------------------------------------------------------

Time Complexity:
----------------

Constructor:

O(n)

The prefix array is built once.

sumRange():

O(1)

Each query requires only two prefix lookups.

------------------------------------------------------------

Space Complexity:
-----------------

O(n)

for storing the prefix sum array.

*/