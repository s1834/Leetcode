class Solution {
public:
    bool checkIfPangram(string sentence) {
        set<char> s1;
        int n = sentence.size();
        for (int i = 0; i < n; i++) {
            s1.insert(sentence[i]);
        }
        return s1.size() == 26 ? true : false;
    }
};