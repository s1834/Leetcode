class Solution {
private:
    void dfs(int node, vector<int>& path, vector<vector<int>>& ans, vector<int>& visited, vector<int> adj[], int n) {
        visited[node] = 1;
        path.push_back(node);

        if(node == n - 1) {
            ans.push_back(path);
            return;
        }

        for(auto neighbour : adj[node]) {
            if(!visited[neighbour]) {
                dfs(neighbour, path, ans, visited, adj, n);
                visited[neighbour] = 0;
                path.pop_back();
            }
        }
    }

public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> adj[n];
        for(int i = 0; i < n; i++) {
            for(auto x : graph[i]) {
                adj[i].push_back(x);
            }
        }

        vector<vector<int>> ans;
        vector<int> visited(n, 0);
        vector<int> path;
        dfs(0, path, ans, visited, adj, n);
        return ans;
    }
};