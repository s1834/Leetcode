class Solution {
    public:
        int majorityElement(vector<int>& nums) {
            unordered_map<int, int> mp;
            int n = nums.size();
            for(int i = 0; i < n; i++) {
                mp[nums[i]]++;
                if(mp[nums[i]] > n / 2) return nums[i];
            }
            return -1;
        }
    };

/*
    LeetCode 169: Majority Element

    Approach: Hash Map (Frequency Counting)

    Intuition:
    We need to find the element that appears more than n / 2 times
    in the given array.

    Since the majority element occurs more than half the size of
    the array, there can be at most one such element.

    We use an unordered_map to maintain the frequency of each element.
    While traversing the array, we update the frequency of the current
    element and immediately check whether it has crossed the majority
    threshold.

    If its frequency becomes greater than n / 2, we have found the
    majority element and can return it without processing the
    remaining elements.

    Step-by-Step Explanation:

    1. Create an unordered_map:
           unordered_map<int, int> mp;

       - Key: Element from the array.
       - Value: Number of times that element has appeared so far.

    2. Store the size of the array in `n`.

    3. Traverse the array using index `i`.

    4. For every element:
           mp[nums[i]]++;

       Increment its frequency in the hash map.

    5. Check whether the current element has become the majority:
           if(mp[nums[i]] > n / 2)

       If its frequency is greater than half the array size, return
       that element immediately.

    6. If the loop finishes without finding a majority element,
       return -1.

       Note: The problem guarantees that a majority element exists,
       so this return statement is only a fallback.

    Example Walkthrough:

    nums = [2, 2, 1, 1, 1, 2, 2]

    n = 7
    Majority threshold = n / 2 = 3

    Iteration 1:
        Element = 2
        mp[2] = 1
        1 is not greater than 3.

    Iteration 2:
        Element = 2
        mp[2] = 2
        2 is not greater than 3.

    Iteration 3:
        Element = 1
        mp[1] = 1
        1 is not greater than 3.

    Iteration 4:
        Element = 1
        mp[1] = 2
        2 is not greater than 3.

    Iteration 5:
        Element = 1
        mp[1] = 3
        3 is not greater than 3.

    Iteration 6:
        Element = 2
        mp[2] = 3
        3 is not greater than 3.

    Iteration 7:
        Element = 2
        mp[2] = 4
        4 is greater than 3.

    Return 2.

    Why It Works:
    The hash map maintains the exact frequency of every element
    encountered so far.

    Whenever an element's frequency exceeds n / 2, it satisfies
    the definition of a majority element.

    Since a majority element is guaranteed to exist, the algorithm
    will eventually encounter and return it.

    Complexity Analysis:
    - Time Complexity: O(n) average
      We traverse the array once. Hash map insertion and lookup
      take O(1) average time.

    - Space Complexity: O(n)
      In the worst case, all elements are distinct, so the hash map
      can store up to n different elements.

    Core Idea:
    Count the frequency of each element while traversing the array.
    Return immediately when an element appears more than n / 2 times.
*/