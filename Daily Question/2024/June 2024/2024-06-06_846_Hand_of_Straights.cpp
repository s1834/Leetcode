class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        int n = hand.size();
        if(n % groupSize != 0) {
            return false;
        }

        map<int, int> mp;
        for(int i = 0; i < n; i++) {
            mp[hand[i]]++;
        }

        int temp, prev;
        while(mp.size() != 0) {
            temp = groupSize;
            for (auto& x : mp) {
                temp--;
                if (temp == -1) {
                    break;
                }
                if(temp <= groupSize - 2) {
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