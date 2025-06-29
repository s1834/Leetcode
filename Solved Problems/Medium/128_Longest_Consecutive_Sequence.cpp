class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        set<int> s;
        for(int x: nums) s.insert(x);
        
        int mx = 0;
        for(auto x : s) {
            int temp = x, count = 1;
            while(s.find(temp + 1) != s.end()) {
                count++;
                temp++;
            }
            mx = max(mx, count);
        }
        return mx;
    }
};

// class Solution {
// public:
//     int longestConsecutive(vector<int>& nums) {
//         map<int, int> mp;
//         int n = nums.size();
//         for (int i = 0; i < n; i++) {
//             mp[nums[i]]++;
//         }

//         int first = INT_MIN, count = 0, mx = 0;
//         for(auto x : mp) {
//             if(first == INT_MIN) {
//                 first = x.first + 1;
//                 count++;
//                 continue;
//             }
//             if(x.first != first) {
//                 if(count > mx) {
//                     mx = count;
//                 }
//                 first = x.first;
//                 count = 0;
//             }
//             count++;
//             first++;
//         }
        
//         if(count > mx) {
//             mx = count;
//         }
//         return mx;
//     }
// };