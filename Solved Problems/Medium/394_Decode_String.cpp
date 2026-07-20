class Solution {
    public:
        string decodeString(string s) {
            stack<string> st;
            int n = s.size();
            for(int i = 0; i < n; i++) {
                if (isdigit(s[i])) {
                    string num = "";
                    while (i < n && isdigit(s[i])) {
                        num += s[i];
                        i++;
                    }
                    st.push(num);
                    i--;
                } else if(s[i] == ']') {
                    string temp = "";
                    while(st.top() != "[") {
                        temp = st.top() + temp;
                        st.pop();
                    }
                    st.pop();
                    int x = stoi(st.top());
                    st.pop();
                    string t = "";
                    while(x--) t += temp;
                    st.push(t);
                } else st.push(string(1, s[i]));
            }
    
            string ans = "";
            while(!st.empty()) {
                ans = st.top() + ans;
                st.pop();
            }
    
            return ans;
        }
    };

/*

Idea:
------
The encoded string follows the pattern

k[encoded_string]

which means the substring inside the brackets should be
repeated

k

times.

Nested brackets are allowed, so we need a way to process
the innermost encoded string first.

A stack naturally handles this because the most recently
opened bracket is always the first one to be closed.

------------------------------------------------------------

How the Stack is Used:
----------------------

The stack stores every component encountered while
traversing the string.

It may contain

• Numbers (repeat counts)

• "["

• Characters

• Already decoded strings

Whenever a closing bracket

']'

is encountered,

the top of the stack contains the complete encoded
string inside its matching '['.

------------------------------------------------------------

Algorithm:
----------

1.

Traverse the string from left to right.

------------------------------------------------------------

2.

If a digit is encountered,

extract the complete number (to handle multi-digit
values such as

10

or

123)

and push it onto the stack.

------------------------------------------------------------

3.

If the current character is not

']',

simply push it onto the stack.

This includes

letters

and

"[".

------------------------------------------------------------

4.

When

']'

is encountered,

the current encoded block has ended.

Construct the encoded substring by popping elements
until

"["

is found.

Since popping occurs in reverse order,

prepend every popped string to reconstruct the original
substring.

------------------------------------------------------------

5.

Remove

"["

from the stack.

The next element is the repeat count.

Convert it into an integer.

------------------------------------------------------------

6.

Repeat the decoded substring

count

times.

Push the expanded string back onto the stack.

This allows nested expressions to be treated as ordinary
strings for future decoding.

------------------------------------------------------------

7.

After processing the complete input,

concatenate every string remaining in the stack.

This forms the final decoded string.

------------------------------------------------------------

Why Does This Work?
-------------------

The stack always postpones decoding until a matching

']'

is encountered.

Since the most recently opened bracket is always closed
first,

nested expressions are decoded from the inside out.

Once an inner expression is expanded,

it is pushed back as a normal string and naturally
becomes part of the surrounding expression.

Thus,

nested encodings are handled correctly without any
special logic.

------------------------------------------------------------

Example:
--------

Input

"3[a2[c]]"

Process

Read

3

Stack

[3]

----------------

Read

[

Stack

[3, []

----------------

Read

a

Stack

[3, [, a]

----------------

Read

2

Stack

[3, [, a, 2]

----------------

Read

[

Stack

[3, [, a, 2, []

----------------

Read

c

Stack

[3, [, a, 2, [, c]

----------------

Encounter

]

Substring

"c"

Repeat

2

times

Push

"cc"

Stack

[3, [, a, cc]

----------------

Encounter

]

Substring

"acc"

Repeat

3

times

Push

"accaccacc"

Stack

[accaccacc]

Final Answer

"accaccacc"

------------------------------------------------------------

Why Store Entire Strings?
-------------------------

After decoding an inner expression,

the expanded substring is pushed back onto the stack as
a single string.

This makes nested decoding simple because previously
decoded substrings are treated exactly like ordinary
characters while constructing larger expressions.

------------------------------------------------------------

Time Complexity:
----------------

O(n + L)

where

n

is the length of the encoded string and

L

is the length of the decoded output.

Every input character is processed once, and generating
the repeated substrings requires time proportional to
the output size.

------------------------------------------------------------

Space Complexity:
-----------------

O(n + L)

The stack stores intermediate strings, and the final
decoded string occupies

O(L)

space.

*/