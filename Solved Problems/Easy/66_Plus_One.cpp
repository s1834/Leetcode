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
            sum /= 10;
        }
        reverse(vec.begin(), vec.end());
        return vec;
    }
};