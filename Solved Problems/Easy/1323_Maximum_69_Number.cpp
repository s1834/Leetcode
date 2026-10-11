class Solution {
    public:
        int maximum69Number (int num) {
            vector<int> v;
            while(num) {
                v.push_back(num % 10);
                num /= 10;
            }
    
            int n = v.size();
            for(int i = n - 1; i >= 0; i--) {
                if(v[i] == 6) {
                    v[i] = 9;
                    break;
                }
            }
    
            num = 0;
            for(int i = n - 1; i >= 0; i--) num = num * 10 + v[i];
    
            return num;
        }
    };

/*
    Approach: Digit Extraction + Greedy

    The goal is to maximize a number containing only the digits 6 and 9
    by changing at most one digit from 6 -> 9.

    Since 9 is greater than 6, changing a 6 to 9 always increases the
    number. Therefore, we should change the MOST SIGNIFICANT 6 (the
    leftmost 6), because changing a digit farther to the left has a
    larger impact on the final number.

    ------------------------------------------------------------
    Step 1: Extract all digits
    ------------------------------------------------------------

    We repeatedly use:

        num % 10

    to get the last digit, and:

        num /= 10

    to remove the last digit.

    For example:

        num = 9669

        9669 % 10 = 9
        966  % 10 = 6
        96   % 10 = 6
        9    % 10 = 9

    So the vector becomes:

        v = {9, 6, 6, 9}

    Notice that the digits are stored in REVERSE order because we
    extracted them from right to left.

    ------------------------------------------------------------
    Step 2: Find the leftmost 6
    ------------------------------------------------------------

    Because the digits are reversed in `v`, the most significant
    digit is at index `n - 1`.

    Therefore, we traverse:

        i = n - 1 ... 0

    This corresponds to checking the original number from left to right.

    The first `6` we encounter is the most significant 6.

    We change:

        6 -> 9

    and immediately break because we are allowed to perform only
    one change.

    Example:

        num = 9669
        v   = {9, 6, 6, 9}

    Traversal:

        9 -> skip
        6 -> change to 9 and stop

    Now:

        v = {9, 9, 6, 9}

    which represents:

        9969

    ------------------------------------------------------------
    Step 3: Reconstruct the number
    ------------------------------------------------------------

    Since `v` is stored in reverse order, we again traverse from:

        n - 1 ... 0

    and construct the number using:

        num = num * 10 + v[i]

    For example:

        v = {9, 9, 6, 9}

        num = 0
        num = 9
        num = 99
        num = 996
        num = 9969

    ------------------------------------------------------------
    Why changing the leftmost 6 is optimal?
    ------------------------------------------------------------

    Consider:

        6669

    If we change the first 6:

        9669

    If we change the second 6:

        6969

    If we change the third 6:

        6699

    Clearly:

        9669 > 6969 > 6699

    So the earliest 6 has the greatest contribution to maximizing
    the final number.

    ------------------------------------------------------------
    Example
    ------------------------------------------------------------

    Input:

        num = 6699

    Extract digits:

        v = {9, 9, 6, 6}

    Traverse from the most significant side:

        6 -> change to 9

    Now:

        v = {9, 9, 6, 9}

    Reconstruct:

        9969

    Answer:

        9969

    ------------------------------------------------------------
    Edge Case
    ------------------------------------------------------------

    If the number contains no 6, then there is nothing to change.

    Example:

        9999

    The loop never changes anything, and the original number is
    reconstructed and returned.

    ------------------------------------------------------------
    Algorithm
    ------------------------------------------------------------

    1. Extract every digit into a vector.
    2. Traverse the vector from the most significant digit.
    3. Change the first 6 into 9.
    4. Reconstruct the number from the vector.
    5. Return the result.

    ------------------------------------------------------------
    Complexity
    ------------------------------------------------------------

    Let `d` be the number of digits in `num`.

    Time Complexity:
        O(d)

    We traverse the digits once for extraction, once for finding the
    6, and once for reconstruction.

    Space Complexity:
        O(d)

    The vector stores all digits of the number.

    ------------------------------------------------------------
    Core Idea
    ------------------------------------------------------------

    Since we can change only one digit and 9 > 6, we should change
    the LEFTMOST 6 to 9 because the most significant digit has the
    greatest effect on the value of the number.
*/