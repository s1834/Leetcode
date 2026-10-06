class Solution {
    public:
        vector<int> separateDigits(vector<int>& nums) {
            vector<int> ans;
            for(auto x : nums) {
                stack<int> st;
                while(x) {
                    st.push(x % 10);
                    x /= 10;
                }
                
                while(!st.empty()) {
                    ans.push_back(st.top());
                    st.pop();
                }
            }
    
            return ans;
        }
    };

/*
    ============================================================
    LeetCode 2553 - Separate the Digits in an Array
    ============================================================

    Approach: Digit Extraction + Stack
    ------------------------------------------------------------

    We need to separate every digit of every number in `nums`
    and append those digits to the answer in their original
    left-to-right order.

    The main issue is that repeatedly using:

        x % 10

    extracts digits from RIGHT to LEFT.

    A stack is used to reverse this order back to the original
    left-to-right order.

    ============================================================
    1. Process Every Number
    ============================================================

    For every number `x` in `nums`, we create a separate stack:

        stack<int> st;

    We then extract its digits one by one.

    ============================================================
    2. Extract Digits
    ============================================================

    The last digit of a number can be obtained using:

        x % 10

    After extracting it, we remove the last digit using:

        x /= 10

    Example:

        x = 1234

        x % 10 -> 4
        x /= 10 -> 123

        x % 10 -> 3
        x /= 10 -> 12

        x % 10 -> 2
        x /= 10 -> 1

        x % 10 -> 1

    The digits are therefore extracted as:

        4, 3, 2, 1

    which is the reverse of what we need.

    So instead of directly adding them to `ans`, we push them
    into the stack.

        st.push(x % 10);

    ============================================================
    3. Use the Stack to Restore the Order
    ============================================================

    A stack follows LIFO:

        Last In -> First Out

    For:

        1234

    the stack receives:

        push 4
        push 3
        push 2
        push 1

    So the stack looks conceptually like:

        1  <- top
        2
        3
        4

    Popping now gives:

        1, 2, 3, 4

    which is exactly the original digit order.

    Therefore:

        while(!st.empty()) {
            ans.push_back(st.top());
            st.pop();
        }

    transfers the digits into `ans` in the correct order.

    ============================================================
    4. Example
    ============================================================

    Suppose:

        nums = [13, 25]

    Process 13:

        Extract:
            3 -> push
            1 -> push

        Pop:
            1
            3

        ans = [1, 3]

    Process 25:

        Extract:
            5 -> push
            2 -> push

        Pop:
            2
            5

        ans = [1, 3, 2, 5]

    Final answer:

        [1, 3, 2, 5]

    ============================================================
    5. Why Does This Work?
    ============================================================

    Every number is processed independently.

    For each number:

        1. `% 10` extracts digits from right to left.
        2. The stack stores these digits in that same order.
        3. Popping the stack reverses the order.
        4. The digits are appended to `ans`.

    Since the numbers themselves are processed from left to
    right in `nums`, the final answer also preserves the
    required ordering between different numbers.

    ============================================================
    Complexity Analysis
    ============================================================

    Let D be the total number of digits across all numbers.

    Time Complexity: O(D)

        Every digit is:
            - pushed onto the stack once
            - popped from the stack once

    Space Complexity: O(D) worst case

        The stack can contain all digits of the current number.

        The output vector `ans` also contains D digits, but this
        is output space rather than auxiliary working space.

        Auxiliary space: O(log(max(nums[i]))) for the stack.

    ============================================================
    Core Idea
    ============================================================

    `% 10` gives digits from right to left.

    Use a stack to reverse that order:

        number -> extract digits -> stack -> pop digits

    This produces the digits in their original left-to-right
    order and appends them to the final answer.
    ============================================================
*/