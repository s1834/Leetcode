class Solution {
    private:
        int n, maxLen;
        unordered_set<string> st;
    
        void solve(string& s, int i, string& curr, int count) {
            if(count < 0) return;
    
            if(i == n) {
                if (count == 0) {
                    if(curr.size() > maxLen) {
                        st.clear();
                        maxLen = curr.size();
                    }
    
                    if(curr.size() == maxLen) st.insert(curr);
                }
                return;
            }
    
            curr.push_back(s[i]);
    
            // alphabet
            if(s[i] != '(' && s[i] != ')') {
                solve(s, i + 1, curr, count);
                curr.pop_back();
                return;
            }
    
            solve(s, i + 1, curr, count + (s[i] == '(' ? 1 : -1));  // Keep parentheses
            curr.pop_back();
            solve(s, i + 1, curr, count); // skip parentheses
            return;
        }
    
    public:
        vector<string> removeInvalidParentheses(string s) {
            n = s.size();
            maxLen = 0;
            st.clear();
            string curr = "";
            
            solve(s, 0, curr, 0);
    
            return vector<string>(st.begin(), st.end());
        }
    };

/*
    ============================================================
    LeetCode 301 - Remove Invalid Parentheses
    ============================================================

    Approach: Backtracking + DFS
    ------------------------------------------------------------

    We need to remove the minimum number of parentheses so that
    the resulting string becomes valid.

    Among all valid results, we need to return every DISTINCT
    string having the maximum possible length.

    This solution explores all possible choices of keeping or
    removing parentheses.

    Important observation:

        We never remove alphabetic characters.

    Only '(' and ')' can be either kept or skipped.

    The recursion keeps track of:

        i       -> current position in the string
        curr    -> string constructed so far
        count   -> current parenthesis balance
        maxLen  -> maximum valid length found so far
        st      -> all distinct valid strings having maxLen

    ============================================================
    1. Meaning of `count`
    ============================================================

    `count` represents the current balance of parentheses:

        '(' -> count + 1
        ')' -> count - 1

    A valid parentheses string must satisfy:

        count >= 0

    throughout the string.

    And after processing the entire string:

        count == 0

    must hold.

    Example:

        "(())"

        '(' -> count = 1
        '(' -> count = 2
        ')' -> count = 1
        ')' -> count = 0

    This is valid.

    But:

        "())"

        '(' -> count = 1
        ')' -> count = 0
        ')' -> count = -1

    Once count becomes negative, the current construction can
    never become valid by adding more characters after it.

    Therefore:

        if(count < 0) return;

    immediately prunes that branch.

    ============================================================
    2. Base Case
    ============================================================

    When:

        i == n

    every character has been considered.

    The constructed string is valid only when:

        count == 0

    If count is not zero, there are unmatched '(' remaining,
    so this string cannot be used.

    Therefore:

        if(count == 0)

    we have found a valid candidate.

    ============================================================
    3. Keeping Alphabetic Characters
    ============================================================

    If the current character is not a parenthesis:

        if(s[i] != '(' && s[i] != ')')

    it cannot make the string invalid and there is no reason
    to remove it.

    So we always keep it:

        curr.push_back(s[i]);

        solve(s, i + 1, curr, count);

        curr.pop_back();

    Notice that there is no "skip" branch for alphabetic
    characters.

    This is important because the problem only allows removing
    parentheses.

    ============================================================
    4. Keeping a Parenthesis
    ============================================================

    For '(':

        count + 1

    For ')':

        count - 1

    The code handles both cases with:

        count + (s[i] == '(' ? 1 : -1)

    So when we choose to KEEP the current parenthesis:

        solve(
            s,
            i + 1,
            curr,
            count + (s[i] == '(' ? 1 : -1)
        );

    This explores the possibility that this parenthesis belongs
    to the final valid string.

    ============================================================
    5. Removing a Parenthesis
    ============================================================

    Every parenthesis also has another possibility:

        skip it.

    Therefore:

        solve(s, i + 1, curr, count);

    explores the case where the current parenthesis is removed.

    This gives two choices for every parenthesis:

        KEEP
          |
          +--> update balance

        REMOVE
          |
          +--> balance remains unchanged

    The DFS explores all possible valid combinations.

    ============================================================
    6. Why `curr.pop_back()` Is Required
    ============================================================

    Before exploring the keep branch:

        curr.push_back(s[i]);

    After that recursive call returns, we must undo this
    modification before exploring another possibility.

        curr.pop_back();

    This is standard backtracking.

    For example:

        curr = "a"

    We choose to keep '(':

        curr = "a("

    After exploring that branch, we restore:

        curr = "a"

    so the next branch starts from the correct state.

    ============================================================
    7. Finding the Maximum Length
    ============================================================

    The problem asks us to remove the MINIMUM number of
    parentheses.

    Since alphabetic characters are always kept, minimizing
    removals is equivalent to maximizing the length of the
    resulting valid string.

    Therefore, when a valid string is found:

        curr.size()

    is compared with:

        maxLen

    ------------------------------------------------------------
    Case 1: A Longer Valid String Is Found
    ------------------------------------------------------------

        if(curr.size() > maxLen)

    We found a better answer.

    Therefore:

        st.clear();
        maxLen = curr.size();

    All previously stored answers were shorter and therefore
    required more removals.

    They are no longer relevant.

    Then the current string is inserted.

    ------------------------------------------------------------
    Case 2: Same Maximum Length
    ------------------------------------------------------------

    If:

        curr.size() == maxLen

    this is another valid answer requiring the same minimum
    number of removals.

    We insert it into:

        st

    ============================================================
    8. Why Use `unordered_set<string>`?
    ============================================================

    Different removal choices can produce the same resulting
    string.

    Example:

        Multiple identical parentheses may be removed in
        different ways but produce the same final string.

    We only want DISTINCT answers.

    Therefore:

        unordered_set<string> st;

    automatically removes duplicate results.

    ============================================================
    9. Example
    ============================================================

    Consider:

        s = "()())()"

    The recursion explores different choices of keeping or
    removing parentheses.

    Some branches may produce:

        "()()()"
        "(())()"
        "()())("
        ...

    Only valid strings with the maximum length are retained.

    Suppose the longest valid length is 6.

    Then:

        maxLen = 6

    and the set contains only valid strings of length 6, such as:

        "()()()"
        "(())()"

    Any valid string shorter than length 6 is discarded because
    it would require more removals.

    ============================================================
    10. Why Maximizing Length Gives Minimum Removals
    ============================================================

    The original string has fixed length `n`.

    If the resulting valid string has length `L`, then the
    number of removed characters is:

        n - L

    Therefore:

        fewer removals <=> larger L

    So instead of explicitly minimizing the number of removals,
    the solution simply maximizes the length of a valid result.

    ============================================================
    11. Overall DFS Structure
    ============================================================

    For every character:

        Alphabet:
            KEEP only

        Parenthesis:
            KEEP
                -> update balance

            REMOVE
                -> balance unchanged

    At every state:

        count < 0
            -> prune

        i == n
            -> accept only if count == 0

    For every valid result:

        longer than maxLen
            -> clear old answers and store it

        equal to maxLen
            -> store it as another answer

    ============================================================
    12. Correctness Intuition
    ============================================================

    The DFS considers every possible decision for every
    parenthesis: either keep it or remove it.

    Therefore, every possible string obtainable by removing
    parentheses is represented by some recursion path.

    A branch is discarded when `count < 0` because a closing
    parenthesis has appeared without enough opening parentheses
    before it. Such a branch can never become valid.

    At the end, only strings with:

        count == 0

    are accepted, guaranteeing balanced parentheses.

    Among all valid strings, `maxLen` keeps only those with the
    maximum length.

    Since maximum length means minimum removals, all stored
    strings are optimal.

    The unordered set ensures that each optimal string appears
    only once.

    ============================================================
    Complexity Analysis
    ============================================================

    Let n be the length of the string.

    Time Complexity:

        In the worst case, every parenthesis can either be kept
        or removed, resulting in up to O(2^n) recursive states.

        Additionally, constructing/copying strings and storing
        results can add extra costs.

        Therefore, the overall worst-case complexity is
        exponential.

    Space Complexity:

        O(n) recursion depth and O(n) space for the current
        string.

        In addition, the set may store many distinct valid
        strings, so the total result storage can also be
        exponential in the worst case.

    ============================================================
    Core Idea
    ============================================================

    Backtrack over every parenthesis:

        KEEP it
            -> update balance

        REMOVE it
            -> balance stays unchanged

    Prune immediately when:

        count < 0

    At the end, accept only:

        count == 0

    Among all valid strings:

        longer string -> fewer removals

    So maintain the maximum valid length and store every
    distinct valid string having that length.

    This directly gives all valid strings obtained using the
    minimum number of removals.
    ============================================================
*/