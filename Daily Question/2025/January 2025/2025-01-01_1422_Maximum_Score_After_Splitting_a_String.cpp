class Solution {
public:
    int maxScore(string s) {
        int n = s.size(), one = 0;
        for (int i = 0; i < n; i++) {
            if(s[i] == '1') one++;
        }

        int zero = 0, mx = 0;
        for(int i = 0; i < n - 1; i++) {
            if(s[i] == '1') one--;
            if(s[i] == '0') zero++;
            if(one + zero > mx) mx = one + zero;
        }

        return mx;
    }
};