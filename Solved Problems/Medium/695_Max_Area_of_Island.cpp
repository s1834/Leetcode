class Solution {
    private:
        int dfs(vector<vector<int>>& grid, vector<vector<int>>& visited, int i, int j) {
            int row = grid.size(), col = grid[0].size();
    
            // if we are outside grid, add 1
            if(i >= row || i < 0 || j >= col || j < 0) return 0;
            
            // if water, add 1
            if(grid[i][j] == 0) return 0;
    
            // Already visited land
            if(visited[i][j]) return 0;
    
            visited[i][j] = 1;
    
            int count = 0;
            count++;
    
            // Check all four directions
            count += dfs(grid, visited, i-1, j); // up
            count += dfs(grid, visited, i+1, j); // down
            count += dfs(grid, visited, i, j-1); // left
            count += dfs(grid, visited, i, j+1); // right
    
            return count;
        }
    
    public:
        int maxAreaOfIsland(vector<vector<int>>& grid) {
            int row = grid.size(), col = grid[0].size();
    
            vector<vector<int>> visited(row, vector<int>(col, 0));
            int ans = 0;
    
            for(int i = 0; i < row; i++) {
                for(int j = 0; j < col; j++) {
                    if(grid[i][j] == 1 && !visited[i][j]) ans = max(ans, dfs(grid, visited, i, j));
                }
            }
    
            return ans;
        }
    };

/*

Idea:
------
The grid consists of

Land  -> 1

Water -> 0

An island is formed by connected land cells in the four
directions

(Up, Down, Left, Right).

Unlike

Number of Islands,

where we count connected components,

here we need to find the

maximum area

of any island.

The idea is to perform a

Depth First Search (DFS)

from every unvisited land cell.

Each DFS computes the total number of land cells belonging
to that island.

Finally,

keep the maximum area among all islands.

------------------------------------------------------------

Key Observation:
----------------

Every island is a connected component.

DFS naturally explores every cell belonging to one connected
component before returning.

Therefore,

one DFS call computes the complete area of exactly one
island.

Taking the maximum over all DFS calls gives the answer.

------------------------------------------------------------

Graph Representation:
---------------------

Treat every land cell as a graph node.

Two nodes share an edge if they are adjacent in one of the
four directions.

Example

1 1 0

1 0 1

0 1 1

Graph

Island 1

(0,0) —— (0,1)
  |
(1,0)

Area = 3

--------------------------------

Island 2

      (1,2)
         |
(2,1) —— (2,2)

Area = 3

Maximum Area = 3

------------------------------------------------------------

DFS Meaning:
------------

dfs(i, j)

returns

the total number of land cells belonging to the island
containing cell

(i, j).

------------------------------------------------------------

Base Cases:
-----------

The recursion stops in the following situations.

------------------------------------------------------------

Case 1

Current cell is outside the grid.

Return

0.

------------------------------------------------------------

Case 2

Current cell contains water.

Water contributes nothing to the island area.

Return

0.

------------------------------------------------------------

Case 3

Current land cell has already been visited.

It has already been counted.

Return

0.

------------------------------------------------------------

Recursive Step:
---------------

For a valid unvisited land cell,

Mark it as visited.

Current cell contributes

1

to the island area.

Then recursively explore all four neighbors.

Area

=

1

+

Up

+

Down

+

Left

+

Right

------------------------------------------------------------

Mathematically,

Area(i,j)

=

1

+

Area(i-1,j)

+

Area(i+1,j)

+

Area(i,j-1)

+

Area(i,j+1)

------------------------------------------------------------

Algorithm:
----------

Step 1

Create a

visited

matrix initialized with

0.

------------------------------------------------------------

Step 2

Traverse every cell of the grid.

------------------------------------------------------------

Step 3

Whenever an unvisited land cell is found,

start a DFS.

------------------------------------------------------------

Step 4

DFS returns the total area of that island.

------------------------------------------------------------

Step 5

Update

ans

with the maximum area found so far.

------------------------------------------------------------

Step 6

Return

ans.

------------------------------------------------------------

Example:
--------

Grid

1 1 0 0

1 0 0 1

0 1 1 1

0 0 0 0

Traversal

Start DFS at

(0,0)

Visited Cells

(0,0)

↓

(0,1)

↓

(1,0)

Area = 3

Maximum = 3

--------------------------------

Continue scanning.

Start DFS at

(1,3)

Visited Cells

(1,3)

↓

(2,3)

↓

(2,2)

↓

(2,1)

Area = 4

Maximum = 4

Answer = 4

------------------------------------------------------------

Visualization:
--------------

Grid

1 1 0 0

1 0 0 1

0 1 1 1

0 0 0 0

DFS #1

***

*...

....

....

Area = 3

--------------------------------

DFS #2

....

...*

.***

....

Area = 4

Maximum Area = 4

------------------------------------------------------------

Why Does This Work?
-------------------

Whenever DFS starts,

it visits every land cell connected to the starting cell.

Each visited cell contributes exactly

1

to the area.

Since every land cell is marked as visited,

no cell is counted more than once.

Therefore,

every DFS correctly computes the area of one complete
island.

Taking the maximum over all such areas gives the largest
island.

------------------------------------------------------------

Correctness Proof:
------------------

We prove that the algorithm returns the maximum island area.

Whenever an unvisited land cell is encountered,

a DFS is started.

DFS recursively visits every land cell reachable from the
starting cell,

which is exactly one connected component.

Each visited cell contributes

1

to the returned value,

so DFS returns the exact area of that island.

Since every island contains at least one unvisited land
cell,

every island is explored exactly once.

The algorithm updates the answer with the maximum area
returned by any DFS.

Therefore,

the final answer equals the area of the largest island in
the grid.

------------------------------------------------------------

Time Complexity:
----------------

Let

R = number of rows

C = number of columns

Each cell is visited at most once.

Overall Time Complexity

O(R × C)

------------------------------------------------------------

Space Complexity:
-----------------

Visited Matrix

O(R × C)

Recursion Stack

Worst Case

O(R × C)

(for one large island covering the entire grid)

Overall Space Complexity

O(R × C)

------------------------------------------------------------

Note:
-----

This solution explicitly maintains a

visited

matrix.

Another common approach is to modify the input grid itself
by changing visited land cells from

1

to

0,

eliminating the extra visited matrix and reducing the
auxiliary space to only the recursion stack.

*/