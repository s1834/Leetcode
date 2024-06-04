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

        return n + 1;
    }
};