class Solution {
    private:
        struct TrieNode {
            TrieNode* links[26];
            bool flag = false;
            string word = "";
    
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
        vector<string> ans;
    
        // insert word
        void insert(string word) {
            TrieNode* node = root;
            for(auto x : word) {
                if(!node->containsKey(x)) node->put(x, new TrieNode());
                node = node->get(x);
            }
            node->setEnd();
            node->word = word;
        }
        
        // search words
        void dfs(vector<vector<char>>& board, int row, int col, TrieNode* node) {
            // invalid index of row or col
            if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size()) return;
    
            // visited
            if(board[row][col] == '#') return;
    
            // char doesn't match
            if (!node->containsKey(board[row][col])) return;
    
            // move to child node
            node = node->get(board[row][col]);
    
            // word found
            if (node->isEnd()){ 
                ans.push_back(node->word);
                node->flag = false; // avoid duplicate words
            }
    
            // visited
            char temp = board[row][col];
            board[row][col] = '#';
    
            // Explore all 4 directions
            dfs(board, row + 1, col, node); // down
            dfs(board, row - 1, col, node); // up
            dfs(board, row, col + 1, node); // right
            dfs(board, row, col - 1, node); // left
    
            // Backtrack
            board[row][col] = temp;
    
            return;
        }
    
    public:
        vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
            for(auto x : words) insert(x);
            
            // use each char as starting point
            for (int i = 0; i < board.size(); i++) {
                for (int j = 0; j < board[0].size(); j++) dfs(board, i, j, root);
            }
    
            return ans;
        }
    };

