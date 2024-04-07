class Solution {
public:
    string addBinary(string a, string b) {
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());

        int n1 = a.size(), n2 = b.size();
        int n = n1 < n2 ? n1 : n2;
        string ans = "";
        char carry = '0';
        for(int i = 0; i < n; i++) {
            if(a[i] == '1' && b[i] == '1') {
                if(carry == '1') {
                    ans += '1';
                } else {
                    ans += '0';
                    carry = '1';
                }
            } else if((a[i] == '1' && b[i] == '0') || (a[i] == '0' && b[i] == '1')) {
                if(carry == '1') {
                    ans += '0';
                } else {
                    ans += '1';
                }
            } else {
                if(carry == '1') {
                    ans += '1';
                    carry = '0';
                } else {
                    ans += '0';
                }
            }
        }
        int size;
        if(n1 > n2) {
            size = n1;
        } else {
            size = n2;
            a = b;
        }
        for (int i = n; i < size; i++) {
            if(a[i] == '1' && carry == '1') {
                ans += '0';
            } else if ((a[i] == '1' && carry == '0') || (a[i] == '0' && carry == '1')) {
                ans += '1';
                carry = '0';
            } else {
                ans += '0';
            }
        }
        if(carry == '1') {
            ans += '1';
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};