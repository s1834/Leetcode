class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        priority_queue<pair<int,int>> maxHeap;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
        int l = 0, maxLen = 0, n = nums.size();
        for (int r = 0; r < n; r++) {
            maxHeap.push({nums[r], r});
            minHeap.push({nums[r], r});

            while(maxHeap.top().first - minHeap.top().first > limit) {
                l = min(maxHeap.top().second, minHeap.top().second) + 1;
                while(maxHeap.top().second < l) {
                    maxHeap.pop();
                }
                while(minHeap.top().second < l) {
                    minHeap.pop();
                }
            }
            maxLen = max(maxLen, r - l + 1);
        }
        return maxLen;
    }
};