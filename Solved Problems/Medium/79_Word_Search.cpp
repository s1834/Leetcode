class Solution {
    private:
        bool dfs(vector<vector<char>>& board, string& word, int row, int col, int idx) {
            // word found
            if (idx == word.size()) return true;
            
            // invalid index of row or col
            if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size()) return false;
    
            // char doesnt match
            if (board[row][col] != word[idx]) return false;
    
            // visited
            char temp = board[row][col];
            board[row][col] = '#';
    
            // Explore all 4 directions
            bool found = 
                dfs(board, word, row + 1, col, idx + 1) || // down
                dfs(board, word, row - 1, col, idx + 1) || // up
                dfs(board, word, row, col + 1, idx + 1) || // right
                dfs(board, word, row, col - 1, idx + 1); // left
    
            // Backtrack
            board[row][col] = temp;
    
            return found;
        }
    
    public:
        bool exist(vector<vector<char>>& board, string word) {
            int n = board.size(), m = board[0].size();
    
            // use each char as starting point
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (dfs(board, word, i, j, 0)) return true;
                }
            }
    
            return false;
        }
    };

/*

Idea:
------
We need to determine whether the given word can be formed
by moving through adjacent cells in the grid.

From any cell, we are allowed to move only in the four
directions:

• Up

• Down

• Left

• Right

Each cell can be used at most once while forming the
current word.

This naturally leads to

Backtracking + Depth First Search (DFS),

where we try every possible starting cell and recursively
attempt to match the remaining characters of the word.

------------------------------------------------------------

Key Observation:
----------------

The word can start from

any

cell in the grid.

Therefore,

we cannot assume the first character starts at a
particular position.

Instead,

every cell is treated as a potential starting point.

For each starting position,

DFS checks whether the complete word can be formed.

------------------------------------------------------------

DFS State:
----------

The recursive function

dfs(row, col, idx)

means:

"Can we form the suffix

word[idx ...]

starting from cell

(row, col)?"

Here,

row

Current row.

--------------------------------

col

Current column.

--------------------------------

idx

Current character of the word that we need to match.

------------------------------------------------------------

Base Case:
----------

If

idx == word.length()

it means every character of the word has already been
matched successfully.

Therefore,

return

true.

------------------------------------------------------------

Invalid Cases:
--------------

The search immediately fails if

1.

The cell lies outside the grid.

--------------------------------

2.

The character in the current cell does not match

word[idx].

--------------------------------

3.

The current cell has already been visited in this DFS
path.

In this implementation,

visited cells are temporarily marked by replacing their
character with

'#'.

Since '#' never appears in the board,

it acts as a special marker indicating that the cell
cannot be visited again in the current path.

------------------------------------------------------------

Backtracking:
-------------

Once a matching cell is found,

we temporarily mark it as visited.

Example

Board

A B C

Suppose

A

is currently being used.

It becomes

# B C

Now,

recursive calls cannot revisit

A.

After exploring every possible direction,

the original character is restored.

# B C

↓

A B C

This restoration is called

Backtracking,

allowing the same cell to participate in other search
paths.

------------------------------------------------------------

Recursive Exploration:
----------------------

After matching the current character,

we recursively search for the next character in all four
possible directions.

Down

(row + 1, col)

--------------------------------

Up

(row - 1, col)

--------------------------------

Right

(row, col + 1)

--------------------------------

Left

(row, col - 1)

If

any

direction successfully finds the remaining suffix,

the answer is immediately

true.

Otherwise,

all four recursive calls return

false.

------------------------------------------------------------

Algorithm:
----------

Step 1

Traverse every cell of the grid.

Each cell is considered as a possible starting position.

------------------------------------------------------------

Step 2

Call

dfs(i, j, 0)

meaning

"Try to match the word beginning from this cell."

------------------------------------------------------------

Step 3

Inside DFS,

check whether the current cell matches

word[idx].

If not,

return

false.

------------------------------------------------------------

Step 4

Mark the current cell as visited by replacing its value
with

'#'.

------------------------------------------------------------

Step 5

Recursively explore all four neighboring cells for the
next character.

------------------------------------------------------------

Step 6

Restore the original character before returning.

This ensures other DFS paths can reuse the cell.

------------------------------------------------------------

Step 7

If any starting cell successfully matches the complete
word,

return

true.

Otherwise,

after trying every cell,

return

false.

------------------------------------------------------------

Why Does Backtracking Work?
---------------------------

At any position,

multiple choices are possible.

For example,

after matching

"A"

we may move either

Right

or

Down.

If one choice eventually fails,

we should still be able to explore the other.

Backtracking restores the board to its previous state,

ensuring every possible path is explored independently.

Without restoration,

cells used in one failed path would incorrectly remain
blocked for future searches.

------------------------------------------------------------

Example:
--------

Board

A B C E
S F C S
A D E E

Word

"ABCCED"

--------------------------------

Start from

A

Match

A

↓

Move Right

Match

B

↓

Move Right

Match

C

↓

Move Down

Match

C

↓

Move Left

Match

E

↓

Move Left

Match

D

All characters matched.

Return

true.

------------------------------------------------------------

Example:
--------

Board

A B
C D

Word

"ABDA"

Start

A

↓

B

↓

D

Need

A

The only possible

A

has already been visited.

This path fails.

Backtracking restores the board,

allowing other starting positions to be explored.

------------------------------------------------------------

Why Does This Work?
-------------------

The algorithm systematically explores every possible path
that could form the given word.

At every recursive call,

exactly one character of the word is matched.

Visited cells are temporarily marked so that the same
cell cannot be reused within a single path,

satisfying the problem constraint.

After all recursive calls finish,

the cell is restored,

allowing it to participate in completely different
searches.

Since every starting position and every valid path are
considered,

the algorithm returns

true

iff

there exists at least one path that forms the given word.

------------------------------------------------------------

Time Complexity:
----------------

Let

N

=

number of rows

M

=

number of columns

L

=

length of the word

There are

N × M

possible starting cells.

For each starting cell,

the first character has up to

4

possible directions.

After moving once,

we cannot immediately return to the previous cell because
it is marked as visited.

Therefore,

every subsequent character has at most

3

choices.

Worst-case Time Complexity:

O(N × M × 4 × 3^(L - 1))

This is commonly written as

O(N × M × 3^L)

------------------------------------------------------------

Space Complexity:
-----------------

No separate visited array is used.

The board itself is modified temporarily and restored
afterwards.

The only extra memory comes from the recursion stack.

Maximum recursion depth

=

Length of the word

Therefore,

Space Complexity:

O(L)

where

L

is the length of the word.

*/