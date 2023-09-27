class Solution {
public:
    int strStr(string haystack, string needle) {
        int n1 = haystack.size(), n2 = needle.size(), count = 1, flag = -1;
        for (int i = 0; i < n1 - n2 + 1; i++) {
            if (haystack[i] == needle[0]) {
                for (int j = 1; j < n2; j++) {
                    if (haystack[i + j] != needle[j]) {
                        count = 1;
                        break;
                    }
                    count++;
                }
                if (count == n2) {
                    flag = i;
                    break;
                }
            }
        }

        if (flag != -1) {
            return flag;
        }

        return flag;
    }
};