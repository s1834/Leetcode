class Solution {
public:
    int numDifferentIntegers(string word) {
        set<string> s1;
        string temp = "";
        int count = 0;
        int n = word.size();
        for (int i = 0; i < n; i++) {
            if (isdigit(word[i])) {
                if (!count && word[i] == '0') {
                    continue;
                }
                temp += word[i];
                count++;
            }
            if (!isdigit(word[i]) && temp != "") {
                s1.insert(temp);
                temp = "";
                count = 0;
            }
        }
        if (temp != "") {
            s1.insert(temp);
        }
        return s1.size();
    }
};