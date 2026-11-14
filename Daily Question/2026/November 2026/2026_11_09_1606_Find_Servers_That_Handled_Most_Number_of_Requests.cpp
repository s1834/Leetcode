class Solution {
    private:
        typedef pair<int, int> P; // {finishTime, ServerId}
    
    public:
        vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
            set<int> availableServers;
            for(int i = 0; i < k; i++) availableServers.insert(i);
    
            priority_queue<P, vector<P>, greater<P>> busyServers;
            vector<int> countRequests(k, 0);
    
            int n = arrival.size();
            for(int i = 0; i < n; i++) {
                int time = arrival[i];
    
                while(!busyServers.empty() && busyServers.top().first <= time) {
                    int server = busyServers.top().second;
                    busyServers.pop();
                    availableServers.insert(server);
                }
    
                int target = i % k;
                auto it = availableServers.lower_bound(target);
                if(it == availableServers.end()) it = availableServers.begin(); // wrap around
                if(availableServers.empty()) continue; // no servers available, drop the current request
    
                int targetServer = *it;
                availableServers.erase(it); // because this server is going to be busy;
                busyServers.push({time + load[i], targetServer});
                countRequests[targetServer]++;
            }
    
            int maxNumberOfRequests = *max_element(countRequests.begin(), countRequests.end());
            vector<int> result;
            for(int i = 0; i < k; i++) {
                if(countRequests[i] == maxNumberOfRequests) result.push_back(i);
            }
    
            return result;
        }
    };

