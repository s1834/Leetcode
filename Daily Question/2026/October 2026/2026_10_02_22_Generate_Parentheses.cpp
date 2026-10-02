class Solution {
    private:
        vector<string> ans;
        stack<char> st;
    
        void backtrack(int n, int open, int close) {
            if(open == n && close == n) {
                stack<char> temp = st;
                string s = "";
                while(!temp.empty()) {
                    s += temp.top();
                    temp.pop();
                }
                reverse(s.begin(), s.end());
                ans.push_back(s);
            }
    
            if(open < n) {
                st.push('(');
                backtrack(n, open + 1, close);
                st.pop();
            }
    
            if(close < open) {
                st.push(')');
                backtrack(n, open, close + 1);
                st.pop();
            }
        }
    
    public:
        vector<string> generateParenthesis(int n) {
            backtrack(n, 0, 0);
            return ans;
        }
    };

/*

Idea:
------
Generate all valid combinations of n pairs of parentheses
using backtracking.

At every step, we decide whether to add

1.

An opening parenthesis '('

or

2.

A closing parenthesis ')'

while ensuring the current sequence always remains valid.

A stack is used to maintain the current sequence being
constructed.

------------------------------------------------------------

Algorithm:
----------

Maintain two counters:

open  -> number of '(' used so far.

close -> number of ')' used so far.

Initially,

open = 0

close = 0

------------------------------------------------------------

Choice 1:

Add an opening parenthesis.

This is possible only if

open < n

Push '(' into the stack.

Increase open by 1.

Recursively generate the remaining sequence.

After returning,

pop the stack (backtracking).

------------------------------------------------------------

Choice 2:

Add a closing parenthesis.

A closing parenthesis can only be added if there is an
unmatched opening parenthesis available.

Therefore,

close < open

Push ')' into the stack.

Increase close by 1.

Recursively continue.

After returning,

pop the stack.

------------------------------------------------------------

Base Case:
----------

When

open == n

and

close == n

all parentheses have been used.

The stack now represents one valid sequence.

Copy the stack into a temporary string.

Since stacks are LIFO, popping produces the string in
reverse order.

Reverse the string and store it in the answer.

------------------------------------------------------------

Example:
--------

n = 2

Start

open = 0

close = 0

Stack =

{}

------------------------------------------------------------

Add '('

Stack:

(

open = 1

------------------------------------------------------------

Add '('

Stack:

((

open = 2

------------------------------------------------------------

Cannot add another '('.

Add ')'

Stack:

(()

close = 1

------------------------------------------------------------

Add ')'

Stack:

(())

close = 2

Store

(())

------------------------------------------------------------

Backtrack.

Explore other choices.

Generate

()()

Final Answer:

(())

()()

------------------------------------------------------------

Why close < open?
-----------------

A closing parenthesis must always match a previously
placed opening parenthesis.

If

close == open

there are no unmatched '(' remaining.

Adding ')' would immediately make the sequence invalid.

Example:

")("

or

"())"

are invalid.

Therefore,

a ')' is added only when

close < open.

------------------------------------------------------------

Backtracking:
-------------

Whenever a parenthesis is added,

it is pushed onto the stack.

After exploring every sequence starting with that
choice,

pop the parenthesis from the stack.

This restores the previous state before trying the next
choice.

------------------------------------------------------------

Time Complexity:
----------------

The number of valid sequences of n pairs of parentheses
is the nth Catalan Number.

Time Complexity:

O(Cn × n)

where

Cn = (1 / (n + 1)) × (2n choose n)

Each valid sequence has length 2n and is copied into
the answer once.

------------------------------------------------------------

Space Complexity:
-----------------

Auxiliary Space:

O(n)

due to the recursion stack and the stack storing the
current sequence.

Output Space:

O(Cn × n)

to store all valid parenthesis strings.

*/