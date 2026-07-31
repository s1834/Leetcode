class Solution {
    private:
    
        void dfs(vector<vector<int>>& heights, set<pair<int, int>>& visited, int prevHeight, int i, int j) {
            if(i < 0 || j < 0 || i >= heights.size() || j >= heights[0].size()) return; // out of bound
            if(visited.find({i, j}) != visited.end()) return; // already visited
            if(heights[i][j] < prevHeight) return; // current height less than previous height, so cant move to water
    
            // insert visited row and column and visit all four directions
            visited.insert({i, j});
            dfs(heights, visited, heights[i][j], i + 1, j);
            dfs(heights, visited, heights[i][j], i - 1, j);
            dfs(heights, visited, heights[i][j], i, j + 1);
            dfs(heights, visited, heights[i][j], i, j - 1);
        }
    
    public:
        vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
            int row = heights.size(), col = heights[0].size();
            set<pair<int,int>> pacific, atlantic;
    
            // visit all columns of first and last row
            for(int i = 0; i < col; i++) {
                dfs(heights, pacific, heights[0][i], 0, i);
                dfs(heights, atlantic, heights[row - 1][i], row - 1, i);
            }
    
            // visit all rows of leftmost and rightmost columns
            for(int i = 0; i < row; i++) {
                dfs(heights, pacific, heights[i][0], i, 0);
                dfs(heights, atlantic, heights[i][col - 1], i, col - 1);
            }
    
            // check for the intersection of two sets
            vector<vector<int>> ans;
            for(int i = 0; i < row; i++) {
                for(int j = 0; j < col; j++) {
                    if(pacific.find({i, j}) != pacific.end() && atlantic.find({i, j}) != atlantic.end()) ans.push_back({i, j});
                }
            }
    
            return ans;
        }
    };

/*

Idea:
------

Instead of checking every cell to see whether water can
reach both oceans,

we reverse the process.

We start DFS

from the oceans

and find every cell that can flow into them.

Finally,

the cells reachable from both oceans are the answer.

------------------------------------------------------------

Key Observation:
----------------

Water normally flows

from higher height to lower (or equal) height.

Checking this from every cell would require a DFS/BFS from
each cell, which is inefficient.

Instead,

we reverse the direction of movement.

Starting from an ocean,

we only move to neighboring cells having

greater than or equal

height.

This is equivalent to tracing the possible paths that water
could have taken to reach the ocean.

------------------------------------------------------------

Reverse DFS Condition:
----------------------

Normal Water Flow

Higher Height

↓

Lower Height

--------------------------------

Reverse DFS

Lower Height

↓

Higher or Equal Height

Therefore,

during DFS we move only if

currentHeight >= previousHeight

which is implemented as

if (heights[i][j] < prevHeight) return;

------------------------------------------------------------

Algorithm:
----------

1. Create two visited sets.

   - Pacific
   - Atlantic

2. Start DFS from every Pacific boundary cell
   (top row and left column).

3. Start DFS from every Atlantic boundary cell
   (bottom row and right column).

4. During DFS,

   move only to neighboring cells whose height is greater
   than or equal to the current cell.

5. After both DFS traversals,

   every cell present in both visited sets can reach both
   oceans.

6. Collect all such cells and return them.

------------------------------------------------------------

Example:
--------

Heights

1 2 2 3

3 2 3 4

2 4 5 3

6 7 1 4

Pacific touches

Top Row + Left Column

Atlantic touches

Bottom Row + Right Column

--------------------------------

Pacific DFS

Marks every cell that can eventually flow into the Pacific.

--------------------------------

Atlantic DFS

Marks every cell that can eventually flow into the Atlantic.

--------------------------------

Intersection

↓

Cells reachable from both oceans.

------------------------------------------------------------

Visualization:
--------------

Pacific

~~~~~~~~~~~~

1 2 2 3

3 2 3 4

2 4 5 3

6 7 1 4

Atlantic

1 2 2 3

3 2 3 4

2 4 5 3

6 7 1 4

~~~~~~~~~~~~

DFS expands inward from both oceans.

The cells visited by

both

DFS traversals form the final answer.

------------------------------------------------------------

Why Does This Work?
-------------------

Instead of asking

"Can this cell reach the ocean?"

we ask

"Which cells can the ocean reach in reverse?"

A reverse path exists if water could have originally flowed
from that cell towards the ocean.

Running DFS from both oceans identifies every cell that can
reach each ocean.

Therefore,

the intersection of the Pacific and Atlantic visited sets
contains exactly those cells from which water can flow to
both oceans.

------------------------------------------------------------

Time Complexity:
----------------

Each cell is visited at most once for the Pacific DFS and
once for the Atlantic DFS.

Overall Time Complexity

O(m × n)

------------------------------------------------------------

Space Complexity:
-----------------

Visited Sets

O(m × n)

Recursion Stack

O(m × n) in the worst case.

Overall Space Complexity

O(m × n)

*/