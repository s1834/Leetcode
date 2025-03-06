class Solution {
private:
    void dfs(int ancestor, vector<int> adj[], int curNode, vector<vector<int>>& ancestors) {
        for(int x : adj[curNode]) {
            if(ancestors[x].empty() || ancestors[x].back() != ancestor) {
                ancestors[x].push_back(ancestor);
                dfs(ancestor, adj, x, ancestors);
            }
        }
    }

public:
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {
        vector<int> adj[n];
        for(auto edge: edges) {
            adj[edge[0]].push_back(edge[1]);
        }

        vector<vector<int>> ancestors(n);
        for(int i = 0; i < n; i++) {
            dfs(i, adj, i, ancestors);
        }
        
        return ancestors;
    }
};
