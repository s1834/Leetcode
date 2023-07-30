class Solution {
public:
    bool isPalindrome(string s) {
        vector<char> ch;
        int size = s.size(),temp = 0;

        for (int i = 0; i < size; i++) {
            if (isalnum(s[i])) {
                ch.push_back(tolower(s[i]));
            }
        }
        size = ch.size();
        temp = size - 1;
        for (int i = 0; i < size / 2; i++) {
            if (ch[i] != ch[temp]) {
                return false;
            }
            temp--;
        }
        return true;
    }
};