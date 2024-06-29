class Solution {
private:
    void dfs(int key, vector<vector<int>>& rooms, vector<int>& keys) {
        keys[key] = 1;
        for(auto room : rooms[key]) {
            if(!keys[room]) dfs(room, rooms, keys);
        }
    }

public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size();
        vector<int> keys(n, 0);
        dfs(0, rooms, keys);
        for(int i = 0; i < n; i++) {
            if(!keys[i]) return false;
        }
        return true;
    }
};