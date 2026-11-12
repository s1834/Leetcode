class Solution {
    public:
        string trafficSignal(int timer) {
            if(timer == 0) return "Green";
            if(timer == 30) return "Orange";
            if(timer > 30 && timer <= 90) return "Red";
            return "Invalid";
        }
    };

/*
    LeetCode 3894: Maximum Number of ... (Traffic Signal)

    Approach: Conditional Statements

    Intuition:
    We are given a timer value and need to determine the corresponding
    traffic signal color based on predefined conditions.

    The function handles four possible cases:
        - timer == 0       -> "Green"
        - timer == 30      -> "Orange"
        - 30 < timer <= 90 -> "Red"
        - Any other value  -> "Invalid"

    Step-by-Step Explanation:

    1. Check for Green:
        if(timer == 0) return "Green";

       If the timer is exactly 0, the traffic signal is Green.
       We immediately return the corresponding string.

    2. Check for Orange:
        if(timer == 30) return "Orange";

       If the timer is exactly 30, return "Orange".

    3. Check for Red:
        if(timer > 30 && timer <= 90) return "Red";

       The signal is Red when the timer is:
           - Strictly greater than 30.
           - Less than or equal to 90.

       Both conditions must be satisfied.

    4. Handle invalid values:
        return "Invalid";

       If none of the previous conditions match, the timer does not
       correspond to any valid signal state, so we return "Invalid".

    Example:
        timer = 0
            Output: "Green"

        timer = 30
            Output: "Orange"

        timer = 60
            Output: "Red"

        timer = 90
            Output: "Red"

        timer = 100
            Output: "Invalid"

    Complexity Analysis:

    - Time Complexity: O(1)
      We perform a constant number of conditional checks.

    - Space Complexity: O(1)
      No additional data structures are used. The function returns
      one of a fixed set of strings.

    Core Idea:
    Use sequential conditional checks to map the timer value to
    its corresponding traffic signal color.
*/