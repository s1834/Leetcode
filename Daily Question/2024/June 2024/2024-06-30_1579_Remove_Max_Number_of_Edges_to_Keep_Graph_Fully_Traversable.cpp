class DSU {
private:
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n + 1, -1);
        rank.resize(n + 1, 1);
    }

    int find(int i) {
        if(parent[i] == -1) return i;
        return parent[i] = find(parent[i]);
    }

    void unite(int x, int y) {
        int xParent = find(x), yParent = find(y);
        if(xParent != yParent) {
            if(rank[xParent] < rank[yParent]) {
                parent[xParent] = yParent;
            } else if(rank[yParent] < rank[xParent]) {
                 parent[yParent] = xParent;
            } else {
                 parent[yParent] = xParent;
                 rank[xParent]++;
            }
        } 
    }

    bool isConnected() {
        int par = find(1), n = parent.size();
        for(int i = 2; i < n; i++) {
            if(par != find(i)) return false;
        }
        return true;
    }
};

class Solution {
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        DSU aliceDSU(n), bobDSU(n);
        auto lamda = [](vector<int>& v1, vector<int>& v2) {
            return v1[0] > v2[0];
        };
        sort(edges.begin(), edges.end(), lamda);
        int edgeCount = 0;
        for(auto edge : edges) {
            int type = edge[0], x = edge[1], y = edge[2];

            if(type == 3) {
                bool addEdge = false;
                if(aliceDSU.find(x) != aliceDSU.find(y)) {
                    aliceDSU.unite(x, y);
                    addEdge = true;
                }
                if(bobDSU.find(x) != bobDSU.find(y)) {
                    bobDSU.unite(x, y);
                    addEdge = true;
                }
                if(addEdge) edgeCount++;
            } else if(type == 2) {
                if(bobDSU.find(x) != bobDSU.find(y)) {
                    bobDSU.unite(x, y);
                    edgeCount++;
                }
            } else {
                if(aliceDSU.find(x) != aliceDSU.find(y)) {
                    aliceDSU.unite(x, y);
                    edgeCount++;
                }
            }
        }

        if(!aliceDSU.isConnected() || !bobDSU.isConnected()) return -1;
        return edges.size() - edgeCount;
    }
};