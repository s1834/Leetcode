class Solution {
public:
    int partitionString(string s) {
        map<char, int> mp;
        int n = s.size(), count = 0;
        for(int i = 0; i < n; i++) {
            if(mp[s[i]] == 1) {
                mp.clear();
                count++;
            }
            mp[s[i]]++;
        }

        return count + 1;
    }
};