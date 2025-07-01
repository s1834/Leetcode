class Solution {
public:
    int characterReplacement(string s, int k) {
        map<char, int> mp;
        int n = s.size(), mx = 0, ans = 0, l = 0, r = 0;
        while(r < n) {
            mp[s[r]]++;
            mx = max(mx, mp[s[r]]);
            if(r - l + 1 - mx > k) {
                mp[s[l]]--;
                l++;
            }
            ans = max(mx, r - l + 1);
            r++;
        }
        return ans;
    }
};