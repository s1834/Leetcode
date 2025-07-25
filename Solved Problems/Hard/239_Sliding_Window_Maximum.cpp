class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        set<pair<int, int>> pq;
        for(int i = 0; i < k; i++) pq.insert({nums[i], i});
        
        vector<int> ans;
        pair<int, int> p = *pq.rbegin();
        ans.push_back(p.first);
        
        int l = 0, r = k - 1, n = nums.size();
        while(++r < n) {
            auto found = pq.find({nums[l], l});
            if(found != pq.end()) pq.erase(found);
            pq.insert({nums[r], r});
            p = *pq.rbegin();
            ans.push_back(p.first);
            l++;
        }

        return ans;
    }
};

/*
Version 1:
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        priority_queue<int> pq;
        for(int i = 0; i < k; i++) pq.push(nums[i]);

        int l = 0, r = k - 1, n = nums.size();
        vector<int> ans;
        ans.push_back(pq.top());

        while(++r < n) {
            if(nums[l] == pq.top() || nums[r] > pq.top()) {
                priority_queue<int> temp;
                for(int i = l + 1; i <= r; i++) temp.push(nums[i]);
                ans.push_back(temp.top());
                pq.swap(temp);
            } else ans.push_back(pq.top());
            
            l++;
        }
        return ans;
    }
};

first I tried to use a priority queue, but it was not efficient enough for large inputs as it would again and agin calculate the maximum for the current window.

Verion 2:
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        set<int> pq;
        for(int i = 0; i < k; i++) pq.insert(nums[i]);
        
        vector<int> ans;
        ans.push_back(*pq.rbegin());
        
        int l = 0, r = k - 1, n = nums.size();
        while(++r < n) {
            pq.erase(pq.find(nums[l]));
            pq.insert(nums[r]);
            ans.push_back(*pq.rbegin());
            l++;
        }

        return ans;
    }
};

then I thought of using a set as a priority queue to store the elements of the current window, which would allow me to efficiently find the maximum element. However, this still had some issue as if the set is empty, it was still trying to find and erase elements, which lead runtime errors.

Version 3:
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        set<int> pq;
        for(int i = 0; i < k; i++) pq.insert(nums[i]);
        
        vector<int> ans;
        ans.push_back(*pq.rbegin());
        
        int l = 0, r = k - 1, n = nums.size();
        while(++r < n) {
            auto found = pq.find(nums[l]);
            if(found != pq.end()) pq.erase(found);
            pq.insert(nums[r]);
            ans.push_back(*pq.rbegin());
            l++;
        }

        return ans;
    }
};

Here i managed the runtime error by checking if the element to be erased is actually present in the set. But this had the issue as in set we dont store similar values, so for example:
nums = [-7,-8,7,5,7,1,6,0]
k = 4
the output was [7, 7, 7, 6, 6] 
instead of [7, 7, 7, 7, 7] 
which meant even if there was a greater element in the current window it already erased it by nums[l], which led to issues in further windows.

Final Version:
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        set<pair<int, int>> pq;
        for(int i = 0; i < k; i++) pq.insert({nums[i], i});
        
        vector<int> ans;
        pair<int, int> p = *pq.rbegin();
        ans.push_back(p.first);
        
        int l = 0, r = k - 1, n = nums.size();
        while(++r < n) {
            auto found = pq.find({nums[l], l});
            if(found != pq.end()) pq.erase(found);
            pq.insert({nums[r], r});
            p = *pq.rbegin();
            ans.push_back(p.first);
            l++;
        }

        return ans;
    }
};

Here I used a set of pairs to store both the value and its index, which allowed me to efficiently find and erase elements without losing track of duplicates. This way, I could always ensure that the maximum element in the current window was correctly identified, even if there were duplicates in the window.
*/