class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        reverse(digits.begin(), digits.end());
        int n = digits.size(), carry = 1;
        for (int i = 0; i < n; i++) {
            if (i == n - 1 && digits[i] == 9) {
                digits[i] = 0;
                digits.push_back(1);
            } else if (digits[i] == 9) {
                digits[i] = 0;
                carry = 1;
            } else if (carry) {
                digits[i] += carry;
                break;
            }
        }
        reverse(digits.begin(), digits.end());
        return digits;
    }
};