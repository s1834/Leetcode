class Solution {
    public:
        int countConsistentStrings(string allowed, vector<string>& words) {
            set<char> s;
            for(auto& x: allowed) s.insert(x);
    
            int n = words.size(), ans = 0;
            for(int i = 0; i < n; i++) {
                bool flag = true;
                for(auto& x: words[i]) {
                    if(s.find(x) == s.end()) {
                        flag = false;
                        break;
                    }
                }
    
                if(flag) ans++;
            }
    
            return ans;
        }
    };

/*
    ============================================================
    LeetCode 1684 - Count the Number of Consistent Strings
    ============================================================

    Approach: Set + String Traversal
    ------------------------------------------------------------

    A string is called consistent if every character in that
    string exists in the given `allowed` string.

    The idea is simple:

        1. Store all characters from `allowed` in a set.
        2. Check every word in `words`.
        3. If any character of a word is not present in the set,
           that word is inconsistent.
        4. Otherwise, count it as a consistent string.

    ============================================================
    1. Store Allowed Characters
    ============================================================

    We create:

        set<char> s;

    and insert every character from `allowed`:

        for(auto& x: allowed)
            s.insert(x);

    The set now contains every character that can appear in
    a consistent word.

    Example:

        allowed = "ab"

        set:

            { 'a', 'b' }

    ============================================================
    2. Check Every Word
    ============================================================

    For every word, we initially assume that it is consistent:

        bool flag = true;

    Then we examine every character of that word.

        for(auto& x: words[i])

    For each character, we check:

        s.find(x) == s.end()

    If this condition is true, the character does not exist
    in `allowed`.

    Therefore, the word cannot be consistent.

        flag = false;
        break;

    We can immediately stop checking the current word because
    finding even one invalid character is enough to reject it.

    ============================================================
    3. Count Consistent Words
    ============================================================

    After checking all characters of a word:

        if(flag) ans++;

    If `flag` is still true, every character of the word was
    found in the allowed-character set.

    Therefore, the word is consistent and we increment `ans`.

    ============================================================
    4. Example
    ============================================================

    Suppose:

        allowed = "ab"

        words = ["ad", "bd", "aaab", "baa", "badab"]

    The set contains:

        { 'a', 'b' }

    Check each word:

        "ad"
            'a' -> allowed
            'd' -> not allowed
            -> inconsistent

        "bd"
            'b' -> allowed
            'd' -> not allowed
            -> inconsistent

        "aaab"
            all characters are allowed
            -> consistent

        "baa"
            all characters are allowed
            -> consistent

        "badab"
            contains 'd'
            -> inconsistent

    Therefore:

        ans = 2

    ============================================================
    5. Why Does This Work?
    ============================================================

    A word is consistent exactly when EVERY character in it
    belongs to `allowed`.

    The set gives us a direct way to test whether a character
    is allowed.

    For each word:

        If even one character is missing from the set:
            the word is invalid.

        If every character is found:
            the word is valid.

    Thus, every word is classified correctly and counted once.

    ============================================================
    Complexity Analysis
    ============================================================

    Let:

        A = length of `allowed`
        L = total number of characters across all words

    Building the set takes:

        O(A log A)

    because `set` is implemented as an ordered tree.

    Checking all words performs one lookup for every character.

    Each lookup in `set` takes:

        O(log A)

    Therefore:

        Time: O(A log A + L log A)

    Space:

        O(A)

    for storing the distinct allowed characters in the set.

    ============================================================
    Core Idea
    ============================================================

    Store every allowed character in a set.

    For each word:

        - Check every character.
        - If a character is not in the set, reject the word.
        - Otherwise, count the word.

    A word is consistent if and only if all of its characters
    belong to the allowed-character set.
    ============================================================
*/