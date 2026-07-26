class Solution {
    private: 
        vector<vector<string>> ans;
        vector<string> part;
    
        bool isPalindrome(string s) {
            int first = 0, last = s.size() - 1;
            while(first < last) {
                if(s[first] != s[last]) return false;
                first++;
                last--;
            }
            return true;
        }
    
        void dfs(string& s, int start) {
            if(start == s.size()) {
                ans.push_back(part);
                return;
            }
    
            int n = s.size();
            for(int i = start; i < n; i++) {
                string x = s.substr(start, i - start + 1);
                if(isPalindrome(x)) {
                    part.push_back(x);
                    dfs(s, i + 1);
                    part.pop_back();
                }
            }
        }
    
    public:
        vector<vector<string>> partition(string s) {
            dfs(s, 0);
            return ans;
        }
    };

/*

Idea:
------
We need to partition the given string into multiple
substrings such that

every substring is a palindrome.

Unlike problems where we only need one valid partition,

here we must generate

all possible palindrome partitions.

This naturally becomes a

Backtracking + Depth First Search (DFS)

problem because at every position we have multiple
possible palindrome substrings to choose from.

------------------------------------------------------------

Key Observation:
----------------

Suppose we are currently at index

start

of the string.

Any substring

s[start...i]

can become the next part of our partition

provided it is a palindrome.

Once we choose that substring,

the remaining problem becomes

"Find all palindrome partitions of the remaining suffix."

This is exactly the same problem on a smaller string,

making recursion a perfect fit.

------------------------------------------------------------

DFS State:
----------

The recursive function

dfs(start)

means:

"Generate every palindrome partition for the suffix

s[start ... n-1]."

During recursion,

the vector

part

stores the palindrome substrings chosen so far.

For example,

String

"aab"

Suppose

part = ["aa"]

Then

dfs(2)

means

"We have already chosen

'aa'

and now need to partition the remaining suffix

'b'."

------------------------------------------------------------

Palindrome Check:
-----------------

Before choosing a substring,

we must verify that it is a palindrome.

The helper function

isPalindrome()

uses two pointers.

Suppose

Substring

"racecar"

Pointer

first

starts from the beginning.

Pointer

last

starts from the end.

Compare

r == r

↓

a == a

↓

c == c

↓

e

Pointers meet.

Therefore,

the substring is a palindrome.

If at any point

s[first] != s[last],

the substring cannot be a palindrome.

Time Complexity of palindrome check

O(length of substring)

------------------------------------------------------------

Recursive Choice:
-----------------

At every recursion level,

we try every possible ending index.

Suppose

start = 2

Possible choices are

s[2...2]

s[2...3]

s[2...4]

...

s[2...n-1]

Each substring is checked.

If it is a palindrome,

it becomes one partition piece.

Otherwise,

it is ignored.

------------------------------------------------------------

Backtracking:
-------------

Whenever a palindrome substring is chosen,

it is added to

part.

After recursively solving the remaining suffix,

the substring is removed before trying the next choice.

Example

String

"aab"

Initially

part = []

--------------------------------

Choose

"a"

part = ["a"]

↓

DFS

--------------------------------

Choose

"a"

part = ["a","a"]

↓

DFS

--------------------------------

Choose

"b"

part = ["a","a","b"]

Complete partition found.

Store it.

--------------------------------

Backtrack

Remove

"b"

part = ["a","a"]

Return.

--------------------------------

Backtrack

Remove

second

"a"

part = ["a"]

Try another substring.

--------------------------------

Choose

"ab"

Not palindrome.

Ignore.

--------------------------------

Backtrack

Remove first

"a"

Try

"aa"

------------------------------------------------------------

Base Case:
----------

When

start == s.length()

it means

every character has already been partitioned.

The current partition stored inside

part

is complete.

Store it inside

ans.

------------------------------------------------------------

Algorithm:
----------

Step 1

Start DFS from index

0.

------------------------------------------------------------

Step 2

For every possible ending index

i

construct the substring

s[start ... i].

------------------------------------------------------------

Step 3

Check whether the substring is a palindrome.

------------------------------------------------------------

Step 4

If it is,

append it to

part.

------------------------------------------------------------

Step 5

Recursively partition the remaining suffix

starting from

i + 1.

------------------------------------------------------------

Step 6

After recursion,

remove the last substring.

This restores the previous state,

allowing another partition choice.

------------------------------------------------------------

Step 7

Repeat until every possible palindrome substring has been
considered.

------------------------------------------------------------

Recursion Tree Example:
-----------------------

Input

"aab"

Start

dfs(0)

                          []
                           |
          ---------------------------------
          |                               |
         "a"                            "aa"
          |                               |
        ["a"]                          ["aa"]
          |                               |
      ------------                        |
      |          |                        |
     "a"        "ab"                     "b"
      |       (invalid)                  |
   ["a","a"]                         ["aa","b"]
      |
      |
     "b"
      |
["a","a","b"]

Valid partitions

["a","a","b"]

["aa","b"]

------------------------------------------------------------

Example:
--------

Input

"aab"

--------------------------------

Choose

"a"

Remaining

"ab"

--------------------------------

Choose

"a"

Remaining

"b"

--------------------------------

Choose

"b"

Partition

["a","a","b"]

--------------------------------

Backtrack

Try

"ab"

Not palindrome.

--------------------------------

Backtrack

Choose

"aa"

Remaining

"b"

--------------------------------

Choose

"b"

Partition

["aa","b"]

Answer

[
 ["a","a","b"],
 ["aa","b"]
]

------------------------------------------------------------

Why Does This Work?
-------------------

At every position,

the algorithm explores

every possible substring beginning from that position.

Only palindrome substrings are allowed to become part of
the partition.

Whenever a palindrome is chosen,

the remaining suffix is solved recursively.

Backtracking guarantees that after exploring one choice,

the algorithm returns to the previous state and explores
every other valid choice.

Since every possible palindrome substring is considered,

and every recursive branch eventually reaches the end of
the string,

every valid palindrome partition is generated exactly
once.

------------------------------------------------------------

Mathematical View:
------------------

Suppose

P(start)

represents

all palindrome partitions of

s[start ... n-1].

Then

P(start)

is obtained by

choosing every palindrome prefix

s[start...i]

and recursively appending every partition from

P(i+1).

Formally,

P(start)

=

⋃

for every palindrome

s[start...i]

{

s[start...i]

+

P(i+1)

}

This recursive definition is exactly what the DFS
implements.

------------------------------------------------------------

Time Complexity:
----------------

Let

n

be the length of the string.

There are

O(2^n)

possible ways to partition a string.

For each partition,

every chosen substring may require

O(n)

time to verify whether it is a palindrome.

Hence,

the overall worst-case time complexity is

O(n × 2^n)

(Without precomputing palindromes.)

More precisely,

because palindrome checking itself is O(n),
the worst-case bound is often written as

O(n² × 2^n).

------------------------------------------------------------

Space Complexity:
-----------------

Recursion depth

At most

n

because one character can be chosen at each recursive
call.

Current partition

Stores at most

n

substrings.

Ignoring the output,

Auxiliary Space

O(n)

The output itself may contain

O(n × 2^n)

characters across all partitions,
which is unavoidable because every valid partition must be
stored.

*/