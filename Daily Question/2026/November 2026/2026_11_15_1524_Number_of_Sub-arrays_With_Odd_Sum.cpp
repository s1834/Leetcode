class Solution {
    private:
        int MOD = 1e9 + 7;
    
    public:
        int numOfSubarrays(vector<int>& arr) {
            int n = arr.size();
            vector<int> prefix(n, 0);
            prefix[0] = arr[0];
            for(int i = 1; i < n; i++) prefix[i] = prefix[i - 1] + arr[i];
    
            int count = 0;
            int odd = 0;
            int even = 1;
            for(int i = 0; i < n; i++) {
                if(prefix[i] % 2 == 0) { // odd + even = odd
                    count = (count + odd) % MOD;
                    even++;
                } else { // even + odd = odd
                    count = (count + even) % MOD;
                    odd++;
                }
            }
    
            return count;
        }
    };

/*
    LeetCode 1524: Number of Sub-arrays With Odd Sum

    Approach: Prefix Sum + Parity Counting

    Intuition:
    We need to count the number of contiguous subarrays whose sum is odd.

    Instead of calculating the sum of every possible subarray, we use
    prefix sums and track how many previous prefix sums are odd or even.

    The key observation is:

    - Even + Even = Even
    - Odd + Odd = Even
    - Even + Odd = Odd

    If prefix[j] is the sum from index 0 to j, then the sum of a
    subarray from index i to j is:

        prefix[j] - prefix[i - 1]

    This difference is odd only when the two prefix sums have
    different parities.

    Therefore:
    - If the current prefix sum is even, we need a previous odd prefix.
    - If the current prefix sum is odd, we need a previous even prefix.

    Variables:
    - MOD: Modulo value (10^9 + 7) to prevent the answer from growing
           too large.
    - prefix: Stores the cumulative sum of elements from index 0 to i.
    - count: Number of subarrays with an odd sum found so far.
    - odd: Number of previous prefix sums having odd parity.
    - even: Number of previous prefix sums having even parity.

    Step-by-Step Explanation:

    1. Build the prefix sum array:
       - prefix[0] = arr[0].
       - For every other index:
             prefix[i] = prefix[i - 1] + arr[i].

       This allows us to determine the parity of every prefix sum.

    2. Initialize the parity counters:
       - odd = 0
       - even = 1

       Why is even initialized to 1?

       We consider an imaginary prefix sum before the array starts,
       equal to 0.

       Since 0 is even, this represents the empty prefix. It allows
       us to count subarrays starting from index 0.

    3. Traverse the prefix sum array:

       Case 1: Current prefix sum is even.

       An odd subarray can be formed by subtracting a previous odd
       prefix sum from the current even prefix sum.

       Therefore:
           count += odd

       Then increment `even`, because the current prefix sum is
       another even prefix sum that future elements can use.

       Case 2: Current prefix sum is odd.

       An odd subarray can be formed by subtracting a previous even
       prefix sum from the current odd prefix sum.

       Therefore:
           count += even

       Then increment `odd`, because the current prefix sum is
       another odd prefix sum.

    4. Apply modulo MOD while updating the answer to keep it within
       the required range.

    5. Return count.

    Example Walkthrough:

    arr = [1, 3, 5]

    Prefix sums:
        prefix = [1, 4, 9]

    Initially:
        odd = 0
        even = 1
        count = 0

    i = 0:
        prefix[0] = 1 (odd)

        We need a previous even prefix.
        count += even = 1

        odd = 1
        count = 1

        Subarray: [1]

    i = 1:
        prefix[1] = 4 (even)

        We need a previous odd prefix.
        count += odd = 1

        even = 2
        count = 2

        Subarray: [3]

    i = 2:
        prefix[2] = 9 (odd)

        We need a previous even prefix.
        count += even = 2

        odd = 2
        count = 4

        Subarrays added:
        [1, 3, 5]
        [5]

    Final answer = 4

    The odd-sum subarrays are:
        [1]
        [3]
        [5]
        [1, 3, 5]

    Why It Works:
    Every subarray sum can be represented as the difference between
    two prefix sums.

    That difference is odd precisely when the prefix sums have
    different parities.

    By maintaining the number of previous odd and even prefix sums,
    we count every valid subarray exactly once, when its right
    endpoint is processed.

    Complexity Analysis:
    - Time Complexity: O(n)
      Building the prefix array takes O(n), and traversing it takes
      another O(n).

    - Space Complexity: O(n)
      The prefix sum array stores n cumulative sums.

    Core Idea:
    A subarray has an odd sum if its two boundary prefix sums have
    different parities. Count previous odd/even prefix sums to
    calculate the answer in linear time.
*/