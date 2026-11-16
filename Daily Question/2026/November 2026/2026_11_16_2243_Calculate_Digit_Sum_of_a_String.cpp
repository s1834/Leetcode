class Solution {
    public:
        string digitSum(string s, int k) {
            while (s.size() > k) {
                string temp;
                int n = s.size();
                for (int i = 0; i < n; i += k) {
                    int val = 0;
                    for (int j = i; j < min(i + k, n); j++) val += s[j] - '0';
                    temp.append(to_string(val));
                }
                s = temp;
            }
            return s;
        }
    };

/*
    LeetCode 2243: Calculate Digit Sum of a String

    Approach: Simulation + String Processing

    Intuition:
    We repeatedly divide the string into consecutive groups of size `k`.
    For each group, we calculate the sum of its digits and append that
    sum to a new string.

    We continue this process until the length of the string becomes
    less than or equal to `k`.

    Since every transformation produces a new string, we use a temporary
    string `temp` to store the result of the current round.

    Step-by-Step Explanation:

    1. Repeat the process while `s.size() > k`.

       If the string length is already less than or equal to `k`,
       no further transformation is required.

    2. Create an empty temporary string `temp`.

       This will store the concatenated digit sums for the current round.

    3. Divide the string into groups of size `k`.

       The outer loop:
           for (int i = 0; i < n; i += k)

       - `i` represents the starting index of the current group.
       - Incrementing `i` by `k` moves to the next group.

    4. Calculate the sum of digits in each group.

       Initialize `val = 0`.

       The inner loop:
           for (int j = i; j < min(i + k, n); j++)

       - Starts from the current group's starting index.
       - Stops at the group's end or the end of the string, whichever
         comes first.
       - `s[j] - '0'` converts the character digit into its integer value.
       - Add each digit to `val`.

       Using `min(i + k, n)` ensures that the last group is also
       processed correctly even when it contains fewer than `k` digits.

    5. Append the calculated sum to `temp`.

           temp.append(to_string(val));

       `to_string(val)` converts the integer sum back into a string.
       Appending it allows multi-digit sums to be included correctly.

    6. After processing all groups, replace the original string:

           s = temp;

       The next iteration operates on this newly generated string.

    7. Once `s.size() <= k`, return `s`.

    Example Walkthrough:

    s = "11111222223", k = 3

    First round:

    Divide into groups:
        "111" | "112" | "222" | "23"

    Calculate digit sums:
        "111" -> 3
        "112" -> 4
        "222" -> 6
        "23"  -> 5

    New string:
        s = "3465"

    Second round:

    Since 4 > 3, process again.

    Divide into groups:
        "346" | "5"

    Calculate digit sums:
        "346" -> 13
        "5"   -> 5

    New string:
        s = "135"

    Now s.size() == k, so the loop terminates.

    Final answer:
        "135"

    Why It Works:
    Each iteration performs exactly one required transformation:
    partitioning the current string into groups of at most `k` digits,
    calculating each group's digit sum, and concatenating those sums.

    Replacing `s` with `temp` ensures that every subsequent round
    uses the result of the previous round.

    The loop terminates when the string length is at most `k`,
    which is precisely the stopping condition in the problem.

    Complexity Analysis:
    - Time Complexity: O(n log_k(n)) for k > 1.
      Each round processes every character in the current string once.
      The string length decreases by approximately a factor of `k`
      per round, so the number of rounds is logarithmic.

    - Space Complexity: O(n)
      The temporary string stores the transformed result.
      Its size is bounded by the size of the current string.

    Core Idea:
    Repeatedly partition the string into groups of size `k`, calculate
    each group's digit sum, and build the next string until its length
    is at most `k`.
*/