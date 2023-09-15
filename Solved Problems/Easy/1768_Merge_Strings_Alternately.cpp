class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        string ans;
        int n1 = word1.size(), n2 = word2.size(), n = n1 > n2 ? n1 : n2;
        for (int i = 0; i < n; i++) {
            if (n1 > i && word1[i] >= 'a' && word1[i] <= 'z') {
                ans.push_back(word1[i]);
            }
            
            if (n2 > i && word2[i] >= 'a' && word2[i] <= 'z') {
                ans.push_back(word2[i]);
            }
        }

        return ans;
    }
};