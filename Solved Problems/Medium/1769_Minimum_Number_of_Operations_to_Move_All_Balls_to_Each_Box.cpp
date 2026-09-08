class Solution {
    public:
        vector<int> minOperations(string boxes) {
            int n = boxes.size();
            vector<int> pos;
            for(int i = 0; i < n; i++) {
                if(boxes[i] == '1') pos.push_back(i);
            }
    
            vector<int> ans;
            for(int i = 0; i < n; i++) {
                int sum = 0;
                for(auto &x : pos) sum += abs(x - i);
                ans.push_back(sum);
            }
    
            return ans;
        }
    };

/*
    Approach:
    ------------------------------------------------------------
    The problem asks us to find the minimum number of operations
    needed to move all balls to each box.

    In one operation, we can move a ball from one box to an
    adjacent box.

    Therefore, if a ball is at position x and we want to move it
    to position i, the number of operations required is:

        |x - i|

    So for every destination box i, we simply need to calculate
    the total distance from i to every box that currently contains
    a ball.



    ------------------------------------------------------------
    Key Observation:
    ------------------------------------------------------------

    Only boxes containing a ball matter.

    Instead of checking every box for every destination, we first
    store the positions of all balls in:

        pos

    For example:

        boxes = "11010"

    Ball positions are:

        pos = {0, 1, 3}

    Now, if we want to move all balls to box i, the total number of
    operations is:

        |0 - i| + |1 - i| + |3 - i|



    ------------------------------------------------------------
    Why Distance Equals Number of Operations:
    ------------------------------------------------------------

    Moving a ball from box x to box i requires moving it one box
    at a time.

    For example:

        x = 2
        i = 5

    We need:

        2 -> 3
        3 -> 4
        4 -> 5

    which requires 3 operations.

    This is exactly:

        |2 - 5| = 3

    Therefore, for every ball at position x, its contribution to
    destination i is:

        abs(x - i)



    ------------------------------------------------------------
    Data Structure:
    ------------------------------------------------------------

    `pos`

    stores the index of every box containing a ball.

    This allows us to directly iterate only over balls instead of
    checking whether every box contains a ball repeatedly.



    ------------------------------------------------------------
    Algorithm:
    ------------------------------------------------------------

    1. Traverse the string.

    2. Whenever:

           boxes[i] == '1'

       store i in `pos`.

    3. For every possible destination box i:
       - Initialize `sum = 0`.
       - For every ball position x in `pos`, add:

             abs(x - i)

       - Store the total in `ans`.

    4. Return `ans`.



    ------------------------------------------------------------
    Example:
    ------------------------------------------------------------

    boxes = "110"

    Ball positions:

        pos = {0, 1}



    Destination i = 0:

        |0 - 0| + |1 - 0|
        = 0 + 1
        = 1

    So:

        ans[0] = 1



    Destination i = 1:

        |0 - 1| + |1 - 1|
        = 1 + 0
        = 1

    So:

        ans[1] = 1



    Destination i = 2:

        |0 - 2| + |1 - 2|
        = 2 + 1
        = 3

    So:

        ans[2] = 3



    Final answer:

        [1, 1, 3]



    ------------------------------------------------------------
    Example:
    ------------------------------------------------------------

    boxes = "001011"

    Ball positions:

        pos = {2, 4, 5}



    For destination box 0:

        |2 - 0| + |4 - 0| + |5 - 0|
        = 2 + 4 + 5
        = 11

    For destination box 4:

        |2 - 4| + |4 - 4| + |5 - 4|
        = 2 + 0 + 1
        = 3

    The same calculation is performed for every destination box.



    ------------------------------------------------------------
    Why This Works:
    ------------------------------------------------------------

    For a fixed destination i, every ball can be moved
    independently to i.

    The total number of operations is therefore simply the sum of
    the individual distances.

    Since `pos` contains the position of every ball, the inner loop
    considers every ball exactly once.

    We repeat this for every possible destination box, so the
    resulting value at `ans[i]` is exactly the minimum number of
    operations required to move all balls into box i.



    ------------------------------------------------------------
    Important Detail:
    ------------------------------------------------------------

    We do NOT actually perform any moves.

    We only calculate how many moves would be necessary.

    For a ball at x:

        operations = abs(x - i)

    Therefore the entire problem reduces to calculating the sum of
    these distances for each i.



    ------------------------------------------------------------
    Complexity:
    ------------------------------------------------------------

    Let:

        n = number of boxes
        k = number of balls

    Building `pos` takes:

        O(n)

    For each of the n destination boxes, we iterate over all k
    balls:

        O(n * k)

    Therefore the total time complexity is:

        O(n + n * k)

    Since k <= n, the worst case is:

        O(n^2)



    ------------------------------------------------------------
    Space Complexity:
    ------------------------------------------------------------

    `pos` stores the positions of all balls:

        O(k)

    `ans` stores the answer for every box:

        O(n)

    Therefore:

        O(n)



    ------------------------------------------------------------
    Core Idea:
    ------------------------------------------------------------

    First store the positions of all balls.

    Then for every destination box i, calculate:

        sum(abs(x - i))

    over every ball position x.

    The absolute distance directly represents the number of
    adjacent moves required for that ball.

    Hence, each `ans[i]` is the minimum number of operations needed
    to move all balls into box i.
*/