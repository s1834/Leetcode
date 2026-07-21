class Solution {
    public:
        int carFleet(int target, vector<int>& position, vector<int>& speed) {
            vector<pair<int, int>> v;
            int n = position.size();
            for(int i = 0; i < n; i++) v.push_back({position[i], speed[i]});
    
            sort(v.begin(), v.end(), greater<pair<int, int>>());
            
            stack<double> st;
            for(auto x : v) {
                double time = (double)(target - x.first) / x.second;
                if(st.empty() || time > st.top()) st.push(time);
            }
            return st.size();
        }
    };

/*

Idea:
------
Each car moves toward the target with a constant speed.

The time required for a car to reach the target is

Time = Distance / Speed
     = (target - position) / speed

If a faster car behind catches a slower car before the
target,

it cannot overtake.

Instead,

both cars travel together at the slower car's speed,
forming a single fleet.

Therefore,

instead of simulating the movement,

we only need to compare the arrival times.

------------------------------------------------------------

Key Observation:
----------------

Sort the cars in decreasing order of their positions,
i.e., from the car closest to the target to the farthest.

Now process the cars one by one.

At any point,

all cars already processed are in front of the current
car.

The current car has only two possibilities:

1.

It reaches the target later than the fleet ahead.

It can never catch that fleet.

Hence,

it forms a new fleet.

------------------------------------------------------------

2.

It reaches the target earlier (or at the same time)
than the fleet ahead.

Since it is behind,

it catches the fleet before reaching the target.

After catching,

it must move with that fleet,

so both become a single fleet.

------------------------------------------------------------

Mathematical Explanation:
-------------------------

Suppose

Front car

Position = p₁

Speed = s₁

Arrival Time

t₁ = (target - p₁) / s₁

--------------------------------

Behind car

Position = p₂

Speed = s₂

where

p₂ < p₁

Arrival Time

t₂ = (target - p₂) / s₂

--------------------------------

Case 1:

t₂ > t₁

The car behind needs more time to reach the target.

Since the front car reaches earlier,

the behind car never catches it.

Therefore,

a new fleet is formed.

--------------------------------

Case 2:

t₂ ≤ t₁

The behind car would reach the target earlier (or at the
same time) if the front car did not exist.

Since overtaking is not allowed,

it must catch the front car before the target.

After meeting,

both travel together.

Hence,

they become a single fleet whose arrival time is

t₁

(the slower fleet's arrival time).

This is exactly why we do not push

t₂

into the stack.

------------------------------------------------------------

Why Does the Stack Work?
------------------------

The stack stores the arrival time of every fleet formed
so far.

The top of the stack always represents the nearest fleet
in front of the current car.

For every car,

Compute

time = (target - position) / speed

--------------------------------

If

time > stack.top()

the current car is slower than the fleet ahead.

It cannot catch that fleet.

Push its arrival time.

A new fleet is created.

--------------------------------

Otherwise,

time ≤ stack.top()

the current car catches the fleet ahead before reaching
the target.

No new fleet is formed,

so we do not push anything.

------------------------------------------------------------

Example:
--------

target = 12

Position

[10, 8, 5, 3]

Speed

[2, 4, 1, 3]

--------------------------------

After sorting by position

(10,2)

(8,4)

(5,1)

(3,3)

--------------------------------

Car at 10

Time

(12 - 10) / 2 = 1

Stack

[1]

Fleet Count = 1

--------------------------------

Car at 8

Time

(12 - 8) / 4 = 1

1 ≤ 1

It catches the fleet ahead.

Stack

[1]

Fleet Count = 1

--------------------------------

Car at 5

Time

(12 - 5) / 1 = 7

7 > 1

Cannot catch.

New fleet.

Stack

[1, 7]

Fleet Count = 2

--------------------------------

Car at 3

Time

(12 - 3) / 3 = 3

3 ≤ 7

It catches the second fleet.

Final Stack

[1, 7]

Answer = 2 Fleets

------------------------------------------------------------

Why Sort in Descending Position?
--------------------------------

A car can only interact with cars in front of it.

By processing cars from nearest to farthest,

the fleet immediately ahead has already been determined.

Thus,

the current car only needs to compare its arrival time
with the fleet in front.

No future car can affect this decision.

------------------------------------------------------------

Time Complexity:
----------------

Sorting:

O(n log n)

Traversing all cars:

O(n)

Overall:

O(n log n)

------------------------------------------------------------

Space Complexity:
-----------------

O(n)

for storing the sorted cars and the stack of fleet
arrival times.

*/