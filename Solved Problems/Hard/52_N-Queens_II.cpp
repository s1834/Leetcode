class Solution {
    private:
        vector<string> board;
        int count = 0;
        set<int> col;
        set<int> posDia; // r + c
        set<int> negDia; // r - c
        
        void backtrack(int row, int n) {
            if(row == n) {
                count++;
                return;
            }
    
            for(int c = 0; c < n; c++) {
                if(col.find(c) != col.end() || posDia.find(row + c) != posDia.end() || negDia.find(row - c) != negDia.end()) continue;
    
                col.insert(c);
                posDia.insert(row + c);
                negDia.insert(row - c);
                board[row][c] = 'Q';
    
    
                backtrack(row + 1, n);
    
                col.erase(c);
                posDia.erase(row + c);
                negDia.erase(row - c);
                board[row][c] = '.';
    
            }
        }
    
    public:
        int totalNQueens(int n) {
            board.assign(n, string(n, '.'));
            backtrack(0, n);
            return count;
        }
    };

/*

Idea:
------
Unlike LeetCode 51, where we must generate every valid
board configuration,

this problem only asks for the

total number

of valid N-Queens arrangements.

The placement rules remain exactly the same:

• One queen per row.

• No two queens share the same column.

• No two queens share the same diagonal.

Therefore,

we again use

Backtracking + Depth First Search (DFS),

but instead of storing every valid board,

we simply increment a counter whenever a valid
configuration is found.

------------------------------------------------------------

Key Observation:
----------------

Since every row must contain exactly one queen,

the recursion processes the board

row by row.

At every row,

the only decision is

"In which column should the queen be placed?"

If no safe column exists,

that branch immediately terminates.

------------------------------------------------------------

Representation:
---------------

The current chessboard is stored in

board,

where

'.'

represents an empty cell,

and

'Q'

represents a queen.

Although the final board is never returned,

maintaining it simplifies placement and backtracking.

Example

. Q . .

. . . .

Q . . .

. . Q .

------------------------------------------------------------

Tracking Attacked Positions:
----------------------------

Instead of checking the entire board every time,

three sets are maintained.

--------------------------------

1. Columns

col

Stores every occupied column.

If

column c

already exists,

another queen cannot be placed there.

--------------------------------

2. Positive Diagonals

posDia

Each anti-diagonal

(top-right → bottom-left)

has a unique value

row + column.

Cells having identical

row + column

belong to the same diagonal.

--------------------------------

3. Negative Diagonals

negDia

Each main diagonal

(top-left → bottom-right)

has a unique value

row - column.

Cells having identical

row - column

belong to the same diagonal.

Thus,

checking whether a queen attacks another requires only
three set lookups.

------------------------------------------------------------

DFS State:
----------

The recursive function

backtrack(row)

means:

"We have successfully placed queens in rows

0

through

row - 1.

Now place a queen in

row."

------------------------------------------------------------

Base Case:
----------

If

row == n,

then queens have been successfully placed in every row
without conflicts.

A valid arrangement has been found.

Increment

count

and return.

Unlike LeetCode 51,

the board is not stored because only the total number of
solutions is required.

------------------------------------------------------------

Recursive Choice:
-----------------

For the current row,

try every column.

For each column

c,

check whether

1.

Column

c

is already occupied.

--------------------------------

2.

Diagonal

row + c

is occupied.

--------------------------------

3.

Diagonal

row - c

is occupied.

If any condition is true,

placing a queen there would create a conflict.

Otherwise,

the position is safe.

------------------------------------------------------------

Placing a Queen:
----------------

When a safe position is found,

perform the following updates.

Insert

c

into

col.

--------------------------------

Insert

row + c

into

posDia.

--------------------------------

Insert

row - c

into

negDia.

--------------------------------

Mark

board[row][c]

=

'Q'

Now recursively place a queen in the next row.

------------------------------------------------------------

Backtracking:
-------------

After recursion completes,

remove the queen.

Erase

c

from

col.

--------------------------------

Erase

row + c

from

posDia.

--------------------------------

Erase

row - c

from

negDia.

--------------------------------

Restore

board[row][c]

=

'.'

This restores the board to its previous state,

allowing other column choices to be explored.

------------------------------------------------------------

Algorithm:
----------

Step 1

Initialize an empty chessboard.

------------------------------------------------------------

Step 2

Start DFS from

row = 0.

------------------------------------------------------------

Step 3

For every column,

check whether the queen can be safely placed.

------------------------------------------------------------

Step 4

If safe,

update the board and all attack sets.

------------------------------------------------------------

Step 5

Recursively process the next row.

------------------------------------------------------------

Step 6

Undo the placement while backtracking.

------------------------------------------------------------

Step 7

Whenever all

n

rows have been processed,

increment the answer.

------------------------------------------------------------

Why Do row + column and row - column Identify Diagonals?
--------------------------------------------------------

Consider a

4 × 4

board.

Main Diagonal

(top-left → bottom-right)

(0,0)

↓

(1,1)

↓

(2,2)

↓

(3,3)

For every cell,

row - column

remains constant.

--------------------------------

Anti-Diagonal

(top-right → bottom-left)

(0,3)

↓

(1,2)

↓

(2,1)

↓

(3,0)

For every cell,

row + column

remains constant.

Therefore,

every diagonal can be uniquely identified using one of
these expressions.

------------------------------------------------------------

Example:
--------

n = 4

Initially

. . . .

. . . .

. . . .

. . . .

--------------------------------

Place queen at

(0,1)

. Q . .

. . . .

. . . .

. . . .

Occupied

Columns

{1}

row + col

{1}

row - col

{-1}

--------------------------------

Move to Row 1.

Continue placing queens recursively.

One valid arrangement is

. Q . .

. . . Q

Q . . .

. . Q .

When

row == 4,

increment

count.

Continue searching because other valid arrangements may
still exist.

------------------------------------------------------------

Recursion Tree:
---------------

For

n = 4

Row 0

          Place Queen
        /   |   |   \
Row 1

Try every safe column

↓

Row 2

↓

Row 3

↓

Valid Arrangement

↓

count++

Backtrack

↓

Continue searching

Unlike LeetCode 51,

the recursion never stops after finding one solution.

It explores the

entire search tree

to count every valid arrangement.

------------------------------------------------------------

Difference from LeetCode 51:
----------------------------

LeetCode 51

Stores every valid board inside

ans.

--------------------------------

LeetCode 52

Does not store the board.

It only increments

count

whenever a valid configuration is found.

Thus,

the search process is identical,

but the output is different.

------------------------------------------------------------

Why Does This Work?
-------------------

The algorithm places exactly one queen in every row.

Before placing a queen,

it ensures that neither the column nor either diagonal is
already occupied.

Therefore,

every intermediate board always satisfies the N-Queens
constraints.

Backtracking guarantees that after exploring one possible
placement,

the queen is removed and all remaining valid placements
are explored.

Since every legal configuration is visited exactly once,

the final value of

count

is precisely the total number of valid N-Queens
arrangements.

------------------------------------------------------------

Time Complexity:
----------------

In the worst case,

each row may try up to

n

columns.

The recursion explores permutations of queen placements,

leading to an exponential search.

Worst-case Time Complexity:

O(N!)

Although pruning eliminates many invalid branches,

the worst-case complexity remains exponential.

------------------------------------------------------------

Space Complexity:
-----------------

Board

O(N²)

--------------------------------

Column Set

O(N)

--------------------------------

Diagonal Sets

O(N)

Each diagonal set stores at most

2N - 1

values.

--------------------------------

Recursion Stack

O(N)

Overall Auxiliary Space:

O(N²)

including the board.

Ignoring the board representation,

the additional working memory is

O(N).

*/