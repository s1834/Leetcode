class Solution {
public:
    bool closeStrings(string word1, string word2) {
        map<char, int> mp1, mp2;
        int n1 = word1.size(), n2 = word2.size();
        if(n1 != n2) {
            return false;
        }

        for (int i = 0; i < n1; i++) {
            mp1[word1[i]]++;
        }
        for (int i = 0; i < n2; i++) {
            mp2[word2[i]]++;
        }

        if(mp1.size() != mp2.size()) {
            return false;
        }

        for(auto x1 = mp1.begin(), x2 = mp2.begin(); x1 != mp1.end(); ++x1, ++x2) {
            if(x1->first != x2->first) {
                return false;
            }
        }

        set<int> st1, st2;
        for (int i = 0; i < n1; i++) {
            st1.insert(mp1[word1[i]]);
        }
        for (int i = 0; i < n2; i++) {
            st2.insert(mp2[word2[i]]);
        }

        n1 = st1.size();
        n2 = st2.size();
        if(n1 != n2) {
            return false;
        }

        auto it1 = st1.begin(), it2 = st2.begin();
        for (int i = 0; i < n1; i++) {
            if(*it1 != *it2) {
                return false;
            }
            it1++;
            it2++;
        }
        
        return true;
    }
};