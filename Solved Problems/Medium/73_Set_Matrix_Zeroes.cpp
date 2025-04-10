class Solution {
    public:
        void setZeroes(vector<vector<int>>& matrix) {
            vector<pair<int, int>> v;
            int n = matrix.size(), m = matrix[0].size();
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++) if(!matrix[i][j]) v.push_back({i, j});
            }
            for(auto x : v) {
                for(int i = 0; i < n; i++) matrix[i][x.second] = 0;
                for(int i = 0; i < m; i++) matrix[x.first][i] = 0;
            }
        }
    };