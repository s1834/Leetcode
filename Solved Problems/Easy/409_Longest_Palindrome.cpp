class Solution {
public:
    int longestPalindrome(string s) {
        map<char, int> mp;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            mp[s[i]]++;
        }

        n = mp.size();
        int sum = 0, max = 0;
        for (auto i : mp) {
            if (i.second % 2 == 0) {
                sum += i.second;
            } else if (i.second > max) {
                max = i.second;
            }
        }

        return sum + max;
    }
};