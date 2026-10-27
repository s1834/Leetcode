class Solution {
    public:
        vector<string> createGrid(int m, int n) {
            vector<string> ans(m, string(n, '.'));
    
            for(int i = 1; i < m; i++) {
                for(int j = 0; j < n - 1; j++) ans[i][j] = '#';
            }
    
            return ans;
        }
    };

/*
Problem: LeetCode 3963 - Create Grid

Approach: Initialize Grid + Fill Selected Cells

Intuition:
----------
We need to create a grid with m rows and n columns.

Initially, every cell contains '.'.
Then, starting from the second row (index 1), we fill the first
n - 1 columns with '#'.

The first row remains entirely filled with '.', and the last column
of every row also remains '.'.

--------------------------------------------------
1. Initialize the Grid
--------------------------------------------------

vector<string> ans(m, string(n, '.'));

Create a vector containing m strings, each of length n.

Every character is initialized to '.'.

For example, if m = 3 and n = 4:

ans = [
    "....",
    "....",
    "...."
]

--------------------------------------------------
2. Traverse Rows Starting from Index 1
--------------------------------------------------

for(int i = 1; i < m; i++)

The loop starts at row index 1 instead of 0.

Therefore, the first row remains unchanged, containing only '.'.

The loop continues until the last row, m - 1.

--------------------------------------------------
3. Fill the First n - 1 Columns
--------------------------------------------------

for(int j = 0; j < n - 1; j++)
    ans[i][j] = '#';

For every row after the first row, iterate through columns
0 to n - 2 and replace each character with '#'.

The condition j < n - 1 ensures that the last column, at index
n - 1, remains '.'.

For example, with n = 4, columns 0, 1, and 2 become '#',
while column 3 remains '.'.

--------------------------------------------------
4. Return the Grid
--------------------------------------------------

return ans;

After filling the required cells, return the completed grid.

--------------------------------------------------
5. Example Walkthrough
--------------------------------------------------

Input:
m = 3, n = 4

Initially:
[
    "....",
    "....",
    "...."
]

After processing row 1:
[
    "....",
    "###.",
    "...."
]

After processing row 2:
[
    "....",
    "###.",
    "###."
]

Output:
[
    "....",
    "###.",
    "###."
]

--------------------------------------------------
6. Complexity Analysis
--------------------------------------------------

Time Complexity: O(m * n)

Initializing the grid takes O(m * n) time, and the nested loops
fill up to (m - 1) * (n - 1) cells.

Space Complexity: O(m * n)

The returned grid contains m strings, each with n characters.

Core Idea:
----------
Initialize the entire grid with '.', then fill the first n - 1
columns with '#' in every row except the first.
*/