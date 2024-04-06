class Solution {
public:
    bool equalFrequency(string word) {
        map<char, int> mp;
        int n = word.size();
        for(int i = 0; i < n; i++) {
            mp[word[i]]++;
        }

        if(mp.size() == 1) {
            return true;
        }

        map<int, int> mpCount;
        for(auto x : mp) {
            mpCount[x.second]++;
        }

        if(mpCount.size() == 1 && mp[word[0]] == 1) {
            return true;
        }

        if(mpCount.size() != 2) {
            return false;
        }
 
        vector<int> v;
        int count = 0;
        for(auto x : mpCount) {
            v.push_back(x.first);
            if(x.second > 1) {
                count++;
            }
            if(x.second == 1) {
                if((v.size() == 2 && abs(v[0] - v[1]) == 1) || (v.size() == 1 && x.first == 1)) {
                    return true;
                }
            }
            if (count == 2) {
                return false;
            }
        }

        if(abs(v[0] * mpCount[v[0]] - v[1] * mpCount[v[1]]) != 1) {
            return false;
        } 
        
        return true;
    }
};