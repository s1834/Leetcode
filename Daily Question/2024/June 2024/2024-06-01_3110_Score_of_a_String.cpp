class Solution {
public:
    int scoreOfString(string s) {
        int n = s.size() - 1, score = 0;
        for (int i = 0; i < n; i++) {
            score += abs(s[i] - s[i + 1]);
        }
        return score;
    }
};