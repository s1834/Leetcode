class Solution {
    private:
        int n;
        unordered_set<string> st;
        vector<int> dp; 
    
    
        bool solve(string &s, int i) {
            if(i >= n) return 1;
            if(dp[i] != -1) return dp[i];
    
            for(int j = i; j < n; j++) {
                string tempWord = s.substr(i, j - i + 1);
                if(st.count(tempWord)) { // valid word
                    if(solve(s, j + 1)) return dp[i] = 1;
                }
            }
    
            return dp[i] = 0;
        }
    
    public:
        bool wordBreak(string s, vector<string>& wordDict) {
            n = s.size();
            dp.assign(n, -1);
            for(auto x : wordDict) st.insert(x);
            return solve(s, 0);  
        }
    };

/*
    ============================================================
    LeetCode 139 - Word Break
    ============================================================

    Approach: Recursion + Memoization (Top-Down DP)
    ------------------------------------------------------------

    We are given a string `s` and a dictionary of words.

    The goal is to determine whether `s` can be segmented into
    one or more dictionary words.

    Each word used in the segmentation must exist in `wordDict`,
    and the words must appear in their original order to form
    the complete string.

    We use:
        st -> An unordered_set containing dictionary words.
        dp[i] -> Whether the suffix s[i ... n-1] can be segmented
                 into valid dictionary words.

    The function solve(s, i) answers:

        Can the substring s[i ... n-1] be segmented successfully?


    ============================================================
    1. Base Case
    ============================================================

    if(i >= n) return 1;

    If i reaches or exceeds the string length, we have
    successfully segmented the entire string.

    This means every character has been covered by valid words,
    so we return true.

    Example:

        s = "leetcode"

        "leet" + "code"

        After finding both dictionary words, the recursive call
        reaches i = n, indicating a successful segmentation.


    ============================================================
    2. Memoization
    ============================================================

    if(dp[i] != -1) return dp[i];

    `dp[i]` stores whether the suffix starting at index i
    can be segmented into valid dictionary words.

        dp[i] =  1 -> Segmentation is possible.
        dp[i] =  0 -> Segmentation is not possible.
        dp[i] = -1 -> State has not been computed yet.

    Different recursive paths may reach the same index i.

    Instead of solving the same suffix repeatedly, we return
    its previously computed result.

    Since the answer depends only on the current index,
    a one-dimensional DP array is sufficient.


    ============================================================
    3. Generate Every Possible Prefix Word
    ============================================================

    for(int j = i; j < n; j++)

    We fix the starting index i and move j from i to n - 1.

    At every position j, we consider the substring:

        s.substr(i, j - i + 1)

    This generates every possible non-empty prefix of the
    remaining suffix s[i ... n-1].

    Example:

        s = "apple"
        i = 0

    The generated substrings are:

        "a"
        "ap"
        "app"
        "appl"
        "apple"

    Each substring is considered as a possible dictionary word.

    The expression:

        j - i + 1

    gives the length of the substring because both endpoints
    i and j are included.


    ============================================================
    4. Check Whether the Substring Is a Dictionary Word
    ============================================================

    if(st.count(tempWord))

    The unordered_set `st` contains all words from `wordDict`.

    `st.count(tempWord)` returns 1 if the word exists and 0
    otherwise.

    Using an unordered_set allows efficient average-case
    dictionary lookups.

    If the substring is not present in the dictionary, we
    cannot use it as the next word, so we continue extending
    the substring by moving j forward.

    If it is present, we have found a valid word beginning
    at index i.


    ============================================================
    5. Recursive Transition
    ============================================================

    if(solve(s, j + 1))
        return dp[i] = 1;

    Once s[i ... j] is found in the dictionary, we have
    successfully segmented the prefix:

        s[i ... j]

    The remaining string starts at:

        j + 1

    We recursively check whether this remaining suffix can
    also be segmented into valid dictionary words.

    For the complete string to be valid, BOTH conditions
    must hold:

        1. s[i ... j] is a dictionary word.
        2. s[j + 1 ... n-1] can be segmented successfully.

    If the recursive call returns true, we have found a
    complete valid segmentation.

    Therefore, we store and return:

        dp[i] = 1

    We can return immediately because the problem asks only
    whether a valid segmentation exists, not how many
    segmentations are possible.


    ============================================================
    6. What Happens If No Segmentation Works?
    ============================================================

    If none of the substrings starting at i leads to a
    successful recursive call, then the suffix starting at i
    cannot be segmented.

        return dp[i] = 0;

    This result is memoized so that future calls to solve(s, i)
    do not repeat the same search.


    ============================================================
    7. Example Walkthrough
    ============================================================

    Input:

        s = "leetcode"

        wordDict = ["leet", "code"]

    Initial call:

        solve(s, 0)

    Step 1:
        Generate substrings starting at index 0.

        "l", "le", "lee", "leet", ...

        When tempWord = "leet", it exists in the dictionary.

        Recursively call:

            solve(s, 4)

    Step 2:
        Generate substrings starting at index 4.

        "c", "co", "cod", "code"

        When tempWord = "code", it exists in the dictionary.

        Recursively call:

            solve(s, 8)

    Step 3:
        Since n = 8:

            if(i >= n) return 1;

        The entire string has been segmented successfully.

    The true result propagates back through both recursive calls.

    Final answer:

        true

    Valid segmentation:

        "leet" + "code"


    ============================================================
    8. Why Memoization Is Necessary
    ============================================================

    Consider:

        s = "aaaaaaa"

        wordDict = ["a", "aa", "aaa"]

    There can be many ways to divide the string into prefixes.

    Multiple combinations may eventually reach the same index.

    Without memoization, the algorithm can repeatedly explore
    the same suffix through different combinations of words.

    With memoization, each index i is fully computed at most
    once, and subsequent calls reuse dp[i].

    This avoids repeatedly solving identical subproblems.


    ============================================================
    9. Correctness Intuition
    ============================================================

    At every index i, the algorithm tries every possible
    non-empty prefix beginning at i.

    For each prefix that belongs to the dictionary, it checks
    whether the remaining suffix can also be segmented.

    If any such choice leads to the end of the string, the
    entire suffix starting at i can be segmented.

    If every valid dictionary prefix fails, no valid
    segmentation exists from index i.

    Memoization stores this result without changing the logic.

    Therefore, solve(s, 0) correctly determines whether the
    entire string can be segmented using dictionary words.


    ============================================================
    10. Complexity Analysis
    ============================================================

    Let n be the length of the string.

    Time Complexity: O(n^3) worst case

        There are O(n) DP states.

        For each state, the loop considers O(n) substrings.
        Creating each substring using substr() can take O(n)
        time in the worst case.

        Therefore, the total worst-case time complexity is
        O(n^3), excluding dictionary construction.

    Space Complexity: O(n^2) worst case

        DP array:
            O(n)

        Recursion stack:
            O(n)

        Dictionary set:
            Depends on the total size of the dictionary.

        The generated substrings can temporarily require O(n)
        space each, with O(n) peak temporary substring storage.

        The DP and recursion stack themselves use O(n) space.


    ============================================================
    Core Idea
    ============================================================

    At every index i:

        1. Try every possible prefix s[i ... j].
        2. Check whether it exists in the dictionary.
        3. If valid, recursively solve the remaining suffix
           starting at j + 1.
        4. If any choice succeeds, return true.
        5. If all choices fail, return false.

    dp[i] memoizes whether the suffix starting at i can be
    segmented, preventing repeated computation of the same
    subproblem.

    The final answer is:

        solve(s, 0)
    ============================================================
*/