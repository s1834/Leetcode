class Solution {
private:
    int KMP(string haystack, string needle) {
        int n = needle.size();
        vector<int> LPS (n, 0); // Longest Prefix Suffix (LPS)
        int prevLPS = 0, i = 1;
        while(i < n) {
            if(needle[i] == needle[prevLPS]) {
                prevLPS++;
                LPS[i] = prevLPS;
                i++;
            } else if(prevLPS == 0) {
                LPS[i] = 0;
                i++;
            } else prevLPS = LPS[prevLPS - 1];
        }

        // Knuth-Morris-Pratt (KMP)
        i = 0; // haystack
        int j = 0; // needle
        int m = haystack.size();
        while(i < m) {
            if(haystack[i] == needle[j]) {
                i++;
                j++;
            } else if(j == 0) i++;
            else j = LPS[j - 1];

            if(j == n) return 1;
        }

        return 0;
    }

public:
    int numOfStrings(vector<string>& patterns, string word) {
        int ans = 0;
        for (auto x : patterns) ans += KMP(word, x);
        return ans;
    }
};

/*

Idea:
------
For every pattern, check whether it exists as a substring of 'word'
using the Knuth-Morris-Pratt (KMP) algorithm.

KMP searches for a pattern in linear time by preprocessing the pattern
into an LPS (Longest Prefix Suffix) array, avoiding unnecessary
character comparisons after mismatches.

Algorithm:
----------
1. For each pattern:
   - Build its LPS array.
   - Run KMP on (word, pattern).
   - If the pattern is found, return 1; otherwise return 0.
2. Sum the results for all patterns.

LPS Array:
----------
LPS[i] = Length of the longest proper prefix of pattern[0...i]
         which is also a suffix of pattern[0...i].

While building LPS:
- If characters match:
      Increase prevLPS and store it.
- If mismatch:
      - If prevLPS == 0, LPS[i] = 0.
      - Otherwise, jump back to LPS[prevLPS - 1]
        without incrementing i.

KMP Search:
-----------
Maintain:
- i -> index in word
- j -> index in pattern

If characters match:
    i++, j++

If mismatch:
- If j == 0:
      Move to the next character in word.
- Otherwise:
      Set j = LPS[j - 1] to reuse the longest valid prefix.

If j reaches pattern.length(),
the pattern exists in the word, so return 1.

If the search finishes without a full match,
return 0.

Why KMP?
--------
Instead of restarting the pattern after every mismatch,
KMP reuses previously matched characters using the LPS array,
making each search run in linear time.

Time Complexity:
----------------
Let:
m = word.length()
k = patterns.size()
ni = length of the i-th pattern

Building LPS + Searching for one pattern:
O(m + ni)

Overall:
O(k * m + Σni)

Space Complexity:
-----------------
O(max pattern length)   // LPS array

*/