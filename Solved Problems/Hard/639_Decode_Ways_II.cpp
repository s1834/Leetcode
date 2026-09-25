class Solution {
    private:
        int n;
        vector<long long> dp;
        const long long MOD = 1e9 + 7;
    
        long long solve(string& s, int i) {
            if(i == n) return 1;
            if(s[i] == '0') return 0;
    
            if(dp[i] != -1) return dp[i];
            
            long long ans = 0;
    
            // take 1 digit
            if(s[i] == '*') ans += 9 * solve(s, i + 1);
            else ans += solve(s, i + 1);
    
            // take 2 digits
            if(i + 1 < n) {
                if(s[i] == '*' && s[i + 1] == '*') {
                    // 15 possibilities (10 – 26)
                    ans += 15 * solve(s, i + 2);
                } else if(s[i] == '*') {
                    int num = s[i + 1] - '0'; // second digit
                    if(num >= 0 && num <= 6) ans += 2 * solve(s, i + 2); // starting with 1 or 2
                    else ans += solve(s, i + 2); // all other starting points
                } else if(s[i + 1] == '*') {
                    // 1 -> 9 possibilities
                    if(s[i] == '1') ans += 9 * solve(s, i + 2);
    
                    // 2 -> 6 possibilities
                    else if(s[i] == '2')  ans += 6 * solve(s, i + 2);
                } else {
                    int num = (s[i] - '0') * 10 + (s[i + 1] - '0');
                    if(num >= 10 && num <= 26) ans += solve(s, i + 2);
                }
            }
    
            return dp[i] = ans % MOD;
        }
    
    
    public:
        int numDecodings(string s) {
            n = s.size();
            dp.assign(n, -1);
            return solve(s, 0);
        }
    };

