class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        // int n = hand.size();
        // if(n % groupSize != 0) {
        //     return false;
        // }

        // map<int, int> mp;
        // for(int i = 0; i < n; i++) {
        //     mp[hand[i]]++;
        // }

        // bool notOne = true;
        // while(notOne) {
        //     notOne = false;
        //     for (auto& x : mp) {
        //         x.second--;
        //         if(x.second > 1) {
        //             notOne = true;
        //         }
        //     }
        // }
        
        // vector<int> v;
        // for (auto x : mp) {
        //     if(x.second == 1) {
        //         v.push_back(x.first);
        //     }
        // }

        // n = v.size();
        // if(n <= 1) {
        //     return true;
        // }

        // for (int i = 0; i < n - 1; i++) {
        //     if(v[i + 1] != v[i] + 1) {
        //         return false;
        //     }
        // }

        // return true;

         int n = hand.size();
        if(n % groupSize != 0) {
            return false;
        }

        map<int, int> mp;
        for(int i = 0; i < n; i++) {
            mp[hand[i]]++;
        }

        bool notOne = true;
        int temp, prev;
        while(notOne) {
            notOne = false;
            temp = groupSize;
            cout<< "again\n";
            for (auto& x : mp) {
                temp--;
                if (temp == -1) {
                    break;
                }
                cout << x.first << ' ' << x.second<<endl;
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
                if(x.second >= 1) {
                    notOne = true;
                }
                if(x.second == 0) {
                    mp.erase(x.first);
                } 
            }
        }
        
        // vector<int> v;
        // for (auto x : mp) {
        //     if(x.second == 1) {
        //         v.push_back(x.first);
        //     }
        // }

        // n = v.size();
        // if(n <= 1) {
        //     return true;
        // }

        // for (int i = 0; i < n - 1; i++) {
        //     if(v[i + 1] != v[i] + 1) {
        //         return false;
        //     }
        // }

        return true;
    }
};