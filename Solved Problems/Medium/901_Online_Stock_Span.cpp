// Version 1: Monotonic Decreasing Stack
class StockSpanner {
    public:
        stack<pair<int, int>> st;
    
        StockSpanner() {
            
        }
        
        int next(int price) {
            if(st.empty()) st.push({price, 0});
            else {
                int count = 0;
                while(!st.empty() && st.top().first <= price) {
                    count += st.top().second + 1;
                    st.pop();
                }
                st.push({price, count});
            }
            return st.top().second + 1;
        }
    };
    
    /**
     * Your StockSpanner object will be instantiated and called as such:
     * StockSpanner* obj = new StockSpanner();
     * int param_1 = obj->next(price);
     */

/*

Idea:
------
For every stock price, we need to find its span:

Span = Number of consecutive previous days (including today)
       whose price is less than or equal to today's price.

Instead of storing every previous price, we store:

    {price, span_of_that_price - 1}

The second value represents how many previous days this price already
covers. This allows us to skip multiple days at once instead of checking
them one by one.

The stack is maintained in decreasing order of prices.

------------------------------------------------------------

Algorithm:
----------

1. For every incoming price:

2. While the stack is not empty and the top price is less than or equal
   to the current price:

      • The current price dominates that previous price.
      • Add all the days covered by that price:
            count += top.second + 1
      • Remove it from the stack.

3. After removing all smaller/equal prices:

      • Push the current price along with the total number of previous
        days it covers.

4. Return:

      current span = stored_count + 1

   (+1 accounts for today's price.)

------------------------------------------------------------

Example:
--------

Prices:

[100, 80, 60, 70, 60, 75, 85]

Process:

100

Stack:
[(100,0)]

Span = 1

----------------

80

100 > 80

Stack:
[(100,0), (80,0)]

Span = 1

----------------

60

100 > 60
80 > 60

Stack:
[(100,0), (80,0), (60,0)]

Span = 1

----------------

70

60 <= 70

count += 0 + 1 = 1

Push (70,1)

Stack:
[(100,0), (80,0), (70,1)]

Span = 2

----------------

60

Stack:
[(100,0), (80,0), (70,1), (60,0)]

Span = 1

----------------

75

60 <= 75

count = 1

70 <= 75

count += 1 + 1 = 3

Push (75,3)

Stack:
[(100,0), (80,0), (75,3)]

Span = 4

----------------

85

75 <= 85

count = 4

80 <= 85

count += 0 + 1 = 5

Push (85,5)

Stack:
[(100,0), (85,5)]

Span = 6

Final Answer:

[1,1,1,2,1,4,6]

------------------------------------------------------------

Why store the span?
-------------------

Suppose the stack contains:

[(100,0), (80,4)]

The value 4 means:

80 already represents 5 consecutive days.

If a future price (say 90) removes 80, we immediately know that all
those 5 days also belong to 90.

Instead of checking each of those days individually, we simply do:

count += 4 + 1

This is why every price is pushed once and popped once.

------------------------------------------------------------

Time Complexity:
----------------
O(n)

Each price is pushed into the stack once and removed at most once.

------------------------------------------------------------

Space Complexity:
-----------------
O(n)

In the worst case, prices are strictly decreasing, so every price
remains in the stack.

*/