class WordDictionary {
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
    
        TrieNode* root;
    
        bool dfs(string &word, TrieNode* node, int i) {
            if(i == word.size()) return node->isEnd();
    
            if(word[i] == '.') {
                for(auto x : node->links) {
                    if(x && dfs(word, x, i + 1)) return true; // if one path is found/succeeded
                }
                return false;
            }
    
            // normal character
            if(!node->containsKey(word[i])) return false;
            node = node->get(word[i]);
    
            return dfs(word, node, i + 1);
        }
    
    public:
        WordDictionary() {
            root = new TrieNode();
        }
        
        void addWord(string word) {
            TrieNode* node = root;
            for(auto x : word) {
                if(!node->containsKey(x)) node->put(x, new TrieNode());
                node = node->get(x);
            }
            node->setEnd();
        }
        
        bool search(string word) {
            return dfs(word, root, 0);
        }
    };
    
    /**
     * Your WordDictionary object will be instantiated and called as such:
     * WordDictionary* obj = new WordDictionary();
     * obj->addWord(word);
     * bool param_2 = obj->search(word);
     */

/*

Idea:
------
This problem extends the basic Trie (LeetCode 208) by
supporting a wildcard character

'.'

which can match

any one lowercase English letter.

The challenge is that whenever a wildcard is encountered,

there is no single path to follow.

Instead,

we must explore

every possible child

from the current Trie node.

Therefore,

the solution combines

Trie

+

Depth First Search (DFS).

------------------------------------------------------------

Why Trie?
---------

A Trie stores words character by character.

Every node represents one character,

and every root-to-node path represents a prefix.

Example

Words

bad

dad

mad

Trie

                 Root
              /     |     \
             b      d      m
             |      |      |
             a      a      a
             |      |      |
             d*     d*     d*

(* indicates end of a word)

Since common prefixes are shared,

searching proceeds character by character rather than
comparing complete strings.

------------------------------------------------------------

Trie Node Structure:
--------------------

Each TrieNode stores

1.

links[26]

Pointers to child nodes.

Each index corresponds to one lowercase letter.

'a'

↓

0

'b'

↓

1

...

'z'

↓

25

If

links[i] == NULL,

that child does not exist.

--------------------------------

2.

flag

Indicates whether a complete word ends at the current node.

This distinguishes

"app"

from merely being a prefix of

"apple".

------------------------------------------------------------

Helper Functions:
-----------------

containsKey(c)

Checks whether the current node already has a child
corresponding to character

c.

Time Complexity:

O(1)

--------------------------------

put(c, node)

Creates a new child node.

Time Complexity:

O(1)

--------------------------------

get(c)

Returns the child corresponding to character

c.

Time Complexity:

O(1)

--------------------------------

setEnd()

Marks the current node as the end of a valid word.

--------------------------------

isEnd()

Checks whether a complete word terminates here.

------------------------------------------------------------

Insertion:
----------

Insertion is identical to a standard Trie.

Start from the root.

For every character

If the child does not exist,

create it.

Move to the child.

After processing every character,

mark the final node as an end node.

------------------------------------------------------------

Example:

Insert

"bad"

Root

↓

b

↓

a

↓

d*

--------------------------------

Insert

"bat"

Only

't'

is added because

"ba"

already exists.

Root

↓

b

↓

a

↙     ↘

d*     t*

------------------------------------------------------------

Searching:
----------

Searching is performed using DFS because of the wildcard.

The recursive function

dfs(word, node, i)

means

"Can the remaining substring

word[i ... end]

be matched starting from the current Trie node?"

------------------------------------------------------------

DFS State:
----------

Current State consists of

1.

Current Trie node

--------------------------------

2.

Current index inside the search word

Together,

these uniquely determine the remaining search.

------------------------------------------------------------

Base Case:
----------

If

i == word.size(),

then every character has already been processed.

The search succeeds only if

the current Trie node marks the end of a complete word.

Return

node->isEnd().

This prevents prefixes from being treated as complete
words.

------------------------------------------------------------

Case 1

Normal Character:
-----------------

Suppose

word[i]

is

'a'

Only one path is possible.

First,

check whether that child exists.

If not,

the word cannot exist.

Return

false.

Otherwise,

move to that child and recursively process the next
character.

Example

Searching

"bad"

Root

↓

b

↓

a

↓

d*

------------------------------------------------------------

Case 2

Wildcard '.':
-------------

This is the key difference from LeetCode 208.

The wildcard can represent

any lowercase letter.

Therefore,

every existing child of the current node becomes a
possible choice.

For every child

if(child != NULL)

recursively search the remaining substring.

If

any

recursive call succeeds,

return

true

immediately.

Otherwise,

after exploring all children,

return

false.

------------------------------------------------------------

Why DFS?
--------

The wildcard introduces multiple possibilities.

For example,

Suppose the Trie contains

bad

dad

mad

Search

".ad"

At the first character,

'.'

can represent

'b'

'd'

or

'm'.

The search tree becomes

             .
        /     |     \
       b      d      m
       |      |      |
      ad     ad     ad

Each branch is explored recursively.

If one branch reaches a valid word,

the search succeeds.

DFS naturally handles this branching.

------------------------------------------------------------

Example 1:
----------

Words

bad

dad

mad

Search

"bad"

Root

↓

b

↓

a

↓

d*

Reached end.

flag == true

Answer

true

------------------------------------------------------------

Example 2:
----------

Search

".ad"

First character

'.'

Explore

b

↓

a

↓

d*

Found.

Immediately return

true.

No need to search

d

or

m.

------------------------------------------------------------

Example 3:
----------

Search

"b.."

Root

↓

b

↓

.

↓

.

At each wildcard,

every existing child is explored.

Eventually,

the path

b

↓

a

↓

d

matches.

Answer

true.

------------------------------------------------------------

Example 4:
----------

Search

"..z"

Suppose no word ends with

'z'.

Every possible branch is explored.

None succeeds.

Answer

false.

------------------------------------------------------------

Recursion Tree:
---------------

Suppose

Search

".a."

Trie contains

bad

bat

dad

                 .
           /      \
          b        d
          |        |
          a        a
        /   \       \
       d     t       d

Each wildcard creates branching.

The recursion explores

every valid path

until one succeeds.

------------------------------------------------------------

Why Does This Work?
-------------------

For a normal character,

there is only one valid child that can continue the
search.

The algorithm follows that unique path.

For a wildcard,

every child is a potential match.

The DFS recursively explores all possible continuations.

A search succeeds if and only if

there exists

at least one path that

1.

matches every character of the search word,

and

2.

ends at a Trie node marked as a complete word.

Therefore,

the algorithm correctly supports both exact characters and
wildcards.

------------------------------------------------------------

Correctness Proof:
------------------

We prove that the algorithm correctly determines whether a
matching word exists.

For a normal character,

the Trie contains at most one corresponding child.

If that child does not exist,

no stored word can match,

so returning

false

is correct.

Otherwise,

every valid matching word must continue through that child.

For a wildcard,

the character may represent any lowercase letter.

The algorithm recursively explores every existing child.

If any recursive call returns

true,

then there exists a word matching the wildcard pattern.

If all recursive calls return

false,

then no matching word exists.

Finally,

when every character has been processed,

the search succeeds only if the current node represents
the end of a stored word.

Thus,

the algorithm returns

true

if and only if

a matching dictionary word exists.

------------------------------------------------------------

Time Complexity:
----------------

Let

L

be the length of the search word.

Insertion

O(L)

--------------------------------

Search (without wildcard)

O(L)

--------------------------------

Search (with wildcards)

Suppose there are

k

wildcards.

Each wildcard may branch into as many as

26

children.

Worst-case Time Complexity

O(26^k × L)

In practice,

the branching factor is usually much smaller because many
child pointers are NULL.

------------------------------------------------------------

Space Complexity:
-----------------

Trie

If the total number of inserted characters is

M,

the Trie contains at most

M + 1

nodes.

Space

O(M)

--------------------------------

DFS Recursion Stack

Maximum depth equals the word length.

Space

O(L)

------------------------------------------------------------

Comparison with LeetCode 208:
-----------------------------

LeetCode 208

• Exact word search only.

• At every character there is exactly one possible path.

• Pure Trie traversal.

--------------------------------

LeetCode 211 (This Problem)

• Supports wildcard '.'.

• A wildcard can branch into multiple possible paths.

• Uses Trie + DFS to explore every valid branch.

The Trie efficiently stores the dictionary,

while DFS enables searching all possible wildcard
interpretations.

*/