/*
    LeetCode 639 - Decode Ways II
    ------------------------------------------------------------

    Approach:
    ------------------------------------------------------------

    This problem is an extension of LeetCode 91 - Decode Ways.

    The difference is that the string can now contain:

        '*'

    A '*' can represent ANY digit from:

        '1' to '9'

    Therefore, instead of simply checking whether one or two digits
    form a valid encoding, we must count how many possible
    interpretations exist.

    The basic decoding rules are still:

        1 -> A
        2 -> B
        ...
        26 -> Z

    The DP state is:

        solve(i)

    = number of ways to decode the suffix:

        s[i ... n-1]


    At every index, we consider:

        1. Taking one character
        2. Taking two characters

    But the number of possibilities depends on whether the current
    characters are digits or '*'.

    ------------------------------------------------------------
    Key Observation:
    ------------------------------------------------------------

    For a normal digit, there is usually only one possibility.

    For:

        '*'

    there are:

        9 possibilities

    because:

        '*' can be:
            1, 2, 3, 4, 5, 6, 7, 8, 9


    The two-character case is more interesting.

    For example:

        "**"

    can represent:

        11, 12, 13, ..., 19
        21, 22, 23, ..., 26

    Only numbers from:

        10 to 26

    are valid.

    Therefore there are:

        9 + 6 = 15

    valid two-digit possibilities for:

        "**"


    ------------------------------------------------------------
    DP State:
    ------------------------------------------------------------

        dp[i]

    represents:

        Number of ways to decode s[i ... n-1].

    The recursive function:

        solve(s, i)

    calculates this value.

    Once calculated, it is stored in:

        dp[i]

    so that the same suffix is never recalculated.


    ------------------------------------------------------------
    Base Case:
    ------------------------------------------------------------

        if(i == n) return 1;


    If we have reached the end of the string, it means that we have
    successfully decoded the entire string.

    Therefore, this represents ONE valid decoding.

    Returning 1 is important because it allows the previous choice
    to count this complete decoding as one possibility.


    Example:

        s = "12"

    If we choose:

        "12"

    we call:

        solve(2)

    Since:

        2 == n

    we return:

        1

    meaning:

        "12" produced one complete valid decoding.


    ------------------------------------------------------------
    Handling '0':
    ------------------------------------------------------------

        if(s[i] == '0') return 0;


    A standalone '0' cannot represent any letter.

    Valid single-digit encodings are:

        1 -> A
        2 -> B
        ...
        9 -> I

    There is no:

        0 -> ?

    Therefore, if the current character is '0', there are no
    valid ways to decode starting from this position.


    IMPORTANT:

    A zero can still be valid as part of a two-digit number:

        10
        20

    Therefore we do NOT reject zero globally.

    We only reject it when it is being considered as a
    single-character decoding.


    ------------------------------------------------------------
    Memoization:
    ------------------------------------------------------------

        if(dp[i] != -1) return dp[i];


    Many different decoding choices can reach the same index.

    For example, several different interpretations of '*' may
    eventually lead to the same suffix.

    But:

        solve(i)

    always has the same answer for a fixed i.

    Therefore we calculate it once and store:

        dp[i]


    ------------------------------------------------------------
    One-Digit Case:
    ------------------------------------------------------------

        if(s[i] == '*')
            ans += 9 * solve(s, i + 1);
        else
            ans += solve(s, i + 1);


    There are two possibilities.


    ------------------------------------------------------------
    Case 1: s[i] is '*'
    ------------------------------------------------------------

    '*' can represent:

        1
        2
        3
        ...
        9

    Therefore there are:

        9

    possible single-digit choices.

    For EVERY one of those choices, the remaining suffix is:

        s[i+1 ... n-1]

    and therefore contributes:

        solve(i + 1)

    for each possibility.

    So:

        one-digit contribution
            =
        9 * solve(i + 1)


    ------------------------------------------------------------
    Example:
    ------------------------------------------------------------

        s = "*"

    '*' can be:

        1
        2
        3
        ...
        9

    Therefore:

        answer = 9


    The code calculates:

        9 * solve(1)

    and:

        solve(1) = 1

    so:

        answer = 9


    ------------------------------------------------------------
    Case 2: s[i] is a normal digit
    ------------------------------------------------------------

    A normal non-zero digit has exactly one interpretation.

    Therefore:

        ans += solve(s, i + 1);


    There is only one way to consume that digit as a single
    character.


    ------------------------------------------------------------
    Two-Digit Case:
    ------------------------------------------------------------

    If:

        i + 1 < n

    then we can also try to decode:

        s[i] and s[i+1]

    together.

    But because either character can be '*', we have several
    different cases.

    The code handles all of them separately.


    ------------------------------------------------------------
    Case 1: "**"
    ------------------------------------------------------------

        if(s[i] == '*' && s[i + 1] == '*') {

            ans += 15 * solve(s, i + 2);

        }


    This is the most important wildcard case.


    '*' can represent 1-9.

    For the first '*':

        If it becomes 1:

            10, 11, 12, 13, 14, 15, 16, 17, 18, 19

        -> 9 valid possibilities


        If it becomes 2:

            20, 21, 22, 23, 24, 25, 26

        -> 7? possibilities numerically from 20 through 26


    However, because the second '*' can represent only 1-9,
    it cannot represent 0.

    Therefore for first '*' = 2:

        21, 22, 23, 24, 25, 26

        -> 6 valid possibilities


    Total:

        9 + 6 = 15


    Therefore:

        "**"

    has exactly:

        15

    valid two-digit decodings.


    The code therefore does:

        ans += 15 * solve(s, i + 2);


    ------------------------------------------------------------
    Why Not 17?
    ------------------------------------------------------------

    The complete valid range is:

        10 ... 26

    But '*' cannot represent zero.

    Therefore:

        10

    cannot be generated from:

        "**"

    because the second '*' only represents 1-9.

    Similarly, the valid numbers beginning with 2 are:

        21,22,23,24,25,26

    not:

        20


    Therefore:

        9 + 6 = 15


    ------------------------------------------------------------
    Case 2: Current '*' + Normal Digit
    ------------------------------------------------------------

        else if(s[i] == '*') {

            int num = s[i + 1] - '0';

            if(num >= 0 && num <= 6)
                ans += 2 * solve(s, i + 2);
            else
                ans += solve(s, i + 2);
        }


    Here:

        s[i] = '*'

    while:

        s[i+1]

    is a normal digit.


    The '*' can potentially represent:

        1

    or:

        2


    depending on the second digit.


    ------------------------------------------------------------
    Why Digits 0-6 Have 2 Possibilities:
    ------------------------------------------------------------

    Suppose the second digit is:

        3

    Then:

        *3

    can represent:

        13
        23

    Both are valid because:

        13 <= 26
        23 <= 26


    Therefore there are:

        2

    possibilities.


    The same applies to:

        0
        1
        2
        3
        4
        5
        6


    For example:

        *0 -> 10, 20
        *1 -> 11, 21
        *2 -> 12, 22
        ...
        *6 -> 16, 26


    Therefore:

        if(num >= 0 && num <= 6)

    we add:

        2 * solve(i + 2)


    ------------------------------------------------------------
    Why Digits 7-9 Have Only 1 Possibility:
    ------------------------------------------------------------

    Suppose:

        *7

    The possibilities would be:

        17
        27

    But:

        27 > 26

    so 27 is invalid.

    Therefore only:

        17

    is valid.

    Similarly:

        *8 -> 18 only
        *9 -> 19 only


    Therefore for:

        7, 8, 9

    we add:

        solve(i + 2)


    ------------------------------------------------------------
    Case 3: Normal Digit + '*'
    ------------------------------------------------------------

        else if(s[i + 1] == '*') {

            if(s[i] == '1')
                ans += 9 * solve(s, i + 2);

            else if(s[i] == '2')
                ans += 6 * solve(s, i + 2);
        }


    Now the first character is fixed and the second character
    is '*'.

    There are two important possibilities.


    ------------------------------------------------------------
    First Digit = '1'
    ------------------------------------------------------------

        1*

    The '*' can represent:

        1,2,3,4,5,6,7,8,9

    Therefore:

        11
        12
        13
        ...
        19

    All of them are valid.

    Therefore there are:

        9

    possibilities.

    Hence:

        if(s[i] == '1')
            ans += 9 * solve(s, i + 2);


    ------------------------------------------------------------
    First Digit = '2'
    ------------------------------------------------------------

        2*

    The '*' can represent:

        1,2,3,4,5,6,7,8,9

    But only:

        21
        22
        23
        24
        25
        26

    are valid.

    27, 28, and 29 are greater than 26.

    Therefore there are:

        6

    possibilities.

    Hence:

        else if(s[i] == '2')
            ans += 6 * solve(s, i + 2);


    ------------------------------------------------------------
    What About First Digit 3-9?
    ------------------------------------------------------------

    Suppose:

        3*

    The smallest possible number is:

        31

    which is already greater than 26.

    Therefore no two-digit decoding is possible.

    The same applies to:

        4*
        5*
        ...
        9*


    So the code simply does nothing for these cases.


    ------------------------------------------------------------
    Case 4: Two Normal Digits
    ------------------------------------------------------------

        else {

            int num =
                (s[i] - '0') * 10
                + (s[i + 1] - '0');

            if(num >= 10 && num <= 26)
                ans += solve(s, i + 2);
        }


    When both characters are normal digits, we form their
    two-digit number.

    Example:

        s[i]     = '2'
        s[i+1]   = '6'

        num = 26


    If:

        10 <= num <= 26

    then this pair represents one valid letter.

    Therefore:

        ans += solve(i + 2);


    Otherwise, the pair cannot be used together.


    ------------------------------------------------------------
    Example: "1*"
    ------------------------------------------------------------

    Suppose:

        s = "1*"


    Single-digit choices:

        '1' -> one possibility

    Then '*' has:

        9

    possibilities.

    For the two-digit choice:

        1*

    can represent:

        11,12,13,14,15,16,17,18,19

    Therefore:

        9

    additional possibilities.


    Total:

        9 + 9 = 18


    ------------------------------------------------------------
    Example: "2*"
    ------------------------------------------------------------

    Single-digit interpretation:

        '2'

    followed by '*' having:

        9

    possibilities.

    So:

        9

    single-digit combinations.


    Two-digit interpretation:

        21,22,23,24,25,26

    gives:

        6

    possibilities.


    Therefore the total is:

        9 + 6 = 15

    multiplied by the number of ways to decode the suffix after
    those characters.


    ------------------------------------------------------------
    Example: "**"
    ------------------------------------------------------------

    For the first '*' as a single digit:

        9 possibilities


    For the two-digit interpretation:

        11-19 -> 9 possibilities
        21-26 -> 6 possibilities

    Therefore:

        15

    two-digit possibilities.


    The recursion counts:

        9 * solve(i+1)

    for the one-digit choice, and:

        15 * solve(i+2)

    for the two-digit choice.


    ------------------------------------------------------------
    Example: "1*2"
    ------------------------------------------------------------

    At index 0:

        '1'

    Single digit:

        "1"

    Two digits:

        "1*"

    which has 9 possibilities:

        11 ... 19


    After taking one digit, the recursion handles:

        "*2"

    independently.

    This demonstrates why the DP state only needs the current
    index.

    Once the current one or two characters are consumed, the
    remaining suffix is exactly the same type of problem.


    ------------------------------------------------------------
    Why We Can Multiply by 9, 6, or 15:
    ------------------------------------------------------------

    This is an important optimization.

    Suppose:

        s[i] = '*'

    and we are taking it as one digit.

    There are 9 possible replacements:

        1 through 9

    For each replacement, the remaining string:

        s[i+1 ...]

    is identical.

    Therefore we do NOT need to recursively call solve(i+1)
    nine separate times.

    We can calculate:

        9 * solve(i+1)


    Similarly:

        2 * solve(i+2)

    means there are two possible interpretations of the current
    two-character combination, and AFTER choosing either one,
    the remaining suffix has exactly the same number of decoding
    possibilities.


    ------------------------------------------------------------
    This Is the Main Optimization:
    ------------------------------------------------------------

    Instead of:

        choice 1 -> solve(i+1)
        choice 2 -> solve(i+1)
        choice 3 -> solve(i+1)
        ...
        choice 9 -> solve(i+1)


    we combine them:

        9 * solve(i+1)


    Likewise:

        "**"

    has 15 possible two-digit interpretations, but all of them
    lead to the same remaining suffix:

        s[i+2 ...]

    Therefore:

        15 * solve(i+2)


    This avoids explicitly branching into every wildcard
    replacement.


    ------------------------------------------------------------
    DP Recurrence:
    ------------------------------------------------------------

    At every position i:

        ans =
            number of valid one-character interpretations
            +
            number of valid two-character interpretations


    One-character contribution:

        '*'  -> 9 * solve(i+1)
        digit -> 1 * solve(i+1)


    Two-character contribution depends on the pair:

        "**"
            -> 15 * solve(i+2)

        "*d"
            -> 2 * solve(i+2) if d <= 6
            -> 1 * solve(i+2) if d >= 7

        "1*"
            -> 9 * solve(i+2)

        "2*"
            -> 6 * solve(i+2)

        "d*"
            -> 0 if d >= 3

        "dd"
            -> 1 * solve(i+2) if 10 <= dd <= 26
            -> 0 otherwise


    ------------------------------------------------------------
    Why the DP State Is Still Only i:
    ------------------------------------------------------------

    Even though '*' can represent many different digits, after
    we decide how the current one or two characters are interpreted,
    the remaining suffix is completely independent.

    For example:

        "*abc..."

    If '*' is interpreted as:

        1
        2
        ...
        9

    the remaining string is still:

        "abc..."

    Therefore all 9 choices share the same:

        solve(i+1)


    Similarly, for:

        "**abc..."

    all 15 valid two-digit choices leave:

        "abc..."

    remaining.

    Therefore the DP state does not need to remember WHICH wildcard
    value was chosen.


    ------------------------------------------------------------
    Why MOD Is Required:
    ------------------------------------------------------------

    The number of possible decodings can become extremely large,
    especially when the string contains many '*' characters.

    Therefore we take the answer modulo:

        1e9 + 7


    The constant is:

        const long long MOD = 1e9 + 7;


    At the end of solve():

        return dp[i] = ans % MOD;


    This keeps the stored DP values within a manageable range.


    ------------------------------------------------------------
    Why long long Is Used:
    ------------------------------------------------------------

    We perform calculations such as:

        15 * solve(i + 2)

    and:

        9 * solve(i + 1)

    The number of decoding ways can be very large.

    Therefore:

        vector<long long> dp

    and:

        long long ans

    are used to safely hold intermediate values before taking
    the modulo.


    ------------------------------------------------------------
    Complete Example: "**"
    ------------------------------------------------------------

    Suppose:

        s = "**"

    At i = 0:

    One-digit interpretation:

        First '*' has 9 choices.

        9 * solve(1)

    Two-digit interpretation:

        "**" has 15 valid combinations.

        15 * solve(2)


    Since:

        solve(1) = 9

    and:

        solve(2) = 1

    we get:

        9 * 9 + 15 * 1

        = 81 + 15

        = 96


    Therefore:

        "**"

    has:

        96

    valid decodings.


    ------------------------------------------------------------
    Complete Example: "1*"
    ------------------------------------------------------------

    One-digit choice:

        '1'

    then '*':

        9 possibilities

    Contribution:

        9


    Two-digit choice:

        1*

    gives:

        11 through 19

    Contribution:

        9


    Total:

        18


    ------------------------------------------------------------
    Complete Example: "2*"
    ------------------------------------------------------------

    One-digit choice:

        '2'

    followed by '*':

        9 possibilities

    Contribution:

        9


    Two-digit choice:

        21 through 26

    Contribution:

        6


    Total:

        15


    ------------------------------------------------------------
    Complete Example: "*7"
    ------------------------------------------------------------

    One-digit choice:

        '*' can be 1-9

    Therefore:

        9

    one-digit possibilities.


    Two-digit choice:

        *7

    can only be:

        17

    because:

        27 > 26


    Therefore:

        1

    two-digit possibility.


    Total:

        9 + 1
        = 10


    ------------------------------------------------------------
    Important Difference From LeetCode 91:
    ------------------------------------------------------------

    In LeetCode 91, every character is fixed.

    Therefore, at most:

        1

    one-digit interpretation exists, and at most:

        1

    two-digit interpretation exists.


    In this problem, '*' introduces MULTIPLE interpretations.

    Therefore, instead of simply doing:

        solve(i+1)

    we sometimes do:

        9 * solve(i+1)

    or:

        15 * solve(i+2)

    or:

        6 * solve(i+2)

    etc.


    ------------------------------------------------------------
    Why the Multiplication Does Not Double Count:
    ------------------------------------------------------------

    Suppose:

        s[i] = '*'

    and we take it as a single digit.

    There are exactly 9 mutually different choices:

        1
        2
        ...
        9

    Every choice leaves exactly the same suffix:

        s[i+1 ... n-1]

    Therefore, if the suffix has X valid decodings, each of the
    9 choices can be combined with those X decodings.

    Hence:

        9 * X


    There is no double counting because the first chosen digit
    distinguishes the 9 groups.


    The same reasoning applies to the 15 valid two-digit
    interpretations of "**".


    ------------------------------------------------------------
    Complexity:
    ------------------------------------------------------------

    There are only n DP states:

        solve(0)
        solve(1)
        ...
        solve(n-1)


    Each state performs only O(1) work because all possible
    wildcard cases are handled using constant-time formulas.

    Therefore:

        Time Complexity = O(n)


    The memoization ensures that every state is computed only once.


    ------------------------------------------------------------
    Space Complexity:
    ------------------------------------------------------------

    The DP array contains n values:

        O(n)


    The recursion depth can also reach n:

        O(n)


    Therefore:

        Space Complexity = O(n)


    ------------------------------------------------------------
    Core Idea:
    ------------------------------------------------------------

    The DP state remains:

        solve(i)
        =
        number of ways to decode s[i ... n-1]


    But unlike LeetCode 91, each position can represent MULTIPLE
    possibilities because of '*'.

    Therefore we count the number of valid interpretations of:

        1 character
        +
        2 characters


    and multiply those counts by the number of ways to decode
    the remaining suffix.


    ------------------------------------------------------------
    Main Takeaway:
    ------------------------------------------------------------

    The most important idea is to GROUP ALL WILDCARD CHOICES that
    lead to the SAME suffix.

    For example:

        '*' as one digit:

            1,2,3,...,9

        -> 9 choices

        Therefore:

            9 * solve(i+1)


    And:

        '**' as two digits:

            11-19
            21-26

        -> 15 choices

        Therefore:

            15 * solve(i+2)


    Similarly:

        "*d"
            -> 2 choices if d <= 6
            -> 1 choice if d >= 7

        "1*"
            -> 9 choices

        "2*"
            -> 6 choices


    So the solution is essentially:

        DP
          +
        wildcard counting
          +
        memoization
          +
        modulo arithmetic


    The crucial state remains only the current index i, because
    after consuming one or two characters, every interpretation
    reaches the SAME remaining suffix.
*/