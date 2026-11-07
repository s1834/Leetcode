class Solution {
    private:
        typedef pair<int, int> P; // <weight, index>
        typedef tuple<long, int, int> T; // <finishTime, weight, index>
    
    public:
        vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
            int n = servers.size(), m = tasks.size();
    
            // free servers <weight, index>
            priority_queue<P, vector<P>, greater<P>> freeServers;
            for(int i = 0; i < n; i++) freeServers.push({servers[i], i});
    
            // busy servers <finishTime, weight, index>
            priority_queue<T, vector<T>, greater<T>> busyServers;
            vector<int> result(m);
            for(int i = 0; i < m; i++) {
                // Move busy servers to free servers if they are free by ith time
                while(!busyServers.empty() && get<0>(busyServers.top()) <= i) {
                    auto [finishTime, weight, index] = busyServers.top();
                    busyServers.pop();
                    freeServers.push({weight, index});
                }
    
                if(freeServers.empty()) {
                    auto [finishTime, weight, index] = busyServers.top();
                    busyServers.pop();
                    result[i] = index;
                    busyServers.push({finishTime + tasks[i], weight, index});
                } else {
                    auto [weight, index] = freeServers.top();
                    freeServers.pop();
                    result[i] = index;
                    busyServers.push({i + tasks[i], weight, index});
                }
            }
    
            return result;
        }
    };

/*
    LeetCode 1882: Process Tasks Using Servers

    Approach: Greedy + Two Min Heaps (Priority Queues)

    Intuition:
    We are given n servers and m tasks.

    Each server has a weight, and each task takes a certain amount
    of time to complete.

    Tasks arrive sequentially:
        - Task i arrives at time i.
        - It must be assigned to an available server.
        - If multiple servers are available, choose the one with
          the smallest weight.
        - If weights are equal, choose the server with the smallest
          index.
        - If no server is available, wait until one becomes free.

    To efficiently manage servers, we maintain two min heaps:

    1. Free Servers:
       Stores servers that are currently available.

       Pair:
           {weight, index}

       The min heap automatically prioritizes:
       - Smaller server weight.
       - Smaller server index in case of a tie.

    2. Busy Servers:
       Stores servers currently processing tasks.

       Tuple:
           {finishTime, weight, index}

       The min heap prioritizes:
       - Earliest finishing time.
       - Smaller weight if finish times are equal.
       - Smaller index if both are equal.

    Variables:
    - n:
        Number of servers.

    - m:
        Number of tasks.

    - P:
        Pair representing {weight, server index}.

    - T:
        Tuple representing {finishTime, weight, server index}.

    - freeServers:
        Min heap containing all currently available servers.

    - busyServers:
        Min heap containing all currently occupied servers.

    - result:
        Stores the server index assigned to each task.

    Step-by-Step Explanation:

    1. Initialize the free server heap:

           priority_queue<P, vector<P>, greater<P>> freeServers;

       Insert every server into this heap as:

           {servers[i], i}

       Initially, all servers are available.

    2. Initialize the busy server heap:

           priority_queue<T, vector<T>, greater<T>> busyServers;

       This heap keeps track of when each busy server will become
       available again.

    3. Process tasks in arrival order:

       For every task i, its arrival time is i.

       A. Move completed tasks' servers back to the free heap:

              while(!busyServers.empty() &&
                    get<0>(busyServers.top()) <= i)

          If a server's finish time is less than or equal to the
          current task arrival time, that server is available.

          Remove it from busyServers and insert it into freeServers.

          We use a while loop because multiple servers may become
          free at the same time.

       B. Check whether any server is available.

          Case 1: No free server exists.

              if(freeServers.empty())

          This means the current task must wait.

          The server at the top of busyServers is the one that
          becomes available earliest.

          Remove that server:

              auto [finishTime, weight, index] = busyServers.top();
              busyServers.pop();

          Assign the current task to it:

              result[i] = index;

          Since the server becomes free at finishTime, the current
          task starts at that time and finishes after tasks[i]
          additional time.

              busyServers.push({
                  finishTime + tasks[i],
                  weight,
                  index
              });

          Notice that we do not push this server into freeServers.
          It immediately starts processing the waiting task.

          Case 2: At least one free server exists.

              else

          Choose the server with the smallest weight, breaking
          ties using the smallest index:

              auto [weight, index] = freeServers.top();

          Remove it from freeServers and assign it to task i.

          Since the task arrives at time i, its finish time is:

              i + tasks[i]

          Insert the server into busyServers:

              busyServers.push({
                  i + tasks[i],
                  weight,
                  index
              });

    4. Return the result array:

       After processing all tasks, result[i] contains the index
       of the server assigned to task i.

    Example Walkthrough:

    servers = [3, 3, 2]
    tasks   = [1, 2, 3, 2, 1, 2]

    Initially:

        Free servers = {(2, 2), (3, 0), (3, 1)}
        Busy servers = {}

    Task 0 arrives at time 0:
        Server 2 is selected (weight 2).
        It finishes at time 1.

        result[0] = 2

    Task 1 arrives at time 1:
        Server 2 becomes free.
        Server 2 is selected again.
        It finishes at time 3.

        result[1] = 2

    Task 2 arrives at time 2:
        No server is free.
        The earliest available server is server 0 or 1
        at time 0? No: both are still free only if they
        were not assigned previously. In this example, the
        remaining servers 0 and 1 are available, so server 0
        is selected (weight 3, smaller index).

        result[2] = 0

    The two heaps continue to track availability and selection
    for the remaining tasks.

    Complexity Analysis:

    Let n be the number of servers and m be the number of tasks.

    Time Complexity: O((n + m) log n)

        - Inserting all servers into freeServers takes O(n log n).
        - Every server can move from busyServers to freeServers
          at most once between task assignments.
        - Each task causes at most one server assignment.
        - Every heap insertion and removal takes O(log n).

        Across all tasks, the total number of heap operations
        is O(n + m), giving O((n + m) log n).

    Space Complexity: O(n + m)

        - Free and busy heaps together store at most n servers.
        - The result array stores m assigned server indices.

        Therefore, total auxiliary space is O(n + m), including
        the output array.

    Core Idea:
    Use one min heap to select the best available server and
    another min heap to track when occupied servers become free.

    At each task arrival:
    - Release all servers whose finish time has arrived.
    - Choose the best available server, or wait for the earliest
      finishing server if none is available.
    - Update that server's next finish time.
*/