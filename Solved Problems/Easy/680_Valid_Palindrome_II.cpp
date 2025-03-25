class Solution {
    public:
        bool validPalindrome(string s) {
            int i = 0, j = s.size() - 1;
            bool palindrome = false;
            while(j > i) {
                if(s[i] == s[j]) {
                    palindrome = true;
                    i++;
                    j--;
                } else {
                    int temp1 = i, temp2 = j - 1;
                    i++;
                    while(j >= i) {
                        if(s[i] == s[j]) {
                            palindrome = true;
                            i++;
                            j--;
                        } else {
                            palindrome = false;
                            break;
                        }
                    }
                    if (palindrome) return true;
                    while(temp2 >= temp1) {
                        if(s[temp1] == s[temp2]) {
                            palindrome = true;
                            temp1++;
                            temp2--;
                        } else return false;
                    }
                    break;
                }
            }
            return true;
        }
    };