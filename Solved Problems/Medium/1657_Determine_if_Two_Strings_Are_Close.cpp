class Solution {
public:
    bool closeStrings(string word1, string word2) {
        map<char, int> mp1, mp2;
        int n1 = word1.size(), n2 = word2.size();
        if(n1 != n2) {
            return false;
        }

        set<char> s1, s2;
        for (int i = 0; i < n1; i++) {
            mp1[word1[i]]++;
            s1.insert(word1[i]);
        }
        for (int i = 0; i < n2; i++) {
            mp2[word2[i]]++;
            s2.insert(word2[i]);
        }

        if(mp1.size() != mp2.size()) {
            return false;
        }

        for(auto x1 = mp1.begin(), x2 = mp2.begin(); x1 != mp1.end(); ++x1, ++x2) {
            if(x1->first != x2->first) {
                return false;
            }
        }

        vector<int> v1, v2;
        auto it1 = s1.begin(), it2 = s2.begin();
        n1 = s1.size();
        for (int i = 0; i < n1; i++) {
            v1.push_back(mp1[*it1]);
            it1++;
        }
        n2 = s2.size();
        for (int i = 0; i < n2; i++) {
            v2.push_back(mp2[*it2]);
            it2++;
        }

        n1 = v1.size();
        n2 = v2.size();
        if(n1 != n2) {
            return false;
        }

        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());
        for (int i = 0; i < n1; i++) {
            if(v1[i] != v2[i]) {
                return false;
            }
        }
        
        return true;
    }
};