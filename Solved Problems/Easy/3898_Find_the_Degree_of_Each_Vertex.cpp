class Solution {
    public:
        vector<int> findDegrees(vector<vector<int>>& matrix) {
            int n = matrix.size();
            vector<int> ans(n, 0);
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) ans[i] += matrix[i][j];
            }
    
            return ans;
        }
    };

/*
    ============================================================
    LeetCode 3898
    ============================================================

    Approach:
    ------------------------------------------------------------

    The given `matrix` represents a graph using an adjacency
    matrix.

    For every vertex `i`, we need to find its degree, i.e. the
    number of edges connected to that vertex.

    In an adjacency matrix:

        matrix[i][j] = 1

    means there is an edge from vertex `i` to vertex `j`.

    Therefore, the degree of vertex `i` is simply the sum of
    all values in row `i`.

    We store these degrees in the `ans` array.

    ============================================================
    1. Iterate Through Every Vertex
    ============================================================

    for(int i = 0; i < n; i++)

    `i` represents the current vertex whose degree we want
    to calculate.

    Initially:

        ans[i] = 0

    for every vertex.

    ============================================================
    2. Count the Degree of Vertex i
    ============================================================

    for(int j = 0; j < n; j++)
        ans[i] += matrix[i][j];

    We traverse the entire row `i`.

    Every `1` represents an edge connected to vertex `i`, while
    a `0` means there is no edge.

    Therefore:

        degree(i) = matrix[i][0]
                  + matrix[i][1]
                  + ...
                  + matrix[i][n-1]

    After processing the row, `ans[i]` contains the degree
    of vertex `i`.

    ============================================================
    3. Example
    ============================================================

    Suppose:

        matrix =
        [
            [0, 1, 1],
            [1, 0, 1],
            [1, 1, 0]
        ]

    For vertex 0:

        0 + 1 + 1 = 2

    So:

        ans[0] = 2

    For vertex 1:

        1 + 0 + 1 = 2

    So:

        ans[1] = 2

    For vertex 2:

        1 + 1 + 0 = 2

    So:

        ans[2] = 2

    Therefore:

        ans = [2, 2, 2]

    ============================================================
    4. Why Does Summing the Row Work?
    ============================================================

    Each position in row `i` tells us whether vertex `i` is
    connected to another vertex.

        matrix[i][j] = 1
            -> one edge contributes to the degree

        matrix[i][j] = 0
            -> no edge contributes anything

    Hence, summing the complete row directly gives the number
    of edges incident to vertex `i`.

    ============================================================
    Complexity Analysis
    ============================================================

    Let n be the number of vertices.

    Time Complexity: O(n²)

        We visit every element of the n x n matrix exactly once.

    Space Complexity: O(n)

        The `ans` vector stores one degree for each vertex.

        Apart from the output array, only O(1) extra space is used.

    ============================================================
    Core Idea
    ============================================================

    In an adjacency matrix:

        Degree of vertex i = sum of row i

    So simply traverse every row and calculate its sum.
    ============================================================
*/