class Solution {
public:
    bool threeConsecutiveOdds(vector<int>& arr) {
        int n = arr.size(), count = 0;
        for(int i = 0; i < n; i++) {
            if(count == 3) return true;
            if(arr[i] % 2 == 0) count = 0;
            else count++;
        }   
        return false;
    }
};