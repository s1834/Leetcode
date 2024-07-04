class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        if(!intervals.size()) return {newInterval};
        vector<vector<int>> ans;
        bool inserted = false, resolved = false;
        for(vector<int> v : intervals) {
            if(resolved) {
                ans.push_back(v);
            } else if(inserted) {
                if(ans.back()[1] >= v[0]) {
                    ans.back()[1] = max(ans.back()[1], v[1]);
                } else {
                    ans.push_back(v);
                    resolved = true;
                }
            } else {
                if(v[0] >= newInterval[0]) {
                    v[0] = min(v[0], newInterval[0]);
                    v[1] = max(v[1], newInterval[1]);
                    inserted = true;
                } else if(v[1] >= newInterval[0]) {
                    v[1] = max(v[1], newInterval[1]);
                    inserted = true;
                }
                ans.push_back(v);
            }
        }
        if(!inserted) ans.push_back(newInterval);
        return ans;
    }
};