class Solution {
    public:
        int countCommas(int n) {
            if(n < 1000) return 0;
            return n - 1000 + 1;
        }
    };

/*
    Approach:
    ------------------------------------------------------------
    The goal is to count how many commas appear when writing every
    integer from 1 to n using standard comma formatting.

    For example:

        999   -> 999      -> 0 commas
        1000  -> 1,000    -> 1 comma
        1001  -> 1,001    -> 1 comma
        2000  -> 2,000    -> 1 comma

    The key observation is that commas first appear when we reach
    1000.

    ------------------------------------------------------------
    Key Observation:
    ------------------------------------------------------------

    Every number from:

        1000 to n

    contains exactly ONE comma, as long as n is within the
    4-digit range.

    Therefore:

        number of commas
        = number of integers from 1000 through n

    The count of integers in the inclusive range [1000, n] is:

        n - 1000 + 1

    which simplifies to:

        n - 999



    ------------------------------------------------------------
    Case 1: n < 1000
    ------------------------------------------------------------

    Every number from 1 to n has at most 3 digits.

    Examples:

        1
        25
        999

    None of these numbers needs a comma.

    Therefore:

        answer = 0



    ------------------------------------------------------------
    Case 2: n >= 1000
    ------------------------------------------------------------

    Starting from 1000, every number contributes one comma:

        1000 -> 1 comma
        1001 -> 1 comma
        1002 -> 1 comma
        ...
        n    -> 1 comma

    The number of such integers is:

        n - 1000 + 1

    Hence:

        answer = n - 1000 + 1



    ------------------------------------------------------------
    Example:
    ------------------------------------------------------------

    n = 1003

    Numbers containing commas:

        1000 -> 1,000
        1001 -> 1,001
        1002 -> 1,002
        1003 -> 1,003

    There are 4 numbers.

    Therefore:

        answer = 1003 - 1000 + 1
               = 4



    ------------------------------------------------------------
    Example:
    ------------------------------------------------------------

    n = 999

    Since:

        n < 1000

    no number from 1 to 999 contains a comma.

    Therefore:

        answer = 0



    ------------------------------------------------------------
    Why This Works:
    ------------------------------------------------------------

    A comma is required for a number once it reaches four digits.

    Since the problem only requires counting commas and every
    number from 1000 onward contributes exactly one comma, we only
    need to count how many numbers lie between 1000 and n.

    The inclusive range count formula is:

        end - start + 1

    so:

        n - 1000 + 1



    ------------------------------------------------------------
    Algorithm:
    ------------------------------------------------------------

    1. If n < 1000, return 0.
    2. Otherwise, count all numbers from 1000 through n.
    3. Return:

           n - 1000 + 1



    ------------------------------------------------------------
    Time Complexity:
    ------------------------------------------------------------

        O(1)

    Only a single comparison and arithmetic operation are needed.



    ------------------------------------------------------------
    Space Complexity:
    ------------------------------------------------------------

        O(1)

    No additional data structures are used.



    ------------------------------------------------------------
    Core Idea:
    ------------------------------------------------------------

    Commas start appearing at 1000.

    Every number from 1000 through n contributes exactly one
    comma, so the answer is simply the size of that inclusive
    range:

        n - 1000 + 1

    If n is below 1000, the answer is 0.
*/