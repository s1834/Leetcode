class Solution {
    private:
        struct TrieNode {
            TrieNode* links[26];
            bool flag = false;
    
            // check if 'c' already exists
            bool containsKey(char c) {
                return links[c - 'a'] != NULL;
            };
    
            // from 'c' create a new empty node
            void put(char c, TrieNode* node) {
                links[c - 'a'] = node;
            }
    
            // move current pointer to newly created node
            TrieNode* get(char c) {
                return links[c - 'a'];
            }
    
            // if word complete, set flag = true;
            void setEnd() {
                flag = true;
            }
            
            // check if a word ends here
            bool isEnd() {
                return flag;
            }
        };
    
        // initialize Trie node
        TrieNode* root = new TrieNode();
        vector<int> dp;
    
        // insert word
        void insert(string word) {
            TrieNode* node = root;
            for(auto x : word) {
                if(!node->containsKey(x)) node->put(x, new TrieNode());
                node = node->get(x);
            }
            node->setEnd();
        }
        
    
        int search(string &s, int i) {
            // if i is greater than equal to the word itself return 0
            if(i >= s.size()) return 0; 
    
            // If we've already computed the answer for this index, return the stored result.
            if(dp[i] != -1) return dp[i];
    
            // assign node to root to use
            TrieNode* node = root;
    
            // Search without current char, add 1 to count
            int ans = 1 + search(s, i + 1);
    
            for(int j = i; j < s.size(); j++) {
                if(!node->containsKey(s[j])) break; // if not word, break
    
                node = node->get(s[j]); // move to next word
    
                if (node->isEnd()) ans = min(ans, search(s, j + 1)); // if word ends, get the smaller value from current and next recursion
            }
    
            // Store the answer for this index, so we don't recompute it later.
            return dp[i] = ans;
        }
    
    public:
        int minExtraChar(string s, vector<string>& dictionary) {
            // insert each word in Trie
            for(auto x : dictionary) insert(x);
    
            dp.assign(s.size(), -1);
    
            // Search Trie
            return search(s, 0);;
        }
    };

