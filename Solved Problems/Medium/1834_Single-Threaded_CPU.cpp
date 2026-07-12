class Solution {
    public:
        vector<int> getOrder(vector<vector<int>>& tasks) {
            // pair<pair<enqueueTime, processingTime>, index>>
            priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, greater<pair<pair<int, int>, int>>> available;
    
            // pair<processingTime, index>
            priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> process;
    
            // push all tasks in ascending order of enqueue time
            int n = tasks.size();
            for(int i = 0; i < n; i++) available.push({{tasks[i][0], tasks[i][1]}, i});
    
            // keep track of total time so far to add available to process queue
            long long int time = 1;
            vector<int> ans;
            while(!available.empty() || !process.empty()) {
                // push all enqueued tasks till current time for processing
                while(!available.empty() && available.top().first.first <= time) {
                    process.push({available.top().first.second, available.top().second});
                    available.pop();
                }
    
                // just choose the task with shortest processing time, and add its time to total time
                if(!process.empty()) {
                    time += process.top().first;
                    ans.push_back(process.top().second);
                    process.pop();
                } else time = available.top().first.first;;
            }
    
            return ans;
        }
    };

/*

Idea:
------
Use two Min Heaps.

1.

Available Heap

Stores every task sorted by its enqueue time.

This helps determine which tasks become available
as time progresses.

------------------------------------------------------------

2.

Processing Heap

Stores all currently available tasks sorted by

(processing time, index).

The CPU always chooses the task with the shortest
processing time.

If multiple tasks have the same processing time,

the smaller index is chosen automatically because
of the pair ordering.

------------------------------------------------------------

Algorithm:
----------

Step 1:

Push every task into the Available Heap as

((enqueue time, processing time), index)

so tasks are processed in increasing enqueue time.

------------------------------------------------------------

Step 2:

Maintain the current CPU time.

Initially,

time = 1

------------------------------------------------------------

Step 3:

While there are still tasks remaining,

move every task whose

enqueue time <= current time

from the Available Heap into the Processing Heap.

Only these tasks are currently available for execution.

------------------------------------------------------------

Step 4:

If the Processing Heap is not empty,

pick the task with

• shortest processing time

• smallest index (if processing times are equal)

Execute the task completely.

Increase

time += processing time

Store its index in the answer.

------------------------------------------------------------

Step 5:

If no task is available for processing,

the CPU remains idle.

Instead of increasing time one unit at a time,

jump directly to the enqueue time of the next task.

This avoids unnecessary simulation.

------------------------------------------------------------

Example:
--------

tasks

Index : (enqueue, process)

0 : (1,2)

1 : (2,4)

2 : (3,2)

3 : (4,1)

------------------------------------------------------------

Available Heap

(1,2)

(2,4)

(3,2)

(4,1)

------------------------------------------------------------

time = 1

Move all available tasks.

Processing Heap

(2,0)

Execute task 0.

time = 3

Answer:

0

------------------------------------------------------------

time = 3

Move newly available tasks.

Processing Heap

(2,2)

(4,1)

Execute task 2.

time = 5

Answer:

0 2

------------------------------------------------------------

time = 5

Move newly available tasks.

Processing Heap

(1,3)

(4,1)

Execute task 3.

time = 6

Answer:

0 2 3

------------------------------------------------------------

Execute remaining task.

Answer:

0 2 3 1

------------------------------------------------------------

Time Complexity:
----------------

Building Available Heap:

O(n log n)

Each task is moved once into the Processing Heap:

O(n log n)

Each task is removed once from the Processing Heap:

O(n log n)

Overall:

O(n log n)

------------------------------------------------------------

Space Complexity:
-----------------

O(n)

Both heaps together store at most n tasks.

*/