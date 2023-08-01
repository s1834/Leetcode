class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        map<char, int> mp1, mp2; 
        int n1 = magazine.size(), n2 = ransomNote.size();
        for (int i = 0; i < n1; i++) {
            mp1[magazine[i]]++;
        }
        for (int i = 0; i < n2; i++) {
            mp2[ransomNote[i]]++;
        }
        for (int i = 0; i < n1; i++) {
            if (mp1[ransomNote[i]] != mp2[ransomNote[i]]) {
                return false;
            }
        }

        return true;
    }
};