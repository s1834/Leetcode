class FindSumPairs {
    private:
        vector<int> num1, num2;
    public:
        FindSumPairs(vector<int>& nums1, vector<int>& nums2) {
            num1 = nums1;
            num2 = nums2;
        }
        
        void add(int index, int val) {
            num2[index] += val;
        }
        
        int count(int tot) {
            int n = num1.size(), m = num2.size(), cnt = 0;
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++) {
                    if(num1[i] + num2[j] == tot) cnt++;
                }
            }
            return cnt;
        }
    };
    
    /**
     * Your FindSumPairs object will be instantiated and called as such:
     * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
     * obj->add(index,val);
     * int param_2 = obj->count(tot);
     */