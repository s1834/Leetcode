class Solution {
    public:
        bool isAlienSorted(vector<string>& words, string order) {
            unordered_map<char, int> mp;
            for(int i = 0; i < order.size(); i++) mp[order[i]] = i;
    
            int n = words.size();
            for(int i = 0; i < n - 1; i++) {
                string word1 = words[i], word2 = words[i + 1];
                int m = word1.size(); 
                for(int j = 0; j < m; j++) {
                    if(j == word2.size()) return false;
                    if (word1[j] != word2[j]) {
                        if (mp[word1[j]] > mp[word2[j]]) return false;
                        break;
                    }
                }
            }
            return true;
        }
    };

/*

Idea:
------
The words are claimed to be sorted according to an

Alien Dictionary Order,

where the order of characters is different from the normal
English alphabet.

Instead of comparing characters using

'a' < 'b' < 'c' ...

we first build a mapping that tells us the position of each
character in the alien alphabet.

Then,

just like checking whether words are sorted in a normal
dictionary,

we compare every pair of adjacent words.

If every adjacent pair is correctly ordered,

then the entire list is sorted.

------------------------------------------------------------

Key Observation:
----------------

To determine whether an entire list is sorted,

we do NOT need to compare every pair of words.

It is sufficient to compare only

adjacent words.

For example,

If

word1 ≤ word2

and

word2 ≤ word3

and

word3 ≤ word4,

then

the entire list is sorted.

This is the same idea used in checking whether an array is
sorted.

------------------------------------------------------------

Character Mapping:
------------------

Since the alphabet order is different,

we first convert every character into its rank.

Example

order

=

"hlabcdefgijkmnopqrstuvwxyz"

Mapping becomes

h → 0

l → 1

a → 2

b → 3

c → 4

...

This allows every character comparison to become an integer
comparison.

------------------------------------------------------------

Hash Map:
---------

unordered_map<char, int> mp

stores

Character

↓

Alien Alphabet Position

For every character

order[i],

store

mp[order[i]] = i

Now,

instead of comparing characters directly,

we compare their mapped positions.

------------------------------------------------------------

Comparing Two Words:
--------------------

Suppose

word1

and

word2

are adjacent.

Compare characters from left to right.

Three situations may occur.

============================================================

Case 1

Characters are Equal

============================================================

Continue comparing the next position.

Example

apple

apply

The prefix

"appl"

is identical.

Continue until the first differing character.

------------------------------------------------------------

Case 2

Characters are Different

============================================================

This is the first position where the words differ.

Only this character determines the lexicographical order.

If

mp[word1[j]] < mp[word2[j]]

then

word1

correctly comes before

word2.

Otherwise,

the list is not sorted.

After finding the first differing character,

there is no need to compare the remaining characters.

------------------------------------------------------------

Case 3

One Word Ends

============================================================

Suppose

word1 = "apple"

word2 = "app"

The shorter word should come first if one word is a prefix
of the other.

Since

"apple"

appears before

"app",

the order is incorrect.

In the code,

if

j == word2.size()

while still comparing characters,

it means

word2

ended before

word1,

so return

false.

------------------------------------------------------------

Algorithm:
----------

Step 1

Build a mapping from every alien character to its rank.

------------------------------------------------------------

Step 2

Compare every adjacent pair of words.

------------------------------------------------------------

Step 3

Scan both words character by character.

------------------------------------------------------------

Step 4

If characters are equal,

continue.

------------------------------------------------------------

Step 5

If the second word finishes before the first,

return

false.

This means a longer prefix appears before its shorter
prefix.

------------------------------------------------------------

Step 6

When the first differing character is found,

compare their alien ranks.

If the first character has a larger rank,

the words are incorrectly ordered.

Return

false.

Otherwise,

the current pair is correctly sorted,

and move to the next pair.

------------------------------------------------------------

Step 7

If every adjacent pair satisfies the ordering,

return

true.

------------------------------------------------------------

Example 1:
----------

words

=

["hello","leetcode"]

order

=

"hlabcdefgijkmnopqrstuvwxyz"

Mapping

h → 0

l → 1

a → 2

...

Compare

hello

leetcode

First differing character

h

vs

l

Alien ranks

0

<

1

Correct order.

Answer

true

------------------------------------------------------------

Example 2:
----------

words

=

["word","world","row"]

Compare

word

world

Characters

w == w

o == o

First difference

r

vs

l

Alien ranks

r > l

Therefore,

word

should come after

world.

Return

false.

------------------------------------------------------------

Example 3:
----------

words

=

["apple","app"]

Characters

a == a

p == p

p == p

Now,

word2

ends,

while

word1

still has remaining characters.

Since a longer word cannot appear before its own prefix,

return

false.

------------------------------------------------------------

Why Compare Only Until the First Difference?
--------------------------------------------

Lexicographical ordering depends entirely on the first
position where two words differ.

Example

cat

car

Compare

c == c

a == a

First difference

t

vs

r

Since

t

comes after

r,

the remaining characters no longer matter.

The decision has already been made.

------------------------------------------------------------

Why Does This Work?
-------------------

Every adjacent pair is compared exactly as dictionary
ordering requires.

Characters are compared using their alien alphabet ranks
instead of normal ASCII values.

If a mismatch is found,

the first differing character completely determines the
correct order.

If one word is a prefix of another,

the shorter word must appear first,

which is also explicitly checked.

Since every adjacent pair satisfies the alien dictionary
rules,

the entire list is correctly sorted.

------------------------------------------------------------

Correctness Proof:
------------------

We prove that the algorithm correctly determines whether
the list is sorted according to the alien alphabet.

For every adjacent pair,

characters are compared from left to right.

If a differing character is found,

their alien ranks determine the lexicographical order.

If the first word's character has a larger rank,

the pair is incorrectly ordered,

so returning

false

is correct.

If all compared characters are identical,

then one word is a prefix of the other.

The algorithm correctly verifies that the shorter word
appears first.

Thus,

every adjacent pair satisfies the exact definition of
lexicographical ordering under the alien alphabet.

Since the list is sorted if and only if every adjacent pair
is sorted,

the algorithm returns

true

exactly when the entire list is correctly ordered.

------------------------------------------------------------

Time Complexity:
----------------

Let

N

be the number of words,

and

L

be the average (or maximum) word length.

Building the character mapping

O(26)

--------------------------------

Comparing adjacent words

O(total characters compared)

Worst Case

O(N × L)

Overall Time Complexity

O(N × L)

------------------------------------------------------------

Space Complexity:
-----------------

Hash Map

Stores the rank of all

26

characters.

Overall Auxiliary Space

O(26)

which is effectively

O(1).

------------------------------------------------------------

Note:
-----

The solution never rearranges the words.

It simply verifies whether the existing order satisfies the
alien dictionary rules using the custom alphabet mapping.

*/