class Solution {
    public:
        string removeDuplicateLetters(string s) {
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
We need to remove duplicate letters so that every
distinct character appears exactly once.

Among all possible valid strings, we must return the
lexicographically smallest one.

Two important observations:

1.

Each character should appear only once.

2.

If a smaller character can be placed before a larger
character without losing the larger character, we should
do so to obtain the smallest lexicographical order.

A monotonic increasing stack helps maintain the smallest
possible answer while ensuring every character appears
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

Stores the current answer while maintaining increasing
lexicographical order.

3.

Set

Keeps track of characters already present in the stack to
avoid duplicates.

------------------------------------------------------------

Algorithm:
----------

1.

Count the frequency of every character.

------------------------------------------------------------

2.

Traverse the string from left to right.

For every character

x,

decrease its remaining frequency since the current
occurrence has now been processed.

------------------------------------------------------------

3.

If

x

is already present in the stack,

skip it because every character should appear only once.

------------------------------------------------------------

4.

Otherwise,

while

• the stack is not empty,

• the current character is smaller than the stack top,

• and the stack top appears again later
  (remaining frequency > 0),

remove the stack top.

This is safe because the removed character will appear
again later, allowing us to place the smaller character
earlier and obtain a lexicographically smaller result.

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

The stack always stores the smallest possible answer
constructed so far.

Whenever a smaller character is encountered,

we remove larger characters from the top of the stack
only if they appear again later.

Therefore,

• No character is permanently lost.

• Every distinct character appears exactly once.

• The final string is the lexicographically smallest
  among all valid answers.

------------------------------------------------------------

Example:
--------

s = "bcabc"

Process

b

Stack

[b]

----------------

c

Stack

[b c]

----------------

a

a < c

c appears later

Remove c

a < b

b appears later

Remove b

Push a

Stack

[a]

----------------

b

Stack

[a b]

----------------

c

Stack

[a b c]

Final Answer

"abc"

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