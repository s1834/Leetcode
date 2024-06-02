class Solution {
public:
    void reverseString(vector<char>& s) {
        int n = s.size() % 2 ? (s.size() + 1) / 2 : s.size() / 2, temp = s.size() - 1;
        for (int i = 0; i < n; i++) {
            if (temp == i) {
                break;
            }
            s[i] = s[i] + s[temp];
            s[temp] = s[i] - s[temp];
            s[i] = s[i] - s[temp];
            temp--;
        }
    }
};