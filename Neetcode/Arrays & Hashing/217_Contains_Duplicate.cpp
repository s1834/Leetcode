class Solution {
    public:
        bool containsDuplicate(vector<int>& nums) {
            unordered_set<int> st;
            for(auto &num : nums) {
                if(st.find(num) != st.end()) return true;
                st.insert(num);
            }
            return false;
        }
    };

/*
    LeetCode 217: Contains Duplicate

    Approach: Hash Set

    Intuition:
    We need to determine whether the given array contains any duplicate
    elements.

    Instead of comparing every pair of elements, we use an unordered_set
    to keep track of the elements we have already visited.

    Since an unordered_set stores only unique elements and provides
    average O(1) lookup and insertion, we can efficiently detect duplicates
    in a single traversal.

    Step-by-Step:
    1. Create an unordered_set `st` to store the elements encountered so far.
    2. Iterate through every element in `nums`:
       - Check whether the current element already exists in the set.
       - If it exists, we have encountered this element before, so a
         duplicate is present. Return true immediately.
       - Otherwise, insert the current element into the set.
    3. If the entire array is traversed without finding a duplicate,
       return false.

    Example:
        nums = [1, 2, 3, 1]

        Initially:
            st = {}

        num = 1:
            1 is not present -> insert 1
            st = {1}

        num = 2:
            2 is not present -> insert 2
            st = {1, 2}

        num = 3:
            3 is not present -> insert 3
            st = {1, 2, 3}

        num = 1:
            1 is already present -> return true

        Output: true

    Another Example:
        nums = [1, 2, 3, 4]

        Every element is encountered only once.
        The loop completes without finding a duplicate.

        Output: false

    Complexity Analysis:
    - Time Complexity: O(n) on average
      We traverse the array once. Each unordered_set lookup and insertion
      takes O(1) time on average.
      In the worst case, hash collisions can make operations take O(n),
      resulting in O(n^2) worst-case time.

    - Space Complexity: O(n)
      In the worst case, all elements are unique, so the set stores all
      n elements.

    Core Idea:
    Maintain a set of previously visited elements.
    If an element is already present, a duplicate exists.
    Otherwise, insert it and continue.
*/