class Solution {
public:
    vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {
        vector<bool> vowel;
        int n = words.size();
        for (int i = 0; i < n; i++) {
            int l = words[i].size() - 1;
            if(words[i][0] == 'a' || words[i][0] == 'e' || words[i][0] == 'i' || words[i][0] == 'o' || words[i][0] == 'u') {
                if(words[i][l] == 'a' || words[i][l] == 'e' || words[i][l] == 'i' || words[i][l] == 'o' || words[i][l] == 'u') vowel.push_back(true);
                else vowel.push_back(false);
            } else vowel.push_back(false);
        }

        vector<int> count;
        n = queries.size();
        int total;
        for(int i = 0; i < n; i++) {
        total = 0;
            for(int j = queries[i][0]; j <= queries[i][1]; j++) {
                if(vowel[j]) total++;
            }
            count.push_back(total);
        }
        return count;
    }
};