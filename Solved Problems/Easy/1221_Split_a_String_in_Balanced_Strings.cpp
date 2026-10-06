class Solution {
    public:
        int balancedStringSplit(string s) {
            int ans = 0, balance = 0;
            for(auto& x : s) {
                if(x == 'R') balance++;
                else balance--;
    
                if(balance == 0) ans++;
            }
            return ans;
        }
    };

/*
    ============================================================
    LeetCode 1221 - Split a String in Balanced Strings
    ============================================================

    Approach: Greedy + Balance Counter
    ------------------------------------------------------------

    A balanced string contains the same number of 'L' and 'R'
    characters.

    We need to split the given string into the maximum number
    of balanced substrings.

    We maintain:

        balance -> difference between the number of 'R' and 'L'
        ans     -> number of balanced substrings found

    ============================================================
    1. Maintain the Balance
    ============================================================

    For every character:

        'R' -> balance++
        'L' -> balance--

    Therefore:

        balance =
            (# of R seen so far) - (# of L seen so far)

    Example:

        s = "RLRRLL"

        R -> balance = 1
        L -> balance = 0
        R -> balance = 1
        R -> balance = 2
        L -> balance = 1
        L -> balance = 0

    ============================================================
    2. When Do We Get a Balanced Substring?
    ============================================================

    A substring is balanced when it contains the same number
    of 'R' and 'L'.

    That means:

        balance = 0

    Whenever the balance becomes zero, the characters since
    the previous balance of zero form a balanced substring.

    Therefore:

        if(balance == 0)
            ans++;

    ============================================================
    3. Example
    ============================================================

    s = "RLRRLLRLRR"

    Process from left to right:

        R -> balance = 1
        L -> balance = 0
               ans = 1

        R -> balance = 1
        R -> balance = 2
        L -> balance = 1
        L -> balance = 0
               ans = 2

        R -> balance = 1
        L -> balance = 0
               ans = 3

        R -> balance = 1
        R -> balance = 2

    Therefore:

        answer = 3

    The balanced parts are:

        "RL"
        "RRLL"
        "RL"

    ============================================================
    4. Why Is the Greedy Approach Optimal?
    ============================================================

    Whenever `balance` becomes zero, we immediately split.

    This is always optimal because the current prefix is already
    balanced, so extending it further would only merge it with
    characters that could form another balanced substring.

    Therefore, taking every possible balanced prefix gives the
    maximum number of balanced substrings.

    ============================================================
    5. Why Do We Only Need One Counter?
    ============================================================

    We do not need to separately count 'L' and 'R'.

    The difference is enough:

        balance = R - L

    If:

        balance > 0

    there are more 'R' characters than 'L'.

    If:

        balance < 0

    there are more 'L' characters than 'R'.

    If:

        balance == 0

    both counts are equal, so the current part is balanced.

    ============================================================
    Complexity Analysis
    ============================================================

    Time Complexity: O(n)

        Every character is processed exactly once.

    Space Complexity: O(1)

        Only `balance` and `ans` are maintained.

    ============================================================
    Core Idea
    ============================================================

    Treat:

        'R' -> +1
        'L' -> -1

    Whenever the running balance becomes zero, we have found
    one balanced substring.

        balance == 0 -> ans++

    Greedily splitting at every zero balance produces the
    maximum possible number of balanced substrings.
    ============================================================
*/