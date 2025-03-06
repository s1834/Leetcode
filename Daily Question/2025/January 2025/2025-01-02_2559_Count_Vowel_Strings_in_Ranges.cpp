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
    
        int count(vector<int> indexes, int l, int r) {
            int cnt = 0;
            for(auto x : indexes) {
                if (x >= l && x <= r) cnt++;
            }
            return cnt;
        }
    
    public:
        vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {
            vector<int> indexes;
            int n = words.size();
            for(int i = 0; i < n; i++) {
                if (checkVowel(words[i][0], words[i][words[i].size() - 1])) {
                    indexes.push_back(i);
                }
            }
    
            vector<int> ans;
            for(auto x : queries) {
                ans.push_back(count(indexes, x[0], x[1]));
            }
            return ans;
        }
    };