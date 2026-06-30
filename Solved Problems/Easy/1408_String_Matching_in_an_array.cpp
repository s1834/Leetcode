class Solution {
private:
    bool KMP(string haystack, string needle) {
        int n = needle.size();
        vector<int> lps(n, 0); // Longest Prefix Suffix (LPS)
        int prevLPS = 0, i = 1;

        while(i < n) {
            if(needle[i] == needle[prevLPS]) {
                prevLPS++;
                lps[i] = prevLPS;
                i++;
            } else if(prevLPS == 0) {
                lps[i] = 0;
                i++;
            } else prevLPS = lps[prevLPS - 1];
        }

        // Knuth-Morris-Pratt (KMP)
        i = 0; // haystack
        int j = 0; // needle
        int m = haystack.size();
        while(i < m) {
            if(haystack[i] == needle[j]) {
                i++;
                j++;
            } else if (j == 0) i++;
            else j = lps[j - 1];
            if (j == n) return true;;
        }
        
        return false;
    }

public:
    vector<string> stringMatching(vector<string>& words) {
        vector<string> ans;
        int n = words.size();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;

                if (KMP(words[j], words[i])) {
                    ans.push_back(words[i]);
                    break;
                }
            }
        }

        return ans;
    }
};

/*

Idea:
------
For every word, check whether it appears as a substring of any
other word using the Knuth-Morris-Pratt (KMP) algorithm.

Instead of using the built-in find(), KMP searches in linear time
by preprocessing the pattern into an LPS (Longest Prefix Suffix)
array.

Algorithm:
----------
1. For each word (needle):
      Compare it against every other word (haystack).

2. Run KMP(haystack, needle):
      - If needle is found inside haystack,
        add it to the answer and stop checking further words.

3. Continue until every word has been processed.

LPS Array:
----------
LPS[i] = Length of the longest proper prefix of needle[0...i]
         which is also a suffix of needle[0...i].

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

KMP Search:
-----------
Maintain:
- i -> index in haystack
- j -> index in needle

If characters match:
    i++, j++

If mismatch:
- If j == 0:
      Move to the next character in haystack.
- Otherwise:
      Set j = LPS[j - 1] to reuse the longest valid prefix.

If j reaches needle.length(),
the pattern exists inside the current haystack.

Why break?
----------
The problem only asks whether a word is a substring of
ANY other word.

Once one match is found:
    ans.push_back(words[i]);

there is no need to search the remaining words, since adding
the same word multiple times would create duplicates.

Therefore:
    break;

moves on to checking the next word.

Time Complexity:
----------------
Let:
n = number of words
L = average length of a word

Each KMP search:
O(L)

Total comparisons:
O(n²)

Overall:
O(n² * L)

Space Complexity:
-----------------
O(L)   // LPS array

*/
