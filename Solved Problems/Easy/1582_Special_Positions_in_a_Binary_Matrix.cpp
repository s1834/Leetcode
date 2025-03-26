class Solution {
    public:
        int numSpecial(vector<vector<int>>& mat) {
            vector<int> row, col;
            int n = mat.size(), m = mat[n - 1].size();
            for (int i = 0; i < n; i++) {
                int one = 0;
                for (int j = 0; j < m; j++) {
                    one += mat[i][j];
                }
                row.push_back(one);
            }
    
            for (int i = 0; i < m; i++) {
                int one = 0;
                for (int j = 0; j < n; j++) {
                    one += mat[j][i];
                }
                col.push_back(one);
            }
            
            int count = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) if(row[i] == 1 && col[j] == 1 && mat[i][j] == 1) count++;
            }
            return count;
        }
    };