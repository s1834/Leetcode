class Solution {
    private:
        int n, m;
    
        void visitIsland(vector<vector<int>>& grid, int i, int j, long long& total) {
            if(i < 0 || i >= n || j < 0 || j >= m) return;
            if(grid[i][j] == 0) return;
    
            total += grid[i][j];
            grid[i][j] = 0;
    
            visitIsland(grid, i - 1, j, total); // up
            visitIsland(grid, i + 1, j, total); // down
            visitIsland(grid, i, j - 1, total); // left
            visitIsland(grid, i, j + 1, total); // right
        }
        
    public:
        int countIslands(vector<vector<int>>& grid, int k) {
            n = grid.size();
            m = grid[0].size();
    
            int count = 0;
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++) {
                    long long total = 0;
                    if(grid[i][j] != 0) {
                        visitIsland(grid, i, j, total);
                        if(total % k == 0) count++;
                    }
                }
            }
    
            return count;
        }
    };

/*
Problem: LeetCode 3619 - Count Islands With Total Value Divisible by K

Approach: DFS (Depth-First Search) + Component Sum

Intuition:
----------
The grid contains:
- 0 = water
- Non-zero values = land cells

An island is a group of connected non-zero cells connected horizontally
or vertically.

For each island, we calculate the sum of all its cell values.
If the total sum is divisible by k, we count that island.

The key idea is to use DFS to explore an entire connected island,
calculate its total value, and mark its cells as visited by changing
them to 0.

--------------------------------------------------
1. Class Variables
--------------------------------------------------

int n, m;

These variables store the number of rows and columns in the grid.
They are used to check whether a cell lies within the grid boundaries.

--------------------------------------------------
2. DFS Function: visitIsland()
--------------------------------------------------

void visitIsland(vector<vector<int>>& grid, int i, int j,
                 long long& total)

This function explores the island connected to cell (i, j) and adds
the values of all its cells to total.

The total parameter is passed by reference, so every recursive call
updates the same running sum.

Base Case 1: Out of Bounds
--------------------------

if(i < 0 || i >= n || j < 0 || j >= m) return;

If the current coordinates lie outside the grid, stop exploring
this direction.

Base Case 2: Water or Visited Cell
----------------------------------

if(grid[i][j] == 0) return;

A cell containing 0 is either water or a land cell that has already
been visited. In either case, there is nothing more to process.

Add the Current Cell's Value
----------------------------

total += grid[i][j];

Add the current land cell's value to the island's total sum.

Mark the Cell as Visited
------------------------

grid[i][j] = 0;

Changing the cell to 0 prevents DFS from visiting it again.
This avoids repeatedly counting the same cell and prevents infinite
recursion between neighboring cells.

Explore All Four Directions
---------------------------

visitIsland(grid, i - 1, j, total); // up
visitIsland(grid, i + 1, j, total); // down
visitIsland(grid, i, j - 1, total); // left
visitIsland(grid, i, j + 1, total); // right

Recursively explore the neighboring cells:
- Up: (i - 1, j)
- Down: (i + 1, j)
- Left: (i, j - 1)
- Right: (i, j + 1)

Every connected non-zero cell is visited and added to total exactly
once.

--------------------------------------------------
3. Main Function: countIslands()
--------------------------------------------------

Initialize Grid Dimensions
--------------------------

n = grid.size();
m = grid[0].size();

Store the number of rows and columns.

Initialize the Island Counter
-----------------------------

int count = 0;

count stores the number of islands whose total value is divisible
by k.

Traverse the Entire Grid
------------------------

for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {

Examine every cell to find unvisited land.

Initialize the Island Sum
-------------------------

long long total = 0;

A fresh total is created for each potential island so that values
from different islands are not mixed together.

Start DFS for Unvisited Land
----------------------------

if(grid[i][j] != 0) {
    visitIsland(grid, i, j, total);

If the current cell is non-zero, it belongs to an island that has
not yet been explored.

DFS visits the entire connected island and calculates its sum.
All cells in that island are marked as 0 during the traversal.

Check Divisibility
------------------

if(total % k == 0) count++;

After DFS finishes, total contains the sum of the entire island.

If total % k == 0, the island's sum is divisible by k, so increment
the answer.

Return the Answer
-----------------

return count;

After processing every cell, count contains the number of islands
whose total value is divisible by k.

--------------------------------------------------
4. Example Walkthrough
--------------------------------------------------

Consider:

grid = [
    [1, 2, 0],
    [3, 0, 4],
    [0, 0, 5]
]

k = 3

Island 1:
Cells = 1, 2, 3

These cells are connected horizontally or vertically.

total = 1 + 2 + 3 = 6

Since 6 % 3 == 0, count becomes 1.

Island 2:
Cells = 4, 5

These cells are connected vertically.

total = 4 + 5 = 9

Since 9 % 3 == 0, count becomes 2.

Output: 2

--------------------------------------------------
5. Why the Algorithm Works
--------------------------------------------------

1. The outer loops examine every cell in the grid.

2. Whenever an unvisited non-zero cell is found, DFS explores all
   cells connected to it, forming exactly one complete island.

3. Each visited cell contributes its value to total exactly once,
   because it is changed to 0 immediately after being processed.

4. After the DFS finishes, total equals the sum of all values in
   that island.

5. Checking total % k == 0 correctly determines whether the island
   should contribute to the answer.

Therefore, every qualifying island is counted exactly once.

--------------------------------------------------
6. Complexity Analysis
--------------------------------------------------

Let n be the number of rows and m be the number of columns.

Time Complexity: O(n * m)

Every cell is examined by the outer loops, and each non-zero cell
is visited by DFS at most once.

Space Complexity: O(n * m)

In the worst case, the recursive DFS call stack can grow to
O(n * m) when a large island is explored.

The grid is modified in place, so no separate visited matrix is
required.

Core Idea:
----------
Use DFS to find each connected component of non-zero cells, calculate
its total sum, mark its cells as visited, and count the component
if its sum is divisible by k.
*/