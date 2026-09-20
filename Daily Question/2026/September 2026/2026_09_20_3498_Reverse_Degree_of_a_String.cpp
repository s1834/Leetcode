class Solution {
    public:
        int reverseDegree(string s) {
            int n = s.size(), sum = 0;
            for(int i = 0; i < n; i++) sum += (26 - (s[i] - 'a')) * (i + 1); 
            return sum;
        }
    };

/*
    LeetCode 3498 - Reverse Degree of a String
    ------------------------------------------------------------

    Approach:
    ------------------------------------------------------------

    For every character in the string, we calculate its REVERSE DEGREE
    and multiply it by the character's 1-based position.

    The reverse degree of a lowercase English character is its position
    when the alphabet is written in reverse order.

    Normal alphabet:

        a b c d e ... x y z
        1 2 3 4 5 ... 24 25 26

    Reverse alphabet:

        z y x w v ... c b a
        1 2 3 4 5 ... 24 25 26

    Therefore:

        reverseDegree('a') = 26
        reverseDegree('b') = 25
        reverseDegree('c') = 24
        ...
        reverseDegree('y') = 2
        reverseDegree('z') = 1


    ------------------------------------------------------------
    Key Observation:
    ------------------------------------------------------------

    Since characters are represented using ASCII values:

        'a' - 'a' = 0
        'b' - 'a' = 1
        'c' - 'a' = 2
        ...
        'z' - 'a' = 25


    The normal zero-based alphabet index of s[i] is:

        s[i] - 'a'


    To convert this into the reverse degree:

        26 - (s[i] - 'a')


    Therefore:

        reverseDegree(s[i]) = 26 - (s[i] - 'a')


    ------------------------------------------------------------
    Example:
    ------------------------------------------------------------

    Suppose:

        s[i] = 'a'

    Then:

        s[i] - 'a' = 0

    Reverse degree:

        26 - 0 = 26


    For:

        s[i] = 'c'

    We have:

        'c' - 'a' = 2

    Therefore:

        26 - 2 = 24


    For:

        s[i] = 'z'

    We have:

        'z' - 'a' = 25

    Therefore:

        26 - 25 = 1


    So the formula correctly maps:

        a -> 26
        b -> 25
        c -> 24
        ...
        z -> 1


    ------------------------------------------------------------
    Position Contribution:
    ------------------------------------------------------------

    The problem uses 1-based positions.

    However, the loop variable i is 0-based:

        i = 0, 1, 2, ...


    Therefore, the actual position of s[i] is:

        i + 1


    The contribution of each character is:

        reverseDegree(s[i]) * (i + 1)


    Substituting the reverse-degree formula:

        (26 - (s[i] - 'a')) * (i + 1)


    This is exactly what the code calculates:

        sum += (26 - (s[i] - 'a')) * (i + 1);


    ------------------------------------------------------------
    Complete Formula:
    ------------------------------------------------------------

    If the string is:

        s = s[0], s[1], ..., s[n-1]

    then the reverse degree is:

        Sum from i = 0 to n-1 of:

        (26 - (s[i] - 'a')) * (i + 1)


    ------------------------------------------------------------
    Example:
    ------------------------------------------------------------

    Consider:

        s = "abc"


    Character table:

        i       character       reverse degree       position
        -----------------------------------------------------
        0           a                  26                1
        1           b                  25                2
        2           c                  24                3


    Contributions:

        'a':

            26 * 1 = 26

        'b':

            25 * 2 = 50

        'c':

            24 * 3 = 72


    Total:

        26 + 50 + 72 = 148


    Therefore:

        reverseDegree("abc") = 148


    ------------------------------------------------------------
    Another Example:
    ------------------------------------------------------------

    Consider:

        s = "z"


    For 'z':

        'z' - 'a' = 25

        reverse degree = 26 - 25 = 1

    Position:

        1

    Contribution:

        1 * 1 = 1

    Therefore:

        reverseDegree("z") = 1


    ------------------------------------------------------------
    Why the Formula Works:
    ------------------------------------------------------------

    The ASCII/character difference:

        s[i] - 'a'

    gives the zero-based position of the character in the normal
    alphabet.

    The normal positions are:

        a -> 0
        b -> 1
        c -> 2
        ...
        z -> 25


    Reversing these values means:

        0 -> 26
        1 -> 25
        2 -> 24
        ...
        25 -> 1


    This transformation is exactly:

        26 - index


    Hence:

        26 - (s[i] - 'a')

    directly gives the reverse degree.


    ------------------------------------------------------------
    Why (i + 1)?
    ------------------------------------------------------------

    The problem uses 1-based indexing.

    But C++ arrays and strings use 0-based indexing.

    Therefore:

        i = 0  -> position 1
        i = 1  -> position 2
        i = 2  -> position 3
        ...
        i = n-1 -> position n

    Hence every character's reverse degree is multiplied by:

        i + 1


    ------------------------------------------------------------
    Algorithm:
    ------------------------------------------------------------

    1. Initialize:

           sum = 0

    2. Traverse every character using index i.

    3. Calculate its reverse degree:

           26 - (s[i] - 'a')

    4. Multiply it by its 1-based position:

           (26 - (s[i] - 'a')) * (i + 1)

    5. Add the contribution to sum.

    6. Return sum.


    ------------------------------------------------------------
    Complexity:
    ------------------------------------------------------------

    Time Complexity:

        O(n)

    where n is the length of the string.

    Every character is processed exactly once.


    Space Complexity:

        O(1)

    Only a few integer variables are used.


    ------------------------------------------------------------
    Core Idea:
    ------------------------------------------------------------

    Convert each character into its reverse-alphabet value using:

        26 - (s[i] - 'a')

    and multiply it by its 1-based position:

        i + 1


    So each character contributes:

        reverse alphabet value × position


    and the answer is simply the sum of all these contributions.


    ------------------------------------------------------------
    Main Takeaway:
    ------------------------------------------------------------

    The entire solution is a direct application of the definition:

        Reverse Degree =
            Σ [reverse value of character × 1-based position]

    The important formula is:

        reverse value = 26 - (character - 'a')

    Therefore:

        sum += (26 - (s[i] - 'a')) * (i + 1);

    gives the required reverse degree in a single O(n) traversal.
*/