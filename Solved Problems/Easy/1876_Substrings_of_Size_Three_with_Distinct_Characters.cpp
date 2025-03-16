class Solution {
    public:
        int countGoodSubstrings(string s) {
            int n = s.size(), count = 0;
            for(int i = 0; i < n - 2; i++) {
                set<char> s1;
                for(int j = i; j < i + 3; j++) s1.insert(s[j]);
                if(s1.size() == 3) count++;
            }
            return count;
        }
    };