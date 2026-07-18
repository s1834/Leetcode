class Solution {
    public:
        string rearrangeString(string s, char x, char y) {
            unordered_map<char, int> mp;
            for(auto x : s) mp[x]++;
    
            string ans = "";
            while(mp[y] > 0) {
                ans += y;
                mp[y]--;
            }
    
            for(auto x : mp) {
                while(x.second > 0) {
                    ans += x.first;
                    x.second--;
                }
            }
    
            return ans;
        }
    };

/*

Idea:
------
The only requirement is that every occurrence of
character y appears before every occurrence of
character x.

The relative order of the remaining characters does not
matter.

Therefore,

1.

Place all occurrences of y first.

2.

Append all remaining characters (excluding y, since it
has already been added).

Since x is added only in the second step, every y
automatically appears before every x.

------------------------------------------------------------

Algorithm:
----------

1.

Count the frequency of every character in the string.

2.

Append character y exactly freq[y] times to the answer.

3.

Decrease its frequency to zero.

4.

Traverse the frequency map.

For every remaining character,

append it according to its frequency.

This naturally includes character x, ensuring that all
occurrences of y come before every occurrence of x.

------------------------------------------------------------

Example:
--------

Input

s = "aabc"

x = 'a'

y = 'c'

------------------------------------------------------------

Frequency

a -> 2

b -> 1

c -> 1

------------------------------------------------------------

Step 1

Append all 'c'

Answer

"c"

------------------------------------------------------------

Step 2

Append remaining characters

"c"

+

"b"

+

"aa"

Result

"cbaa"

Every 'c' appears before every 'a'.

------------------------------------------------------------

Example:

Input

s = "axe"

x = 'o'

y = 'x'

Frequency

a -> 1

x -> 1

e -> 1

Append all 'x'

Answer

"x"

Append remaining characters

"a"

"e"

Final Answer

"xae"

This is also valid since all occurrences of 'x' appear
before every occurrence of 'o' (which does not exist).

------------------------------------------------------------

Why This Works:
---------------

The only constraint is that no occurrence of x should
appear before an occurrence of y.

By placing every y first and appending all remaining
characters afterward,

this condition is always satisfied.

The order of all other characters is irrelevant.

------------------------------------------------------------

Time Complexity:
----------------

O(n)

Building the frequency map takes O(n).

Appending characters also takes O(n).

------------------------------------------------------------

Space Complexity:
-----------------

O(1)

The frequency map stores at most 26 lowercase English
letters.

*/