class Solution {
public:
    string maxValue(string n, int x) {
        int size = n.size(), insert = 1;
        string ans = "";
        if(n[0] == '-') {
            ans += "-";
            for(int i = 1; i < size; i++) {
                if(insert && n[i] - '0' >= x) {
                    ans += to_string(x);
                    insert = 0;
                }
                ans += n[i];
            }
        } else {
            for(int i = 0; i < size; i++) {
                if(insert && n[i] - '0' < x) {
                    ans += to_string(x);
                    insert = 0;
                }
                ans += n[i];
            }
        }

        if(insert) {
            ans += to_string(x);
        }

        return ans;
    }
};