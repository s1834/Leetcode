class Solution {
    public:
        long long countCommas(long long n) {
            long long ans = 0;
            for(long long base = 1000; base <= n; base *= 1000) ans += n - base + 1;
            return ans;
        }
    };

/*
    Approach:
    ------------------------------------------------------------
    The problem asks us to count the TOTAL number of commas that
    would appear when writing every integer from 1 to n using
    standard comma formatting.

    Unlike the simpler version, n can be very large, so numbers
    can contain more than one comma.

    For example:

        999      -> 999          -> 0 commas
        1000     -> 1,000        -> 1 comma
        999999   -> 999,999      -> 1 comma
        1000000  -> 1,000,000    -> 2 commas
        1000000000 -> 1,000,000,000 -> 3 commas

    The key is to count commas by their position rather than
    processing every number individually.



    ------------------------------------------------------------
    Key Observation:
    ------------------------------------------------------------

    Commas appear every 3 digits from the right.

    Therefore:

        1000
        1,000

    is the first number that contains a comma.

    Then:

        1,000,000

    has a second comma.

    Then:

        1,000,000,000

    has a third comma.

    In general, for every:

        base = 1000, 1000^2, 1000^3, ...

    every number greater than or equal to `base` contributes
    ONE comma corresponding to that comma position.



    ------------------------------------------------------------
    Counting the First Comma:
    ------------------------------------------------------------

    Consider:

        base = 1000

    Every number from 1000 through n has at least one comma.

    The number of integers in this range is:

        n - 1000 + 1

    Therefore the first comma contributes:

        n - 1000 + 1



    ------------------------------------------------------------
    Counting the Second Comma:
    ------------------------------------------------------------

    The second comma starts appearing at:

        base = 1,000,000

    Every number from 1,000,000 through n has a second comma.

    Therefore the second comma contributes:

        n - 1,000,000 + 1



    ------------------------------------------------------------
    Counting the Third Comma:
    ------------------------------------------------------------

    The third comma starts appearing at:

        base = 1,000,000,000

    Every number from 1,000,000,000 through n has a third comma.

    Therefore it contributes:

        n - 1,000,000,000 + 1



    ------------------------------------------------------------
    General Formula:
    ------------------------------------------------------------

    For every power of 1000:

        base = 1000
        base = 1000^2
        base = 1000^3
        ...

    as long as:

        base <= n

    that comma position contributes:

        n - base + 1

    Therefore:

        answer =
            (n - 1000 + 1)
          + (n - 1000000 + 1)
          + (n - 1000000000 + 1)
          + ...

    The loop calculates exactly this sum.



    ------------------------------------------------------------
    Why Does Each Base Represent One Comma?
    ------------------------------------------------------------

    A number gets:

        1 comma  -> when it reaches 10^3
        2 commas -> when it reaches 10^6
        3 commas -> when it reaches 10^9
        4 commas -> when it reaches 10^12

    These thresholds are precisely:

        1000^1
        1000^2
        1000^3
        1000^4
        ...

    Instead of counting how many commas each individual number has,
    we count how many numbers contribute to each comma position.



    ------------------------------------------------------------
    Example:
    ------------------------------------------------------------

    n = 1,005

    Only the first comma threshold is reached:

        base = 1000

    Contribution:

        1005 - 1000 + 1
        = 6

    The numbers contributing one comma are:

        1000
        1001
        1002
        1003
        1004
        1005

    Therefore:

        answer = 6



    ------------------------------------------------------------
    Example:
    ------------------------------------------------------------

    n = 1,000,005

    First comma:

        base = 1000

        contribution =
            1,000,005 - 1,000 + 1
            = 999,006

    Second comma:

        base = 1,000,000

        contribution =
            1,000,005 - 1,000,000 + 1
            = 6

    Total:

        999,006 + 6
        = 999,012



    Notice that numbers from 1,000,000 onward contribute TWO
    commas.

    The first contribution counts their first comma, while the
    second contribution counts their second comma.



    ------------------------------------------------------------
    Another Way to Visualize It:
    ------------------------------------------------------------

    Suppose:

        n = 1,000,005

    We can think of the total commas as:

        First comma:
        1000 ----------------------------> 1,000,005
        ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                 all contribute 1

        Second comma:
        1,000,000 -----------------------> 1,000,005
        ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                 all contribute 1

    So the same number can be counted once for each comma that it
    contains.

    This is exactly what we want.



    ------------------------------------------------------------
    Why the Loop Uses `base *= 1000`:
    ------------------------------------------------------------

    Starting with:

        base = 1000

    multiplying by 1000 gives:

        1000
        1,000,000
        1,000,000,000
        1,000,000,000,000
        ...

    These are exactly the thresholds where an additional comma
    starts appearing.



    ------------------------------------------------------------
    Important Overflow Consideration:
    ------------------------------------------------------------

    The code uses:

        long long

    for both `n` and `base`.

    This is important because the thresholds grow rapidly:

        1000
        1,000,000
        1,000,000,000
        1,000,000,000,000
        ...

    Using `long long` allows the algorithm to handle values much
    larger than the range of a normal `int`.

    The loop condition:

        base <= n

    also ensures that we only process comma positions that can
    actually appear for numbers up to n.



    ------------------------------------------------------------
    What Does `ans += n - base + 1` Mean?
    ------------------------------------------------------------

    For the current comma position represented by `base`:

        n - base + 1

    is the number of integers in the inclusive range:

        [base, n]

    Every one of those integers has this particular comma.

    Therefore we add that count to `ans`.



    ------------------------------------------------------------
    Algorithm:
    ------------------------------------------------------------

    1. Initialize:

           ans = 0

    2. Start the first comma threshold at:

           base = 1000

    3. While `base <= n`:
       - Count how many numbers from `base` through `n` contain
         this comma.
       - Add:

             n - base + 1

         to `ans`.
       - Move to the next comma threshold:

             base *= 1000

    4. Return `ans`.



    ------------------------------------------------------------
    Why This Works:
    ------------------------------------------------------------

    Every comma in every number corresponds to one of the
    positions:

        10^3, 10^6, 10^9, ...

    For a fixed comma position `base = 1000^k`, exactly the
    numbers from `base` through n contain that comma.

    Therefore:

        n - base + 1

    counts every occurrence of that particular comma.

    Summing this over every possible `base` counts every comma
    exactly once.

    Thus the final value of `ans` is the total number of commas
    appearing across all integers from 1 to n.



    ------------------------------------------------------------
    Example With Multiple Commas:
    ------------------------------------------------------------

    n = 1,000,000,000

    First comma:

        base = 1,000

        contribution =
            1,000,000,000 - 1,000 + 1



    Second comma:

        base = 1,000,000

        contribution =
            1,000,000,000 - 1,000,000 + 1



    Third comma:

        base = 1,000,000,000

        contribution =
            1,000,000,000 - 1,000,000,000 + 1
            = 1

    The number 1,000,000,000 itself has three commas, and it is
    therefore counted once in each of the three contributions.



    ------------------------------------------------------------
    Complexity:
    ------------------------------------------------------------

    The value of `base` is multiplied by 1000 on every iteration.

    Therefore the number of iterations is proportional to the
    number of groups of three digits in n.

    Time Complexity:

        O(log_1000(n))

    which is effectively:

        O(log n)



    ------------------------------------------------------------
    Space Complexity:
    ------------------------------------------------------------

        O(1)

    Only `ans`, `n`, and `base` are used.



    ------------------------------------------------------------
    Core Idea:
    ------------------------------------------------------------

    Do NOT count commas number-by-number.

    Instead, count each comma position separately.

    The thresholds for additional commas are:

        1000
        1,000,000
        1,000,000,000
        ...

    For every threshold `base`, all numbers from `base` to `n`
    contain that particular comma.

    Therefore:

        contribution = n - base + 1

    and we sum these contributions while repeatedly doing:

        base *= 1000

    This gives the total number of commas in O(log n) time and
    O(1) space.
*/