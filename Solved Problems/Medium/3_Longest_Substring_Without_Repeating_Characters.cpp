class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        map<char, int> mp;
        int longest = 0;
        for(auto x : s) {
            mp[x]++;
            if(mp[x] > 1) {
                if(mp.size() > longest) longest = mp.size();
                mp.clear();
                mp[x]++;
            }
        }
        return longest;
    }
};