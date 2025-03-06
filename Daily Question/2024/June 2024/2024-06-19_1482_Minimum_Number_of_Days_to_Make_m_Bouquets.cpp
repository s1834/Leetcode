class Solution {
public:
    int numBouquets(vector<int>& bloomDay, int mid, int k) {
        int num = 0, count = 0;
        for (int i = 0; i < bloomDay.size(); i++) {
            if(bloomDay[i] <= mid) {
                count++;
            } else {
                count = 0;
            }

            if (count == k) {
                num++;
                count = 0;
            }
        }

        return num;
    }

    int minDays(vector<int>& bloomDay, int m, int k) {
        int start = 0;
        int end = 0;
        for(int day : bloomDay) {
            end = max(end, day);
        }

        int minDays = -1;
        while(start <= end) {
            int mid = (start + end) /2;

            if(numBouquets(bloomDay, mid, k) >= m) {
                minDays = mid;
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }

        return minDays;
    }
};