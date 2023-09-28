class Solution {
public:
    string thousandSeparator(int n) {
        if (n == 0) {
            return "0";
        } 
        
        string s = "";
        int count = 0;
        while (n) {
            if (count == 3) {
                s += '.';
                count = 0;
            }
            s.push_back('0' + n % 10);
            count++;
            n /= 10;
        }
        reverse(s.begin(), s.end());
        return s;
    }
};