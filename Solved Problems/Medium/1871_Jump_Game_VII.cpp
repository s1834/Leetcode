class Solution {
    public:
        bool canReach(string s, int minJump, int maxJump) {
            int n = s.size();
            
            // dp[i] > 0 : possible to reach i
            // dp[i] == 0 : not possilbe to reach i
            vector<int> dp(n, 0);
    
            dp[0] = 1;
            int count = 0;
    
            for(int j = 1; j <= n - 1; j++) {
                if(j - minJump >= 0) count += dp[j - minJump];
    
                if(j - maxJump - 1 >= 0) count -= dp[j - maxJump - 1];
    
                if(count > 0 && s[j] == '0') dp[j] = 1;
            }
    
            return dp[n - 1] > 0;
        }
    };

/*
Problem: LeetCode 1871 - Jump Game VII

Approach: Dynamic Programming + Sliding Window Optimization

Intuition:
----------
We need to determine whether we can reach the last index of
the string starting from index 0.

We can jump from index i to index j if:
- minJump <= j - i <= maxJump
- s[j] == '0'

We cannot land on positions containing '1'.

A direct DP solution would check all possible previous positions
for every index, resulting in O(n * maxJump) time.

Instead, this solution uses a sliding window to efficiently
determine whether at least one reachable position exists
within the valid jump range.

--------------------------------------------------
1. Initialize the DP Array
--------------------------------------------------

int n = s.size();

vector<int> dp(n, 0);

dp[i] indicates whether index i is reachable from index 0.

- dp[i] = 1: Index i is reachable.
- dp[i] = 0: Index i is not reachable.

Initially, every position is unreachable.

dp[0] = 1;

We can always start at index 0, so mark it reachable.

--------------------------------------------------
2. Initialize the Sliding Window Counter
--------------------------------------------------

int count = 0;

count represents the number of reachable positions within
the valid range of previous indices from which the current
position can be reached.

For a current index j, the valid previous indices are:

    [j - maxJump, j - minJump]

If count > 0, at least one reachable position exists in
this range.

--------------------------------------------------
3. Traverse the String
--------------------------------------------------

for(int j = 1; j <= n - 1; j++)

We start from index 1 because index 0 is already reachable.

For every position j, we update the sliding window to
represent exactly the indices from which we can jump to j.

--------------------------------------------------
4. Add the Newly Eligible Position
--------------------------------------------------

if(j - minJump >= 0)
    count += dp[j - minJump];

The index:

    j - minJump

is the newest position that becomes eligible to reach j.

If this position is reachable, add 1 to count.

This ensures that count includes all reachable positions
up to the upper boundary of the valid previous-index range.

--------------------------------------------------
5. Remove the Position That Is No Longer Eligible
--------------------------------------------------

if(j - maxJump - 1 >= 0)
    count -= dp[j - maxJump - 1];

The index:

    j - maxJump - 1

is now outside the valid jump range.

It is too far behind the current index j to reach it.

Therefore, remove its contribution from count.

After these two updates, count represents:

    Sum of dp[i] for all i in [j - maxJump, j - minJump]

Only valid indices are included.

--------------------------------------------------
6. Determine Whether the Current Index Is Reachable
--------------------------------------------------

if(count > 0 && s[j] == '0')
    dp[j] = 1;

Two conditions must be satisfied:

1. count > 0

   At least one reachable previous index exists within
   the allowed jump distance.

2. s[j] == '0'

   We can only land on positions containing '0'.

If both conditions hold, mark the current index as reachable.

Otherwise, dp[j] remains 0.

--------------------------------------------------
7. Return the Final Result
--------------------------------------------------

return dp[n - 1] > 0;

After processing all positions, check whether the last
index is reachable.

If dp[n - 1] is 1, return true.

Otherwise, return false.

--------------------------------------------------
8. Example Walkthrough
--------------------------------------------------

Input:

    s = "011010"
    minJump = 2
    maxJump = 3

Initially:

    dp = [1, 0, 0, 0, 0, 0]
    count = 0

j = 1:

    j - minJump = -1
    No position is added.

    j - maxJump - 1 = -3
    No position is removed.

    s[1] = '1'

    dp[1] = 0

j = 2:

    Add dp[0] = 1

    count = 1

    s[2] = '1'

    dp[2] = 0

j = 3:

    Add dp[1] = 0

    count = 1

    s[3] = '0'

    count > 0, so dp[3] = 1.

j = 4:

    Add dp[2] = 0

    Remove dp[0] = 1

    count = 0

    s[4] = '1'

    dp[4] = 0

j = 5:

    Add dp[3] = 1

    Remove dp[1] = 0

    count = 1

    s[5] = '0'

    dp[5] = 1

Final DP array:

    [1, 0, 0, 1, 0, 1]

Since dp[5] = 1, return true.

--------------------------------------------------
9. Why Does the Sliding Window Work?
--------------------------------------------------

For every index j, we only need to know whether at least
one reachable index exists in the range:

    [j - maxJump, j - minJump]

Checking this entire range for every j would be inefficient.

Instead, we maintain its sum using count.

As j increases by one:
- One new index enters the valid range.
- One old index leaves the valid range.

Therefore, we only need one addition and one subtraction
per iteration.

If count > 0, there is at least one valid previous position
from which we can reach the current index.

Combined with the condition s[j] == '0', this correctly
determines whether j is reachable.

--------------------------------------------------
10. Complexity Analysis
--------------------------------------------------

Time Complexity: O(n)

We traverse the string once.

Each iteration performs:
- At most one addition.
- At most one subtraction.
- A constant number of comparisons.

Space Complexity: O(n)

The DP vector stores one state for every index.

Core Idea:
----------
Use DP to track reachable positions and maintain a sliding
window sum of reachable positions within the valid jump range.

For every index j:

    Valid Previous Range = [j - maxJump, j - minJump]

If this range contains at least one reachable index and
s[j] == '0', mark dp[j] as reachable.

This optimizes the straightforward DP solution from
O(n * maxJump) to O(n) time.
*/