class Solution {
    public:
        int countServers(vector<vector<int>>& grid) {
            int m = grid.size();
            int n = grid[0].size();
    
            vector<int> rowCount(m, 0);
            vector<int> colCount(n, 0);
    
            for(int i = 0; i < m; i++) {
                for(int j = 0; j < n; j++) {
                    if(grid[i][j] == 1) {
                        rowCount[i]++;
                        colCount[j]++;
                    }
                }
            }
    
            int count = 0;
            for(int i = 0; i < m; i++) {
                for(int j = 0; j < n; j++) {
                    if(grid[i][j] == 1 && (rowCount[i] > 1 || colCount[j] > 1)) count++;
                }
            }
    
            return count;
        }
    };

/*
    LeetCode 1267: Count Servers that Communicate

    Approach: Row and Column Frequency Counting

    Intuition:
    We are given an m x n binary grid where:
        - 1 represents a server.
        - 0 represents an empty cell.

    A server can communicate with another server if they are
    located in the same row or the same column.

    We need to count the number of servers that can communicate
    with at least one other server.

    Instead of checking every server against every other server,
    we can efficiently count the number of servers in each row
    and column.

    Key Observation:
    A server at position (i, j) can communicate with another
    server if:
        - Its row contains more than one server, OR
        - Its column contains more than one server.

    Therefore, we only need to maintain row and column frequencies.

    Variables:
    - m:
        Number of rows in the grid.

    - n:
        Number of columns in the grid.

    - rowCount:
        rowCount[i] stores the total number of servers in row i.

    - colCount:
        colCount[j] stores the total number of servers in column j.

    - count:
        Stores the total number of servers that can communicate.

    Step-by-Step Explanation:

    1. Get the dimensions of the grid:

           int m = grid.size();
           int n = grid[0].size();

    2. Initialize frequency arrays:

           vector<int> rowCount(m, 0);
           vector<int> colCount(n, 0);

       Both arrays are initialized with zeros.

    3. Count servers in every row and column:

       Traverse the entire grid using two nested loops.

       Whenever we encounter a server:

           if(grid[i][j] == 1)

       Increment:
           rowCount[i]++;
           colCount[j]++;

       After this traversal:
       - rowCount[i] tells us how many servers exist in row i.
       - colCount[j] tells us how many servers exist in column j.

    4. Count communicating servers:

       Traverse the grid again.

       For every cell containing a server, check:

           rowCount[i] > 1 || colCount[j] > 1

       Explanation:
       - If rowCount[i] > 1, there is at least one other server
         in the same row.
       - If colCount[j] > 1, there is at least one other server
         in the same column.

       If either condition is true, the current server can
       communicate with at least one other server.

       Increment count:

           count++;

    5. Return the final count.

    Example Walkthrough:

    grid = [
        [1, 0],
        [1, 1]
    ]

    First traversal:

        rowCount = [1, 2]
        colCount = [2, 1]

    Second traversal:

        Server at (0, 0):
            rowCount[0] = 1
            colCount[0] = 2
            Communicates through its column.
            count = 1

        Server at (1, 0):
            rowCount[1] = 2
            colCount[0] = 2
            Communicates through both row and column.
            count = 2

        Server at (1, 1):
            rowCount[1] = 2
            colCount[1] = 1
            Communicates through its row.
            count = 3

    Final Answer = 3

    Complexity Analysis:

    Time Complexity: O(m * n)

        - First traversal: O(m * n) to calculate row and column counts.
        - Second traversal: O(m * n) to count communicating servers.

        Overall: O(m * n).

    Space Complexity: O(m + n)

        - rowCount requires O(m) space.
        - colCount requires O(n) space.

        No additional data structures are used.

    Core Idea:
    Precompute the number of servers in every row and column.
    A server can communicate if its row or column contains
    more than one server. Use these frequencies to count all
    communicating servers in a second traversal.
*/