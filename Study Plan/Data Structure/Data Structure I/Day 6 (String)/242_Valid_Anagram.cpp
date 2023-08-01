class Solution {
public:
    bool isAnagram(string s, string t) {
        map<char, int> mp1, mp2; 
        int n1 = s.size(), n2 = t.size();
        for (int i = 0; i < n1; i++) {
            mp1[t[i]]++;
        }
        for (int i = 0; i < n2; i++) {
            mp2[s[i]]++;
        }
        for (auto x:mp2) {
            if (x.second != mp1[x.first]) {
                return false;
            }
        }

        return true;
    }
};