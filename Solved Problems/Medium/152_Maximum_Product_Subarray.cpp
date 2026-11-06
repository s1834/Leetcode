class Solution {
    private:
        int n;
        int result = INT_MIN;
        vector<int> dp;
    
        int solve(vector<int>& nums, int i) {
            if(i == n) return 0;
            if(dp[i] != -1) return dp[i];
            int mul = 1;
            int mx = INT_MIN;
            for(int j = i; j < n; j++) {
                mul *= nums[j];
                mx = max(mx, mul);
            }
    
            dp[i] = result = max(result, mx);
    
            return solve(nums, i + 1);
        }
    
    public:
        int maxProduct(vector<int>& nums) {
            n = nums.size();
            dp.assign(n, -1);
            solve(nums, 0);
            return result;
        }
    };

/*
Problem: LeetCode 152 - Maximum Product Subarray

Approach: Recursion + Memoization + Subarray Enumeration

Intuition:
----------
We need to find the maximum product of any non-empty
contiguous subarray.

The solution uses recursion to consider every possible
starting index of a subarray.

For each starting index i:
- Extend the subarray towards the right.
- Maintain the product of the current subarray.
- Track the maximum product among all subarrays starting
  at i.
- Update the global maximum answer.

The recursion then moves to the next starting index.

--------------------------------------------------
1. Class-Level Variables
--------------------------------------------------

int n;
int result = INT_MIN;
vector<int> dp;

- n stores the size of the input array.
- result stores the maximum product found across all
  possible contiguous subarrays.
- dp[i] stores the maximum product of a subarray starting
  at index i.

The dp array is initialized with -1 to indicate that
an index has not been processed yet.

--------------------------------------------------
2. Recursive Function: solve()
--------------------------------------------------

int solve(vector<int>& nums, int i)

This function processes subarrays starting from index i
and recursively moves towards the end of the array.

--------------------------------------------------
3. Base Case
--------------------------------------------------

if(i == n) return 0;

When i reaches n, there are no more elements to process.

Return 0 to terminate the recursion.

--------------------------------------------------
4. Check Memoization
--------------------------------------------------

if(dp[i] != -1) return dp[i];

If dp[i] is already calculated, return the stored value
instead of processing the same starting index again.

This avoids repeating the subarray enumeration for
an already processed index.

--------------------------------------------------
5. Initialize Variables for Subarray Enumeration
--------------------------------------------------

int mul = 1;
int mx = INT_MIN;

- mul maintains the product of the current subarray.
- mx stores the maximum product among all subarrays
  starting at index i.

--------------------------------------------------
6. Enumerate Every Subarray Starting at Index i
--------------------------------------------------

for(int j = i; j < n; j++) {

    mul *= nums[j];

    mx = max(mx, mul);

}

The inner loop extends the subarray one element at a time.

For every j:

    Subarray = nums[i ... j]

First, multiply the current product by nums[j]:

    mul *= nums[j];

Then update the maximum product:

    mx = max(mx, mul);

This considers all possible contiguous subarrays
starting at index i.

For example:

    nums = [2, 3, -2, 4]

For i = 0:

    j = 0:
        Subarray = [2]
        mul = 2
        mx = 2

    j = 1:
        Subarray = [2, 3]
        mul = 6
        mx = 6

    j = 2:
        Subarray = [2, 3, -2]
        mul = -12
        mx = 6

    j = 3:
        Subarray = [2, 3, -2, 4]
        mul = -48
        mx = 6

Therefore, the maximum product starting at index 0 is 6.

--------------------------------------------------
7. Update DP and Global Answer
--------------------------------------------------

dp[i] = result = max(result, mx);

This statement performs two updates:

1. dp[i] = mx

   Stores the maximum product among all subarrays
   starting at index i.

2. result = max(result, mx)

   Updates the global maximum product found across
   all starting positions processed so far.

--------------------------------------------------
8. Move to the Next Starting Index
--------------------------------------------------

return solve(nums, i + 1);

After processing every subarray starting at index i,
recursively process the next starting index.

This ensures that every possible starting position
is considered.

Eventually, all contiguous subarrays are evaluated.

--------------------------------------------------
9. Main Function
--------------------------------------------------

int maxProduct(vector<int>& nums) {

    n = nums.size();

    dp.assign(n, -1);

    solve(nums, 0);

    return result;
}

Steps:

1. Store the array size in n.
2. Initialize dp with -1 for all indices.
3. Start recursion from index 0.
4. Return the global maximum product.

--------------------------------------------------
10. Example Walkthrough
--------------------------------------------------

Input:

    nums = [2, 3, -2, 4]

Subarrays and their products:

Starting at index 0:
    [2]             -> 2
    [2, 3]          -> 6
    [2, 3, -2]      -> -12
    [2, 3, -2, 4]   -> -48

Maximum = 6

Starting at index 1:
    [3]             -> 3
    [3, -2]         -> -6
    [3, -2, 4]      -> -24

Maximum = 3

Starting at index 2:
    [-2]            -> -2
    [-2, 4]         -> -8

Maximum = -2

Starting at index 3:
    [4]             -> 4

Maximum = 4

Global maximum:

    result = max(6, 3, -2, 4)
           = 6

Output:

    6

--------------------------------------------------
11. Complexity Analysis
--------------------------------------------------

Time Complexity: O(n²)

- The recursive function processes n starting indices.
- For every starting index i, the inner loop can
  traverse the remaining elements.
- Memoization prevents repeated processing of the
  same starting index, but each index still enumerates
  all subarrays starting there.

Total work:

    n + (n - 1) + (n - 2) + ... + 1

    = O(n²)

Space Complexity: O(n)

- dp requires O(n) space.
- Recursive call stack requires O(n) space.

Core Idea:
----------
Enumerate every contiguous subarray by fixing its starting
index and extending its ending index.

Maintain the running product and update the maximum
product found.

The global result stores the maximum across all starting
positions.

Note:
----
This implementation uses int for multiplication, so it can
overflow for sufficiently large intermediate products.

Also, using -1 as the uncomputed marker is ambiguous because
-1 can itself be a valid maximum subarray product. In this
particular implementation, solve() is called only once per
index through the recursion, so the memoization check does
not provide a meaningful optimization.
*/