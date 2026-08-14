class Solution {
    public:
        int maximumLengthSubstring(string s) {
            unordered_map<char, int> mp;
            int n = s.size(), l = 0, r = 0, mx = 0;
            while(r < n) {
                mp[s[r]]++;
                while(mp[s[r]] > 2 && l <= r) {
                    mp[s[l]]--;
                    l++;
                }
                mx = max(mx, r - l + 1);
                r++;
            }
            return mx;
        }
    };