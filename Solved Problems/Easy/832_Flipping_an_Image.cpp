class Solution {
    public:
        vector<vector<int>> flipAndInvertImage(vector<vector<int>>& image) {
            for(auto& x : image) {
                int i = 0, j = x.size() - 1;
                while(i < j) {
                    x[i] = x[i] + x[j];
                    x[j] = x[i] - x[j];
                    x[i] = x[i] - x[j];
                    x[i] = x[i] == 0 ? 1 : 0;
                    x[j] = x[j] == 0 ? 1 : 0;
                    i++;
                    j--;
                } 
                if(i == j)  x[i] = x[i] == 0 ? 1 : 0;
            }
            return image;
        }
    };