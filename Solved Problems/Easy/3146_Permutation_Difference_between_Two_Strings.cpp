class Solution {
    public:
        int findPermutationDifference(string s, string t) {
            unordered_map<char, int> mp;
            int n = s.size();
            for(int i = 0; i < n; i++) mp[s[i]] = i;
    
            int ans = 0;
            for(int i = 0; i < n; i++) ans += abs(i - mp[t[i]]);
    
            return ans;
        }
    };

/*
    ============================================================
    LeetCode 3146 - Permutation Difference between Two Strings
    ============================================================

    Approach: Hash Map
    ------------------------------------------------------------

    We need to calculate the permutation difference between
    two strings `s` and `t`.

    For every character, we find:

        |position of character in s
         - position of character in t|

    Then add these differences for all characters.

    The key observation is that we can store the position of
    every character in `s` inside a hash map.

    ============================================================
    1. Store Positions from s
    ============================================================

    We create:

        unordered_map<char, int> mp;

    and store:

        mp[s[i]] = i;

    Therefore, `mp[c]` gives the index at which character `c`
    appears in `s`.

    Example:

        s = "abcde"

        mp['a'] = 0
        mp['b'] = 1
        mp['c'] = 2
        mp['d'] = 3
        mp['e'] = 4

    ============================================================
    2. Find the Position Difference
    ============================================================

    Now we traverse `t`.

    For every character `t[i]`:

        i

    is its position in `t`, while:

        mp[t[i]]

    is its position in `s`.

    Therefore, the positional difference is:

        abs(i - mp[t[i]])

    We add this difference to `ans`.

    ============================================================
    3. Example
    ============================================================

    Suppose:

        s = "abc"
        t = "bac"

    Positions in `s`:

        a -> 0
        b -> 1
        c -> 2

    Now process `t`:

        t[0] = 'b'

        position in t = 0
        position in s = 1

        difference = |0 - 1| = 1

        t[1] = 'a'

        position in t = 1
        position in s = 0

        difference = |1 - 0| = 1

        t[2] = 'c'

        position in t = 2
        position in s = 2

        difference = |2 - 2| = 0

    Therefore:

        ans = 1 + 1 + 0
            = 2

    ============================================================
    4. Why Does This Work?
    ============================================================

    Since `s` and `t` are permutations of the same characters,
    every character in `t` must also exist in `s`.

    The map gives us the original position of each character
    in `s`.

    While traversing `t`, the current index `i` gives the
    position of that same character in `t`.

    Thus:

        abs(i - mp[t[i]])

    gives the exact positional difference for that character.

    Summing this value for every character gives the required
    permutation difference.

    ============================================================
    Complexity Analysis
    ============================================================

    Time Complexity: O(n)

        - Building the hash map takes O(n).
        - Traversing `t` takes O(n).
        - Hash-map lookup is O(1) on average.

    Space Complexity: O(n)

        The hash map stores the position of every character
        from `s`.

    ============================================================
    Core Idea
    ============================================================

    Store the position of every character in `s`.

    Then for each character in `t`:

        difference = abs(position in t - position in s)

    Add all these differences to obtain the permutation
    difference.
    ============================================================
*/