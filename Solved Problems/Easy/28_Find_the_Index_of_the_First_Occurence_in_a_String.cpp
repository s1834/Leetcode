class Solution {
public:
    int strStr(string haystack, string needle) {
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

            if(j == n) return i - n;
        }

        return -1;
    }
};

/*

Idea:
------
Use the Knuth-Morris-Pratt (KMP) algorithm to efficiently find the
first occurrence of 'needle' in 'haystack'.

KMP avoids rechecking previously matched characters by preprocessing
the pattern into an LPS (Longest Prefix Suffix) array.

LPS Array:
----------
LPS[i] = Length of the longest proper prefix of needle[0...i]
         which is also a suffix of needle[0...i].

Example:
--------
needle = "ababaca"

Index : 0 1 2 3 4 5 6
Char  : a b a b a c a
LPS   : 0 0 1 2 3 0 1

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

Searching (KMP):
----------------
Use two pointers:
- i -> haystack
- j -> needle

If characters match:
    i++, j++

If mismatch:
- If j == 0:
      Move to next character in haystack.
- Otherwise:
      Set j = LPS[j - 1]
      (reuse the longest valid prefix already matched)

When j == needle.length(),
the entire pattern is found.
Starting index = i - needle.length().

Why KMP?
--------
Instead of restarting the pattern after every mismatch,
KMP uses the LPS array to determine how much of the previous
match can still be reused, avoiding unnecessary comparisons.

Time Complexity:
----------------
Building LPS : O(n)
Searching    : O(m)

Overall      : O(m + n)

where:
m = haystack.length()
n = needle.length()

Space Complexity:
-----------------
O(n)   // LPS array

*/

// class Solution {
// public:
//     int strStr(string haystack, string needle) {
//         int n1 = haystack.size(), n2 = needle.size(), count = 1, flag = -1;
//         for (int i = 0; i < n1 - n2 + 1; i++) {
//             if (haystack[i] == needle[0]) {
//                 for (int j = 1; j < n2; j++) {
//                     if (haystack[i + j] != needle[j]) {
//                         count = 1;
//                         break;
//                     }
//                     count++;
//                 }
//                 if (count == n2) {
//                     flag = i;
//                     break;
//                 }
//             }
//         }

//         if (flag != -1) {
//             return flag;
//         }

//         return flag;
//     }
// };