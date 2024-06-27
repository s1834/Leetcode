class Solution {
public:
    int findCenter(vector<vector<int>>& edges) {
        unordered_map<int, int> degree;
        int n = edges.size();
        for(int i = 0; i < n; i++) {
            degree[edges[i][0]]++;
            degree[edges[i][1]]++;
        }

        for (auto x : degree) {
            if(x.second == n) {
                return x.first;
            }
        }

        return -1;
    }
};