/*
    LeetCode 1606: Find Servers That Handled Most Number of Requests

    Approach: Greedy + Ordered Set + Min Heap (Priority Queue)

    Intuition:
    We are given `k` servers numbered from 0 to k - 1 and `n` incoming
    requests.

    Each request has:
        - arrival[i]: Time at which the request arrives.
        - load[i]: Time required to process the request.

    The server assignment follows these rules:

    1. For request `i`, the preferred server is `i % k`.

    2. If the preferred server is busy, choose the next available server
       with an ID greater than the preferred server.

    3. If no such server exists, wrap around and choose the available
       server with the smallest ID.

    4. If all servers are busy, drop the request.

    5. A server assigned at time `arrival[i]` remains busy until:
           arrival[i] + load[i]

    Our goal is to return all servers that handled the maximum number
    of requests.

    Key Observation:
    We need to efficiently perform two operations:

        1. Find which busy servers have finished processing.
        2. Find the next available server starting from `i % k`.

    We use two data structures:

    A. Ordered Set:
        set<int> availableServers;

       Stores the IDs of all currently available servers.

       Since std::set maintains elements in sorted order, we can use
       lower_bound() to find the smallest available server ID that
       is greater than or equal to the preferred server ID.

    B. Min Heap:
        priority_queue<P, vector<P>, greater<P>> busyServers;

       Stores pairs:
           {finishTime, serverId}

       The heap is ordered by finishTime in ascending order.

       Therefore, the server finishing earliest is always at the top.

    Variables:
        k                  -> Total number of servers.
        n                  -> Total number of requests.
        availableServers   -> Ordered set of free server IDs.
        busyServers        -> Min heap containing busy servers.
        countRequests      -> Number of requests handled by each server.
        time               -> Arrival time of the current request.
        target             -> Preferred server ID (i % k).
        targetServer       -> Actual server assigned to the request.
        maxNumberOfRequests -> Maximum requests handled by any server.
        result             -> IDs of all busiest servers.

    Step-by-Step Explanation:

    1. Initialize all servers as available:

        set<int> availableServers;

        for(int i = 0; i < k; i++)
            availableServers.insert(i);

       Initially, no requests have been assigned.

       Therefore, all k servers are available:

           availableServers = {0, 1, 2, ..., k - 1}

    2. Create the min heap:

        typedef pair<int, int> P;

        priority_queue<P, vector<P>, greater<P>> busyServers;

       Each entry contains:
           {finishTime, serverId}

       The heap allows us to retrieve the earliest finishing server
       in O(1) time and remove it in O(log k) time.

       If two servers finish at the same time, the smaller server ID
       appears first because pairs are compared lexicographically.

    3. Initialize the request counter:

        vector<int> countRequests(k, 0);

       countRequests[j] stores the number of requests handled by
       server j.

       Initially, every server has handled zero requests.

    4. Process requests in arrival order:

        for(int i = 0; i < n; i++)

       Requests are processed in increasing order of arrival time.

       For the current request:

           int time = arrival[i];

    5. Release all servers that have finished processing:

        while(!busyServers.empty() &&
              busyServers.top().first <= time) {

            int server = busyServers.top().second;
            busyServers.pop();
            availableServers.insert(server);
        }

       Before assigning the current request, we check whether any
       busy servers have completed their previous requests.

       A server becomes available when:

           finishTime <= arrival[i]

       For every completed request:
           - Remove its entry from the min heap.
           - Insert its server ID back into availableServers.

       Since the heap is ordered by finish time, we repeatedly
       remove servers until the earliest remaining finish time
       is greater than the current arrival time.

       This ensures that availableServers contains exactly the
       servers that can accept the current request.

    6. Calculate the preferred server:

        int target = i % k;

       The preferred server for request i is determined by
       the request index modulo k.

       Example:
           k = 3

           Request 0 -> Server 0
           Request 1 -> Server 1
           Request 2 -> Server 2
           Request 3 -> Server 0
           Request 4 -> Server 1
           Request 5 -> Server 2

       This creates a cyclic preference among the servers.

    7. Find the next available server:

        auto it = availableServers.lower_bound(target);

       lower_bound(target) returns an iterator pointing to the
       smallest available server ID greater than or equal to target.

       Example:
           availableServers = {0, 2, 4}
           target = 1

           lower_bound(1) -> 2

       Therefore, server 2 is selected.

    8. Handle wrap-around:

        if(it == availableServers.end())
            it = availableServers.begin();

       If no available server has an ID greater than or equal
       to target, we wrap around to the beginning of the set.

       Example:
           availableServers = {0, 1}
           target = 3

           lower_bound(3) -> end()

           Wrap around:
               it = begin()

           Selected server = 0

       This follows the circular server assignment rule.

       Note:
       If the set is empty, begin() also equals end().
       The next condition checks for this before the iterator
       is dereferenced.

    9. Drop the request if all servers are busy:

        if(availableServers.empty()) continue;

       If no servers are available, the current request cannot
       be processed.

       We skip this request and move to the next one.

       Dropped requests do not increase any server's request count.

    10. Assign the request:

        int targetServer = *it;

       The iterator points to the selected available server.

       We extract its ID and store it in targetServer.

    11. Mark the selected server as busy:

        availableServers.erase(it);

       Since the server is now processing the current request,
       it must be removed from the available set.

       This prevents another request from being assigned to it
       before its current request finishes.

    12. Calculate the finishing time and update the heap:

        busyServers.push({time + load[i], targetServer});

       The assigned server will finish processing at:

           finishTime = arrival[i] + load[i]

       We insert this finishing time and server ID into the min heap.

       The server will become available again when a future request
       arrives at or after its finishing time.

    13. Increment the assigned server's request count:

        countRequests[targetServer]++;

       Since the server successfully accepted the current request,
       its processed request count increases by one.

    14. Find the maximum number of handled requests:

        int maxNumberOfRequests =
            *max_element(countRequests.begin(), countRequests.end());

       After processing all requests, find the maximum value
       in countRequests.

       This represents the highest number of requests handled
       by any server.

    15. Collect all busiest servers:

        vector<int> result;

        for(int i = 0; i < k; i++) {
            if(countRequests[i] == maxNumberOfRequests)
                result.push_back(i);
        }

       Every server whose request count equals the maximum
       is considered a busiest server.

       We collect all such server IDs.

       Since we iterate from 0 to k - 1, the resulting server IDs
       are automatically returned in increasing order.

    16. Return the result:

        return result;

    ------------------------------------------------------------
    Example Walkthrough:
    ------------------------------------------------------------

        k = 3
        arrival = [1, 2, 3, 4, 5]
        load    = [5, 2, 3, 3, 3]

        Initially:
            availableServers = {0, 1, 2}
            busyServers = {}
            countRequests = [0, 0, 0]

        Request 0:
            arrival = 1
            load = 5
            target = 0 % 3 = 0

            Server 0 is available.

            Assign request to server 0.
            finishTime = 1 + 5 = 6

            availableServers = {1, 2}
            countRequests = [1, 0, 0]

        Request 1:
            arrival = 2
            load = 2
            target = 1 % 3 = 1

            Server 1 is available.

            Assign request to server 1.
            finishTime = 2 + 2 = 4

            availableServers = {2}
            countRequests = [1, 1, 0]

        Request 2:
            arrival = 3
            load = 3
            target = 2 % 3 = 2

            Server 2 is available.

            Assign request to server 2.
            finishTime = 3 + 3 = 6

            availableServers = {}
            countRequests = [1, 1, 1]

        Request 3:
            arrival = 4
            load = 3
            target = 3 % 3 = 0

            Server 1 finishes at time 4.

            Release server 1.

            availableServers = {1}

            lower_bound(0) -> 1

            Assign request to server 1.
            finishTime = 4 + 3 = 7

            availableServers = {}
            countRequests = [1, 2, 1]

        Request 4:
            arrival = 5
            load = 3
            target = 4 % 3 = 1

            All servers are busy.

            Drop the request.

            countRequests = [1, 2, 1]

        Final request counts:
            Server 0 -> 1 request
            Server 1 -> 2 requests
            Server 2 -> 1 request

        Maximum requests handled = 2

        Output:
            [1]

    ------------------------------------------------------------
    Why This Approach Works:
    ------------------------------------------------------------

    1. Correct Server Availability:
       The min heap maintains the finishing times of all busy servers.

       Before processing each request, every server whose finishing
       time is less than or equal to the current arrival time is
       returned to the available set.

       Therefore, the available set accurately represents all
       servers that can accept the current request.

    2. Correct Server Selection:
       The ordered set maintains available server IDs in sorted order.

       lower_bound(i % k) finds the first available server starting
       from the preferred server ID.

       If none exists, begin() correctly implements circular
       wrap-around.

       Thus, every accepted request is assigned according to the
       problem's server selection rules.

    3. Correct Request Counting:
       A server's counter increases exactly once whenever it
       successfully accepts a request.

       Dropped requests are ignored.

       Therefore, countRequests correctly stores the total number
       of requests handled by each server.

    4. Correct Final Answer:
       After all requests have been processed, we find the maximum
       request count and return every server achieving that value.

       Hence, the algorithm returns all busiest servers.

    ------------------------------------------------------------
    Complexity Analysis:
    ------------------------------------------------------------

    Let:
        n = Number of incoming requests.
        k = Number of servers.

    Time Complexity: O(k log k + n log k)

    1. Initializing availableServers:
       Inserting k server IDs into an ordered set takes O(k log k).

    2. Processing requests:
       For every request:
           - Releasing a server takes O(log k) per released server.
           - lower_bound() takes O(log k).
           - Removing an available server takes O(log k).
           - Inserting a busy server into the heap takes O(log k).

       Although the while loop can release multiple servers during
       one iteration, each assigned request creates only one heap
       entry, and each entry is removed at most once.

       Therefore, across all n requests, the total number of heap
       insertions and removals is O(n).

       Total request processing time: O(n log k).

    3. Finding the maximum and collecting the result:
       Both operations take O(k).

    Overall:
        O(k log k + n log k)

    Space Complexity: O(k)

    1. availableServers:
       Stores at most k server IDs.

    2. busyServers:
       Stores at most k busy servers.

    3. countRequests:
       Stores k integers.

    4. result:
       Can contain at most k server IDs.

    Therefore:
        O(k) auxiliary space.

    ------------------------------------------------------------
    Core Idea:
    ------------------------------------------------------------

    Use two complementary data structures:

        1. Ordered Set:
           Efficiently find the next available server using
           lower_bound() and circular wrap-around.

        2. Min Heap:
           Efficiently track busy servers and release them
           when their processing time finishes.

    For every incoming request:
        - Release completed servers.
        - Find the preferred available server.
        - Drop the request if no server is available.
        - Otherwise, assign it and update the finishing time.
        - Increment the assigned server's request count.

    Finally, return every server that handled the maximum
    number of requests.
*/