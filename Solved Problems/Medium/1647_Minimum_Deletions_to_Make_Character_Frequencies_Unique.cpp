class Solution {
public:
    int minDeletions(string s) {
        map<char, int> mp;
        int n = s.size();

        for(int i = 0; i < n; i++) {
            mp[s[i]]++;
        }

        int sum = 0, max = 0;
        for(auto x : mp) {
            if(x.second > max) {
                max = x.second;
            }
            sum += x.second;
        }
        
        for (int i = 1; i <= max; i++) {
            sum -= i;
        }

        return sum;
    }
};