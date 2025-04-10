class Solution {
    private:
        int left(vector<int> v) {
            if(v.size() == 1) return v[0];
            vector<int> temp;
            int n = v.size();
            for(int i = 1; i < n; i += 2) temp.push_back(v[i]);
            return right(temp);
        }
    
        int right(vector<int> v) {
            if(v.size() == 1) return v[0];
            vector<int> temp;
            int n = v.size();
            for(int i = n - 2; i >= 0; i -= 2) temp.push_back(v[i]);
            reverse(temp.begin(), temp.end());
            return left(temp);
        }
    
    public:
        int lastRemaining(int n) {
            if(n == 1) return 1;
            vector<int> v;
            for(int i = 2; i <= n; i += 2) v.push_back(i);
            return right(v);
        }
    };