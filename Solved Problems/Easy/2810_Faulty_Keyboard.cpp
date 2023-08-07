class Solution {
public:
    string finalString(string s) {
        int n = s.size();
        string ans;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'i' && i > 1) {
                reverse(ans.begin(), ans.end());
            } else {
                ans += s[i];
            }
        }
        return ans;
    }
};