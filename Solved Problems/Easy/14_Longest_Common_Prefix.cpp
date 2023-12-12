class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string s = "";
        int min = INT_MAX;
        for (int i = 0; i < strs.size(); i++) {
            if (strs[i].size() < min) {
                min = strs[i].size();
            }
        }

        for (int i = 0; i < min; i++) {
            bool temp = true;
            for (int j = 0; j < strs.size(); j++) {
                if (strs[j][i] != strs[0][i]) {
                    temp = false;
                    break;
                }
            }
            if (temp) {
                s += strs[0][i];
            } else {
                break;
            }
        }

        return s;
    }
};