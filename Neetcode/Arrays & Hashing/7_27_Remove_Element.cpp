class Solution {
    public:
        int removeElement(vector<int>& nums, int val) {
            int i = 0, n = nums.size();
            while(i < n) {
                if(nums[i] == val) nums[i] = nums[--n];
                else i++;
            }
            return n;
        }
    };

/*
    LeetCode 27: Remove Element

    Approach: Two Pointers (In-place Replacement)

    Intuition:
    We need to remove all occurrences of `val` from the array in-place.
    The order of the remaining elements does not matter, so whenever
    we encounter `val`, we can replace it with the last element of the
    current valid portion of the array.

    This avoids shifting elements and allows us to remove elements in
    O(1) time per occurrence.

    Variables:
    - i: Index used to examine the current element.
    - n: Represents the current size of the valid portion of the array.
         It also becomes the final number of elements not equal to `val`.

    Step-by-Step Explanation:

    1. Initialize `i = 0` and `n = nums.size()`.

    2. Iterate while `i < n`:
       - If `nums[i] == val`:
         a. Decrease `n` to exclude the last element from the valid portion.
         b. Replace `nums[i]` with `nums[n]`, the last element of the
            remaining valid portion.
         c. Do NOT increment `i`, because the newly swapped element
            has not been checked yet. It might also be equal to `val`.

       - Otherwise:
         a. The current element is valid.
         b. Increment `i` to examine the next element.

    3. Once `i == n`, every element in the range [0, n) is different
       from `val`.

    4. Return `n`, which is the number of elements that should remain.

    Example Walkthrough:

    nums = [3, 2, 2, 3], val = 3

    Initially:
    i = 0, n = 4

    Iteration 1:
    nums[0] == 3
    Decrease n to 3.
    Replace nums[0] with nums[3].

    Array: [3, 2, 2, 3]
            ^
    The replacement is also 3, so check the same index again.

    Iteration 2:
    nums[0] == 3
    Decrease n to 2.
    Replace nums[0] with nums[2].

    Array: [2, 2, 2, 3]
            ^
    Do not increment i yet.

    Iteration 3:
    nums[0] == 2
    It is valid, so increment i to 1.

    Iteration 4:
    nums[1] == 2
    It is valid, so increment i to 2.

    Now i == n, so the loop terminates.

    Final valid portion: [2, 2]
    Returned length: 2

    Why It Works:
    - Every time we find `val`, we shrink the valid portion by one.
    - The element moved from the end is checked again before proceeding.
    - We increment `i` only when the current element is valid.
    - Therefore, when the loop terminates, every element in [0, n)
      is different from `val`.

    Complexity Analysis:
    - Time Complexity: O(n)
      Each iteration either advances `i` or decreases `n`.
      Both can happen at most n times.

    - Space Complexity: O(1)
      All modifications happen directly in the input array, using
      only two variables.

    Core Idea:
    Replace unwanted elements with elements from the end of the array,
    shrinking the valid portion instead of shifting elements.
*/