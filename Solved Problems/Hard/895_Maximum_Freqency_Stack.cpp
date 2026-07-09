class FreqStack {
    private:
        int maxFreq = 0;
        unordered_map<int, int> freq;
        unordered_map<int, stack<int>> group;
    
    public:
        FreqStack() {
            
        }
        
        void push(int val) {
            freq[val]++;
            maxFreq = max(maxFreq, freq[val]);
            group[freq[val]].push(val);
        }
        
        int pop() {
            int ans = group[maxFreq].top();
            group[maxFreq].pop();
            freq[ans]--;
            if (group[maxFreq].empty()) maxFreq--;
            return ans;
        }
    };
    
    /**
     * Your FreqStack object will be instantiated and called as such:
     * FreqStack* obj = new FreqStack();
     * obj->push(val);
     * int param_2 = obj->pop();
     */

/*

Idea:
------
We need a stack that supports:

    1. push(x)
    2. pop() -> remove the element with the highest frequency.

If multiple elements have the same highest frequency,
remove the one that was pushed most recently.

------------------------------------------------------------

Observation:
------------

Each element has two priorities:

    1. Higher frequency.
    2. More recent insertion (stack order).

A normal stack only maintains recency and cannot efficiently
find the element with the highest frequency.

------------------------------------------------------------

Data Structures:
----------------

1. freq

    unordered_map<int, int>

    freq[x] stores the current frequency of x.

------------------------------------------------------------

2. group

    unordered_map<int, stack<int>>

    group[f] stores a stack of all elements that have
    reached frequency f.

    Each stack naturally preserves insertion order, so
    the top of the stack is the most recently inserted
    element with that frequency.

Example:

push(5)

freq:
5 -> 1

group:

1:
5

----------------

push(7)

freq:
5 -> 1
7 -> 1

group:

1:
5
7

----------------

push(5)

freq:
5 -> 2
7 -> 1

group:

1:
5
7

2:
5

Notice that 5 is NOT removed from group[1].

Each stack records the order in which elements reached
that particular frequency.

------------------------------------------------------------

3. maxFreq

    Stores the maximum frequency currently present.

Instead of searching for the highest frequency during pop(),
we always know exactly which stack to use.

------------------------------------------------------------

Push Operation:
---------------

1. Increase the frequency of the element.

2. Update maxFreq if necessary.

3. Push the element into the stack corresponding to
   its new frequency.

Example:

push(5)

freq[5] becomes 3

Push 5 into

group[3]

------------------------------------------------------------

Pop Operation:
--------------

1. The answer is always on top of

       group[maxFreq]

because:

    • Every element in this stack has the highest frequency.
    • The stack guarantees the most recently inserted one
      appears on top.

2. Pop that element.

3. Decrease its frequency.

4. If no element now has frequency maxFreq,
   decrease maxFreq by one.

------------------------------------------------------------

Why doesn't an element get removed from lower-frequency stacks?
---------------------------------------------------------------

Suppose:

push(5)
push(5)
push(5)

The stacks become:

group[1]:
5

group[2]:
5

group[3]:
5

Each stack represents the moment an element reached that
frequency, not its current frequency.

During pop(), we always remove from the highest-frequency
stack first, so these historical entries are exactly what
allows us to correctly break ties using recency.

------------------------------------------------------------

Example:
--------

Operations:

push(5)
push(7)
push(5)
push(7)
push(4)
push(5)

freq:

5 -> 3
7 -> 2
4 -> 1

group:

1:
5 7 4

2:
5 7

3:
5

maxFreq = 3

pop()

Take the top of group[3].

Answer = 5

group[3] becomes empty.

Decrease maxFreq to 2.

Next pop()

Take the top of group[2].

Answer = 7

This correctly satisfies both:

• Highest frequency.
• Most recently inserted among ties.

------------------------------------------------------------

Time Complexity:
----------------

push()

    O(1)

pop()

    O(1)

------------------------------------------------------------

Space Complexity:
-----------------

O(n)

where n is the total number of pushed elements.

Both hash maps together store information proportional
to the number of push operations.

*/