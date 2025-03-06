class Solution {
public:
    vector<string> commonChars(vector<string>& words) {
        vector<int> v (26, 0);
        vector<string> ans;
        for (int i = 0; i < words[0].size(); i++) {
             v[words[0][i] - 'a']++;
        }

        for (int i = 1; i < words.size(); i++) {
            vector<int> v1 (26,0);
            for (int j = 0; j < words[i].size(); j++) {
                v1[words[i][j] - 'a']++;
            }

            for(int j = 0; j < 26; j++) {
                v[j] = min(v[j], v1[j]);
            }
        }

        for(int i = 0; i < 26; i++) {
            for (int j = 0; j < v[i]; j++) {
                ans.push_back(string(1, i + 'a'));
            }
        }

        return ans;
    }
};