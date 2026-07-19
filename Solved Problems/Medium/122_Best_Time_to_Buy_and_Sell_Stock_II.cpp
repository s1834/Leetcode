class Solution {
    public:
        int maxProfit(vector<int>& prices) {
            int cheap = prices[0], n = prices.size(), mx = 0;
    
            for (int i = 0; i < n - 1; i++) {
                if (prices[i] < cheap) {
                    cheap = prices[i];
                }
    
                if (prices[i + 1] < prices[i]) {
                    mx += prices[i] - cheap;
                    cheap = prices[i];
                }
            }
    
            if(cheap < prices[n - 1]) mx += prices[n - 1] - cheap;
    
            return mx;  
        }
    };

/*

Idea:
------
We are allowed to perform as many buy-sell transactions
as we want, but we can hold only one stock at a time.

Instead of searching for the global maximum selling
price, we treat every increasing sequence of prices as
an opportunity to earn profit.

Buy at the beginning of an increasing sequence and sell
just before the price drops.

Repeat this process for every increasing segment.

------------------------------------------------------------

Key Observation:
----------------

Consider the prices

1  3  5  2  4  7

The best strategy is

Buy at 1, Sell at 5

Profit = 4

Buy at 2, Sell at 7

Profit = 5

Total Profit = 9

Whenever the next day's price is smaller than today's
price, the current increasing sequence ends.

Therefore,

sell today and start looking for the next buying
opportunity.

------------------------------------------------------------

Algorithm:
----------

1.

Initialize

cheap

as the first day's price.

This represents the buying price for the current
transaction.

------------------------------------------------------------

2.

Traverse the array.

If the current price is smaller than

cheap,

update

cheap

since buying at a lower price is always better.

------------------------------------------------------------

3.

If tomorrow's price is less than today's price,

the current increasing sequence ends.

Sell today.

Profit earned

=

Today's Price - cheap

Add this profit to the answer.

Reset

cheap

to today's price so the next transaction can begin from
here if needed.

------------------------------------------------------------

4.

After the traversal,

if the last increasing sequence has not been sold,

sell on the last day.

------------------------------------------------------------

Why Does This Work?
-------------------

Every increasing sequence contributes its maximum
possible profit.

Suppose prices are

2  4  6

Buying at

2

and selling at

6

gives

4

profit.

This is identical to

(4 - 2) + (6 - 4)

=

2 + 2

=

4

Therefore,

capturing the profit of each increasing segment is
equivalent to making the optimal set of transactions.

Selling whenever the price is about to decrease locks in
the current profit before the stock loses value.

------------------------------------------------------------

Example:
--------

prices =

[7, 1, 5, 3, 6, 4]

Initially

cheap = 7

----------------

Day 2

Price = 1

Update

cheap = 1

----------------

Day 3

Price = 5

Tomorrow is 3

Price decreases.

Sell at 5.

Profit = 5 - 1 = 4

Total = 4

cheap = 5

----------------

Day 4

Price = 3

Update

cheap = 3

----------------

Day 5

Price = 6

Tomorrow is 4

Price decreases.

Sell at 6.

Profit = 6 - 3 = 3

Total = 7

----------------

Last day

Price = 4

No profit.

Final Answer

7

------------------------------------------------------------

Time Complexity:
----------------

O(n)

The array is traversed exactly once.

------------------------------------------------------------

Space Complexity:
-----------------

O(1)

Only a few variables are used.

*/