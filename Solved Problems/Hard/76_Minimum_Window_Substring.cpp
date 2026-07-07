// Version 1: Sliding Window
// class Solution {
// public:
//     string minWindow(string s, string t) {
//         map<char, int> mp1, mp2;
//         for (auto x : t) mp1[x]++;
        
//         int n = s.size(), l = 0, r = 0, mn = INT_MAX, minL = -1, minR = -1;
//         int have = 0, need = mp1.size();
//         while(r < n) {
//             if(mp1[s[r]]) mp2[s[r]]++;

//             if(mp1[s[r]] && mp1[s[r]] == mp2[s[r]]) have++;

//             while(have == need) {
//                 if(r - l + 1 < mn) {
//                     minL = l;
//                     minR = r;
//                     mn = r - l + 1;
//                 }

//                 mp2[s[l]]--;
//                 if(mp1[s[l]] && mp2[s[l]] < mp1[s[l]]) have--;
//                 l++;
//             }
//             r++;
//         }

//         string ans = "";
//         for(int i = minL; i <= minR && mn != INT_MAX; i++) ans += s[i];
//         return ans;
//     }
// };

// Version 2: Two Pointers
// class Solution {
// public:
//     string minWindow(string s, string t) {
//         int n = s.size(), m = t.size();
//         if (n < m) return "";

//         unordered_map<char, int> mp1, mp2;
//         for (char c : t) mp1[c]++;

//         int l = 0, r = 0, have = 0, need = mp1.size(), first = 0, last = INT_MAX;

//         while (r < n) {
//             mp2[s[r]]++;

//             if (mp1[s[r]] && mp2[s[r]] == mp1[s[r]]) have++;

//             while (have == need) {
//                 if (r - l + 1 < last) {
//                     last = r - l + 1;
//                     first = l;
//                 }

//                 mp2[s[l]]--;
//                 if (mp1[s[l]] && mp2[s[l]] < mp1[s[l]]) have--;
//                 l++;
//             }
//             r++;
//         }

//         if (last == INT_MAX) return "";
//         return s.substr(first, last);
//     }
// };


// /*
// Explanation of commented code:
// 1) map all the charaters of t in mp1
// 2) use two pointers l and r to traverse the string s
// 3) use mp2 to keep track of the characters in the current window
// 4) if the character at s[r] is in mp1, increment its count in mp2
// 5) if the count of s[r] in mp2 is equal to its count in mp1, increment have
// 6) while have is equal to need, check if the current window is smaller than the minimum window found so far
// 7) if it is, update minL, minR, and mn
// 8) decrement the count of s[l] in mp2
// 9) if the count of s[l] in mp2 is less than its count in mp1, decrement have
// 10) increment l
// 11) increment r
// 12) return the substring from minL to minR if mn is not INT_MAX, otherwise return an empty string

// before i was trying almost the same approach but was not taking into account all the edge cases and was not going for generalised solution, was more focused on what testcases were failing and make it correct for that specific case
// */

// Version 3: Two Pointers
class Solution {
    public:
        string minWindow(string s, string t) {
            int m = s.size(), n = t.size();
            if(m < n) return "";
            
            unordered_map<char, int> mp1, mp2;
            for(char c : t) mp1[c]++;
    
            int l = 0, r = 0, start = 0, length = m + 1, have = 0, need = mp1.size();
            while(r < m) {
                mp2[s[r]]++;
                if(mp1.count(s[r]) && mp1[s[r]] == mp2[s[r]]) have++;
    
                while(have == need) {
                    if (r - l + 1 < length) {
                        length = r - l + 1;
                        start = l;
                    }
    
                    mp2[s[l]]--;
                    if (mp1.count(s[l]) && mp2[s[l]] < mp1[s[l]]) have--;
                    l++;
                }
                r++;
            }
    
            if(length == m + 1) return "";
            return s.substr(start, length);
        }
    };

/*

Idea:
------
We need to find the smallest substring of 's' that contains every
character of 't', including duplicates.

This is solved using the Sliding Window (Two Pointers) technique.

Maintain:
----------
1. A frequency map of the required characters.
2. A frequency map of the current window.
3. Two pointers representing the current window.

Expand the window until it becomes valid, then shrink it as much as
possible while keeping it valid.

--------------------------------------------------------------------

Definitions:
------------

mp1:
Frequency of characters required from string 't'.

Example:

t = "AABC"

mp1:

A -> 2
B -> 1
C -> 1

--------------------------------

mp2:
Frequency of characters currently inside the sliding window.

--------------------------------------------------------------------

Meaning of 'need':
------------------

need = mp1.size()

This represents the number of UNIQUE characters whose required
frequency must be satisfied.

Example:

t = "AABC"

Although there are 4 characters, only

A
B
C

must become satisfied.

Therefore,

need = 3

--------------------------------------------------------------------

Meaning of 'have':
------------------

have represents how many unique characters currently satisfy their
required frequency.

Example:

Need:

A -> 2

Window:

A

Frequency:

A -> 1

Not enough.

have = 0

--------------------------------

Window:

AA

Frequency:

A -> 2

Requirement satisfied.

have = 1

--------------------------------

Window:

AAA

Frequency:

A -> 3

Still only one requirement is satisfied.

have remains 1.

--------------------------------------------------------------------

Algorithm:
----------

1. Expand the window by moving the right pointer.

2. Update the frequency of the current character.

3. If this character has now reached its required frequency,
   increment 'have'.

4. Once:

       have == need

   the current window contains every required character.

5. Record the current window if it is the smallest seen so far.

6. Shrink the window from the left while it remains valid.

7. If removing a character causes its frequency to become smaller
   than required, decrement 'have' because the window is no longer
   valid.

8. Continue until the right pointer reaches the end.

--------------------------------------------------------------------

Why save the answer before shrinking?
-------------------------------------

When:

    have == need

the current window is valid.

Before removing any character, we first check whether this is the
smallest valid window found so far.

Window Length:

    r - l + 1

If this length is smaller than the previous minimum,

save:

start = l

length = current window length

--------------------------------------------------------------------

Dry Run:
--------

s = "ADOBECODEBANC"

t = "ABC"

Need:

A
B
C

need = 3

------------------------------------------------

Expand:

Window:

ADOBEC

All three characters are present.

have = 3

Window is valid.

Save answer:

"ADOBEC"

Length = 6

------------------------------------------------

Shrink:

Remove A.

Window becomes invalid.

have = 2

Expand again.

------------------------------------------------

Continue expanding...

Eventually reach:

"BANC"

Window:

BANC

Length = 4

Smaller than previous answer.

Update:

start = index of 'B'

length = 4

Continue shrinking.

Window becomes invalid.

End of traversal.

Answer:

"BANC"

--------------------------------------------------------------------

Why does this work?
-------------------

Each character enters the window exactly once when the right pointer
moves.

Each character leaves the window at most once when the left pointer
moves.

Therefore, every character is processed at most twice.

This gives an overall linear-time solution.

--------------------------------------------------------------------

Time Complexity:
----------------

O(m + n)

where

m = length of s
n = length of t

--------------------------------------------------------------------

Space Complexity:
-----------------

O(k)

where k is the number of distinct characters stored in the hash maps.

(For English letters, this is effectively O(1).)

*/