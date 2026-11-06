class Solution {
    public:
        vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
            int m = logs.size();
    
            auto lambda = [](vector<int>& v1, vector<int>& v2) {
                return v1[1] < v2[1]; // sort on basis of time in ascening order
            };
    
            sort(logs.begin(), logs.end(), lambda); // {serverId, time}
    
            int q = queries.size();
            vector<int> result(q);
    
            vector<pair<int, int>> timeIndex(q); // {time, originalIndex}
            for(int i = 0; i < q; i++) timeIndex[i] = {queries[i], i};
    
            sort(timeIndex.begin(), timeIndex.end()); // sort on the basis of time
    
            unordered_map<int, int> mp;
            int i = 0;
            int j = 0;
    
            // we are touching each log only 2 times: one by i and one by j
            for(auto [time, idx] : timeIndex) {
                // Range
                int start = time - x;
                int end = time;
    
                // Expansion
                while(j < m && logs[j][1] <= end) {
                    mp[logs[j][0]]++;
                    j++;
                }
    
                // Shrinking
                while(i < m && logs[i][1] < start) {
                    mp[logs[i][0]]--;
                    if(mp[logs[i][0]] == 0) mp.erase(logs[i][0]);
                    i++;
                }
    
                result[idx] = n - mp.size(); // mp.size() = number of servers getting request in [start, end]
            }
    
            return result;
        }
    };

