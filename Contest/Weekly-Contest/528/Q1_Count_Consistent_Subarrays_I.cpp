class Solution {
    public:
        int countConsistent(vector<int>& nums) {
            int n = nums.size();
            long long ans = 0;
            for(int i = 0; i < n; i++) {
                int mn = INT_MAX;
                int andVal = -1;
                for(int j = i; j < n; j++) {
                    mn = min(mn, nums[j]);
                    andVal &= nums[j];
                    if(andVal == mn) ans++;
                }
            }
            return ans;
        }
    };

/*
    LeetCode 4111: Count Consistent Subarrays I

    Approach: Brute Force + Running Minimum + Bitwise AND

    Intuition:
    We are given an integer array `nums`.

    A subarray is called consistent if:

        Bitwise AND of all elements == Minimum element of the subarray

    We need to count all non-empty contiguous subarrays satisfying
    this condition.

    Instead of generating every subarray and calculating its minimum
    and bitwise AND separately, we fix a starting index and extend
    the subarray one element at a time.

    While extending the subarray, we maintain:
        - `mn`: Minimum element encountered so far.
        - `andVal`: Bitwise AND of all elements encountered so far.

    Whenever both values become equal, we increment the answer.

    Step-by-Step Explanation:

    1. Initialize the array size and answer:

        int n = nums.size();
        long long ans = 0;

       `n` stores the number of elements.

       `ans` stores the total number of consistent subarrays.

       We use `long long` for the answer to safely accommodate
       the number of subarrays.

    2. Fix the starting index:

        for(int i = 0; i < n; i++)

       The outer loop considers every possible starting position
       of a subarray.

       For each starting index, we explore all subarrays beginning
       at that position.

    3. Initialize the minimum and bitwise AND:

        int mn = INT_MAX;
        int andVal = -1;

       `mn` stores the minimum element in the current subarray.

       We initialize it to INT_MAX so that the first element
       automatically becomes the minimum.

       `andVal` stores the running bitwise AND of the current
       subarray.

       We initialize it to -1 because all bits of -1 are set
       in the usual two's-complement representation.

       Therefore:

           -1 & x = x

       This makes the first AND operation equivalent to simply
       taking the first element.

    4. Extend the subarray:

        for(int j = i; j < n; j++)

       The inner loop extends the current subarray by including
       one element at a time.

       At every iteration, the current subarray is:

           nums[i ... j]

    5. Update the minimum:

        mn = min(mn, nums[j]);

       Update the minimum using the newly included element.

       After this operation, `mn` represents the smallest element
       in the current subarray.

    6. Update the bitwise AND:

        andVal &= nums[j];

       Calculate the bitwise AND of the current subarray.

       Bitwise AND is applied cumulatively:

           andVal = previous AND & nums[j]

       Since AND is associative:

           a & b & c = (a & b) & c

       We do not need to recalculate the AND from the beginning
       whenever the subarray is extended.

    7. Check whether the subarray is consistent:

        if(andVal == mn) ans++;

       A subarray is consistent when its bitwise AND equals
       its minimum element.

       If both values match, increment the answer.

       Every pair of starting and ending indices represents
       a unique subarray, so each valid subarray is counted
       exactly once.

    8. Return the total count:

        return ans;

       After considering every possible starting and ending
       index, return the number of consistent subarrays.

    Example 1:
        nums = [5, 3, 1, 2]

        Start i = 0:

            j = 0:
                Subarray = [5]
                mn = 5
                andVal = -1 & 5 = 5

                5 == 5 -> ans = 1

            j = 1:
                Subarray = [5, 3]
                mn = 3
                andVal = 5 & 3 = 1

                1 != 3 -> ans = 1

            j = 2:
                Subarray = [5, 3, 1]
                mn = 1
                andVal = 1 & 1 = 1

                1 == 1 -> ans = 2

            j = 3:
                Subarray = [5, 3, 1, 2]
                mn = 1
                andVal = 1 & 2 = 0

                0 != 1 -> ans = 2

        Start i = 1:

            j = 1:
                Subarray = [3]
                mn = 3
                andVal = 3

                3 == 3 -> ans = 3

            j = 2:
                Subarray = [3, 1]
                mn = 1
                andVal = 3 & 1 = 1

                1 == 1 -> ans = 4

            j = 3:
                Subarray = [3, 1, 2]
                mn = 1
                andVal = 1 & 2 = 0

                0 != 1 -> ans = 4

        Start i = 2:

            j = 2:
                Subarray = [1]
                mn = 1
                andVal = 1

                1 == 1 -> ans = 5

            j = 3:
                Subarray = [1, 2]
                mn = 1
                andVal = 1 & 2 = 0

                0 != 1 -> ans = 5

        Start i = 3:

            j = 3:
                Subarray = [2]
                mn = 2
                andVal = 2

                2 == 2 -> ans = 6

        Final Answer = 6

    Example 2:
        nums = [1, 1, 1]

        Every possible subarray has:
            Minimum = 1
            Bitwise AND = 1

        Number of non-empty subarrays:

            n * (n + 1) / 2
            = 3 * 4 / 2
            = 6

        Output: 6

    Why This Works:

    1. Every non-empty subarray is considered:
       The outer loop fixes its starting index, and the inner loop
       visits every possible ending index from that starting position.

    2. The minimum is maintained correctly:
       Taking the minimum of the previous minimum and the newly
       included element always gives the minimum of the extended
       subarray.

    3. The bitwise AND is maintained correctly:
       AND-ing the previous result with the newly included element
       gives the AND of the entire extended subarray.

    4. Every consistent subarray is counted exactly once:
       We increment the answer precisely when the current subarray's
       AND equals its minimum.

    Therefore, the algorithm counts all and only consistent subarrays.

    Complexity Analysis:

    Let n be the size of the input array.

    - Time Complexity: O(n^2)

      The outer loop runs n times.

      For each starting index i, the inner loop considers all
      possible ending indices from i to n - 1.

      Total number of subarrays examined:

          n * (n + 1) / 2

      Each iteration performs constant-time minimum, bitwise AND,
      and comparison operations.

      Therefore, the overall time complexity is O(n^2).

    - Space Complexity: O(1)

      We only use a constant number of variables:
          - n
          - ans
          - i
          - j
          - mn
          - andVal

      No additional data structure is required.

    Core Idea:
    Fix the starting index and extend the subarray one element
    at a time.

    Maintain the running minimum and running bitwise AND.
    Whenever both values are equal, increment the answer.

    This checks every possible subarray in O(n^2) time using O(1)
    auxiliary space.
*/