class Solution {
    public:
        bool isSameAfterReversals(int num) {
            return (num % 10) != 0 || num == 0;
        }
    };

/*
    LeetCode 2119: A Number After a Double Reversal

    Approach: Mathematical Observation

    Intuition:
    We are given an integer num and need to determine whether
    reversing its digits twice gives us the original number.

    A reversal removes leading zeros from the resulting number.
    Therefore, the only way the original number can change after
    two reversals is if it originally ends with one or more zeros.

    For example:
        num = 120

        First reversal:
            120 -> 21

        Second reversal:
            21 -> 12

        The result is different from the original number.

    On the other hand:

        num = 123

        First reversal:
            123 -> 321

        Second reversal:
            321 -> 123

        The original number is restored.

    Key Observation:
    - If num ends with zero and num is non-zero, reversing it removes
      those trailing zeros. Reversing again cannot restore them.
    - If num does not end with zero, reversing twice restores
      the original number.
    - Zero itself is a special case and remains zero after both
      reversals.

    Code Explanation:

    We simply check:

        (num % 10) != 0 || num == 0

    1. num % 10 != 0:
       Checks whether the last digit of num is non-zero.

       If true, reversing the number twice gives the original number.

    2. num == 0:
       Handles zero separately because 0 % 10 == 0, but zero
       remains unchanged after reversing it twice.

    3. If either condition is true, return true; otherwise,
       return false.

    Example Walkthrough:

    Example 1:
        num = 526

        num % 10 = 6

        Since the last digit is non-zero:
            return true

    Example 2:
        num = 1800

        num % 10 = 0
        num != 0

        Both conditions are false:
            return false

    Example 3:
        num = 0

        num % 10 = 0
        num == 0

        The second condition is true:
            return true

    Complexity Analysis:

    Time Complexity: O(1)
        Only two constant-time conditions are evaluated.

    Space Complexity: O(1)
        No additional data structures or variables are used.

    Core Idea:
    A number can be reversed twice and remain unchanged if and
    only if it is zero or its last digit is non-zero.
*/