class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        map<int, int> mp;
        int n = arr1.size();
        for (int i = 0; i < n; i++) {
            mp[arr1[i]]++;
        }
        
        int ind = 0;
        n = arr2.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < mp[arr2[i]]; j++) {
                arr1[ind] = arr2[i];
                ind++;
            }
            mp[arr2[i]] = 0;
        }

        for (auto x:mp) {
            if (x.second != 0) {
                for (int i = 0; i < x.second; i++) {
                    arr1[ind] = x.first;
                    ind++;
                }
            }
        }

        return arr1;
    }
};