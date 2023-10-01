class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size(), ten = n - 1;
        long long int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += digits[i] * pow(10, ten);
            ten--;
        }
        sum++;
        vector<int> vec;
        while(sum) {
            vec.push_back(sum % 10);
            sum /= 1class Solution {
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
                carry++;
            } else if (carry) {
                digits[i] += carry;
                break;
            }
        }
        reverse(digits.begin(), digits.end());
        return digits;
    }
};0;
        }
        reverse(vec.begin(), vec.end());
        return vec;
    }
};