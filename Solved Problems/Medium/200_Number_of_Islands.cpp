class Solution {
    private:
        void dfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int i, int j) {
            // i, j out of grid
            if(i >= grid.size() || i < 0 || j >= grid[0].size() || j < 0) return;
    
            // water
            if(grid[i][j] == '0') return;
    
            // already visited
            if (visited[i][j]) return;
    
            // visit
            visited[i][j] = true;
            
            // explaore all 4 directions
            dfs(grid, visited, i + 1, j);
            dfs(grid, visited, i - 1, j);
            dfs(grid, visited, i, j + 1);
            dfs(grid, visited, i, j - 1);
        }
    
    public:
        int numIslands(vector<vector<char>>& grid) {
            int n = grid.size(), m = grid[0].size(), islands = 0;
            vector<vector<bool>> visited (n, vector<bool>(m, false));
            
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++) {
                    if (grid[i][j] == '1' && !visited[i][j]) {
                        islands++;
                        dfs(grid, visited, i, j);
                    }
                }
            }
    
            return islands;   
        }
    };

/*

Idea:
------
The grid consists of

Land  -> '1'

Water -> '0'

An

island

is formed by a group of connected land cells.

Two land cells belong to the same island if they are
connected horizontally or vertically.

The main idea is:

Whenever we encounter an unvisited land cell,

it must be the starting point of a new island.

From this cell,

we perform a

Depth First Search (DFS)

to visit every land cell belonging to that island.

After the DFS finishes,

the entire island is marked as visited.

Repeating this process for every cell gives the total number
of islands.

------------------------------------------------------------

Key Observation:
----------------

Every island is a connected component in the grid.

Therefore,

counting the number of islands is equivalent to counting the
number of connected components consisting of land cells.

DFS naturally explores every cell of a connected component
before returning.

Hence,

one DFS corresponds to exactly one island.

------------------------------------------------------------

Graph Representation:
---------------------

Treat every land cell as a graph node.

Edges exist between adjacent land cells in the four
directions.

Example

1 1 0

1 0 0

0 1 1

Graphically,

Island 1

(0,0) —— (0,1)
  |
(1,0)

Island 2

(2,1) —— (2,2)

Total Islands = 2

------------------------------------------------------------

DFS Traversal:
--------------

Starting from an unvisited land cell,

DFS recursively explores

Down

Up

Right

Left

until no unvisited neighboring land cells remain.

Thus,

every cell belonging to the current island gets visited.

------------------------------------------------------------

Base Cases:
-----------

The recursion stops in the following situations.

------------------------------------------------------------

Case 1

Current cell is outside the grid.

Return immediately.

------------------------------------------------------------

Case 2

Current cell contains water ('0').

Water cannot be part of an island.

Return.

------------------------------------------------------------

Case 3

Current cell has already been visited.

Return to avoid revisiting the same cell.

------------------------------------------------------------

Recursive Step:
---------------

If the current cell is an unvisited land cell,

Mark it as visited.

Then recursively explore all four neighboring cells.

dfs(i + 1, j)

dfs(i - 1, j)

dfs(i, j + 1)

dfs(i, j - 1)

This guarantees that every reachable land cell in the
current island is visited.

------------------------------------------------------------

Algorithm:
----------

Step 1

Create a

visited

matrix initialized to

false.

------------------------------------------------------------

Step 2

Traverse every cell of the grid.

------------------------------------------------------------

Step 3

Whenever an unvisited land cell ('1') is found,

Increment the island count.

------------------------------------------------------------

Step 4

Run DFS starting from that cell.

DFS marks every land cell of the current island as visited.

------------------------------------------------------------

Step 5

Continue scanning the remaining cells.

------------------------------------------------------------

Step 6

Return the total number of islands.

------------------------------------------------------------

Example:
--------

Grid

1 1 0 0

1 0 0 1

0 0 1 1

0 0 0 0

Traversal

Start at (0,0)

↓

DFS visits

(0,0)

↓

(0,1)

↓

(1,0)

Island Count = 1

--------------------------------

Continue scanning.

Reach

(1,3)

↓

DFS visits

(1,3)

↓

(2,3)

↓

(2,2)

Island Count = 2

--------------------------------

No more unvisited land.

Answer = 2

------------------------------------------------------------

Visualization:
--------------

Grid

1 1 0 0

1 0 0 1

0 0 1 1

0 0 0 0

DFS #1

*****

*....

.....

.....

--------------------------------

DFS #2

*****

...*

..**

.....

--------------------------------

Total DFS Calls = 2

Therefore,

Number of Islands = 2

------------------------------------------------------------

Why Does This Work?
-------------------

Whenever an unvisited land cell is encountered,

it must belong to an island that has not been counted yet.

Running DFS from that cell visits every land cell connected
to it.

Hence,

none of those cells will start another DFS later.

Thus,

every island contributes exactly one DFS call,

and every DFS call corresponds to exactly one island.

------------------------------------------------------------

Correctness Proof:
------------------

We prove that the algorithm returns the correct number of
islands.

Whenever the algorithm encounters an unvisited land cell,

it starts a DFS.

DFS visits every land cell reachable from that starting
cell,

which is exactly one connected component (one island).

After the DFS completes,

all cells of that island are marked as visited.

Therefore,

the same island is never counted again.

Conversely,

every island contains at least one land cell.

When the outer traversal reaches the first unvisited cell of
that island,

a DFS is initiated,

ensuring that every island is counted exactly once.

Hence,

the algorithm returns the exact number of islands.

------------------------------------------------------------

Time Complexity:
----------------

Let

n = number of rows

m = number of columns

Each cell is visited at most once.

Overall Time Complexity

O(n × m)

------------------------------------------------------------

Space Complexity:
-----------------

Visited matrix

O(n × m)

Recursion stack

Worst Case

O(n × m)

(for a grid consisting entirely of land)

Overall Space Complexity

O(n × m)

------------------------------------------------------------

Note:
-----

This solution uses an explicit

visited

matrix.

An alternative approach is to modify the input grid itself
(by changing visited land cells from '1' to '0'),

which eliminates the need for the extra visited array and
reduces the auxiliary space to only the recursion stack.

*/