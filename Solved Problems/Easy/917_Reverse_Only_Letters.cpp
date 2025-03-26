class Solution {
    public:
        string reverseOnlyLetters(string s) {
           int i = 0, j = s.size() - 1;
           while(i < j) {
                if(!isalpha(s[i])) i++;
                else if(!isalpha(s[j])) j--;
                else {
                    char c = s[i];
                    s[i] = s[j];
                    s[j] = c;
                    i++;
                    j--;
                }
           } 
           return s;
        }
    };