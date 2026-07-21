class Solution {
    private:
        bool split(vector<int>& nums, int largest, int k) {
            int parts = 1, sum = 0;
            for(auto x : nums) {
                sum += x;
                if(sum > largest) {
                    parts++;
                    sum = x;
                }
            }
            return parts <= k;
        }
    
    public:
        int splitArray(vector<int>& nums, int k) {
            int n = nums.size(), left = INT_MIN, right = 0;
            for(int i = 0; i < n; i++){
                left = max(left, nums[i]);
                right += nums[i];
            } 
            int ans = right;
            while(left <= right) {
                int mid = left + (right - left) / 2;
                if(split(nums, mid, k)) {
                    ans = mid;
                    right = mid - 1;
                } else left = mid + 1;
            }
    
            return ans;
        }
    };

/*

Idea:
------
We need to split the array into exactly

k

non-empty subarrays such that the

largest subarray sum

is as small as possible.

Instead of trying every possible way to split the array,
we binary search on the answer.

The answer is the minimum possible value of the largest
subarray sum.

------------------------------------------------------------

Why Binary Search?
------------------

Suppose we guess that the maximum allowed subarray sum is

X.

Now the question becomes:

"Can we split the array into at most

k

parts such that every part has sum ≤ X?"

If the answer is YES,

then any value greater than

X

will also work because increasing the allowed maximum
sum only makes splitting easier.

If the answer is NO,

then every value smaller than

X

will also fail because decreasing the allowed maximum
sum makes the constraint even stricter.

Therefore,

the answer space is monotonic.

This monotonic property allows Binary Search.

------------------------------------------------------------

Search Space:
-------------

Lowest possible answer

=

max(nums)

No subarray can have sum smaller than the largest
individual element.

Example

[7,2,5]

Largest element = 7

Answer can never be less than 7.

--------------------------------

Highest possible answer

=

sum(nums)

Putting the entire array into one subarray.

Example

[7,2,5]

Largest sum = 14

Therefore,

Binary Search is performed on

[max(nums), sum(nums)]

------------------------------------------------------------

Checking a Candidate (split function):
--------------------------------------

Suppose we assume

largest = X.

Traverse the array from left to right.

Maintain the sum of the current subarray.

--------------------------------

For every element,

add it to the current sum.

If

sum ≤ X

continue extending the current subarray.

--------------------------------

If

sum > X

the current element cannot belong to this subarray.

Therefore,

start a new subarray.

Increment

parts

and begin the new subarray with the current element.

------------------------------------------------------------

Why is this Greedy Strategy Correct?
-----------------------------------

Whenever adding the next element exceeds

X,

we are forced to split.

Splitting earlier would only create more subarrays
without reducing the maximum sum.

Therefore,

the greedy strategy always creates the

minimum possible number of subarrays

for the chosen limit

X.

If even this minimum number of subarrays is greater than

k,

then it is impossible to satisfy the constraint with
maximum sum

X.

------------------------------------------------------------

Mathematical Explanation:
-------------------------

Let

F(X)

be the minimum number of subarrays required when every
subarray must have sum ≤ X.

Then

If

X₁ < X₂

⇒

F(X₁) ≥ F(X₂)

because allowing a larger maximum sum lets us merge some
subarrays together.

Thus,

F(X)

is a monotonically non-increasing function.

We need to find the smallest

X

such that

F(X) ≤ k.

This is exactly what Binary Search finds.

------------------------------------------------------------

Example:
--------

nums =

[7,2,5,10,8]

k = 2

Search Space

left = 10

right = 32

--------------------------------

mid = 21

Split using limit = 21

[7,2,5]

Sum = 14

Add 10

Sum = 24

Too large.

Create new subarray.

[10,8]

Sum = 18

Total Parts = 2

Valid.

Try smaller answer.

--------------------------------

mid = 15

Split

[7,2,5]

Sum = 14

Next element

10

Need new subarray.

[10]

Next element

8

Need another subarray.

[8]

Total Parts = 3

Too many.

Need a larger maximum sum.

--------------------------------

Eventually,

Binary Search converges to

18.

Optimal split

[7,2,5]

Sum = 14

[10,8]

Sum = 18

Largest subarray sum = 18

------------------------------------------------------------

Why Do We Check

parts <= k

Instead of

parts == k ?
--------------------------------

The greedy algorithm computes the

minimum

number of subarrays needed for the chosen maximum sum.

If we can split into fewer than

k

parts,

we can always split any existing subarray further
(because every element is positive) without increasing
the largest subarray sum.

Therefore,

forming fewer than

k

parts is still acceptable.

Hence,

the condition is

parts ≤ k.

------------------------------------------------------------

Time Complexity:
----------------

Let

S = sum(nums)

Binary Search Range

[max(nums), S]

Binary Search performs

O(log(S))

iterations.

Each iteration scans the array once.

Total Complexity:

O(n log(S))

------------------------------------------------------------

Space Complexity:
-----------------

O(1)

Only a few variables are used.

*/