class Solution {
    public:
        int countKeyChanges(string s) {
            int n = s.size(), change = 0;
            for(int i = 1; i < n; i++) if(tolower(s[i - 1]) != tolower(s[i])) change++;
            return change;
        }
    };