class Solution {
public:
    int appendCharacters(string s, string t) {
        int n = s.size(), m = t.size(), i = 0, j = 0;
        while(i < m && j < n) {
            for (j = 0; j < n; j++) {
                if(s[j] == t[i]) {
                    i++;
                }
            }
        }
        return m - i;
    }
};