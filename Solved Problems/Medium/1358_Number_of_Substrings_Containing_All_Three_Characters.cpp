class Solution {
public:
    int numberOfSubstrings(string s) {
        vector<int> lastSeen (3, -1);
        int count = 0, n = s.size();
        for(int i = 0; i < n; i++) {
            lastSeen[s[i] - 'a'] = i;
            count += 1 + min({lastSeen[0], lastSeen[1], lastSeen[2]});
        }
        return count;
    }
};

/*

Idea:
------
Keep track of the last index where each character
('a', 'b', and 'c') was seen.

At every index i, determine how many substrings ending at i
contain all three characters.

Algorithm:
----------
1. Maintain lastSeen[3]:
      lastSeen[0] -> last index of 'a'
      lastSeen[1] -> last index of 'b'
      lastSeen[2] -> last index of 'c'

   Initially all are -1 since no character has been seen.

2. Traverse the string from left to right.

3. Update the last occurrence of the current character:
      lastSeen[s[i] - 'a'] = i;

4. Compute:
      min({lastSeen[0], lastSeen[1], lastSeen[2]})

   Why min()?
   ----------
   The minimum gives the earliest last occurrence among
   'a', 'b', and 'c'.

   To include all three characters, a substring ending at i
   must start at or before this earliest index.

5. Why +1?
   --------
   If the minimum last occurrence is x, then the valid
   starting indices are:

      0, 1, 2, ..., x

   Number of such indices = x + 1.

   Therefore,

      count += 1 + min({lastSeen[0], lastSeen[1], lastSeen[2]});

   If any character has not appeared yet, one of the values
   in lastSeen is -1.

   Then:
      1 + (-1) = 0

   meaning no valid substring ends at the current index.

Example:
--------
s = "abcabc"

i = 2
lastSeen = [0,1,2]

min = 0

Valid starting indices:
0

Substrings:
abc

count += 0 + 1 = 1

------------------------------------

i = 4
lastSeen = [3,4,2]

min = 2

Valid starting indices:
0, 1, 2

Substrings:
abcab
bcab
cab

count += 2 + 1 = 3

Time Complexity:
----------------
O(n)

Space Complexity:
-----------------
O(1)

*/
