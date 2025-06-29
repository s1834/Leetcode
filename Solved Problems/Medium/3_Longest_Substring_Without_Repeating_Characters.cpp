class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        set<char> st;
        int l = 0, r = 0, n = s.size(), mx = 0, count = 0;
        while(r < n) {
            while(st.find(s[r]) != st.end()) {
                st.erase(s[l]);
                l++;
                mx = max(mx, count);
                count--;
            }
            st.insert(s[r]);
            count++;
            r++;
        }
        return max(mx, count);
    }
};

// class Solution {
// public:
//     int lengthOfLongestSubstring(string s) {
//         unordered_map<char, int> mp;
//         int longest = 0, left = 0, right = 0, n = s.size();
//         while(left <= right && right < n) {
//             mp[s[right]]++;
//             while(mp[s[right]] > 1) {
//                 mp[s[left]]--;
//                 if(!mp[s[left]]) mp.erase(s[left]);
//                 left++;
//             }
//             longest = max(longest, right - left + 1);
//             right++;
//         }
        
//         return longest;
//     }
// };