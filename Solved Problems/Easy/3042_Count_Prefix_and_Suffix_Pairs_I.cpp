class Solution {
    private:
        bool isPrefixAndSuffix(string str1, string str2) {
            if(str1.size() > str2.size()) return false;
            int n = str1.size(), m = str2.size();
            for(int i = 0; i < n; i++) if(str1[i] != str2[i]) return false;
            for(int i = m - n, j = 0; i < m && j < n; i++, j++) if(str1[j] != str2[i]) return false;
            return true;
        }
    
    public:
        int countPrefixSuffixPairs(vector<string>& words) {
            int n = words.size(), count = 0;
            for(int i = 0; i < n; i++) {
                for(int j = i + 1; j < n; j++) if(isPrefixAndSuffix(words[i], words[j])) count++;
            }
            return count;
        }
    };