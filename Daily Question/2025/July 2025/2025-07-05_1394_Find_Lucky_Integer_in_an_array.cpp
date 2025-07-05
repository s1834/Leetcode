class Solution {
public:
    int findLucky(vector<int>& arr) {
        map<int, int> mp;
        for(auto x : arr) mp[x]++;
        int ans = -1;
        for(auto x : mp) if(x.first == x.second) ans = x.first;
        return ans;
    }
};

/*
1) map all the elements
2) iterate through the map and check if the key is equal to its value
3) if it is, update ans with the key and if multiple keys are equal to their values, then we need to return the largetst of them and as maps is sorted in ascending order, we always get the largest key at the end of the map
4) return ans
*/