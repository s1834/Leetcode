class Solution {
public:
    int longestContinuousSubstring(string s) {
        int n = s.size(), count = 1, mx = 1;
        for(int i = 1; i < n; i++) {
            if(s[i - 1] + 1 == s[i]) {
                count++;
            } else {
                mx = max(mx, count);
                count = 1;
            }
        }
        mx = max(mx, count);
        return mx;
    }
};