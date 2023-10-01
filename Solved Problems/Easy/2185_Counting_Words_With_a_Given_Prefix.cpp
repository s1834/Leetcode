class Solution {
public:
    int prefixCount(vector<string>& words, string pref) {
        int n = words.size(), n1 = pref.size(), count = 0, flag;
        for (int i = 0; i < n; i++) {
            flag = 1;
            for (int j = 0; j < n1; j++) {
                if (words[i][j] != pref[j]) {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                count++;
            }
        } 
        return count;
    }
};