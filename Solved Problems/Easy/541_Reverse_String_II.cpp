class Solution {
    public:
        string reverseStr(string s, int k) {
            int n = s.size();
            for(int i = 0; i < n; i++) {
                if(i + k > n) {
                    reverse(s.begin() + i, s.end());
                    break;
                } else {
                    reverse(s.begin() + i, s.begin() + i + k);
                    i += 2 * k - 1;
                }
            }
            return s;
        }
    };