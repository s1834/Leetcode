class Solution {
    private:
        vector<string> ans;
        unordered_set<string> st;
    
        void solve(string &s, string &currSentence, int i) {
            if(i >= s.size()) {
                ans.push_back(currSentence);
                return;
            }
    
            for(int j = i; j < s.size(); j++) {
                string tempWord = s.substr(i, j - i + 1);
                if(st.count(tempWord)) { // valid word
                    string tempSentence = currSentence; // store current sentence to backtrack to this later
    
                    if(currSentence != "") currSentence += " "; // add space
    
                    currSentence += tempWord; // add tempWord
    
                    solve(s, currSentence, j + 1); // Explore
    
                    currSentence = tempSentence; // remove tempWord
                }
            }
        }
    
    public:
        vector<string> wordBreak(string s, vector<string>& wordDict) {
            for(auto x : wordDict) st.insert(x);
            string currSentence = "";
            solve(s, currSentence, 0);
            return ans;
        }
    };

/*

Idea:
------
The problem asks us to generate

all possible sentences

by inserting spaces into the given string such that every
resulting word belongs to the dictionary.

Unlike Word Break I (LeetCode 139), which only asks whether
a valid segmentation exists,

this problem requires generating every valid sentence.

Since every position can branch into multiple valid words,

Backtracking + Depth First Search (DFS)

is a natural approach.

------------------------------------------------------------

Key Observation:
----------------

At every index,

we try every possible substring starting from that index.

If the substring exists in the dictionary,

we choose it as the next word,

append it to the current sentence,

and recursively solve the remaining suffix.

After recursion finishes,

we undo the choice and explore the next possible word.

This is the classic

"Choose → Explore → Backtrack"

pattern.

------------------------------------------------------------

Data Structures:
----------------

1. unordered_set<string> st

Stores every dictionary word.

Using a hash set allows checking whether a substring is a
valid dictionary word in

O(1)

average time.

--------------------------------

2. vector<string> ans

Stores every valid sentence.

--------------------------------

3. string currSentence

Represents the sentence currently being constructed during
DFS.

------------------------------------------------------------

DFS State:
----------

The recursive function

solve(s, currSentence, i)

means:

"We have already formed a valid sentence using characters

0 ... i-1.

Now find every possible way to split the remaining suffix
starting from index

i."

------------------------------------------------------------

Base Case:
----------

If

i == s.size()

then every character has been successfully used.

The current sentence represents one complete valid
segmentation.

Store it inside

ans

and return.

------------------------------------------------------------

Recursive Choice:
-----------------

From the current index

i,

try every ending position

j

such that

i ≤ j < n.

Construct

tempWord

=

s.substr(i, j - i + 1)

If

tempWord

exists in the dictionary,

it is one possible choice.

------------------------------------------------------------

Choose Step:
------------

Before modifying

currSentence,

store its current value.

string tempSentence = currSentence;

This snapshot allows us to restore the sentence later.

--------------------------------

If the sentence is not empty,

append a space.

--------------------------------

Append the chosen word.

currSentence += tempWord;

Now recursively solve the remaining string beginning from

j + 1.

------------------------------------------------------------

Backtracking:
-------------

After recursion returns,

restore

currSentence

to its previous state.

currSentence = tempSentence;

This removes the recently chosen word and allows exploring
other possible choices from the same index.

Without this restoration,

future recursive calls would incorrectly reuse words from
previous branches.

------------------------------------------------------------

Algorithm:
----------

Step 1

Insert every dictionary word into a hash set.

------------------------------------------------------------

Step 2

Start DFS from index

0.

------------------------------------------------------------

Step 3

Generate every substring beginning at the current index.

------------------------------------------------------------

Step 4

If the substring is a dictionary word,

append it to the sentence.

------------------------------------------------------------

Step 5

Recursively solve the remaining suffix.

------------------------------------------------------------

Step 6

Restore the previous sentence after recursion finishes.

------------------------------------------------------------

Step 7

Whenever the end of the string is reached,

store the completed sentence.

------------------------------------------------------------

Example:
--------

Input

s =

"catsanddog"

Dictionary

{

"cat",

"cats",

"and",

"sand",

"dog"

}

--------------------------------

Start

Index = 0

Possible words

cat

cats

--------------------------------

Choose

cat

Sentence

"cat"

Remaining

"sanddog"

--------------------------------

Choose

sand

Sentence

"cat sand"

Remaining

"dog"

--------------------------------

Choose

dog

Sentence

"cat sand dog"

Reached end.

Store

"cat sand dog"

--------------------------------

Backtrack

Return to

"cat"

Try another word.

--------------------------------

Choose

cats

Sentence

"cats"

Remaining

"anddog"

--------------------------------

Choose

and

Sentence

"cats and"

Remaining

"dog"

--------------------------------

Choose

dog

Sentence

"cats and dog"

Store it.

Final Answer

{

"cat sand dog",

"cats and dog"

}

------------------------------------------------------------

Recursion Tree:
---------------

catsanddog

├── cat
│     └── sand
│             └── dog
│                    ✓
│
└── cats
      └── and
              └── dog
                     ✓

Every root-to-leaf path represents one valid sentence.

------------------------------------------------------------

Why Does This Work?
-------------------

At every recursive call,

the algorithm considers every possible word that starts at
the current position.

Whenever a valid dictionary word is found,

it is appended to the current sentence,

and the remaining suffix is solved recursively.

Backtracking restores the sentence after each recursive
call,

ensuring that every possible segmentation is explored
independently.

The recursion terminates only when every character has been
used exactly once,

guaranteeing that every stored sentence is valid.

Since every possible split is explored,

no valid sentence is missed.

------------------------------------------------------------

Correctness Proof:
------------------

We prove that the algorithm generates exactly all valid
sentences.

At every index,

the algorithm considers every possible substring beginning
at that index.

Whenever a substring belongs to the dictionary,

it recursively generates every valid sentence that can be
formed from the remaining suffix.

By the induction hypothesis,

the recursive call returns every valid continuation.

Appending the chosen word before the recursive call
produces every valid sentence beginning with that word.

Since this is done for every valid dictionary word starting
at the current index,

every possible sentence is generated.

Backtracking restores the previous state before exploring
another choice,

preventing interference between different recursive
branches.

Therefore,

every valid sentence is generated exactly once.

------------------------------------------------------------

Time Complexity:
----------------

Let

n

be the length of the string.

In the worst case,

every position can branch into many valid words.

The number of valid sentences itself can be exponential.

Therefore,

Worst-case Time Complexity:

O(2^n × n)

The additional factor of

n

comes from constructing substrings and sentences.

(Without memoization, many suffixes may also be recomputed.)

------------------------------------------------------------

Space Complexity:
-----------------

Hash Set

O(D)

where

D

is the number of dictionary words.

--------------------------------

Recursion Stack

O(n)

--------------------------------

Current Sentence

O(n)

--------------------------------

Output

O(total length of all valid sentences)

which dominates in the worst case.

Ignoring the output,

Auxiliary Space:

O(n + D)

------------------------------------------------------------

Note:
-----

This solution does not use memoization.

The same suffix may be solved multiple times from different
recursive paths, leading to repeated work.

An optimized solution memoizes the sentences that can be
formed from each starting index, reducing redundant
computations significantly.

*/