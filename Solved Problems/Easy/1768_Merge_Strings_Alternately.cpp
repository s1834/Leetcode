class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        string ans;
        int n = word1.size() > word2.size() ? word1.size() : word2.size();
        for (int i = 0; i < n; i++) {
            if (word1[i] >= 'a' && word1[i] <= 'z') {
                ans.push_back(word1[i]);
            }
            
            if (word2[i] >= 'a' && word2[i] <= 'z') {
                ans.push_back(word2[i]);
            }
        }

        return ans;
    }
};