/*
Problem: LeetCode 2747 - Count Zero Request Servers

Approach: Offline Queries + Sorting + Sliding Window + Two Pointers

Intuition:
----------
We are given server logs in the form:

    [serverId, time]

For every query time, we need to count how many servers
did NOT receive any requests within the time interval:

    [query - x, query]

A server is considered active if it has at least one log
inside this interval.

Instead of independently checking every log for every query,
we process queries in sorted order and maintain a sliding
window over the sorted logs.

The key idea is:
- Sort logs by timestamp.
- Sort queries by time while preserving their original indices.
- Use two pointers to maintain logs inside the current window.
- Use a hashmap to track the number of logs belonging to
  each server inside that window.

This allows every log to be added and removed at most once.

--------------------------------------------------
1. Get the Number of Logs
--------------------------------------------------

int m = logs.size();

Stores the total number of server logs.

--------------------------------------------------
2. Sort Logs by Timestamp
--------------------------------------------------

auto lambda = [](vector<int>& v1, vector<int>& v2) {
    return v1[1] < v2[1];
};

sort(logs.begin(), logs.end(), lambda);

Each log contains:

    [serverId, time]

We sort the logs in ascending order of timestamp.

This is important because the sliding window will move
forward in time as we process the sorted queries.

--------------------------------------------------
3. Sort Queries While Preserving Original Indices
--------------------------------------------------

int q = queries.size();
vector<int> result(q);

vector<pair<int, int>> timeIndex(q);

for(int i = 0; i < q; i++)
    timeIndex[i] = {queries[i], i};

Each pair stores:

    {queryTime, originalIndex}

We sort these pairs:

sort(timeIndex.begin(), timeIndex.end());

Now queries are processed in increasing order of time.

However, because the original indices are stored, we can
place every answer at its correct position in result.

This is necessary because the output must follow the
original query order, not sorted query order.

--------------------------------------------------
4. Initialize the Sliding Window
--------------------------------------------------

unordered_map<int, int> mp;

int i = 0;
int j = 0;

The hashmap stores:

    mp[serverId] = Number of logs of this server
                   inside the current time window.

Therefore:

    mp.size() = Number of distinct active servers

The two pointers represent the current range of logs:

- i: First log that belongs to the current window.
- j: First log that has not yet been added to the window.

The current window is maintained using the range:

    [start, end]

--------------------------------------------------
5. Process Queries in Sorted Order
--------------------------------------------------

for(auto [time, idx] : timeIndex)

For every sorted query:
- time represents the query timestamp.
- idx represents its original position in queries.

The required time interval is:

    start = time - x
    end = time

A server is active if it has at least one request
whose timestamp lies within this inclusive interval.

--------------------------------------------------
6. Expansion: Add Logs Up to the Current End Time
--------------------------------------------------

while(j < m && logs[j][1] <= end) {

    mp[logs[j][0]]++;
    j++;

}

We move pointer j forward while the current log timestamp
is less than or equal to the query time.

For every newly included log:

    mp[serverId]++

This increases the frequency of that server inside
the current window.

If the server was not already present in the hashmap,
it becomes a new active server.

Because queries are processed in increasing order,
we never need to move j backwards.

--------------------------------------------------
7. Shrinking: Remove Logs Before the Current Start Time
--------------------------------------------------

while(i < m && logs[i][1] < start) {

    mp[logs[i][0]]--;

    if(mp[logs[i][0]] == 0)
        mp.erase(logs[i][0]);

    i++;

}

Some logs that were included in previous query windows
may now fall outside the current interval.

If a log timestamp is smaller than start, it must be removed.

For every removed log:

1. Decrease its server's frequency in the hashmap.
2. If its frequency becomes zero, erase that server
   from the hashmap.
3. Move pointer i forward.

We use:

    logs[i][1] < start

rather than <= start because the starting boundary is
inclusive.

A log exactly at start must remain inside the window.

Similarly, the expansion condition uses <= end because
the ending boundary is also inclusive.

After expansion and shrinking, the hashmap contains
exactly the servers that have at least one log in:

    [time - x, time]

--------------------------------------------------
8. Calculate the Number of Inactive Servers
--------------------------------------------------

result[idx] = n - mp.size();

Here:

    n = Total number of servers
    mp.size() = Number of servers with at least one
                request in the current time interval

Therefore:

    Inactive Servers = Total Servers - Active Servers

We store the answer at idx, which is the original
position of the query.

This ensures that sorting the queries does not change
the required output order.

--------------------------------------------------
9. Return the Result
--------------------------------------------------

return result;

After processing all queries, result contains the
number of inactive servers for every original query.

--------------------------------------------------
10. Example Walkthrough
--------------------------------------------------

Input:

    n = 3

    logs = [[1, 3], [2, 6], [1, 5], [3, 7]]

    x = 2

    queries = [4, 6]

Query 1: time = 4

    start = 4 - 2 = 2
    end = 4

    Current window = [2, 4]

Expansion:

    [1, 3] is included.

    mp = {1: 1}

    Other logs have timestamps greater than 4.

Shrinking:

    No logs need to be removed.

Active servers = 1

Inactive servers:

    3 - 1 = 2

Answer for query 4 = 2.

Query 2: time = 6

    start = 6 - 2 = 4
    end = 6

    Current window = [4, 6]

Expansion:

    [2, 6] is included.

    [1, 5] is included.

    mp = {1: 2, 2: 1}

Shrinking:

    Remove [1, 3] because 3 < 4.

    mp = {1: 1, 2: 1}

Active servers = 2

Inactive servers:

    3 - 2 = 1

Answer for query 6 = 1.

Final result:

    [2, 1]

--------------------------------------------------
11. Why Does the Sliding Window Work?
--------------------------------------------------

The queries are processed in increasing timestamp order.

Therefore, both boundaries of the time window move
only forward.

For every query:

- Pointer j adds all newly eligible logs whose timestamps
  are <= the current end.
- Pointer i removes all logs whose timestamps are
  smaller than the current start.

The hashmap maintains the frequency of logs for each
server inside the current window.

A server is active exactly when its frequency is greater
than zero.

Since both pointers only move forward, every log is:
- Added at most once.
- Removed at most once.

This avoids repeatedly scanning all logs for every query.

--------------------------------------------------
12. Complexity Analysis
--------------------------------------------------

Let:
    n = Number of servers
    m = Number of logs
    q = Number of queries

Sorting logs:
    O(m log m)

Sorting queries:
    O(q log q)

Sliding window:
    O(m + q) expected

Each log is added at most once and removed at most once.
Hashmap operations take O(1) expected time.

Overall Time Complexity:

    O(m log m + q log q + m + q)

Simplified:

    O(m log m + q log q)

Space Complexity:

    O(m + q + n) auxiliary storage in the worst case.

- result stores q answers.
- timeIndex stores q query-time/index pairs.
- mp stores at most n distinct server IDs.
- Sorting logs is performed on the input vector.

Core Idea:
----------
Use offline query processing.

1. Sort logs by timestamp.
2. Sort queries while storing their original indices.
3. Maintain the current inclusive time window using
   two pointers.
4. Track active servers using a frequency hashmap.
5. Calculate inactive servers as:

       n - mp.size()

6. Store each answer at its original query index.

This reduces repeated log scanning to an efficient
sliding-window traversal.
*/