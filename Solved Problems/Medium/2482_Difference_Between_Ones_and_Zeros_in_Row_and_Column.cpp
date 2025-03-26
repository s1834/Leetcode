class Solution {
    public:
        vector<vector<int>> onesMinusZeros(vector<vector<int>>& grid) {
            vector<int> row, col;
            int n = grid.size(), m = grid[n - 1].size();
            for (int i = 0; i < n; i++) {
                int one = 0, zero = 0;
                for (int j = 0; j < m; j++) {
                    if (grid[i][j] == 0) zero++;
                    else one++;
                }
                row.push_back(one - zero);
            }
    
            for (int i = 0; i < m; i++) {
                int one = 0, zero = 0;
                for (int j = 0; j < n; j++) {
                    if (grid[j][i] == 0) zero++;
                    else one++;
                }
                col.push_back(one - zero);
            }
            
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) grid[i][j] = row[i] + col[j];
            }
            return grid;
        }
    };