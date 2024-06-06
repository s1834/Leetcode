class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        int n = nums.size();
        if(n % k != 0) {
            return false;
        }
        if(k == 1) {
            return true;
        }

        map<int, int> mp;
        for(int i = 0; i < n; i++) {
            mp[nums[i]]++;
        }

        int temp, prev;
        while(mp.size() != 0) {
            temp = k;
            for (auto& x : mp) {
                temp--;
                if (temp == -1) {
                    break;
                }
                if(temp <= k - 2) {
                    if(prev + 1 != x.first) {
                        return false;
                    }
                    x.second--;
                    prev = x.first;

                } else {
                    x.second--;
                    prev = x.first;
                }
                if(mp.size() == 1 && x.second > 0) {
                    return 0;
                }
                if(x.second == 0) {
                    mp.erase(x.first);
                } 
            }
        }

        return true;
    }
};