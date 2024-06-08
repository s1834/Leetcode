class Solution {
public:
    string clearDigits(string s) {  
        vector<char> v;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            if(s[i] >= '0' && s[i] <= '9') {
                v.pop_back();
            } else {
                v.push_back(s[i]);
            }
        }
        
        n = v.size();
        s = "";
        for (int i = 0; i < n; i++) {
            s += v[i];
        }
        
        return s;
    }
};