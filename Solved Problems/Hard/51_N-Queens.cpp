class Solution {
    private:
        vector<vector<string>> ans;
        vector<string> board;
        set<int> col;
        set<int> posDia; // r + c
        set<int> negDia; // r - c
        
        void backtrack(int row, int n) {
            if(row == n) {
                ans.push_back(board);
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
        vector<vector<string>> solveNQueens(int n) {
            board.assign(n, string(n, '.'));
            backtrack(0, n);
            return ans;
        }
    };

/*

Idea:
------
The N-Queens problem asks us to place

N

queens on an

N × N

chessboard such that no two queens attack each other.

A queen can attack along

• Row

• Column

• Main Diagonal

• Anti-Diagonal

Since every row must contain exactly one queen,

we process the board

row by row,

and for each row, we try every possible column where a
queen can be safely placed.

This naturally leads to a

Backtracking + Depth First Search (DFS)

solution.

------------------------------------------------------------

Key Observation:
----------------

At any stage of the recursion,

all previous rows have already been assigned exactly one
queen.

Therefore,

when placing a queen in the current row,

we only need to check whether the chosen column or
diagonals are already occupied.

There is no need to check rows because each recursive
call processes exactly one row.

------------------------------------------------------------

Representation:
---------------

The current chessboard is stored as

board,

where

'.'

represents an empty cell,

and

'Q'

represents a queen.

Example

. Q . .

. . . .

Q . . .

. . Q .

------------------------------------------------------------

Tracking Attacked Positions:
----------------------------

Instead of scanning the board every time,

three sets are maintained.

--------------------------------

1. Columns

col

Stores every occupied column.

If

column c

already exists in the set,

another queen cannot be placed there.

--------------------------------

2. Positive Diagonals

posDia

Every cell lying on the same

top-left → bottom-right

diagonal has the same value

row + column

Example

0 1 2

1 2 3

2 3 4

Cells having identical

row + column

belong to the same diagonal.

--------------------------------

3. Negative Diagonals

negDia

Every cell lying on the same

top-right → bottom-left

diagonal has the same value

row - column

Example

0 -1 -2

1  0 -1

2  1  0

Cells with identical

row - column

belong to the same diagonal.

Thus,

checking whether a queen attacks another becomes an

O(1)

set lookup.

------------------------------------------------------------

DFS State:
----------

The recursive function

backtrack(row)

means:

"We have successfully placed queens in all rows

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

then queens have been placed in every row without any
conflicts.

The current board is a valid solution.

Store it inside

ans

and return.

------------------------------------------------------------

Recursive Choice:
-----------------

For the current row,

every column is considered.

For each column

c,

first check

1.

Column already occupied?

--------------------------------

2.

Positive diagonal already occupied?

--------------------------------

3.

Negative diagonal already occupied?

If any of these are true,

the queen cannot be placed there.

Otherwise,

the position is safe.

------------------------------------------------------------

Placing a Queen:
----------------

When a safe position is found,

perform the following updates.

Insert

column

into

col.

--------------------------------

Insert

row + column

into

posDia.

--------------------------------

Insert

row - column

into

negDia.

--------------------------------

Mark

board[row][column]

=

'Q'

Now recursively solve the next row.

------------------------------------------------------------

Backtracking:
-------------

After recursion finishes,

the queen is removed.

Remove

column

from

col.

--------------------------------

Remove

row + column

from

posDia.

--------------------------------

Remove

row - column

from

negDia.

--------------------------------

Restore

board[row][column]

=

'.'

This restoration allows other column choices in the same
row to be explored independently.

------------------------------------------------------------

Algorithm:
----------

Step 1

Initialize an empty board.

------------------------------------------------------------

Step 2

Start DFS from

row = 0.

------------------------------------------------------------

Step 3

For every column in the current row,

check whether the column or either diagonal is already
occupied.

------------------------------------------------------------

Step 4

If safe,

place the queen,

update all three sets,

and recursively process the next row.

------------------------------------------------------------

Step 5

After recursion,

remove the queen and restore all data structures.

------------------------------------------------------------

Step 6

Whenever every row contains one queen,

store the board as a valid solution.

------------------------------------------------------------

Why Do row + column and row - column Work?
------------------------------------------

Consider the board coordinates.

For the main diagonal

(top-left → bottom-right)

(0,0)

↓

(1,1)

↓

(2,2)

↓

(3,3)

For every cell,

row + column

is

0

2

4

6

Actually, the invariant for a main diagonal is
**row - column**.

For the anti-diagonal

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

is constant.

In this implementation,

the naming is

posDia = row + column

negDia = row - column

although mathematically,

row + column

identifies one diagonal direction and

row - column

identifies the other.

The names themselves are arbitrary—the important point is
that each diagonal is uniquely identified by one of these
expressions.

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

Try every column.

Skip columns or diagonals already occupied.

Eventually choose

(1,3)

. Q . .

. . . Q

. . . .

. . . .

Continue recursively until all four queens are placed.

One valid solution

. Q . .

. . . Q

Q . . .

. . Q .

------------------------------------------------------------

Recursion Tree:
---------------

For

n = 4

Row 0

        (0,0)
       /  |  |  \
Row 1

Try every safe column

↓

Row 2

↓

Row 3

↓

Solution

Whenever a branch reaches an invalid state,

backtracking restores the previous board and another
column is attempted.

------------------------------------------------------------

Why Does This Work?
-------------------

The algorithm processes the board row by row,

ensuring that every row contains exactly one queen.

Before placing a queen,

it verifies that neither the column nor either diagonal
already contains another queen.

Thus,

every intermediate configuration always satisfies the
problem constraints.

Backtracking guarantees that if one placement eventually
fails,

the algorithm returns to the previous state and explores
every remaining valid column.

Since every possible safe placement is explored,

every valid N-Queens configuration is generated exactly
once.

------------------------------------------------------------

Time Complexity:
----------------

At each row,

up to

n

columns may be attempted.

The recursion explores permutations of queen placements,

leading to an exponential search.

Worst-case Time Complexity:

O(N!)

Although the branching factor decreases as more queens
are placed,

the search remains exponential.

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

Ignoring the board required for constructing the answer,

the extra working space is

O(N).

*/