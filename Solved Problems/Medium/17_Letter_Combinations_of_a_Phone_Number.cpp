class Solution {
    private:
        vector<string> ans;
        string s = "";
        unordered_map<char, vector<char>> mp;
    
        void dfs(string digits, int idx) {
            if(digits.size() == s.size()) {
                ans.push_back(s);
                return;
            }
    
            for(auto x : mp[digits[idx]]) {
                s += x;
                dfs(digits, idx + 1);
                s.pop_back();
            }
        }
    
    public:
        vector<string> letterCombinations(string digits) {
            mp['2'] = {'a','b','c'};
            mp['3'] = {'d','e','f'};
            mp['4'] = {'g','h','i'};
            mp['5'] = {'j','k','l'};
            mp['6'] = {'m','n','o'};
            mp['7'] = {'p','q','r','s'};
            mp['8'] = {'t','u','v'};
            mp['9'] = {'w','x','y','z'};
    
            dfs(digits, 0);
            return ans;
        }
    };

/*

Idea:
------
Each digit on a phone keypad represents a set of letters.

For example,

2 → abc

3 → def

...

The task is to generate

all possible strings

by choosing exactly one letter corresponding to each
digit.

At every digit,

there are multiple choices,

making this a classic

Backtracking + Depth First Search (DFS)

problem.

------------------------------------------------------------

Key Observation:
----------------

Suppose the input is

"23"

For the first digit

2,

we can choose

a, b, or c.

After choosing one letter,

the remaining problem becomes

"Generate all combinations for the remaining digits."

This is the exact same problem on a smaller input,

making recursion a natural solution.

------------------------------------------------------------

Phone Keypad Mapping:
---------------------

The unordered_map stores the mapping between each digit
and its corresponding letters.

2 → {a, b, c}

3 → {d, e, f}

4 → {g, h, i}

5 → {j, k, l}

6 → {m, n, o}

7 → {p, q, r, s}

8 → {t, u, v}

9 → {w, x, y, z}

Using this mapping,

given any digit,

we can immediately obtain all possible characters that
can occupy the current position.

------------------------------------------------------------

DFS State:
----------

The recursive function

dfs(digits, idx)

means:

"Generate every possible letter combination starting from
digit index

idx."

The string

s

stores the partial combination constructed so far.

Example

digits = "279"

Suppose

s = "ap"

Then

dfs(digits, 2)

means

"We have already chosen

'a'

for digit

2

and

'p'

for digit

7.

Now generate all possibilities for the remaining digit

9."

------------------------------------------------------------

Base Case:
----------

If

s.length() == digits.length()

then one character has been chosen for every digit.

Therefore,

a complete valid combination has been formed.

Store

s

inside

ans

and return.

------------------------------------------------------------

Recursive Choice:
-----------------

At every recursive call,

we examine the current digit

digits[idx].

Using the keypad mapping,

we obtain all letters corresponding to that digit.

For each possible letter,

1.

Append the letter to the current string.

2.

Recursively process the next digit.

3.

Remove the appended letter (Backtracking).

------------------------------------------------------------

Backtracking:
-------------

Backtracking allows one string object

s

to be reused for every possible combination.

Example

digits = "23"

Initially

s = ""

--------------------------------

Choose

'a'

s = "a"

↓

Process next digit.

--------------------------------

Choose

'd'

s = "ad"

Complete combination.

Store it.

--------------------------------

Backtrack

Remove

'd'

s = "a"

--------------------------------

Choose

'e'

s = "ae"

Store.

--------------------------------

Backtrack

Remove

'e'

s = "a"

--------------------------------

Choose

'f'

s = "af"

Store.

--------------------------------

Backtrack

Remove

'f'

s = "a"

--------------------------------

Backtrack

Remove

'a'

s = ""

Now choose

'b'

and repeat.

Without removing characters after recursion,

future combinations would incorrectly contain letters from
previous choices.

------------------------------------------------------------

Algorithm:
----------

Step 1

Build the digit-to-letter mapping.

------------------------------------------------------------

Step 2

Start DFS from

index = 0.

------------------------------------------------------------

Step 3

If all digits have been processed,

store the current string.

------------------------------------------------------------

Step 4

Otherwise,

retrieve all letters corresponding to the current digit.

------------------------------------------------------------

Step 5

For every possible letter,

append it to the current combination.

------------------------------------------------------------

Step 6

Recursively process the next digit.

------------------------------------------------------------

Step 7

Remove the last character before trying the next letter.

------------------------------------------------------------

Repeat until every possible choice for every digit has
been explored.

------------------------------------------------------------

Recursion Tree Example:
-----------------------

Input

"23"

Start

dfs(0)

                    ""
                     |
          -----------------------
          |          |          |
          a          b          c
          |          |          |
      --------    --------   --------
      |  |  |     |  |  |    |  |  |
      d  e  f     d  e  f    d  e  f

Generated combinations

ad

ae

af

bd

be

bf

cd

ce

cf

------------------------------------------------------------

Example:
--------

Input

digits = "79"

Mapping

7 → pqrs

9 → wxyz

--------------------------------

Choose

p

↓

Choose

w

Combination

"pw"

--------------------------------

Backtrack

Choose

x

Combination

"px"

--------------------------------

Continue

"py"

"pz"

--------------------------------

Backtrack

Choose

q

Generate

"qw"

"qx"

"qy"

"qz"

Continue similarly for

r

and

s.

------------------------------------------------------------

Why Does This Work?
-------------------

For every digit,

the algorithm explores

every

possible letter mapped to that digit.

Each recursive call fixes one character of the final
answer.

After fixing one letter,

the remaining suffix is solved recursively.

Backtracking restores the previous partial combination,

ensuring every possible choice is explored independently.

Since every digit contributes all of its possible letters,

the DFS generates every valid phone keypad combination
exactly once.

------------------------------------------------------------

Mathematical View:
------------------

Suppose

f(i)

represents all possible combinations that can be formed
starting from digit

i.

If

Letters(i)

is the set of letters corresponding to

digits[i],

then

f(i)

=

⋃

for every

c ∈ Letters(i)

{

c + f(i + 1)

}

The base case is

f(n)

=

{""}

where

n

is the number of digits.

The DFS directly implements this recursive definition.

------------------------------------------------------------

Example of Number of Combinations:
----------------------------------

Suppose

digits = "234"

Each digit has

3

possible letters.

Total combinations

=

3 × 3 × 3

=

27

--------------------------------

Suppose

digits = "79"

Digit

7

has

4

choices.

Digit

9

has

4

choices.

Total combinations

=

4 × 4

=

16

In general,

the total number of combinations equals the product of
the number of letters corresponding to each digit.

------------------------------------------------------------

Time Complexity:
----------------

Let

n

be the number of digits.

Each digit contributes at most

4

choices
(digits 7 and 9).

Therefore,

the recursion generates at most

4^n

combinations.

Each combination has length

n,

so constructing and storing one answer requires

O(n)

time.

Overall Time Complexity:

O(n × 4^n)

------------------------------------------------------------

Space Complexity:
-----------------

The recursion depth is at most

n,

since one recursive call is made for each digit.

The temporary string

s

also stores at most

n

characters.

Ignoring the output,

Auxiliary Space:

O(n)

The output itself stores every generated combination,

requiring

O(n × 4^n)

space in the worst case.

*/