class Solution {
public:
    int compress(vector<char>& chars) {
        int count = 1, n = chars.size();
        string s = "";
        for (int i = 0; i < n - 1; i++) {
            if(chars[i] != chars[i + 1]) {
                if(count == 1) {
                    s += chars[i];
                } else {
                    s += chars[i];
                    s += to_string(count);
                }
                count = 1;
            } else {
                count++;
            }
        }
        if(count) {
            if(count == 1) {
                s += chars[n - 1];
            } else {
                s += chars[n - 1];
                s += to_string(count);
            }
        }

        chars.clear();
        n = s.size();
        for(int i = 0; i < n; i++) {
            chars.push_back(s[i]);
        }

        return chars.size();
    }
};