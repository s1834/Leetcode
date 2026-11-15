class Solution {
    private:
        vector<long long> dp;
        int n;
    
        long long solve(vector<int>& nums, int i) {
            if(i >= n) return 0;
            if(dp[i] != -1) return dp[i];
    
            // take 1
            long long take1;
            if(nums[i] % 3 == 0) take1 = nums[i] - solve(nums, i + 1);
            else take1 = nums[i] + solve(nums, i + 1);
    
            // take 2
            long long take2;
            if(i + 1 < n) {
                long long sum = nums[i] + nums[i + 1];
                if(sum % 3 == 0) take2 = sum - solve(nums, i + 2);
                else take2 = sum + solve(nums, i + 2);
            }
    
            return dp[i] = max(take1, take2);
        }
        
    public:
        long long maxDifference(vector<int>& nums) {
            n = nums.size();
            dp.assign(n, -1);
            return solve(nums, 0);
        }
    };

/*
    LeetCode 4113: Game of Divisible Sums

    Approach: Dynamic Programming (Top-Down DP + Memoization)

    Intuition:
    Alice and Bob play a game where, on each turn, the current player
    can take either:
        1. The leftmost element.
        2. The two leftmost elements, if at least two elements remain.

    The sum of the elements taken determines who plays next:

        - If the sum is divisible by 3, the other player plays next.
        - Otherwise, the current player gets another turn.

    Both players play optimally, trying to maximize their own scores.

    We need to return:

        Alice's score - Bob's score

    Instead of tracking Alice's and Bob's scores separately, we use
    a DP state that represents the maximum score difference the
    current player can achieve over the other player.

    DP State:
        dp[i] = Maximum score difference the current player can achieve
                over the opponent, considering the remaining subarray
                starting at index i.

    The important observation is that after taking some elements,
    the game can be viewed from the perspective of the next player.

    If the current player takes a sum `x`:
        - When x % 3 == 0, the opponent plays next.
          The resulting score difference is x - solve(nextIndex).

        - When x % 3 != 0, the current player plays again.
          The resulting score difference is x + solve(nextIndex).

    This gives us the two possible transitions.

    Step-by-Step Explanation:

    1. Class Variables:

        vector<long long> dp;
        int n;

       `dp[i]` stores the maximum score difference obtainable from
       the remaining array starting at index i.

       `n` stores the size of the input array.

    2. Base Case:

        if(i >= n) return 0;

       If the current index reaches or exceeds n, all elements
       have been taken.

       No elements remain, so the score difference is 0.

    3. Memoization:

        if(dp[i] != -1) return dp[i];

       Before calculating the answer for index i, check whether
       its result has already been computed.

       If it has, return the stored result instead of solving
       the same state again.

    4. Option 1: Take One Element

        long long take1;

       The current player takes only nums[i].

       The score gained in this turn is:

           nums[i]

       Now we check whether this sum is divisible by 3.

       Case 1: Sum is divisible by 3.

            if(nums[i] % 3 == 0)
                take1 = nums[i] - solve(nums, i + 1);

          Since the sum is divisible by 3, the opponent gets
          the next turn.

          The opponent's optimal score difference is represented
          by solve(nums, i + 1).

          From the current player's perspective, the opponent's
          advantage becomes a subtraction.

          Therefore:

              Current advantage = nums[i] - opponent advantage

       Case 2: Sum is not divisible by 3.

            else
                take1 = nums[i] + solve(nums, i + 1);

          The current player gets another turn.

          The future game is still played by the same player,
          so we add the result of the remaining subproblem.

          Therefore:

              Current advantage = nums[i] + future advantage

    5. Option 2: Take Two Elements

        long long take2;

       The current player can also take the first two elements,
       but only if at least two elements remain.

        if(i + 1 < n)

       This ensures that nums[i + 1] is a valid array index.

       Calculate the sum of the two elements:

            long long sum = nums[i] + nums[i + 1];

       Again, the sum determines who plays next.

       Case 1: Sum is divisible by 3.

            if(sum % 3 == 0)
                take2 = sum - solve(nums, i + 2);

          The opponent gets the next turn.

          The remaining subarray starts at index i + 2.

          Therefore, subtract the opponent's optimal score
          difference:

              take2 = sum - solve(nums, i + 2)

       Case 2: Sum is not divisible by 3.

            else
                take2 = sum + solve(nums, i + 2);

          The current player gets another turn.

          Therefore, add the optimal score difference from
          the remaining subarray:

              take2 = sum + solve(nums, i + 2)

    6. Choose the Optimal Move:

        return dp[i] = max(take1, take2);

       Both players play optimally.

       Since the current player wants to maximize their score
       difference over the opponent, we choose the better of
       the two possible moves.

       Store the result in dp[i] for future use.

    7. Main Function:

        n = nums.size();
        dp.assign(n, -1);

       Initialize the DP array with -1, indicating that no state
       has been calculated yet.

        return solve(nums, 0);

       Initially, Alice is the current player and the entire array
       is available.

       Therefore, solve(nums, 0) gives:

           Alice's score - Bob's score

    ------------------------------------------------------------
    Example Walkthrough:
    ------------------------------------------------------------

        nums = [3, 6, 4]

        We start with:
            solve(nums, 0)

        At index 0, Alice has two choices.

        Option 1: Take one element.

            Take 3.

            3 % 3 == 0

            Therefore, Bob gets the next turn.

            take1 = 3 - solve(nums, 1)

        Option 2: Take two elements.

            Take 3 + 6 = 9.

            9 % 3 == 0

            Therefore, Bob gets the next turn.

            take2 = 9 - solve(nums, 2)

        Now calculate the remaining states.

        solve(nums, 2):
            Remaining array = [4]

            Only one element can be taken.

            4 % 3 != 0

            The current player gets another turn, but no elements
            remain.

            solve(nums, 2) = 4 + 0 = 4

        solve(nums, 1):
            Remaining array = [6, 4]

            Option 1: Take 6.

                6 % 3 == 0

                take1 = 6 - solve(nums, 2)
                      = 6 - 4
                      = 2

            Option 2: Take 6 + 4 = 10.

                10 % 3 != 0

                take2 = 10 + solve(nums, 3)
                      = 10 + 0
                      = 10

            Therefore:

                solve(nums, 1) = max(2, 10) = 10

        Return to index 0:

            take1 = 3 - 10 = -7

            take2 = 9 - 4 = 5

        Therefore:

            solve(nums, 0) = max(-7, 5) = 5

        Final Answer: 5

        Optimal sequence:
            Alice takes [3, 6] -> sum = 9, divisible by 3.
            Bob takes [4].

            Alice's score = 9
            Bob's score = 4

            Difference = 9 - 4 = 5

    ------------------------------------------------------------
    Why This DP Works:
    ------------------------------------------------------------

    1. Optimal Substructure:

       After taking one or two elements, the remaining game is
       another instance of the same problem, starting at a later
       index.

       Therefore, we can recursively solve the remaining subarray.

    2. Score Difference:

       We calculate the difference from the perspective of the
       player whose turn it currently is.

       When the opponent gets the next turn, their advantage
       must be subtracted.

       When the current player gets another turn, their future
       advantage is added.

    3. Optimal Choice:

       The current player can choose between taking one element
       or two elements.

       Since they want to maximize their score difference, we
       take the maximum of both possibilities.

    4. Memoization:

       Every state is identified by its starting index i.

       Each state is calculated only once, avoiding repeated
       recursive computations.

    ------------------------------------------------------------
    Complexity Analysis:
    ------------------------------------------------------------

    Let n be the number of elements.

    - Time Complexity: O(n)

      There are n possible DP states (indices 0 through n - 1).

      Each state considers at most two transitions:
          1. Take one element.
          2. Take two elements.

      Since every state is computed only once due to memoization,
      the total time complexity is O(2 * n) = O(n).

    - Space Complexity: O(n)

      The DP array stores n states.

      The recursive call stack can also grow up to O(n) in the
      worst case.

      Overall auxiliary space complexity is O(n).

    Core Idea:
    Use top-down DP where dp[i] represents the maximum score
    difference the current player can achieve from index i.

    For each state, try taking either one or two elements.

    If the taken sum is divisible by 3, the opponent plays next,
    so subtract the remaining score difference.

    Otherwise, the current player plays again, so add the
    remaining score difference.

    Take the maximum of both choices and memoize the result.
*/