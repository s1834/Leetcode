class Trie {
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
    
    public:
        Trie() {
            root = new TrieNode();
        }
        
        // insert word
        void insert(string word) {
            TrieNode* node = root;
            for(auto x : word) {
                if(!node->containsKey(x)) node->put(x, new TrieNode());
                node = node->get(x);
            }
            node->setEnd();
        }
        
        // search complete word
        bool search(string word) {
            TrieNode* node = root;
            for(auto x : word) {
                if(!node->containsKey(x)) return false;
                node = node->get(x);
            }
            return node->isEnd();
        }
        
        // search only if a prefix exists
        bool startsWith(string prefix) {
            TrieNode* node = root;
            for(auto x : prefix) {
                if(!node->containsKey(x)) return false;
                node = node->get(x);
            }
            return true;
        }
    };
    
    /**
     * Your Trie object will be instantiated and called as such:
     * Trie* obj = new Trie();
     * obj->insert(word);
     * bool param_2 = obj->search(word);
     * bool param_3 = obj->startsWith(prefix);
     */

/*

Idea:
------
A Trie (also called a Prefix Tree) is a specialized tree
data structure designed for storing and searching strings
efficiently.

Unlike storing complete words separately, a Trie stores
their common prefixes only once.

Each node represents a single character, and every path
from the root corresponds to a prefix.

Example:

Insert

"cat"

"car"

Trie becomes

                 Root
                   |
                   c
                   |
                   a
                 /   \
                t     r

Notice that the prefix

"ca"

is stored only once.

This sharing of prefixes makes Trie extremely efficient
for prefix-related operations.

------------------------------------------------------------

Trie Node Structure:
--------------------

Each TrieNode contains

1.

links[26]

An array of pointers.

Each index represents one lowercase English letter.

Index Mapping

'a' -> 0

'b' -> 1

...

'z' -> 25

If

links[i]

is NULL,

that character does not exist from the current node.

Otherwise,

it points to the next character.

--------------------------------

2.

flag

A boolean indicating whether a complete word ends at the
current node.

For example,

After inserting

"app"

and

"apple"

                 Root
                   |
                   a
                   |
                   p
                   |
                   p (flag = true)
                   |
                   l
                   |
                   e (flag = true)

Both words exist simultaneously.

Without

flag,

we could not distinguish

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

Creates a new edge for character

c.

Time Complexity:

O(1)

--------------------------------

get(c)

Returns the child node corresponding to character

c.

Time Complexity:

O(1)

--------------------------------

setEnd()

Marks that a complete word ends at the current node.

--------------------------------

isEnd()

Checks whether the current node represents the end of a
valid word.

------------------------------------------------------------

Why Does Every Node Store 26 Pointers?
--------------------------------------

Since the problem contains only lowercase English letters,

every node may have at most

26

children.

Instead of searching through a list,

the correct child is obtained directly using

c - 'a'

Example

Character

'd'

Index

'd' - 'a'

=

3

So,

links[3]

stores the next node.

This allows every character transition to happen in

O(1)

time.

------------------------------------------------------------

Insert Operation:
-----------------

Goal:

Insert every character of the word into the Trie.

If a character does not already exist,

create a new node.

Otherwise,

reuse the existing node.

Finally,

mark the last node as the end of the word.

------------------------------------------------------------

Algorithm:
----------

Suppose

word = "apple"

Start from

root.

--------------------------------

Character

'a'

Does not exist.

Create node.

Move to it.

--------------------------------

Character

'p'

Create if necessary.

Move.

--------------------------------

Character

'p'

Create if necessary.

Move.

--------------------------------

Character

'l'

Create if necessary.

Move.

--------------------------------

Character

'e'

Create if necessary.

Move.

--------------------------------

Mark last node

flag = true.

------------------------------------------------------------

Example:

Insert

"cat"

Initially

Root

After

'c'

Root

 |
 c

After

'a'

Root

 |
 c
 |
 a

After

't'

Root

 |
 c
 |
 a
 |
 t (End)

------------------------------------------------------------

Suppose we now insert

"car"

The Trie becomes

Root

 |
 c
 |
 a
/ \
t  r

Notice

"ca"

was reused.

Only

'r'

was newly created.

------------------------------------------------------------

Search Operation:
-----------------

Goal:

Determine whether the complete word exists.

Algorithm:

Start from

root.

For every character

If child does not exist,

return

false.

Otherwise,

move to the child.

After processing every character,

return

flag.

Why check

flag?

Suppose Trie contains

"apple"

Searching

"app"

reaches the node successfully.

However,

if

flag == false,

then

"app"

was never inserted.

It is merely a prefix.

Therefore,

search returns

false.

------------------------------------------------------------

Example:

Inserted

"apple"

Search

"apple"

Root

↓

a

↓

p

↓

p

↓

l

↓

e

flag = true

Answer

true

--------------------------------

Search

"app"

Root

↓

a

↓

p

↓

p

flag = false

Answer

false

------------------------------------------------------------

Prefix Search (startsWith):
---------------------------

Unlike

search(),

we only need to verify that every character of the prefix
exists.

The last node

does not

need to be marked as the end of a word.

Algorithm:

Start from

root.

For every character

If child missing

return false.

Otherwise,

move.

After processing every character,

return true.

------------------------------------------------------------

Example:

Inserted

"apple"

startsWith("app")

Root

↓

a

↓

p

↓

p

Reached successfully.

Answer

true

Although

"app"

may not be a complete word,

it is a valid prefix.

------------------------------------------------------------

Why Does This Work?
-------------------

Every inserted word creates exactly one path from the
root.

Common prefixes share the same nodes,

preventing duplicate storage.

During insertion,

new nodes are created only when necessary.

During search,

following the characters uniquely determines whether the
word exists.

If any required edge is missing,

the word cannot exist.

The

flag

ensures that complete words are distinguished from mere
prefixes.

Thus,

Insert

correctly stores every word,

Search

correctly identifies complete words,

and

startsWith

correctly verifies prefixes.

------------------------------------------------------------

Example Walkthrough:
--------------------

Insert

"apple"

                Root
                  |
                  a
                  |
                  p
                  |
                  p
                  |
                  l
                  |
                  e*

(* indicates flag = true)

--------------------------------

Insert

"app"

The existing nodes are reused.

Only

flag

at the second

'p'

is marked.

                Root
                  |
                  a
                  |
                  p
                  |
                  p*
                  |
                  l
                  |
                  e*

Now

search("app")

returns

true

because the second

'p'

has

flag = true.

------------------------------------------------------------

Time Complexity:
----------------

Let

L

be the length of the word.

Insert

Visits each character once.

Time:

O(L)

--------------------------------

Search

Visits each character once.

Time:

O(L)

--------------------------------

startsWith

Visits each character once.

Time:

O(L)

------------------------------------------------------------

Space Complexity:
-----------------

Each newly inserted character may create one new node.

If

N

words are inserted having total length

M,

the Trie contains at most

M + 1

nodes (including the root).

Overall Space Complexity:

O(M)

where

M

is the total number of inserted characters.

------------------------------------------------------------

Advantages of Trie:
-------------------

✓ Fast word insertion.

✓ Fast exact word search.

✓ Fast prefix search.

✓ Common prefixes are stored only once, reducing
redundant storage.

✓ Ideal for autocomplete, dictionaries, spell checking,
word search, and prefix matching problems.

*/