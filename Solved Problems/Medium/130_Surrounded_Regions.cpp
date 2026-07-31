class Solution {
    private:
        void dfs(vector<vector<char>>& board, int i, int j) {
            if(i < 0 || j < 0 || i >= board.size() || j >= board[0].size()) return; // out of bound
            if(board[i][j] == 'X' || board[i][j] == 'Y') return; // already 'X' or already flipped to 'Y'
    
            // flip 'O' to 'Y' and visit all four directions
            board[i][j] = 'Y';
            dfs(board, i + 1, j);
            dfs(board, i - 1, j);
            dfs(board, i, j + 1);
            dfs(board, i, j - 1);
        }
    
    public:
        void solve(vector<vector<char>>& board) {
            int row = board.size(), col = board[0].size();
    
            // traverse all columns of top and bottom row
            for (int j = 0; j < col; j++) {
                if (board[0][j] == 'O') dfs(board, 0, j);
                if (board[row - 1][j] == 'O') dfs(board, row - 1, j);
            }
    
            // traverse all rows of left and right column
            for (int i = 0; i < row; i++) {
                if (board[i][0] == 'O') dfs(board, i, 0);
                if (board[i][col - 1] == 'O') dfs(board, i, col - 1);
            }
    
            // flip 'O' to 'X' and 'Y' back to 'O'
            for(int i = 0; i < row; i++) {
                for(int j = 0; j < col; j++) {
                    if(board[i][j] == 'O') board[i][j] = 'X';
                    else if(board[i][j] == 'Y') board[i][j] = 'O';
                }
            }
        }
    };

/*

Idea:
------

A region of 'O's should be flipped to 'X' only if it is
completely surrounded by 'X'.

Instead of checking every region individually,

we identify the regions that

cannot

be surrounded.

These are the regions connected to any boundary 'O'.

We perform DFS from all boundary 'O's and temporarily mark
them as safe.

Finally,

every remaining 'O' is surrounded and can be flipped to 'X'.

------------------------------------------------------------

Key Observation:
----------------

If an 'O' is connected to the boundary,

it can never be surrounded because there exists a path from
that cell to the edge of the board.

Therefore,

only the 'O's that are

not

connected to any boundary should be flipped.

------------------------------------------------------------

Approach:
---------

1. Traverse the boundary of the board.

2. Whenever a boundary 'O' is found, perform DFS.

3. During DFS, temporarily change every reachable 'O' into
   'Y' to mark it as safe.

4. After all boundary DFS traversals,

   - Every remaining 'O' is surrounded, so change it to 'X'.
   - Every 'Y' was connected to the boundary, so convert it
     back to 'O'.

------------------------------------------------------------

Why Use 'Y'?
------------

While performing DFS, we need to distinguish between

• Original 'O's that should be flipped.

• Boundary-connected 'O's that should remain unchanged.

Therefore,

we temporarily mark the safe cells as 'Y'.

After processing,

'Y' is converted back to 'O'.

------------------------------------------------------------

Example:
--------

Initial Board

X X X X

X O O X

X X O X

X O X X

Boundary DFS starts from

(3,1)

After DFS

X X X X

X O O X

X X O X

X Y X X

--------------------------------

Final Conversion

Remaining 'O'

↓

'X'

'Y'

↓

'O'

Final Board

X X X X

X X X X

X X X X

X O X X

------------------------------------------------------------

Visualization:
--------------

Before DFS

X X X X

X O O X

X X O X

X O X X

-------------------------

After Boundary DFS

X X X X

X O O X

X X O X

X Y X X

-------------------------

After Final Pass

X X X X

X X X X

X X X X

X O X X

------------------------------------------------------------

Why Does This Work?
-------------------

DFS visits every 'O' connected to the boundary and marks it
as safe.

Since these cells have a path to the boundary, they are not
surrounded and must remain unchanged.

Any 'O' left unvisited has no connection to the boundary,
meaning it is completely enclosed by 'X'.

Therefore,

it is safe to flip every remaining 'O' to 'X'.

------------------------------------------------------------

Time Complexity:
----------------

Each cell is visited at most once.

O(row × col)

------------------------------------------------------------

Space Complexity:
-----------------

Recursion Stack

Worst Case

O(row × col)

No extra visited matrix is required because the board itself
is used for marking visited cells.

*/