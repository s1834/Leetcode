class Solution {
    public:
        string reversePrefix(string s, int k) {
            reverse(s.begin(), s.begin() + k);
            return s;
        }
    };

/*
    ============================================================
    LeetCode 3794 - Reverse Prefix
    ============================================================

    Approach: In-place Prefix Reversal
    ------------------------------------------------------------

    We need to reverse the first `k` characters of the string
    while keeping the remaining characters unchanged.

    The C++ `reverse()` function can directly reverse a range
    of elements.

    ============================================================
    1. Reverse the First k Characters
    ============================================================

    The code uses:

        reverse(s.begin(), s.begin() + k);

    `s.begin()` points to the first character.

    `s.begin() + k` points to the position immediately AFTER
    the first `k` characters.

    The range used by `reverse()` is:

        [s.begin(), s.begin() + k)

    Since the right endpoint is exclusive, exactly the first
    `k` characters are reversed.

    Example:

        s = "abcdef"
        k = 3

    The selected range is:

        "abc"

    After reversing:

        "cba"

    The remaining part:

        "def"

    stays unchanged.

    Final string:

        "cbadef"

    ============================================================
    2. Why Does the Rest of the String Stay Unchanged?
    ============================================================

    Only the range:

        [begin(), begin() + k)

    is passed to `reverse()`.

    Therefore, characters from index `k` onward are never
    modified.

    In other words:

        Before:
            [ first k characters ][ remaining characters ]

        After:
            [ reversed first k ][ remaining characters ]

    ============================================================
    3. Example
    ============================================================

    Suppose:

        s = "abcdef"
        k = 4

    First 4 characters:

        "abcd"

    Reverse them:

        "dcba"

    Keep the remaining characters unchanged:

        "ef"

    Result:

        "dcbaef"

    ============================================================
    4. Why Return s?
    ============================================================

    The string is passed by value:

        string s

    so `s` is a local copy of the original string.

    We can safely modify this copy using `reverse()` and then
    return the modified string.

    ============================================================
    Complexity Analysis
    ============================================================

    Time Complexity: O(k)

        Only the first `k` characters are reversed.

    Space Complexity: O(1) auxiliary space

        `reverse()` performs the reversal in-place using constant
        extra space.

        The function parameter itself is passed by value, so the
        string copy is part of the function's input handling,
        not additional algorithmic working space.

    ============================================================
    Core Idea
    ============================================================

    Reverse exactly the first `k` characters:

        reverse(s.begin(), s.begin() + k);

    Everything after index `k - 1` remains unchanged.
    ============================================================
*/