class Solution {
    public:
        bool checkInclusion(string s1, string s2) {
            int m = s1.size(), n = s2.size();
            if(m > n) return false;
    
            unordered_map<char, int> mp1, mp2;
            for(auto x : s1) mp1[x]++;
    
            for(int i = 0; i < m; i++) {
                if(mp1.find(s2[i]) != mp1.end()) mp2[s2[i]]++;
            }
    
            int left = 0, right = m - 1;
            while(right < n) {
                if(mp1.size() == mp2.size()) {
                    int flag = true;
                    for(auto x : mp1) {
                        if(x.second != mp2[x.first]) {
                            flag = false;
                            break;
                        }
                    }
                    if(flag) return true;
                }
    
                if(mp1.find(s2[left]) != mp1.end()) {
                    mp2[s2[left]]--;
                    if(mp2[s2[left]] == 0) mp2.erase(s2[left]);
                }
                left++;
                right++;
                if(right < n && mp1.find(s2[right]) != mp1.end()) mp2[s2[right]]++;
    
            }
            return false;
        }
    };

/*

Idea:
------
We need to determine whether any substring of

s2

is a permutation of

s1.

A permutation contains exactly the same characters with
the same frequencies.

Instead of generating every permutation of

s1,

we slide a window of length

|s1|

over

s2

and compare the character frequencies.

If any window has the same frequency distribution as

s1,

then that window is a permutation of

s1.

------------------------------------------------------------

Algorithm:
----------

1.

Store the frequency of every character in

s1

using

mp1.

------------------------------------------------------------

2.

Build the frequency map

mp2

for the first window of length

m

in

s2.

Only characters that exist in

mp1

are stored since all other characters are irrelevant.

------------------------------------------------------------

3.

Maintain a sliding window of size

m

using two pointers

left

and

right.

------------------------------------------------------------

4.

For every window,

first check whether both maps contain the same number of
distinct characters.

If not,

they cannot be equal.

------------------------------------------------------------

5.

If the sizes are equal,

compare the frequency of every character in

mp1

with

mp2.

If every frequency matches,

a permutation has been found.

Return

true.

------------------------------------------------------------

6.

Slide the window by one position.

• Remove the character leaving the window.

• If its frequency becomes zero,

erase it from

mp2

to keep the map compact.

• Add the new character entering the window.

------------------------------------------------------------

7.

Repeat until every window has been processed.

If no matching window is found,

return

false.

------------------------------------------------------------

Why Does This Work?
-------------------

Every permutation of

s1

must have exactly

m

characters.

Therefore,

only substrings of length

m

need to be considered.

The sliding window ensures that every such substring is
processed exactly once.

If a window has exactly the same character frequencies
as

s1,

then rearranging its characters would produce

s1,

which means that window is a valid permutation.

------------------------------------------------------------

Example:
--------

s1 =

"ab"

s2 =

"eidbaooo"

Frequency of

s1

a → 1

b → 1

--------------------------------

Window

"ei"

No matching frequencies.

--------------------------------

Window

"id"

No match.

--------------------------------

Window

"db"

b → 1

Need

a

also.

No match.

--------------------------------

Window

"ba"

a → 1

b → 1

Frequencies match.

Return

true.

------------------------------------------------------------

Why Ignore Other Characters?
----------------------------

Suppose

s1 = "abc"

Current window

"xab"

Character

'x'

does not exist in

s1,

so it can never contribute toward forming a valid
permutation.

Ignoring such characters keeps

mp2

smaller while still allowing correct frequency
comparisons.

------------------------------------------------------------

Time Complexity:
----------------

Building the frequency maps:

O(m)

Sliding the window:

O(n)

For each window,

at most the distinct characters of

s1

are compared.

Overall:

O(n × d)

where

d

is the number of distinct characters in

s1.

Since lowercase English letters are limited to 26,

this is effectively

O(n).

------------------------------------------------------------

Space Complexity:
-----------------

O(d)

where

d

is the number of distinct characters in

s1.

In the worst case,

d ≤ 26,

so the extra space is constant.

*/