class Solution {
    private:
        int n, m;
    
        bool visitIsland(vector<vector<int>>& grid, int i, int j) {
            if(i < 0 || i >= n || j < 0 || j >= m) return false;
            if(grid[i][j] == 1) return true;
    
            // Mark visited by converting land (0) into water (1)
            grid[i][j] = 1;
    
            // Explore all four directions
            bool up = visitIsland(grid, i - 1, j);
            bool down = visitIsland(grid, i + 1, j);
            bool left = visitIsland(grid, i, j - 1);
            bool right = visitIsland(grid, i, j + 1);
    
            return up && down && left && right;
        }
    
    public:
        int closedIsland(vector<vector<int>>& grid) {
            n = grid.size();
            m = grid[0].size();
    
            int count = 0;
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++) {
                    if(grid[i][j] == 0 && visitIsland(grid, i, j)) count++; 
                }
            }
    
            return count;
        }
    };

/*
Problem: LeetCode 1254 - Number of Closed Islands

Approach: DFS (Depth-First Search)

Intuition:
----------
The grid contains:
- 0 = land
- 1 = water

A closed island is a group of connected land cells completely
surrounded by water. Therefore, none of its land cells can connect
to the boundary of the grid.

The key idea is to explore each island using DFS and determine
whether it is closed.

The DFS returns false if the exploration reaches outside the grid.
It returns true when it encounters water or a previously visited
cell. Otherwise, it marks the current land cell as visited and
explores all four directions.

An island is closed only if all four recursive explorations return
true.

--------------------------------------------------
1. Class Variables
--------------------------------------------------

int n, m;

These variables store the number of rows and columns in the grid.

They are used by visitIsland() to check whether a cell lies within
the grid boundaries.

--------------------------------------------------
2. DFS Function: visitIsland()
--------------------------------------------------

bool visitIsland(vector<vector<int>>& grid, int i, int j)

This function explores the connected land region starting at (i, j)
and determines whether that region is closed.

Base Case 1: Out of Bounds
--------------------------

if(i < 0 || i >= n || j < 0 || j >= m) return false;

If DFS moves outside the grid, the current island touches the
boundary and cannot be closed.

Therefore, return false.

Base Case 2: Water or Already Visited
-------------------------------------

if(grid[i][j] == 1) return true;

If the current cell is water, this direction does not lead to
land outside the grid, so it contributes true to the result.

The same condition also handles previously visited cells because
the algorithm marks visited land by changing its value from 0 to 1.

Mark the Current Cell as Visited
--------------------------------

grid[i][j] = 1;

The current cell is converted from land to water so that DFS does
not repeatedly visit it.

This also prevents infinite recursion when neighboring cells
explore each other.

Explore All Four Directions
---------------------------

bool up = visitIsland(grid, i - 1, j);
bool down = visitIsland(grid, i + 1, j);
bool left = visitIsland(grid, i, j - 1);
bool right = visitIsland(grid, i, j + 1);

DFS explores the neighboring cells in all four directions:
- Up: (i - 1, j)
- Down: (i + 1, j)
- Left: (i, j - 1)
- Right: (i, j + 1)

Each recursive call determines whether that direction stays
within a closed region.

Combine the Results
-------------------

return up && down && left && right;

The island is considered closed only if every direction returns true.

If any recursive call reaches outside the grid, it returns false.
That false result propagates through the recursive calls, ensuring
the entire connected island is not counted.

--------------------------------------------------
3. Main Function: closedIsland()
--------------------------------------------------

Initialize Dimensions
---------------------

n = grid.size();
m = grid[0].size();

Store the grid's number of rows and columns.

Initialize the Counter
----------------------

int count = 0;

count tracks the total number of closed islands.

Traverse the Entire Grid
------------------------

for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {

Every cell is examined.

Start DFS for Unvisited Land
----------------------------

if(grid[i][j] == 0 && visitIsland(grid, i, j))
    count++;

DFS starts only when the current cell is land (0). Since every
explored land cell is converted to water (1), each connected island
is processed only once.

If visitIsland() returns true, the entire island is closed, so
increment count.

If it returns false, the island touches the boundary and is not
counted. Its cells have still been marked visited, preventing
unnecessary repeated exploration.

Return the Answer
-----------------

return count;

After traversing the grid, count contains the total number of
closed islands.

--------------------------------------------------
4. Example Walkthrough
--------------------------------------------------

Consider:

grid = [
    [1, 1, 1, 1, 1],
    [1, 0, 0, 1, 1],
    [1, 0, 1, 1, 1],
    [1, 1, 1, 0, 1],
    [1, 1, 1, 1, 1]
]

The first island consists of the land cells near the upper-left
area. It is surrounded by water and does not touch the boundary.

DFS explores all its connected land cells and returns true.
Therefore, count becomes 1.

The second land cell near the lower-right area is isolated and
surrounded by water. It is also a closed island.

DFS returns true again, so count becomes 2.

Output: 2

--------------------------------------------------
5. Why the Algorithm Works
--------------------------------------------------

1. Every unvisited land cell starts a DFS that explores its entire
   connected island.

2. Every visited land cell is changed to water, so the same island
   cannot be counted more than once.

3. If any DFS path reaches outside the grid, false propagates
   through the recursive calls, identifying the island as open.

4. If every explored direction returns true, the island does not
   reach the boundary and is counted as closed.

Therefore, the algorithm counts every closed island exactly once.

--------------------------------------------------
6. Complexity Analysis
--------------------------------------------------

Let n be the number of rows and m be the number of columns.

Time Complexity: O(n * m)

Each cell is visited and processed at most once because visited
land cells are converted to water.

Space Complexity: O(n * m)

In the worst case, the recursive DFS call stack can contain up to
O(n * m) calls if a large island is explored.

The grid is modified in place, so no separate visited matrix is
required.

Core Idea:
----------
Use DFS to explore each connected land region. Mark visited cells
as water, and count an island only if its exploration never reaches
outside the grid.
*/