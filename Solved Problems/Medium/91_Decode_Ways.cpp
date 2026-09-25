class Solution {
    private:
        int n;
        vector<int> dp;
    
        int solve(string& s, int i) {
            if(i == n) return 1;
            if(s[i] == '0') return 0;
    
            if(dp[i] != -1) return dp[i];
            
            // take 1 digit
            int ans = solve(s, i + 1);
    
            // take 2 digits
            if(i + 1 < n) {
                int num = (s[i] - '0') * 10 + (s[i + 1] - '0');
                if(num >= 10 && num <= 26) ans += solve(s, i + 2);
            }
    
            return dp[i] = ans;
        }
    
    
    public:
        int numDecodings(string s) {
            n = s.size();
            dp.assign(n, -1);
            return solve(s, 0);
        }
    };

/*
    LeetCode 91 - Decode Ways
    ------------------------------------------------------------

    Approach:
    ------------------------------------------------------------

    We are given a string containing digits.

    Each valid encoding follows:

        '1' -> 'A'
        '2' -> 'B'
        ...
        '26' -> 'Z'

    Therefore, while decoding the string, at every position we have
    at most TWO choices:

        1. Take the current digit as a single character.
        2. Take the current digit together with the next digit as a
           two-digit number, if that number lies between 10 and 26.

    This naturally forms a recursion + memoization problem.

    The important DP idea is:

        solve(i) = number of valid ways to decode s[i ... n-1]


    ------------------------------------------------------------
    Key Observation:
    ------------------------------------------------------------

    At index i, we only need to decide how many digits to consume:

        One digit:
            s[i]

        Two digits:
            s[i], s[i+1]

    Once we choose one of these possibilities, the rest of the
    problem is independent and becomes the same problem starting
    at a later index.

    Therefore:

        solve(i)

    can be expressed using:

        solve(i + 1)

    and possibly:

        solve(i + 2)


    ------------------------------------------------------------
    DP State:
    ------------------------------------------------------------

        dp[i]

    represents:

        The number of valid ways to decode the substring
        s[i ... n-1].

    The recursive function:

        solve(s, i)

    calculates exactly this value.

    Once calculated, the answer is stored in:

        dp[i]

    so that the same state does not need to be solved again.


    ------------------------------------------------------------
    Example:
    ------------------------------------------------------------

    Consider:

        s = "226"

    We start at:

        i = 0

    The possible choices are:

        "2" + "26"

    or:

        "22" + "6"


    Therefore:

        "226"
          |
          +---- take "2" ----> solve(1)
          |
          +---- take "22" ---> solve(2)


    The two resulting decodings are:

        2 2 6
        22 6

    which correspond to:

        B B F
        V F

    Therefore the answer is:

        2


    ------------------------------------------------------------
    Base Case:
    ------------------------------------------------------------

        if(i == n) return 1;


    This is a very important base case.

    If:

        i == n

    then we have successfully consumed the entire string.

    That represents ONE complete valid decoding.

    Therefore we return:

        1


    ------------------------------------------------------------
    Why Return 1 Instead of 0?
    ------------------------------------------------------------

    Suppose we decode:

        "12"

    by taking the two-digit number:

        "12"

    We call:

        solve(2)

    Since:

        2 == n

    the decoding is complete.

    We need this path to contribute one valid decoding.

    Therefore:

        solve(n) = 1


    If we returned 0 instead, every successful decoding path would
    contribute zero to the answer.


    So:

        solve(n) = 1

    means:

        "There is exactly one valid way to decode an already-consumed
         string: do nothing more."


    ------------------------------------------------------------
    Handling '0':
    ------------------------------------------------------------

        if(s[i] == '0') return 0;


    This is another critical condition.

    A single '0' cannot be decoded.

    The valid mappings start from:

        1 -> A
        2 -> B
        ...
        9 -> I

    There is no:

        0 -> ?

    Therefore, if the current character is:

        '0'

    then there are ZERO valid decodings starting from this position.


    Example:

        s = "06"

    At:

        i = 0

    we see:

        s[0] = '0'

    Therefore:

        solve(0) = 0


    ------------------------------------------------------------
    Why "0" Can Still Be Valid as Part of Two Digits:
    ------------------------------------------------------------

    Although a single '0' is invalid, numbers such as:

        10
        20

    are valid.

    They represent:

        10 -> J
        20 -> T

    This is handled by the two-digit choice.

    For example:

        s = "10"

    At i = 0:

        s[0] = '1'

    So the one-digit choice is:

        "1"

    Then we reach:

        i = 1

    where s[1] is '0'.

    That path becomes invalid.

    But we also have the two-digit number:

        10

    which is valid.

    Therefore the string has exactly one decoding.


    ------------------------------------------------------------
    Memoization:
    ------------------------------------------------------------

        if(dp[i] != -1) return dp[i];


    Without memoization, the recursion would repeatedly calculate
    the same suffix.

    For example, in:

        "226"

    both choices from the beginning may eventually reach the same
    index.

    More generally, many different decoding paths can reach the
    same position i.

    But once we know:

        solve(i)

    the answer for that suffix never changes.

    Therefore we store it:

        dp[i] = answer


    ------------------------------------------------------------
    Choice 1: Take One Digit
    ------------------------------------------------------------

        int ans = solve(s, i + 1);


    Since we already checked:

        s[i] != '0'

    the current digit is a valid single-digit encoding.

    Therefore we can consume exactly one digit:

        s[i]

    and then solve the remaining suffix:

        s[i+1 ... n-1]

    Hence:

        one-digit choice = solve(i + 1)


    ------------------------------------------------------------
    Example:
    ------------------------------------------------------------

    Suppose:

        s = "123"

    At:

        i = 0

    we can take:

        "1"

    Then the remaining string is:

        "23"

    Therefore:

        solve(0)
            includes
        solve(1)


    ------------------------------------------------------------
    Choice 2: Take Two Digits
    ------------------------------------------------------------

        if(i + 1 < n) {

            int num =
                (s[i] - '0') * 10
                + (s[i + 1] - '0');

            if(num >= 10 && num <= 26)
                ans += solve(s, i + 2);
        }


    We can only take two digits if:

        i + 1 < n

    so that s[i+1] actually exists.


    We then convert the two characters into an integer.

    For example:

        s[i]     = '2'
        s[i+1]   = '6'

    Then:

        (2 * 10) + 6
        = 26


    ------------------------------------------------------------
    Why Check 10 <= num <= 26?
    ------------------------------------------------------------

    Only numbers from:

        10 through 26

    correspond to valid letters.

    Therefore:

        num >= 10 && num <= 26

    means the two digits can be treated as ONE character.


    Examples:

        10 -> J       valid
        11 -> K       valid
        12 -> L       valid
        ...
        25 -> Y       valid
        26 -> Z       valid


    But:

        27 -> invalid
        30 -> invalid
        99 -> invalid


    Therefore, if the two-digit number is outside [10,26], we
    cannot take both digits together.


    ------------------------------------------------------------
    Why num >= 10 Automatically Handles Leading Zero:
    ------------------------------------------------------------

    Consider:

        s = "06"

    The two-digit number would be:

        06

    Numerically:

        6

    Therefore:

        num = 6

    and:

        num >= 10

    is false.

    So "06" is not considered a valid two-digit encoding.

    This correctly prevents leading-zero combinations.


    ------------------------------------------------------------
    Important Example: "10"
    ------------------------------------------------------------

    Consider:

        s = "10"

    At:

        i = 0

    We first take one digit:

        "1"

    which calls:

        solve(1)

    But:

        s[1] = '0'

    so:

        solve(1) = 0


    Then we check the two-digit number:

        num = 10

    Since:

        10 >= 10
        10 <= 26

    it is valid.

    Therefore:

        ans += solve(2)

    and:

        solve(2) = 1


    So:

        solve(0) = 0 + 1 = 1


    There is exactly one valid decoding:

        "10" -> J


    ------------------------------------------------------------
    Important Example: "27"
    ------------------------------------------------------------

    Consider:

        s = "27"

    At i = 0:

    One digit:

        "2"

    is valid, so:

        solve(1)


    Two digits:

        "27"

    are NOT valid because:

        27 > 26


    Therefore we cannot use:

        solve(2)


    The only valid decoding is:

        "2" + "7"


    So the answer is:

        1


    ------------------------------------------------------------
    Important Example: "226"
    ------------------------------------------------------------

    Start:

        solve(0)

    Choices:

        "2" + solve(1)

        "22" + solve(2)


    From "26":

        "2" + "6"

        "26"


    Therefore the recursion represents:

        226
        |
        +-- 2 + 26
        |
        +-- 22 + 6


    Valid decodings:

        2 2 6
        22 6

    Answer:

        2


    ------------------------------------------------------------
    Recursion Tree:
    ------------------------------------------------------------

    For:

        s = "226"


                    solve(0)
                   /        \
                "2"          "22"
                 |             |
              solve(1)      solve(2)
              /     \        /    \
           "2"      "22"   "6"    ...
             |        |      |
          solve(2) solve(3) solve(3)
             |        |       |
            ...       1       1


    The exact duplicate states are handled by dp.

    For example:

        solve(2)

    may be reached from different decoding choices.

    We calculate it once and then reuse:

        dp[2]


    ------------------------------------------------------------
    Why the Recurrence Adds the Two Choices:
    ------------------------------------------------------------

    Suppose both choices are valid.

    Every valid decoding beginning at i must do EXACTLY one of:

        1. Consume one digit
        2. Consume two digits

    These two groups of decodings are mutually exclusive because
    they consume a different number of characters first.

    Therefore:

        total ways
            =
        ways after taking 1 digit
            +
        ways after taking 2 digits


    Hence:

        ans =
            solve(i + 1)
            +
            solve(i + 2)


    when the two-digit number is valid.


    ------------------------------------------------------------
    Why We Don't Try Three Digits:
    ------------------------------------------------------------

    Every letter is represented by either:

        1 digit: 1-9

    or:

        2 digits: 10-26

    No valid encoding contains three digits.

    Therefore, at each position there are at most two choices.


    ------------------------------------------------------------
    DP Recurrence:
    ------------------------------------------------------------

    For every index i:

        If i == n:

            dp state is complete
            return 1


        If s[i] == '0':

            no valid decoding
            return 0


        Otherwise:

            dp[i] = solve(i + 1)

            If s[i..i+1] forms a number between 10 and 26:

                dp[i] += solve(i + 2)


    In mathematical form:

        dp[i] =
            dp[i+1]
            +
            dp[i+2]   if 10 <= value(s[i..i+1]) <= 26

    Otherwise:

        dp[i] = dp[i+1]


    ------------------------------------------------------------
    Why Memoization Makes It Efficient:
    ------------------------------------------------------------

    There are only n possible states:

        solve(0)
        solve(1)
        solve(2)
        ...
        solve(n-1)

    Each state is calculated at most once.

    After that:

        dp[i] != -1

    and the stored value is returned immediately.


    Therefore, although the recursion has branching, the total
    number of actual states is only O(n).


    ------------------------------------------------------------
    Example of Repeated State:
    ------------------------------------------------------------

    In:

        s = "1111"

    many different decoding choices can eventually reach the
    same index.

    For example:

        solve(2)

    may be reached by:

        "1" + "1" + ...

    or:

        "11" + ...

    Instead of recalculating the number of ways from index 2,
    the first calculation stores:

        dp[2]

    Every later call simply returns:

        dp[2]


    ------------------------------------------------------------
    Why the Answer Is solve(0):
    ------------------------------------------------------------

    The original problem asks for the number of ways to decode
    the ENTIRE string.

    The entire string starts at index:

        0

    Therefore:

        solve(s, 0)

    represents exactly:

        Number of ways to decode s[0 ... n-1]


    The public function initializes the DP array:

        dp.assign(n, -1);

    and starts the recursion:

        return solve(s, 0);


    ------------------------------------------------------------
    Complexity:
    ------------------------------------------------------------

    Let:

        n = s.size()


    Number of DP states:

        O(n)


    Each state performs only constant work:

        - Check for '0'
        - One recursive call
        - At most one additional recursive call
        - Constant arithmetic


    Therefore:

        Time Complexity = O(n)


    ------------------------------------------------------------
    Space Complexity:
    ------------------------------------------------------------

    The memoization array:

        dp

    uses:

        O(n)


    The recursion can go as deep as:

        O(n)


    Therefore total auxiliary space is:

        O(n)


    ------------------------------------------------------------
    Core Idea:
    ------------------------------------------------------------

    At every index, decide:

        Take 1 digit
            OR
        Take 2 digits if they form a number from 10 to 26


    Then recursively count the valid ways for the remaining suffix.

    Memoization ensures every index is solved only once.


    ------------------------------------------------------------
    Main Takeaway:
    ------------------------------------------------------------

    The most important DP state is:

        solve(i)
        =
        number of ways to decode s[i ... n-1]


    From each valid non-zero position:

        One-digit choice:
            solve(i + 1)

        Two-digit choice:
            solve(i + 2)
            only when the two-digit number is in [10, 26]


    The recurrence is therefore:

        solve(i)
            =
        solve(i + 1)
        +
        solve(i + 2)   if valid two-digit number


    The two critical edge cases are:

        s[i] == '0'
            -> 0 ways

        i == n
            -> 1 completed decoding


    With memoization, the recursive solution runs in:

        O(n) time
        O(n) space
*/