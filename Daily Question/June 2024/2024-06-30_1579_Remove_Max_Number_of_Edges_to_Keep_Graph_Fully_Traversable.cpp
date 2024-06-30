class Solution {
private:
    void checkPath(int i, vector<pair<int, int>>& adj, vector<int>& alice, vector<int>& bob, int& count) {
        if(i == 3) {
            for(auto x : adj) {
                bool change = false;
                if(!alice[x.first]) {
                    alice[x.first] = 1;
                    bob[x.first] = 1;
                    change = true;
                }

                if(!alice[x.second]) {
                    alice[x.second] = 1;
                    bob[x.second] = 1;
                    change = true;
                }
                
                if(change) count++;
            }
        } else if(i == 2) {
            for(auto x : adj) {
                bool change = false;
                if(!bob[x.first]) {
                    bob[x.first] = 1;
                    change = true;
                }

                if(!bob[x.second]) {
                    bob[x.second] = 1;
                    change = true;
                }
                
                if(change) count++;
            }
        } else {
            for(auto x : adj) {
                bool change = false;
                if(!alice[x.first]) {
                    alice[x.first] = 1;
                    change = true;
                }

                if(!alice[x.second]) {
                    alice[x.second] = 1;
                    change = true;
                }
                
                if(change) count++;
            }
        }
    }

public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        vector<vector<pair<int,int>>> adj(4);
        for(auto edge : edges) {
            adj[edge[0]].push_back(make_pair(edge[1], edge[2]));
        }
        
        vector<int> alice(n + 1, 0), bob(n + 1, 0);
        int count = 0;
        for (int i = 3; i > 0; i--) {
            checkPath(i, adj[i], alice, bob, count);  
        }

        for(int i = 1; i <= n; i++) {
            if(!alice[i] || !bob[i]) return -1;
        }

        return edges.size() - count;
    }
};