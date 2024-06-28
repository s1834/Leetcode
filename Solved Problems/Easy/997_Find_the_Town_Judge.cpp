class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        unordered_map<int, int> indegree;
        int siz = trust.size();
        for (int i = 0; i < siz; i++) {
            indegree[trust[i][0]] = -1;
            if(indegree[trust[i][1]] != -1) {
                indegree[trust[i][1]]++;
            }
        }

        for(auto x : indegree) {
            if(x.second == n - 1) {
                return x.first;
            } 
        }
        return -1;
    }
};