class Solution {
    public:
        vector<int> recoverOrder(vector<int>& order, vector<int>& friends) {
            set<int> st;
            for(auto x : friends) st.insert(x);
            vector<int> ans;
            for(auto x : order) {
                if(st.find(x) != st.end()) ans.push_back(x);
            }
    
            return ans;
        }
    };

/*

Idea:
------
We need to recover the order of only those friends that appear in
the given `friends` list while preserving their relative order from
the original `order` array.

Approach:
---------
1. Insert all friend IDs into a set for fast lookups.
2. Traverse the `order` array from left to right.
3. For each ID:
   - If it exists in the set, add it to the answer.
4. Return the resulting list.

Since we iterate through `order` only once, the relative ordering of
the selected friends is preserved.

Example:
--------
order   = [3, 1, 2, 5, 4]
friends = [2, 3, 4]

Set:
{2, 3, 4}

Traverse order:

3 -> present -> ans = [3]
1 -> not present
2 -> present -> ans = [3, 2]
5 -> not present
4 -> present -> ans = [3, 2, 4]

Output:

[3, 2, 4]

Time Complexity:
----------------
O(n log m)

n = size of order
m = size of friends

- Building the set: O(m log m)
- Each lookup: O(log m)

Space Complexity:
-----------------
O(m)

*/