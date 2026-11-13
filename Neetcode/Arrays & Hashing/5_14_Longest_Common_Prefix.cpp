class Solution {
    public:
        string longestCommonPrefix(vector<string>& strs) {
            int n = strs.size(), minSize = strs[0].size();
            for(int i = 0; i < n; i++) minSize = min(minSize, (int)strs[i].size());
    
            string ans = "";
            for(int i = 0; i < minSize; i++) {
                bool match = true;
                for(int j = 0; j < n; j++) {
                    if(strs[j][i] != strs[0][i]) {
                        match = false;
                        break;
                    }
                }
                if(match) ans += strs[0][i];
                else break;
            }
    
            return ans;
        }
    };

/*
    LeetCode 14: Longest Common Prefix

    Approach: Vertical Scanning

    Intuition:
    We are given an array of strings and need to find the longest
    prefix that is common to every string.

    A prefix consists of characters starting from index 0.

    Instead of comparing complete strings, we compare characters
    column by column across all strings.

    The first string acts as our reference string.

    The key observation is that:
        - A common prefix cannot be longer than the shortest string.
        - At every index, all strings must contain the same character.
        - Once a mismatch is found, no further character can be part
          of the common prefix.

    Step-by-Step Explanation:

    1. Calculate the number of strings and initialize the minimum length:
        int n = strs.size(), minSize = strs[0].size();

       `n` stores the total number of strings.

       `minSize` stores the length of the shortest string encountered
       so far.

    2. Find the length of the shortest string:
        for(int i = 0; i < n; i++)
            minSize = min(minSize, (int)strs[i].size());

       The longest common prefix cannot exceed the length of the
       shortest string.

       Therefore, we only need to check indices from 0 to minSize - 1.

    3. Initialize the answer:
        string ans = "";

       This string stores the common prefix found so far.

    4. Traverse each character position:
        for(int i = 0; i < minSize; i++)

       We check one character position at a time, starting from index 0.

    5. Assume all strings match at the current position:
        bool match = true;

       This variable tracks whether every string contains the same
       character at index `i` as the reference string.

    6. Compare the current character across all strings:
        for(int j = 0; j < n; j++) {
            if(strs[j][i] != strs[0][i]) {
                match = false;
                break;
            }
        }

       For every string:
           - Compare its character at index `i` with the character
             at the same index in the first string.
           - If any character differs, mark `match` as false.
           - Break immediately because the common prefix cannot
             extend beyond this position.

    7. Update the common prefix:
        if(match) ans += strs[0][i];
        else break;

       If all strings have the same character at the current position,
       append that character to `ans`.

       Otherwise, stop the traversal because a mismatch means that
       no longer prefix can be common to all strings.

    8. Return the result:
        return ans;

       The string contains all characters that matched across every
       input string, in their original order.

    Example:
        strs = ["flower", "flow", "flight"]

        Step 1:
            String lengths = [6, 4, 6]
            minSize = 4

        Step 2: Compare characters position by position.

            i = 0:
                f == f == f
                match = true
                ans = "f"

            i = 1:
                l == l == l
                match = true
                ans = "fl"

            i = 2:
                o == o != i
                match = false
                Break

        Final answer:
            "fl"

        Output: "fl"

    Complexity Analysis:

    Let:
        n = Number of strings.
        m = Length of the shortest string.

    - Time Complexity: O(n * m)
      Finding the shortest string takes O(n) time.
      The character comparison checks at most m positions across
      all n strings.

      Therefore, the overall time complexity is O(n * m).

    - Space Complexity: O(m)
      The output string can contain at most m characters.
      Apart from the returned string, only a constant amount of
      auxiliary space is used.

    Core Idea:
    Compare characters vertically, one index at a time, using the
    first string as the reference.

    Append a character only when every string matches at that index.
    Stop immediately when a mismatch is encountered.
*/