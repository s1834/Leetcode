class Solution {
    public:
        int orangesRotting(vector<vector<int>>& grid) {
            queue<pair<int, int>> q;
            int n = grid.size(), m = grid[0].size();
    
            // push all rotten oranges in queue
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++) {
                    if(grid[i][j] == 2) q.push({i, j});
                }
            }
    
            // all four directions
            int delRow[] = {-1, 0, 1, 0};
            int delCol[] = {0, 1, 0, -1};
    
            int count = 0;
            
            while(!q.empty()) {
                int size = q.size();
                int flag = 0;
    
                while(size--) {
                    // check 4 directions to this row and col
                    int row = q.front().first;
                    int col = q.front().second;
                    q.pop();
    
                    for(int i = 0; i < 4; i++) {
                        int newRow = row + delRow[i];
                        int newCol = col + delCol[i];
                        
                        // if newRow and newCol are inside grid and are 1, push them in queue
                        if(newRow < n && newRow >= 0 && newCol < m && newCol >= 0) {
                            if(grid[newRow][newCol] == 1) {
                                grid[newRow][newCol] = 2;
                                q.push({newRow, newCol});
                                flag = 1;
                            }
                        }
                    }
                }
                if(flag) count++;
            }
    
            // count the remaining islands which are not visited from boundry land
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++) {
                    if(grid[i][j] == 1) return -1;
                }
            }
    
            return count;
        }
    };

/*

Idea:
------

Rotten oranges spread the infection to all adjacent fresh
oranges every minute.

Since all rotten oranges spread simultaneously, we cannot
start BFS from just one rotten orange.

Instead, we perform a

Multi-Source BFS,

where every initially rotten orange is added to the queue at
the beginning.

Each BFS level represents

one minute

of time.

------------------------------------------------------------

Key Observation:
----------------

All rotten oranges infect their neighboring fresh oranges
at the same time.

Therefore,

every rotten orange acts as a source of infection.

By inserting all rotten oranges into the queue initially,

BFS naturally simulates the spread of rot minute by minute.

------------------------------------------------------------

Algorithm:
----------

1. Traverse the grid and push every initially rotten orange
   into the queue.

2. Perform BFS level by level.

3. For every rotten orange in the current level, infect all
   adjacent fresh oranges.

4. Newly rotten oranges are added to the queue and will
   spread the infection during the next minute.

5. If at least one fresh orange becomes rotten during the
   current level, increment the minute counter.

6. After BFS completes, check the grid.

   - If any fresh orange still exists, return -1.
   - Otherwise, return the total minutes required.

------------------------------------------------------------

Example:
--------

Grid

2 1 1

1 1 0

0 1 1

Initially Rotten

↓

(0,0)

Minute 0

2 1 1

1 1 0

0 1 1

----------------------------

Minute 1

2 2 1

2 1 0

0 1 1

----------------------------

Minute 2

2 2 2

2 2 0

0 1 1

----------------------------

Minute 3

2 2 2

2 2 0

0 2 1

----------------------------

Minute 4

2 2 2

2 2 0

0 2 2

All oranges are rotten.

Answer = 4

------------------------------------------------------------

Visualization:
--------------

Initial Queue

(0,0)

↓

Minute 1

(0,1)

(1,0)

↓

Minute 2

(0,2)

(1,1)

↓

Minute 3

(2,1)

↓

Minute 4

(2,2)

The queue grows level by level, where each level represents
one minute of infection.

------------------------------------------------------------

Why Does This Work?
-------------------

BFS always processes nodes level by level.

Since every BFS level corresponds to one minute,

all oranges that become rotten during a minute infect their
neighbors together in the next minute.

This perfectly matches the rules of the problem.

If any fresh orange remains after BFS, it means that orange
was never reachable from any rotten orange, so it can never
rot.

------------------------------------------------------------

Time Complexity:
----------------

Each cell is processed at most once.

O(n × m)

------------------------------------------------------------

Space Complexity:
-----------------

Queue stores each orange at most once.

O(n × m)

*/