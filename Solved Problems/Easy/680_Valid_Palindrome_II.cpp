class Solution {
    public:
        bool validPalindrome(string s) {
            int i = 0, j = s.size() - 1;
            bool palindrome = false, remove = true;
            while(j > i) {
                if(s[i] == s[j]) {
                    palindrome = true;
                    i++;
                    j--;
                } else if(remove) {
                    if(s[i] == s[j - 1]) j--;
                    else i++;
                    remove = false;
                } else {
                    return false;
                }
            }
            return true;
        }
    };