class Solution {
public:
    string maximumOddBinaryNumber(string s) {
        int n = s.size(), count = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '1') {
                count++;
            }
        }
        
        for (int i = 0; i < n - 1; i++) {
            if (count > 1) {
                s[i] = '1';
                count--;
            } else {
                s[i] = '0';
            }
        }
        
        s[n - 1] = '1';
        return s;
    }
};