class Solution {
public:
    string restoreString(string s, vector<int>& indices) {
        int n = indices.size();
        vector<char> str(n, '\0'); 
        for(int i = 0; i < n; i++) {
            str[indices[i]] = s[i];
        }

        return string(str.begin(), str.end());
    }
};