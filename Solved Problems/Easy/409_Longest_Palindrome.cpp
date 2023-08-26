class Solution {
public:
    int longestPalindrome(string s) {
        map<char, int> mp;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            mp[s[i]]++;
        }

        int odd = 0;
        for (auto i : mp) {
            if (i.second % 2 != 0) {
                odd++;
            }
        }

        if (odd) {
            return n - odd + 1;
        }
        return n;
    }
};