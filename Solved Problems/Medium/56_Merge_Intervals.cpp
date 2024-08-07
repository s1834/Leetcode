// class Solution {
// public:
//     vector<vector<int>> merge(vector<vector<int>>& intervals) {
//         auto lamda = [](vector<int> v1, vector<int> v2) {
//             return v1[0] < v2[0];
//         };
//         sort(intervals.begin(), intervals.end(), lamda);

//         stack<vector<int>> st;
//         st.push(intervals[0]);
//         int n = intervals.size();
//         for(int i = 1; i < n; i++) {
//             if(intervals[i][0] <= st.top()[1]) st.top()[1] = max(st.top()[1], intervals[i][1]);
//             else st.push(intervals[i]);
//         }

//         intervals.clear();
//         while(!st.empty()) {
//             intervals.push_back(st.top());
//             st.pop();
//         }
//         return intervals;
//     }
// };

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> ans;
        ans.push_back(intervals[0]);
        for(vector<int> v : intervals) {
            if(ans.back()[1] >= v[0]) ans.back()[1] = max(ans.back()[1], v[1]);
            else ans.push_back(v);
        }
        return ans;
    }
};