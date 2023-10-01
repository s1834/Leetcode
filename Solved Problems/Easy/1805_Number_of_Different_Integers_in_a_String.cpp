class Solution {
public:
    int numDifferentIntegers(string word) {
        set<string> s1;
        string temp = "";
        int count = 0, zero = 0;
        int n = word.size();
        for (int i = 0; i < n; i++) {
            if (isdigit(word[i])) {
                if (!count && word[i] == '0') {
                    zero = 1;
                    continue;
                }
                temp += word[i];
                count++;
                zero = 0;
            }
            if (!isdigit(word[i]) && (temp != "" || zero)) {
                if (zero) {
                    s1.insert("0");
                    continue;
                }
                s1.insert(temp);
                temp = "";
                count = 0;
                zero = 0;
            }
        }
        if (temp != "") {
            s1.insert(temp);
        }
        if (zero) {
            s1.insert("0");
        }
        return s1.size();
    }
};