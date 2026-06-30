class Solution {
public:
    string longestPrefix(string s) {
        int n = s.size();
        vector<int> lps (n, 0); // Longest Prefix Suffix (LPS)
        int prevLPS = 0, i = 1;
        while(i < n) {
            if(s[i] == s[prevLPS]) {
                prevLPS++;
                lps[i] = prevLPS;
                i++;
            } else if (prevLPS == 0) {
                lps[i] = 0;
                i++;
            } else prevLPS = lps[prevLPS - 1];
        }

        string ans = "";
        for (i = 0; i < lps[n - 1]; i++) ans += s[i];
        return ans;
    }
};

/*

Idea:
------
A "happy prefix" is the longest prefix of the string that is also
a suffix, excluding the entire string itself.

Instead of comparing every prefix and suffix (O(n²)),
use the LPS (Longest Prefix Suffix) array from the KMP algorithm.

LPS Array:
----------
LPS[i] = Length of the longest proper prefix of s[0...i]
         which is also a suffix of s[0...i].

Example:
--------
s = "level"

Index : 0 1 2 3 4
Char  : l e v e l
LPS   : 0 0 0 0 1

Answer = "l"

Another Example:
----------------
s = "ababab"

Index : 0 1 2 3 4 5
Char  : a b a b a b
LPS   : 0 0 1 2 3 4

LPS[n-1] = 4
Answer = "abab"

Building LPS:
-------------
Maintain:
- prevLPS = length of the current longest prefix-suffix.
- i = current index.

If characters match:
    prevLPS++
    LPS[i] = prevLPS
    i++

If mismatch:
- If prevLPS == 0:
      LPS[i] = 0
      i++
- Otherwise:
      Jump back to LPS[prevLPS - 1]
      (do not increment i)

Observation:
------------
The last value of the LPS array (LPS[n-1]) gives the length of the
longest proper prefix that is also a suffix of the entire string.

Therefore:
- Let len = LPS[n-1].
- Return the first 'len' characters of the string.

Time Complexity:
----------------
O(n)

Space Complexity:
-----------------
O(n)   // LPS array

*/