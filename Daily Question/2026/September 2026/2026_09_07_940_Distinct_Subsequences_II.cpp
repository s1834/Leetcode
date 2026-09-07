class Solution {
    private:
        int MOD = 1e9 + 7;
        int dp[2001];
        vector<int> prev; // prev[n] = last time when we saw this nth character (1-based indexing)
    
        int solve(int n) {
            if(n == 0) return 1;
    
            if(dp[n] != -1) return dp[n];
    
            int total = (2 * solve(n - 1)) % MOD;
    
            if(prev[n] != 0) {
                int duplicates = solve(prev[n] - 1);
                total = (total - duplicates + MOD) % MOD;
            }
    
            return dp[n] = total;
        }
    
    public:
        int distinctSubseqII(string s) {
            int n = s.size();
            memset(dp, -1, sizeof(dp));
            prev.assign(n + 1, 0);
    
            vector<int> lastSeen(26, 0);
            for(int i = 1; i <= n; i++) {
                int idx = s[i - 1] - 'a';
                prev[i] = lastSeen[idx];
                lastSeen[idx] = i;
            }
    
            return (solve(n) - 1 + MOD) % MOD;
        }
    };

/*
    Approach:
    ------------------------------------------------------------
    We need to count the number of DISTINCT non-empty subsequences
    of the string.

    A subsequence is formed by choosing some characters while
    keeping their original order.

    The important difficulty is that different choices of indices
    can produce the same subsequence string.

    For example:

        s = "aaa"

    The index selections can produce:

        "a"  -> from index 1, 2, or 3
        "aa" -> from (1,2), (1,3), or (2,3)
        "aaa" -> from (1,2,3)

    But the distinct subsequences are only:

        "a", "aa", "aaa"

    So we cannot simply count all subsequences as 2^n - 1.



    ------------------------------------------------------------
    Key Observation:
    ------------------------------------------------------------

    Let:

        solve(n) = number of distinct subsequences
                   that can be formed using s[0 ... n-1]

    We include the empty subsequence in this count.

    Suppose we already know the distinct subsequences using the
    first n-1 characters.

    For the new character s[n-1], every existing subsequence can
    either:

        1. NOT use s[n-1]
        2. USE s[n-1]

    Therefore, initially:

        solve(n) = 2 * solve(n-1)

    because every old distinct subsequence creates one new
    subsequence by appending the current character.

    However, this can create duplicates if the current character
    has appeared before.

    The purpose of the `prev` array is to identify exactly where
    that character appeared previously so that those duplicates
    can be removed.



    ------------------------------------------------------------
    DP State:
    ------------------------------------------------------------

        dp[n]

    represents:

        The number of distinct subsequences of the prefix
        s[0 ... n-1], INCLUDING the empty subsequence.

    Therefore:

        dp[0] = 1

    because the empty string is the only subsequence of an empty
    string.



    ------------------------------------------------------------
    Why do we start with 2 * solve(n - 1)?
    ------------------------------------------------------------

    Suppose:

        s = "ab"

    After processing "a":

        ""
        "a"

    So:

        solve(1) = 2

    Now process 'b'.

    Every existing subsequence can be:

        not followed by 'b':
            ""
            "a"

        followed by 'b':
            "b"
            "ab"

    Therefore:

        ""
        "a"
        "b"
        "ab"

    giving:

        solve(2) = 4

    Since 'b' has never appeared before, there are no duplicates
    to remove.



    ------------------------------------------------------------
    What goes wrong when a character appears again?
    ------------------------------------------------------------

    Consider:

        s = "aa"

    After the first 'a':

        ""
        "a"

    So:

        solve(1) = 2

    Now process the second 'a'.

    Doubling gives:

        ""
        "a"

    and by appending the new 'a':

        "a"
        "aa"

    So we temporarily have:

        ""
        "a"
        "a"
        "aa"

    But the two copies of "a" are identical.

    Therefore:

        solve(2) = 4 - 1 = 3

    The distinct subsequences are:

        ""
        "a"
        "aa"



    ------------------------------------------------------------
    What does prev[n] store?
    ------------------------------------------------------------

    `prev[n]` stores the previous position where the same
    character as s[n-1] was seen.

    The code uses 1-based indexing for positions.

    For example:

        s = "abca"

    Positions:

        1 -> a
        2 -> b
        3 -> c
        4 -> a

    Then:

        prev[1] = 0
        prev[2] = 0
        prev[3] = 0
        prev[4] = 1

    because the 'a' at position 4 was previously seen at
    position 1.



    ------------------------------------------------------------
    Building prev[]:
    ------------------------------------------------------------

    `lastSeen` stores the latest position of every character.

    For every position i:

        idx = s[i - 1] - 'a'

    `prev[i]` receives the previous occurrence of that character.

    Then:

        lastSeen[idx] = i

    updates the latest occurrence.

    Example:

        s = "abca"

        i = 1:
            character = 'a'
            lastSeen['a'] = 0

            prev[1] = 0
            lastSeen['a'] = 1

        i = 2:
            character = 'b'

            prev[2] = 0
            lastSeen['b'] = 2

        i = 3:
            character = 'c'

            prev[3] = 0
            lastSeen['c'] = 3

        i = 4:
            character = 'a'

            previous 'a' was at position 1

            prev[4] = 1
            lastSeen['a'] = 4



    ------------------------------------------------------------
    Duplicate Removal:
    ------------------------------------------------------------

    Suppose:

        prev[n] = p

    meaning the current character appeared previously at position p.

    We initially calculate:

        total = 2 * solve(n - 1)

    But some of those newly created subsequences are duplicates
    of subsequences that were already created when the previous
    occurrence of this character was processed.

    The duplicated group corresponds exactly to:

        solve(p - 1)

    subsequences formed using the characters before that previous
    occurrence.

    Therefore we subtract:

        solve(prev[n] - 1)

    giving:

        solve(n)
            = 2 * solve(n - 1)
              - solve(prev[n] - 1)



    ------------------------------------------------------------
    Why solve(prev[n] - 1)?
    ------------------------------------------------------------

    Suppose:

        s = "aba"

    We are processing the final 'a'.

    The previous 'a' occurred at position:

        p = 1

    Before that previous 'a', there are:

        p - 1 = 0

    characters.

    The subsequences that can be duplicated are exactly the
    subsequences that existed before that earlier 'a'.

    Therefore:

        duplicates = solve(p - 1)



    A slightly larger example:

        s = "abca"

    Current 'a' is at position 4.

    Previous 'a' was at position 1.

    So:

        prev[4] = 1

    and:

        duplicates = solve(0)

    which is just:

        ""

    Appending the current 'a' to it gives:

        "a"

    and that "a" was already created using the previous 'a'.

    Hence we remove it once.



    ------------------------------------------------------------
    Example: s = "aaa"
    ------------------------------------------------------------

    Positions:

        1 -> a
        2 -> a
        3 -> a

    Therefore:

        prev[1] = 0
        prev[2] = 1
        prev[3] = 2



    For n = 0:

        solve(0) = 1

    Subsequences:

        ""



    For n = 1:

        total = 2 * solve(0)
              = 2

        prev[1] = 0

        solve(1) = 2

    Subsequences:

        ""
        "a"



    For n = 2:

        total = 2 * solve(1)
              = 4

        prev[2] = 1

        duplicates = solve(0)
                   = 1

        solve(2) = 4 - 1
                 = 3

    Subsequences:

        ""
        "a"
        "aa"



    For n = 3:

        total = 2 * solve(2)
              = 6

        prev[3] = 2

        duplicates = solve(1)
                   = 2

        solve(3) = 6 - 2
                 = 4

    Subsequences:

        ""
        "a"
        "aa"
        "aaa"



    Finally, the problem asks for NON-EMPTY subsequences.

    Since solve(n) includes the empty subsequence:

        answer = solve(n) - 1



    ------------------------------------------------------------
    Why subtracting solve(prev[n] - 1) removes exactly the
    duplicates:
    ------------------------------------------------------------

    Consider the current character c.

    When c is processed for the first time, appending c to every
    existing subsequence creates a new family of subsequences.

    When c appears again, some of the subsequences created by
    appending the new c are not actually new strings.

    They are exactly the strings that could already be formed by
    appending the previous occurrence of c to subsequences that
    existed before that previous occurrence.

    The number of those prefix subsequences is:

        solve(prev[n] - 1)

    Therefore subtracting that quantity removes each duplicated
    distinct subsequence exactly once.



    ------------------------------------------------------------
    Recurrence:
    ------------------------------------------------------------

    If the current character has never appeared before:

        dp[n] = 2 * dp[n - 1]

    If it appeared previously at position prev[n]:

        dp[n] = 2 * dp[n - 1]
                - dp[prev[n] - 1]

    All calculations are performed modulo:

        1,000,000,007



    ------------------------------------------------------------
    Why MOD is handled this way:
    ------------------------------------------------------------

    The subtraction can become negative after taking modulo.

    Therefore the code uses:

        (total - duplicates + MOD) % MOD

    Adding MOD first guarantees that the value is non-negative
    before applying `% MOD`.



    ------------------------------------------------------------
    Role of the `dp` array:
    ------------------------------------------------------------

    The recursion can reach the same state multiple times.

    For example, several duplicate-removal calculations may ask
    for:

        solve(x)

    again.

    Instead of recalculating the entire recursion tree, the result
    is stored in:

        dp[x]

    Once computed:

        if(dp[n] != -1)
            return dp[n];

    immediately returns the saved result.

    Therefore this is TOP-DOWN DP / MEMOIZATION.



    ------------------------------------------------------------
    Algorithm:
    ------------------------------------------------------------

    1. Initialize `dp` with -1.

    2. Build `prev[]`:
       - `lastSeen[c]` stores the most recent position of character c.
       - For every position i, store the previous occurrence in
         `prev[i]`.
       - Update `lastSeen`.

    3. Call:

           solve(n)

       where n is the length of the string.

    4. Inside `solve(n)`:
       - Base case:
             solve(0) = 1
       - Start with:
             2 * solve(n - 1)
       - If the current character appeared before, subtract:
             solve(prev[n] - 1)
       - Memoize and return the result.

    5. Remove the empty subsequence:

           solve(n) - 1



    ------------------------------------------------------------
    Important Indexing Detail:
    ------------------------------------------------------------

    The string itself is 0-indexed:

        s[0], s[1], ..., s[n-1]

    But `prev` uses 1-based positions:

        prev[1], prev[2], ..., prev[n]

    So:

        position i in prev
        corresponds to
        character s[i - 1]

    This is why the code uses:

        int idx = s[i - 1] - 'a';



    ------------------------------------------------------------
    Example: s = "aba"
    ------------------------------------------------------------

    The distinct subsequences are:

        ""
        "a"
        "b"
        "ab"
        "aa"
        "ba"
        "aba"

    So there are 7 including the empty subsequence.

    The answer is:

        7 - 1 = 6



    The recurrence gives:

        solve(0) = 1

        solve(1):
            2 * 1 = 2

        solve(2):
            2 * 2 = 4

        solve(3):
            2 * 4 - solve(0)
            = 8 - 1
            = 7

    Therefore:

        answer = 7 - 1 = 6



    ------------------------------------------------------------
    Why This Works:
    ------------------------------------------------------------

    Every subsequence of the first n-1 characters has exactly two
    possibilities when the new character is considered:

        - keep it unchanged
        - append the new character

    Thus doubling accounts for every possible choice involving
    the new character.

    The only issue is that repeated characters can cause two
    different index selections to produce the same subsequence.

    `prev[n]` identifies the previous occurrence of the same
    character, and:

        solve(prev[n] - 1)

    counts exactly the earlier subsequences whose versions with
    the previous occurrence have already been generated.

    Removing those duplicates leaves every distinct subsequence
    counted exactly once.

    Finally, removing the empty subsequence gives the required
    number of distinct non-empty subsequences.



    ------------------------------------------------------------
    Correctness Intuition:
    ------------------------------------------------------------

    At every position n:

        2 * solve(n - 1)

    considers all subsequences without and with the current
    character.

    If the character is new, no duplicate can be created, so the
    doubled count is correct.

    If the character has appeared before, the only duplicate
    subsequences are those that could already have been generated
    using the previous occurrence. Their count is exactly:

        solve(prev[n] - 1)

    Subtracting them ensures that every distinct subsequence is
    counted once.

    By applying this argument for every character position, the
    final value `solve(n)` contains every distinct subsequence
    exactly once.

    Since the empty subsequence is always included, subtracting
    one produces the required answer.



    ------------------------------------------------------------
    Time Complexity:
    ------------------------------------------------------------

    Building `prev`:

        O(n)

    Number of DP states:

        O(n)

    Each state performs O(1) work apart from recursive calls, and
    memoization ensures every state is solved only once.

    Total:

        O(n)



    ------------------------------------------------------------
    Space Complexity:
    ------------------------------------------------------------

    DP array:

        O(n)

    prev array:

        O(n)

    lastSeen:

        O(26) = O(1)

    Recursion stack:

        O(n)

    Total:

        O(n)



    ------------------------------------------------------------
    Core Idea:
    ------------------------------------------------------------

    Count distinct subsequences by doubling the previous count
    whenever a new character is processed, then remove exactly the
    subsequences that became duplicates because the same character
    appeared before.

    The key recurrence is:

        dp[n] = 2 * dp[n - 1]

    and, for a repeated character:

        dp[n] -= dp[prev[n] - 1]

    Finally:

        answer = dp[n] - 1

    because `dp` intentionally includes the empty subsequence.
*/