class Solution {
public:
    bool isDistinct(string s, int i, int j) {
        vector<bool> visited(256);
        for(int k = i; k <= j; k++) {
            if(visited[s[k]]) {
                return false;
            }
            visited[s[k]] = true;
        }
        return true;
    }

    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        int len = 0;
        for (int i = 0; i < n; i++) {
            for(int j = i; j < n; j++) {
                if(isDistinct(s, i, j)) {
                    len = max(len, j - i + 1);
                }
            }
        }
        return len;
    }
};