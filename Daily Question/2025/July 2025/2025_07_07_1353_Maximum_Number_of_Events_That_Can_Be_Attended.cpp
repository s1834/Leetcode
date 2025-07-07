class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        int n = events.size();
        sort(events.begin(), events.end());

        priority_queue<int, vector<int>, greater<int>> pq;
        int day = events[0][0], i = 0, count = 0;
        while(!pq.empty() || i < n) {
            if(pq.empty()) day = events[i][0];

            while(i < n && events[i][0] == day) {
                pq.push(events[i][1]);
                i++;
            }

            if(!pq.empty()) {
                pq.pop();
                count++;
            }
            day++;
            
            while(!pq.empty() && pq.top() < day) pq.pop();
        }
        return count;
    }
};

/*
1) Sort the events based on their start time.
2) Use a priority queue to keep track of the end times.
3) Initialize the day to the start of the first event and a counter for attended events.
4) While there are events left or the priority queue is not empty:
   a) If the priority queue is empty, set the day to the start of the next event. Basically to skip time from i++ like one starts on day 5 and other on day 15 and no othere event is left in priority queue, so we can directly jump to day 15.
   b) Add all events starting on the current day to the priority queue.
   c) If the priority queue is not empty, pop the earliest ending event and increment the count of attended events.
   d) Increment the day.
5) Remove any events from the priority queue that have already ended.
6) Return the count of attended events.
*/