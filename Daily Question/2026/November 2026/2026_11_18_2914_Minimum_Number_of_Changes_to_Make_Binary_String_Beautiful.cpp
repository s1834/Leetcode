class Solution {
    public:
        int minChanges(string s) {
            int n = s.size(), changes = 0;
            for(int i = 0; i < n; i += 2) {
                if(s[i] != s[i + 1]) changes++;
            }
            return changes;
        }
    };

/*
    LeetCode 2914: Minimum Number of Changes to Make Binary String Beautiful

    Approach: Greedy + Pairwise Comparison

    Intuition:
    We need to make the binary string beautiful using the minimum
    number of character changes.

    A beautiful binary string must satisfy two conditions:
    1. Its length must be divisible by 2.
    2. Every substring of length 2 must contain identical characters.

    Since the string is divided into consecutive pairs, the only
    valid patterns are pairs like:
        "00", "11", "00", "11", ...

    Therefore, we simply examine every consecutive pair.

    - If both characters are already equal, no change is required.
    - If the characters are different, we must change exactly one
      of them to make the pair equal.

    Step-by-Step Explanation:

    1. Initialize:
           n = s.size()
           changes = 0

       - `n` stores the length of the string.
       - `changes` counts the minimum number of character modifications.

    2. Traverse the string with `i += 2`.

       The loop processes non-overlapping pairs:
           (s[0], s[1])
           (s[2], s[3])
           (s[4], s[5])
           ...

       We increment `i` by 2 because each pair is independent.

    3. Compare the two characters in the current pair:
           if(s[i] != s[i + 1])

       If they are different, one character must be changed to make
       both characters equal.

       Increment `changes`.

    4. If the characters are already equal, no modification is needed.

    5. After checking all pairs, return `changes`.

    Example Walkthrough:

    s = "1001"

    Initial:
        changes = 0

    First pair:
        s[0], s[1] = '1', '0'

        Characters are different.
        One change is required.

        changes = 1

    Second pair:
        s[2], s[3] = '0', '1'

        Characters are different.
        One more change is required.

        changes = 2

    Final answer:
        2

    One possible beautiful string is:
        "1100"

    Why It Works:
    Every valid beautiful string must have identical characters
    at positions (0, 1), (2, 3), (4, 5), and so on.

    Each pair can be fixed independently:
    - Equal characters require zero changes.
    - Different characters require exactly one change.

    Since at least one change is necessary for every mismatched pair,
    and changing either character fixes that pair in one operation,
    this greedy approach achieves the minimum possible number
    of changes.

    Complexity Analysis:
    - Time Complexity: O(n)
      We traverse the string once, examining each pair.

    - Space Complexity: O(1)
      We use only two variables, `n` and `changes`.

    Core Idea:
    Divide the string into consecutive pairs. Every mismatched pair
    requires exactly one change, so count the mismatched pairs.
*/