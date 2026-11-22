class Solution {
    public:
        bool checkString(string s) {
            bool a = false, b = false;
            for(char &x : s) {
                if(x == 'a') a = true;
                if(x == 'b') b = true;
                if(a && b && x == 'a') return false;
            }
            return true;
        }
    };

/*
    LeetCode 2124: Check if All A's Appears Before All B's

    Approach: Single Pass + Boolean Flags

    Intuition:
    We need to check whether all occurrences of 'a' appear before
    any occurrence of 'b'.

    In other words, once we encounter a 'b', we should never encounter
    an 'a' again.

    We traverse the string from left to right and maintain two flags:
    - `a`: Tracks whether we have encountered an 'a'.
    - `b`: Tracks whether we have encountered a 'b'.

    If both flags become true and the current character is 'a',
    it means an 'a' has appeared after a 'b', violating the required
    order. Therefore, we immediately return false.

    Variables:
    - a: Becomes true when at least one 'a' is encountered.
    - b: Becomes true when at least one 'b' is encountered.
    - x: Reference to the current character during traversal.

    Step-by-Step Explanation:

    1. Initialize both flags to false:

           bool a = false, b = false;

       Initially, we have not encountered either character.

    2. Traverse the string using a range-based for loop:

           for(char &x : s)

       This examines every character from left to right.

    3. If the current character is 'a':

           if(x == 'a') a = true;

       Mark that we have encountered an 'a'.

    4. If the current character is 'b':

           if(x == 'b') b = true;

       Mark that we have encountered a 'b'.

    5. Check for an invalid ordering:

           if(a && b && x == 'a') return false;

       If both flags are true and the current character is 'a',
       we know that a 'b' appeared earlier and now an 'a' has appeared.

       This violates the condition that all 'a's must come before
       all 'b's.

       We can immediately return false without checking the rest
       of the string.

    6. If the entire string is traversed without finding an invalid
       ordering, return true.

    Example Walkthrough 1:

    s = "aaabbb"

    Initially:
        a = false
        b = false

    Characters:
        'a' -> a = true, b = false
        'a' -> a = true, b = false
        'a' -> a = true, b = false
        'b' -> a = true, b = true
        'b' -> no violation
        'b' -> no violation

    No 'a' appears after a 'b'.

    Return true.

    Example Walkthrough 2:

    s = "ba"

    Initially:
        a = false
        b = false

    First character = 'b':
        a = false
        b = true

    Second character = 'a':
        a = true
        b = true

        Both flags are true and the current character is 'a'.

        Return false.

    Why It Works:
    The flag `b` tells us whether a 'b' has appeared earlier,
    while `a` tells us whether an 'a' has appeared.

    If we encounter an 'a' after a 'b', both flags will be true,
    and the current character will be 'a'.

    Therefore, the condition `a && b && x == 'a'` detects every
    possible violation of the required ordering.

    If no violation is found, all occurrences of 'a' must appear
    before all occurrences of 'b'.

    Complexity Analysis:
    - Time Complexity: O(n)
      We traverse the string once, where n is its length.

    - Space Complexity: O(1)
      We use only two boolean variables.

    Core Idea:
    Track whether 'a' and 'b' have appeared. Once a 'b' has been
    encountered, any subsequent 'a' makes the string invalid.
*/