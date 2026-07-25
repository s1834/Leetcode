class Solution {
    public:
        int maxProduct(int n) {
            vector<int> ans;
            while(n) {
                ans.push_back(n % 10);
                n /= 10;
            }
    
            sort(ans.begin(), ans.end(), greater<int>());
            return ans[0] * ans[1];
        }
    };