/*

Idea:
------
The problem asks us to find every word from the given
dictionary that can be formed by traversing adjacent cells
(horizontal or vertical) on the board.

A naive solution would perform an independent DFS for every
dictionary word.

If there are

W

words,

each DFS explores a large portion of the board, leading to
significant repeated work.

Instead,

we insert every dictionary word into a

Trie

and perform a single DFS from every board cell.

While exploring the board,

we simultaneously walk through the Trie.

The moment the current board path is no longer a prefix of
any dictionary word,

the Trie immediately tells us to stop exploring that path.

Thus,

the Trie prunes a huge number of unnecessary DFS branches.

This solution combines

Trie

+

Backtracking DFS.

------------------------------------------------------------

Why Trie?
---------

Suppose the dictionary contains

{

"cat",

"car",

"care",

"dog"

}

Trie

                     Root
                    /    \
                   c      d
                   |      |
                   a      o
                 /   \      \
                t*    r*      g*
                       |
                       e*

Notice

"cat"

"car"

and

"care"

share the prefix

"ca".

Instead of searching each word separately,

one traversal of

"ca"

can potentially discover all three words.

------------------------------------------------------------

Trie Node Structure:
--------------------

Each Trie node stores

1.

links[26]

Pointers to child characters.

--------------------------------

2.

flag

Indicates whether a complete dictionary word ends here.

--------------------------------

3.

word

Stores the complete dictionary word.

Why store the word?

Suppose we reach the Trie node representing

"apple".

Instead of reconstructing the word from the DFS path,

we simply return

node->word.

This makes reporting the answer very convenient.

------------------------------------------------------------

Insertion:
----------

Each dictionary word is inserted character by character.

Example

Insert

"cat"

Root

↓

c

↓

a

↓

t*

Store

word = "cat"

at the last node.

------------------------------------------------------------

DFS State:
----------

The recursive function

dfs(board, row, col, node)

means

"We are currently standing at board cell

(row, col)

and have already matched the Trie path represented by

node.

Now continue extending the current word."

------------------------------------------------------------

Stopping Conditions:
--------------------

The DFS immediately terminates in four situations.

--------------------------------

1.

Outside the board.

--------------------------------

2.

Current cell has already been visited.

Visited cells are marked using

'#'.

--------------------------------

3.

Current board character does not exist as a child in the
Trie.

This is the most important pruning step.

If the current board path is not even a prefix of any
dictionary word,

there is absolutely no reason to continue exploring.

--------------------------------

4.

All recursive exploration finishes.

------------------------------------------------------------

Trie Traversal:
---------------

Suppose the board contains

c

and

node

currently represents

the Trie root.

If

board[row][col]

=

'c'

Move to

node->get('c')

Now,

the Trie represents the prefix

"c".

As DFS continues,

the Trie continues extending along the current board path.

------------------------------------------------------------

Word Found:
-----------

Whenever

node->isEnd()

becomes true,

a complete dictionary word has been matched.

Instead of rebuilding the string,

simply append

node->word

to

ans.

--------------------------------

Avoiding Duplicates

The same word may be discovered from multiple board paths.

Example

Board

a a

a a

Dictionary

"aa"

Without additional handling,

"aa"

would be inserted multiple times.

To prevent duplicates,

after discovering a word,

set

node->flag = false.

This marks the word as already reported.

Future DFS traversals reaching the same Trie node will no
longer insert duplicates.

------------------------------------------------------------

Backtracking:
-------------

A board cell cannot be reused within the same word.

Therefore,

before exploring neighbours,

store the original character

temp = board[row][col]

Mark the cell as visited

board[row][col] = '#'

Explore all four directions.

After recursion finishes,

restore

board[row][col] = temp

This restoration allows the cell to participate in other
independent DFS paths.

------------------------------------------------------------

Algorithm:
----------

Step 1

Insert every dictionary word into the Trie.

------------------------------------------------------------

Step 2

Treat every board cell as a possible starting position.

------------------------------------------------------------

Step 3

Start DFS from that cell using the Trie root.

------------------------------------------------------------

Step 4

If the current board character is not a Trie child,

immediately stop searching.

------------------------------------------------------------

Step 5

Move to the corresponding Trie node.

------------------------------------------------------------

Step 6

If the Trie node marks the end of a word,

store the word in the answer.

------------------------------------------------------------

Step 7

Mark the current board cell as visited.

------------------------------------------------------------

Step 8

Recursively explore

Down

Up

Right

Left

------------------------------------------------------------

Step 9

Restore the board while backtracking.

------------------------------------------------------------

Example:
--------

Board

o a a n

e t a e

i h k r

i f l v

Dictionary

{

"oath",

"pea",

"eat",

"rain"

}

------------------------------------------------------------

Start from

'o'

Trie path

o

↓

a

↓

t

↓

h

Reached

flag = true

Found

"oath"

------------------------------------------------------------

Start from

'e'

Trie path

e

↓

a

↓

t

Reached

flag = true

Found

"eat"

------------------------------------------------------------

Searching

"pea"

fails because

'p'

does not exist on the board.

Searching

"rain"

fails because the required path cannot be completed.

Final Answer

{

"oath",

"eat"

}

------------------------------------------------------------

Recursion Tree:
---------------

Suppose current cell contains

'c'

Trie

Root

↓

c

↓

a

↓

t

↓

e

DFS

            c
       /    |    |    \
      a     x     y     z
      |
      t
      |
      e

Only branches that continue to exist inside the Trie are
explored.

Every invalid prefix is immediately discarded.

------------------------------------------------------------

Why Does Trie Greatly Improve Performance?
------------------------------------------

Without a Trie,

every DFS would continue exploring many useless paths.

Example

Dictionary

{

"apple"

}

Board Path

a

↓

b

↓

c

↓

d

↓

e

A normal DFS would still continue exploring.

Using a Trie,

after

"a"

↓

"b"

the Trie has no child

'b'.

The DFS immediately terminates.

This pruning dramatically reduces the search space.

------------------------------------------------------------

Why Does This Work?
-------------------

Every dictionary word is represented as a unique path in
the Trie.

During DFS,

the current board path and the Trie path always remain
synchronized.

Whenever a board character cannot continue the Trie path,

the current prefix cannot lead to any dictionary word,

so recursion safely stops.

Whenever the DFS reaches a Trie node marked as the end of a
word,

a complete dictionary word has been successfully formed on
the board.

Backtracking restores the board after every recursive call,

allowing every possible path to be explored independently.

Since DFS starts from every board cell,

every valid word is eventually discovered.

------------------------------------------------------------

Correctness Proof:
------------------

We prove that every reported word is correct and every
valid word is found.

Every recursive call follows adjacent board cells while
simultaneously following the corresponding Trie path.

A recursive path continues only if every visited character
matches a Trie edge.

Therefore,

every reported word belongs to the dictionary.

Conversely,

consider any dictionary word that can be formed on the
board.

Since DFS begins from every cell,

it will eventually begin from the word's first character.

At every subsequent step,

the required neighbouring character exists,

and the corresponding Trie edge also exists because the
word was inserted into the Trie.

Hence,

DFS follows exactly that path and eventually reaches the
Trie node marking the end of the word,

causing the word to be reported.

Finally,

setting

flag = false

after the first discovery prevents duplicate insertions
without preventing any new words from being found.

Therefore,

the algorithm returns every valid dictionary word exactly
once.

------------------------------------------------------------

Time Complexity:
----------------

Let

M

=

number of rows

N

=

number of columns

L

=

maximum dictionary word length

Building the Trie

O(total characters in dictionary)

--------------------------------

DFS

Each board cell is used as a starting point.

From each starting cell,

the search depth is at most

L

because no dictionary word is longer than the longest word
in the Trie.

Trie pruning eliminates branches that are not prefixes of
any dictionary word.

Worst-case Time Complexity

O(M × N × 4 × 3^(L-1))

The factor

3^(L-1)

appears because after the first move,

we cannot immediately return to the previously visited
cell, leaving at most three choices per step.

In practice,

Trie pruning makes the algorithm much faster.

------------------------------------------------------------

Space Complexity:
-----------------

Trie

O(total characters in dictionary)

--------------------------------

Recursion Stack

O(L)

--------------------------------

Board Modification

Done in-place.

No additional visited matrix is required.

Overall Auxiliary Space

O(total dictionary characters + L)

*/