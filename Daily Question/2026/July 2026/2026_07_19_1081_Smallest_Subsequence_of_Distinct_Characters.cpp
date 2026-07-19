class Solution {
    public:
        string smallestSubsequence(string s) {
            unordered_map<char, int> mp;
            for(auto x : s) mp[x]++;
    
            stack<char> st;
            set<char> inStack;
            for(auto x : s) {
                mp[x]--;
    
                if(inStack.find(x) != inStack.end()) continue;
    
                while(!st.empty() && x < st.top() && mp[st.top()] > 0) {
                    inStack.erase(st.top());
                    st.pop();
                }
    
                st.push(x);
                inStack.insert(x);
            }
    
            string ans = "";
            while(!st.empty()) {
                ans += st.top();
                st.pop();
            }
    
            reverse(ans.begin(), ans.end());
            return ans;
        }
    };

/*

Idea:
------
We need to construct the lexicographically smallest
subsequence such that every distinct character appears
exactly once.

Two important observations:

1.

Every character should be included only once.

2.

If a smaller character appears later, we should place it
earlier whenever it is safe to do so.

A monotonic increasing stack helps maintain the smallest
possible order while ensuring every character is included
exactly once.

------------------------------------------------------------

Data Structures Used:
---------------------

1.

Frequency Map

Stores how many occurrences of each character are still
left to process.

2.

Stack

Maintains the current answer in increasing
lexicographical order.

3.

Set

Keeps track of which characters are already present in
the stack to avoid duplicates.

------------------------------------------------------------

Algorithm:
----------

1.

Count the frequency of every character.

------------------------------------------------------------

2.

Traverse the string from left to right.

For every character

x

decrease its remaining frequency because the current
occurrence is now being processed.

------------------------------------------------------------

3.

If

x

is already present in the stack,

skip it since each character should appear only once.

------------------------------------------------------------

4.

Otherwise,

while

• the stack is not empty,

• the current character is smaller than the stack top,

• and the stack top appears again later
  (remaining frequency > 0),

remove the stack top.

Why?

Because we can safely place that larger character later,
allowing the smaller current character to come first,
making the subsequence lexicographically smaller.

Also remove it from the set.

------------------------------------------------------------

5.

Push the current character into the stack and mark it as
present.

------------------------------------------------------------

6.

The stack stores the answer from bottom to top.

Pop all characters, reverse the obtained string, and
return it.

------------------------------------------------------------

Why Does This Work?
-------------------

The stack always maintains the smallest possible
lexicographical order.

Whenever we encounter a smaller character,

we try to move it earlier by removing larger characters
from the stack.

However,

a character is removed only if it appears again later.

This guarantees:

• No character is lost.

• Every distinct character appears exactly once.

• The resulting subsequence is lexicographically
  smallest.

------------------------------------------------------------

Example:
--------

s = "cbacdcbc"

Remaining Frequencies

c : 4
b : 2
a : 1
d : 1

Process

c

Stack

[c]

----------------

b

b < c

c appears later

Remove c

Stack

[b]

----------------

a

a < b

b appears later

Remove b

Stack

[a]

----------------

c

Stack

[a c]

----------------

d

Stack

[a c d]

----------------

c

Already present

Skip

----------------

b

b < d

d does NOT appear later

Cannot remove d

Push b

Stack

[a c d b]

----------------

c

Already present

Skip

Final Answer

"acdb"

------------------------------------------------------------

Time Complexity:
----------------

O(n)

Each character is pushed into the stack at most once and
popped at most once.

------------------------------------------------------------

Space Complexity:
-----------------

O(n)

for the stack, frequency map, and set.

*/