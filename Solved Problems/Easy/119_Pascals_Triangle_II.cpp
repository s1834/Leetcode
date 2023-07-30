class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<vector<int>> ans;
        vector<int> vect;

        for (int i = 0; i <= rowIndex; i++) {
            for (int j = 0; j <= i; j++) {
                if (j == 0 || j == i) {
                    vect.push_back(1);
                } else {
                    vect.push_back(ans[i - 1][j] + ans[i - 1][j - 1]);
                }
            }

            ans.push_back(vect);
            if (i != rowIndex) {
                vect.clear();
            }
        }

        return vect;
    }
};