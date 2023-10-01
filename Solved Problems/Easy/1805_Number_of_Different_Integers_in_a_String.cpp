class Solution {
public:
    int numDifferentIntegers(string word) {
        set<char> s1;
        string temp = "";
        int n = word.size();
        for (int i = 0; i < n; i++) {
            if (isdigit(word[i])) {
                temp += word[i];
            }
            if (!isdigit(word[i]) && temp != "") {
                s1.insert(stoi(temp));
                temp = "";
            }
        }
        if (temp != "") {
            s1.insert(stoi(temp));
        }
        return s1.size();
    }
};