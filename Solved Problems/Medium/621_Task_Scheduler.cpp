class Solution {
    public:
        int leastInterval(vector<char>& tasks, int n) {
            // Count number of occurrences of each char
            unordered_map<char, int> mp;
            for(auto x : tasks) mp[x]++;
    
            int time = 0;
    
            // push {count, char} in priority queue to sort by max occurrence
            priority_queue<pair<int, char>> pq;
            for(auto x : mp) pq.push({x.second, x.first});
    
            while(!pq.empty()) {
                queue<pair<int, char>> q; // queue to store elements until we can use it again
                int temp = n + 1; // n + 1 because current task + n 
                
                while(temp--) {
                    if(!pq.empty()) {
                        pair<int, int> p = pq.top();
                        pq.pop();
    
                        time++;
    
                        // decrease 1 occurrence
                        p.first--;
    
                        // if still occurrences of that char left, push in queue
                        if(p.first > 0) q.push(p);
                    } else {
                        if(q.empty()) break;
                        else time++;
                    }
                }
    
                // push back the elements which can be used again now
                while(!q.empty()) {
                    pq.push(q.front());
                    q.pop();
                }
            }
            return time;
        }
    };

/*

Idea:
------
Always execute the task with the highest remaining frequency.

Use a Max Heap to efficiently select the task with the
maximum occurrences.

After executing a task, it cannot be executed again until
the current cooling cycle finishes, so temporarily store it
in a queue.

------------------------------------------------------------

Why process (n + 1) intervals?
------------------------------

If a task is executed now,

it cannot be executed again until after

n

more intervals.

Therefore, one complete cooling cycle contains

1 (current task) + n (cooling intervals)

= n + 1 intervals.

During one cycle, execute as many different tasks
as possible.

------------------------------------------------------------

Algorithm:
----------

1.

Count the frequency of every task.

------------------------------------------------------------

2.

Push

(frequency, task)

into a Max Heap.

The task with the highest remaining frequency will
always be processed first.

------------------------------------------------------------

3.

Process one cooling cycle of length

n + 1.

For every interval:

• If the heap is not empty,

    Execute the most frequent task.

    Decrease its remaining frequency.

    If occurrences are still left,

    store it in a temporary queue until the
    cooling cycle finishes.

• Otherwise,

    If the queue is empty,

    all tasks are completed.

    Break immediately.

    Else,

    CPU remains idle for this interval.

------------------------------------------------------------

4.

After completing the current cooling cycle,

move every task stored in the queue back into the
Max Heap.

These tasks have now completed their cooling period
and are available for execution again.

------------------------------------------------------------

Example:
--------

tasks =

A A A B B B

n = 2

Frequencies:

A -> 3

B -> 3

------------------------------------------------------------

Cycle 1

A

B

idle

Queue:

A(2)

B(2)

Move queue back to heap.

------------------------------------------------------------

Cycle 2

A

B

idle

Queue:

A(1)

B(1)

Move queue back.

------------------------------------------------------------

Cycle 3

A

B

Answer:

8

------------------------------------------------------------

Time Complexity:
----------------

O(m log 26)

where m is the number of tasks.

Since there are at most 26 different task types,
this is effectively O(m).

------------------------------------------------------------

Space Complexity:
-----------------

O(26)

The heap, queue, and frequency map together store
at most 26 task types.

*/