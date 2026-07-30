class Solution {
    public:
        int numEnclaves(vector<vector<int>>& grid) {
            queue<pair<int, int>> q;
            int n = grid.size(), m = grid[0].size();
            vector<vector<int>> visited(n, vector<int>(m, 0));
    
            // push all boundry 1s in queue and mark them visited
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++) {
                    // first row || first col || last row || last col
                    if(i == 0 || j == 0 || i == n - 1 || j == m - 1) {
                        if(grid[i][j] == 1) {
                            q.push({i, j});
                            visited[i][j] = 1;
                        }
                    }
                }
            }
    
            // all four directions
            int delRow[] = {-1, 0, 1, 0};
            int delCol[] = {0, 1, 0, -1};
    
            while(!q.empty()) {
                // check 4 directions to this row and col
                int row = q.front().first;
                int col = q.front().second;
                q.pop();
    
                for(int i = 0; i < 4; i++) {
                    int newRow = row + delRow[i];
                    int newCol = col + delCol[i];
                    
                    // if newRow and new Col are inside grid and are 1 and not visited push them in queue and mark them visited
                    if(newRow < n && newRow >= 0 && newCol < m && newCol >= 0) {
                        if(grid[newRow][newCol] == 1 && !visited[newRow][newCol]) {
                            q.push({newRow, newCol});
                            visited[newRow][newCol] = 1;
                        }
                    }
                }
            }
    
            // count the remaining islands which are not visited from boundry land
            int count = 0;
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++) {
                    if(grid[i][j] == 1 && !visited[i][j]) count++;
                }
            }
    
            return count;
        }
    };

/*

Idea:
------

Instead of finding enclave land cells directly, we eliminate
all land cells that can reach the boundary.

Any land cell connected to the boundary can always walk out
of the grid, so it cannot be an enclave.

Therefore, after removing all boundary-connected land, the
remaining land cells are exactly the enclaves.

------------------------------------------------------------

Key Observation:
----------------

Every enclave belongs to an island that is completely
surrounded by water.

If an island touches the boundary, then every land cell of
that island can eventually reach the boundary.

Hence, we only need to start a BFS from every boundary land
cell and mark every reachable land cell.

The unvisited land cells are our answer.

------------------------------------------------------------

Algorithm:
----------

1. Traverse the boundary of the grid.

2. Push every boundary land cell into the queue and mark it
   as visited.

3. Perform BFS in all four directions.

4. Every land cell reached during BFS is connected to the
   boundary, so mark it visited.

5. Finally, traverse the grid again and count every land
   cell that is still unvisited.

------------------------------------------------------------

Example:
--------

Grid

0 0 0 0

1 0 1 0

0 1 1 0

0 0 0 0

Boundary BFS starts from

(1,0)

Visited

V 0 0 0

V 0 1 0

0 1 1 0

0 0 0 0

The remaining three land cells were never reached from the
boundary, so they form the enclave.

Answer = 3

------------------------------------------------------------

Why Does This Work?
-------------------

BFS visits every land cell that has a path to the boundary.

If a land cell remains unvisited after BFS, there is no path
from it to any boundary land cell.

Hence, it is completely enclosed by water and must be an
enclave.

------------------------------------------------------------

Time Complexity:
----------------

Each cell is processed at most once.

O(n × m)

------------------------------------------------------------

Space Complexity:
-----------------

Visited Matrix + Queue

O(n × m)

*/