class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        int count = 0, n = arr.size();
        if (n == 1) {
            return true;
        }
        vector<int> v;
        for (int i = 0; i < n; i++) {
            if (i == n - 1) {
                v.push_back(count + 1);
                break;
            }
            if (arr[i] != arr[i + 1]) {
                v.push_back(count + 1);
                count = 0;
            } else {
                count++;
            }
        }
        n = v.size();
        sort(v.begin(), v.end());
        for (int i = 0; i < n - 1; i++) {
            if (v[i] == v[i + 1]) {
                return false;
            }
        }
        return true;
    }
};