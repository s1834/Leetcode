class Solution {
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        // vector<int> adj[n];
        // for(auto edge : edges) {
        //     adj[edge[0]].push_back(edge[1]);
        // }
        // vector<int> reached(n, 0);
        // for(auto row : adj) {
        //     for(auto col : row) {
        //         if(!reached[col]) reached[col] = 1;
        //     }
        // }

        // vector<int> ans;
        // for(int i = 0; i < n; i++) {
        //     if(!reached[i]) ans.push_back(i);
        // }

        // return ans;

        vector<int> indegree(n, 0);
        for(auto edge : edges) {
            indegree[edge[1]] = 1;
        }

        vector<int> ans;
        for(int i = 0; i < n; i++) {
            if(!indegree[i]) ans.push_back(i);
        }

        return ans;
    }
};