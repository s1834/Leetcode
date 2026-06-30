class Solution {
public:
    bool repeatedSubstringPattern(string s) {
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

        return lps[n - 1] > 0 && n % (n - lps[n - 1]) == 0;
    }
};

/*

Idea:
------
A string is formed by repeating a substring if:

1. It has a non-empty proper prefix that is also a suffix.
2. The length of the repeating substring exactly divides the
   length of the entire string.

Instead of checking every possible substring (O(n²)),
use the LPS (Longest Prefix Suffix) array from the KMP algorithm.

LPS Array:
----------
LPS[i] = Length of the longest proper prefix of s[0...i]
         which is also a suffix of s[0...i].

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
Only LPS[n-1] matters because it represents the longest proper
prefix that is also a suffix of the ENTIRE string.

Let:
    len = LPS[n-1]

If the string is made by repeating a substring, then:

Repeating substring length = n - len

Example:
--------
s = "ababab"

LPS = [0,0,1,2,3,4]

len = 4
Repeating substring length = 6 - 4 = 2 ("ab")

Since:
6 % 2 == 0

The string is "ab" repeated 3 times.

Counter Example:
----------------
s = "aabaa"

LPS = [0,1,0,1,2]

len = 2
Repeating substring length = 5 - 2 = 3

5 % 3 != 0

Hence, it is NOT formed by repeating a substring.

Final Condition:
----------------
return (len > 0) && (n % (n - len) == 0);

where:
- len > 0 ensures there is a non-empty prefix that is also a suffix.
- n % (n - len) == 0 ensures the candidate repeating substring
  exactly tiles the entire string.

Time Complexity:
----------------
O(n)

Space Complexity:
-----------------
O(n)

*/