class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> mp;
        int longest = 0;
        for(auto x : s) {
            mp[x]++;
            if(mp[x] > 1) {
                if(mp.size() > longest) longest = mp.size();
                for (auto y : s) {
                    if(y == x) {
                        mp.erase(y);
                        break;
                    }
                    mp.erase(y);
                }
                mp[x]++;
            }
        }
        if(mp.size() > longest) longest = mp.size();
        return longest;
    }
};