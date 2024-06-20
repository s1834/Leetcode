class Solution {
public:
    bool placeBalls(int x, vector<int> &position, int m) {
        int prevBall = position[0];
        int ballsPlaced = 1;
        for(int i = 1; i < position.size() && ballsPlaced < m; ++i) {
            int curPos = position[i];
            if(curPos - prevBall >= x) {
                ballsPlaced += 1;
                prevBall = curPos;
            }
        }
        return ballsPlaced == m;
    }

    int maxDistance(vector<int>& position, int m) {
        int ans = 0, n = position.size();
        sort(position.begin(), position.end());
        int l = 1, h = ceil(position[n - 1] / (m - 1.0));
        while(l <= h) {
            int mid = l + (h - l) / 2;
            if(placeBalls(mid, position, m)) {
                ans = mid;
                l = mid + 1;
            } else {
                h = mid - 1;
            }
        }
        return ans;
    }
};