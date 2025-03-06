class Solution {
    private:
        bool checkVowel(char x, char y) {
            if(x == 'a'|| x == 'e' || x == 'i' || x == 'o' || x == 'u') {
                if(y == 'a'|| y == 'e' || y == 'i' || y == 'o' || y == 'u') {
                    return true;
                }
            }
            return false;
        }
        
    public:
        vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {
            vector<int> prefixSum;
            if(checkVowel(words[0][0], words[0][words[0].size() - 1])) prefixSum.push_back(1);
            else prefixSum.push_back(0);
            
            int n = words.size();
            for (int i = 1; i < n; i++) {
                if(checkVowel(words[i][0], words[i][words[i].size() - 1])) prefixSum.push_back(prefixSum[i - 1] + 1);
            else prefixSum.push_back(prefixSum[i - 1]);
            }
    
            vector<int> ans;
            for (auto x : queries) {
                if(x[0] == 0) ans.push_back(prefixSum[x[1]]);
                else ans.push_back(prefixSum[x[1]] - prefixSum[x[0] - 1]);
            }
            return ans;
        }
    };