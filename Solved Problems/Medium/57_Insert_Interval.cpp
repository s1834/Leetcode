class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        if(!intervals.size()) return {newInterval};
        vector<vector<int>> ans;
        bool inserted = false, resolve = false;
        for(vector<int> v : intervals) {
            if(resolve) {
                ans.push_back(v);
            } else if(inserted) {
                if(ans.back()[1] >= v[0]) {
                    ans.back()[1] = max(ans.back()[1], v[1]);
                } else {
                    ans.push_back(v);
                    resolve = true;
                }
            } else {
                if(v[1] >= newInterval[0]) {
                    v[1] = max(v[1], newInterval[1]);
                    inserted = true;
                }
                ans.push_back(v);
            }
        }
        return ans;
    }
};