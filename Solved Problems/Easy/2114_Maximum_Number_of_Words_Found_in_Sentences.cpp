class Solution {
public:
    int mostWordsFound(vector<string>& sentences) {
        int count, max = 0, n = sentences.size();
        for (int i = 0; i < n; i++) {
            count = 0;
            for (int j = 0; j < sentences[i].size(); j++) {
                if (sentences[i][j] == ' ') {
                    count++;
                }
            }
            if (count > max) {
                max = count;
            }
        }

        return max + 1;
    }
};