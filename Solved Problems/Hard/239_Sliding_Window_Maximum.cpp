// version 3: deque
class Solution {
    public:
        vector<int> maxSlidingWindow(vector<int>& nums, int k) {
            vector<int> ans;
            deque<int> q;
            for(int i = 0; i < k; i++) {
                while (!q.empty() && nums[q.back()] < nums[i]) q.pop_back();
                q.push_back(i);
            }
            ans.push_back(nums[q.front()]);
    
            int n = nums.size();
            for(int i = k; i < n; i++) {
                while (!q.empty() && q.front() <= i - k) q.pop_front();
                while (!q.empty() && nums[q.back()] < nums[i]) q.pop_back();
                q.push_back(i);
                ans.push_back(nums[q.front()]);
            }
            
            return ans;
        }
    };

/*
Idea:
------
We need to find the maximum element in every contiguous subarray
(window) of size k.

A brute-force approach would scan every window separately,
resulting in O(n * k) time.

Instead, we use a Monotonic Deque to obtain the maximum of every
window in O(n) time.

--------------------------------------------------------------------

Monotonic Deque:
----------------

The deque stores INDICES of elements, not the values themselves.

The indices are maintained such that their corresponding values are
always in decreasing order.

Example:

nums = [5, 3, 4]

Deque:

Index : 0  2

Value : 5  4

The front of the deque always stores the index of the largest
element in the current window.

--------------------------------------------------------------------

Why store indices instead of values?
------------------------------------

Indices allow us to determine whether an element is still inside the
current sliding window.

If

index <= i - k

then that element has moved out of the current window and must be
removed.

Using only values would not tell us whether an element has expired.

--------------------------------------------------------------------

Why remove elements from the back?
----------------------------------

Suppose the deque currently contains:

Value:

8  6  4

Now we process:

10

Since 10 is greater than every element at the back,

8  6  4

can never become the maximum of any future window containing 10.

Therefore, all smaller elements are removed before inserting 10.

After insertion:

10

The deque always remains in decreasing order.

--------------------------------------------------------------------

Why remove elements from the front?
-----------------------------------

The front always stores the maximum element.

However, if its index lies outside the current window,

index <= i - k

it can no longer contribute to the answer and must be removed.

--------------------------------------------------------------------

Algorithm:
----------

1. Process the first k elements.
   - Remove smaller elements from the back.
   - Insert the current index.
   - After processing the first window, the front stores the maximum.

2. For every remaining element:
   - Remove expired indices from the front.
   - Remove all smaller elements from the back.
   - Insert the current index.
   - The front of the deque is the maximum for the current window.

3. Repeat until every window has been processed.

--------------------------------------------------------------------

Dry Run:
--------

nums = [1, 3, -1, -3, 5, 3, 6, 7]

k = 3

------------------------------------------------

First window:

[1, 3, -1]

Deque:

3, -1

Maximum:

3

------------------------------------------------

Slide window:

[3, -1, -3]

Remove expired indices.

Insert -3.

Deque:

3, -1, -3

Maximum:

3

------------------------------------------------

Slide window:

[-1, -3, 5]

3 leaves the window.

Remove smaller elements (-1 and -3) because 5 is larger.

Deque:

5

Maximum:

5

Continue similarly for the remaining windows.

Final Answer:

[3, 3, 5, 5, 6, 7]

--------------------------------------------------------------------

Why does this work?
-------------------

The deque always satisfies two properties:

1. Indices are within the current window.
2. Their corresponding values are stored in decreasing order.

Therefore, the front of the deque is always the maximum element of
the current window.

Each element is:
- Inserted exactly once.
- Removed at most once.

Hence, every element is processed a constant number of times.

--------------------------------------------------------------------

Time Complexity:
----------------

O(n)

Each index is pushed once and popped at most once.

--------------------------------------------------------------------

Space Complexity:
-----------------

O(k)

The deque stores at most k indices.
*/

// version 2: 
// class Solution {
// public:
//     vector<int> maxSlidingWindow(vector<int>& nums, int k) {
//         set<pair<int, int>> pq;
//         for(int i = 0; i < k; i++) pq.insert({nums[i], i});
        
//         vector<int> ans;
//         pair<int, int> p = *pq.rbegin();
//         ans.push_back(p.first);
        
//         int l = 0, r = k - 1, n = nums.size();
//         while(++r < n) {
//             auto found = pq.find({nums[l], l});
//             if(found != pq.end()) pq.erase(found);
//             pq.insert({nums[r], r});
//             p = *pq.rbegin();
//             ans.push_back(p.first);
//             l++;
//         }

//         return ans;
//     }
// };

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