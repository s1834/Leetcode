class Solution {
public:
    int romanToInt(string s) {
        int num = 0;
        for(int i = 0; i < s.length(); i++) {
            if (s[i] == 'I') {
                num++;
            } else if (s[i] == 'V') {
                if (i > 0 && s[i - 1] == 'I') {
                    num += 4;
                    num -= 1;
                } else {
                    num += 5;
                }
            } else if (s[i] == 'X') {
                if (i > 0 && s[i - 1] == 'I') {
                    num += 9;
                    num -= 1;
                } else {
                    num += 10;
                }
            } else if (s[i] == 'L') {
                if (i > 0 && s[i - 1] == 'X') {
                    num += 40;
                    num -= 10;
                } else {
                    num += 50;
                }
            } else if (s[i] == 'C') {
                if (i > 0 && s[i - 1] == 'X') {
                    num += 90;
                    num -= 10;
                } else {
                    num += 100;
                }
            } else if (s[i] == 'D') {
                if (i > 0 && s[i - 1] == 'C') {
                    num += 400;
                    num -= 100;
                } else {
                    num += 500;
                }
            } else {
                if (i > 0 && s[i - 1] == 'C') {
                    num += 900;
                    num -= 100;
                } else {
                    num += 1000;
                }
            }
        }
        return num;
    }
};