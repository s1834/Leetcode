class Solution {
public:
    int longestPalindrome(string s) {
        map<char, int> mp;
        int n = s.size();
        for(int i = 0; i < n; i++) {
            mp[s[i]]++;
        }

        for(auto x:mp) {
            if(x.second % 2) {
                n--;
            }
        }

        if(n != s.size()) {
            return n + 1;
        }
        return n;
    }
};