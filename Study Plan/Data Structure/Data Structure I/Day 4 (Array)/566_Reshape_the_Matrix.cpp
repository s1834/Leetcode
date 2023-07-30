class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
        vector<int> vec;
        int m = mat.size(), n = mat[0].size();
        
        if (m * n != r * c) {
            return mat;
        }
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                vec.push_back(mat[i][j]);
            }
        }

        vector<vector<int>> ans(r, vector<int> (c));
        int count = 0;
        for(int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                ans[i][j] = vec[count];
                count++;
            }
        }

        return ans;
    }
};