/*

Idea:
------
The goal is to split the string into dictionary words while
minimizing the number of characters that do not belong to
any dictionary word.

Unlike the classic Word Break problem (LeetCode 139),

we are allowed to skip characters.

However,

every skipped character contributes

1

to the final answer.

Therefore,

at every position we have two choices:

1.

Treat the current character as an extra character.

2.

Start a dictionary word from the current position.

We choose whichever option produces fewer extra
characters.

To efficiently search dictionary words starting from any
position,

a Trie is used.

Since the same suffix may be solved many times,

Dynamic Programming (Memoization) is used to avoid repeated
computations.

Thus, the solution combines

Trie

+

DFS

+

Memoization (Top-Down DP).

------------------------------------------------------------

Why Trie?
---------

Suppose the dictionary contains

{

"look",

"looking",

"book",

"cat"

}

and we are currently at position

i.

Without a Trie,

we would compare every dictionary word with

s[i...]

which is inefficient.

Instead,

the Trie allows us to walk through the string one
character at a time.

The moment a character is missing,

we know

no longer dictionary word

can match,

so we immediately stop searching.

------------------------------------------------------------

Trie Structure:
---------------

Each Trie node contains

1.

links[26]

Pointers to children.

Each index corresponds to one lowercase letter.

--------------------------------

2.

flag

Indicates whether a dictionary word ends here.

------------------------------------------------------------

Example:

Dictionary

cat

car

care

Trie

                  Root
                    |
                    c
                    |
                    a
                 /      \
                t*       r*
                          \
                           e*

The prefix

"ca"

is shared by all words.

------------------------------------------------------------

DP Definition:
--------------

This is the most important part of the solution.

Define

dp[i]

=

Minimum number of extra characters needed to process

s[i ... n-1].

In other words,

starting from index

i,

what is the minimum penalty we must pay?

Once

dp[i]

is computed,

we never recompute it again.

------------------------------------------------------------

Meaning of search(s, i):
------------------------

The recursive function

search(s, i)

returns

"The minimum number of extra characters required to process
the suffix

s[i ... end]."

Every recursive call solves

one suffix.

------------------------------------------------------------

Base Case:
----------

If

i == s.size(),

there are no characters remaining.

Therefore,

no extra characters are needed.

Return

0.

------------------------------------------------------------

Why Memoization?
----------------

Different recursive paths often reach the same index.

Example

s =

"leetcode"

Suppose one path reaches

index = 4

through

"leet"

Another path reaches

index = 4

after skipping some characters.

Both now need to solve

"code"

Without memoization,

the suffix

"code"

would be solved repeatedly.

Instead,

once

dp[4]

is computed,

every future call simply returns

dp[4].

This reduces exponential recursion into polynomial
subproblems.

------------------------------------------------------------

The Two Choices:
----------------

Suppose we are currently at index

i.

We have exactly two possibilities.

============================================================

Choice 1

Skip Current Character

============================================================

Treat

s[i]

as an extra character.

Then

1

extra character is added,

and we continue from

i + 1.

Therefore,

cost

=

1 + search(s, i + 1)

This line appears as

int ans = 1 + search(s, i + 1);

Initially,

this assumes

the current character is not part of any dictionary word.

------------------------------------------------------------

Example

String

apple

Current index

0

Skip

'a'

↓

Need to solve

"pple"

If solving

"pple"

requires

2

extra characters,

then total becomes

1 + 2 = 3.

------------------------------------------------------------

Choice 2

Match Dictionary Words

============================================================

Instead of skipping,

try to form a dictionary word beginning at

i.

Start from the Trie root.

Move character by character.

For every position

j,

follow

s[j].

If the path disappears,

break immediately.

No longer word can match.

Whenever

node->isEnd()

becomes true,

we have discovered a dictionary word

s[i...j].

Now,

none of those characters are extra.

Therefore,

the answer becomes

search(s, j + 1)

Notice

we do NOT add

1

because those characters belong to a valid dictionary word.

So,

ans = min(ans, search(s, j + 1));

------------------------------------------------------------

Example

Dictionary

{

"leet",

"code"

}

String

leetcode

Index

0

Trie discovers

"leet"

Instead of paying

4

extra characters,

jump directly to

index = 4.

Answer becomes

search(4)

------------------------------------------------------------

Why Take the Minimum?
---------------------

Suppose

String

apple

Dictionary

{

"app"

}

At index

0

Option 1

Skip

'a'

Cost

=

1 + search(1)

--------------------------------

Option 2

Take

"app"

Cost

=

search(3)

Obviously,

using the dictionary word is better.

Therefore,

we choose

minimum

of both options.

------------------------------------------------------------

Algorithm:
----------

Step 1

Insert every dictionary word into the Trie.

------------------------------------------------------------

Step 2

Initialize

dp

with

-1

meaning

"Not yet computed."

------------------------------------------------------------

Step 3

Start DFS from

index = 0.

------------------------------------------------------------

Step 4

Assume the current character is extra.

ans =

1 + search(i + 1)

------------------------------------------------------------

Step 5

Walk through the Trie while extending the substring.

------------------------------------------------------------

Step 6

Whenever a dictionary word ends,

update

ans

using

search(nextIndex).

------------------------------------------------------------

Step 7

Store

ans

inside

dp[i].

------------------------------------------------------------

Step 8

Return

dp[0].

------------------------------------------------------------

Example Walkthrough:
--------------------

String

"leetscode"

Dictionary

{

"leet",

"code",

"leetcode"

}

Initially

search(0)

--------------------------------

Choice 1

Skip

'l'

Cost

=

1 + search(1)

--------------------------------

Trie Search

l

↓

e

↓

e

↓

t

Dictionary word found.

Cost

=

search(4)

--------------------------------

Now solve

"scode"

At index

4

Choice 1

Skip

's'

Cost

=

1 + search(5)

Trie finds no word beginning with

's'

Therefore,

answer for index

4

=

1 + search(5)

--------------------------------

Index

5

Trie matches

"code"

Cost

=

search(9)

Since

9 == n,

Return

0.

Therefore,

dp[5] = 0

Now,

dp[4]

=

1

Finally,

dp[0]

=

1

Only

's'

is an extra character.

------------------------------------------------------------

DP Visualization:
-----------------

Suppose

s = "leetscode"

Indexes

0 1 2 3 4 5 6 7 8

l e e t s c o d e

The DP values become

dp[8] = 1

dp[7] = 2

dp[6] = 3

dp[5] = 0

dp[4] = 1

dp[3] = ...

...

Every

dp[i]

stores the answer for the suffix beginning at

i.

Once computed,

it is reused whenever another recursion reaches the same
index.

------------------------------------------------------------

Why Does This Work?
-------------------

For every index,

the algorithm explores every possible decision.

Either

the current character is treated as extra,

or

the current position starts a valid dictionary word.

Every dictionary word beginning at the current position is
considered,

and the minimum cost among all possibilities is chosen.

Since

dp[i]

stores the optimal answer for every suffix,

every recursive call immediately reuses previously
computed results.

Therefore,

every suffix is solved exactly once,

guaranteeing the globally minimum number of extra
characters.

------------------------------------------------------------

Correctness Proof:
------------------

We prove that

search(i)

returns the minimum number of extra characters required
for the suffix

s[i...n-1].

Base Case:

When

i == n,

the suffix is empty,

so zero extra characters are needed.

This is optimal.

Inductive Step:

Assume every suffix beginning after

i

returns its optimal answer.

At position

i,

there are only two valid actions.

1.

Treat

s[i]

as an extra character.

Cost

=

1 + search(i + 1).

2.

Use any dictionary word beginning at

i.

Cost

=

search(nextIndex).

By the induction hypothesis,

every recursive call already returns the optimal answer
for its remaining suffix.

Taking the minimum over all valid choices therefore yields
the optimal answer for

dp[i].

Hence,

by induction,

search(0)

returns the minimum possible number of extra characters.

------------------------------------------------------------

Time Complexity:
----------------

Let

n

be the length of the string.

Each index

i

is computed only once because of memoization.

For every index,

we traverse the Trie until either

the path ends,

or

the string ends.

If

L

is the maximum dictionary word length,

each state performs at most

L

Trie transitions.

Overall Time Complexity:

O(n × L)

In the worst case,

L ≤ n,

giving

O(n²).

------------------------------------------------------------

Space Complexity:
-----------------

Trie

O(total characters in dictionary)

--------------------------------

DP Array

O(n)

--------------------------------

Recursion Stack

O(n)

Overall Auxiliary Space

O(total dictionary characters + n)

*/