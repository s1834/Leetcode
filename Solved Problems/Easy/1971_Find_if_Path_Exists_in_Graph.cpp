class Solution {
private:
    void dfs(int node, vector<vector<int>> adj, vector<int>& visited) {
        visited[node] = 1;
        for(auto neighbour : adj[node]) {
            if(!visited[neighbour]) {
                dfs(neighbour, adj, visited);
            }
        }
    }

public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        vector<vector<int>> adj(n);
        for (vector<int> edge: edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        vector<int> visited(n, 0);
        dfs(source, adj, visited);\
        return visited[destination] ? true : false;
    }
};