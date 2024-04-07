class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();
        int l = 0, m = n - 1, sum = 0;
        for (int i = 0; i < k; i++) {
            if(cardPoints[l] > cardPoints[m]) {
                sum += cardPoints[l];
                l++;
            } else if(cardPoints[l] < cardPoints[m]) {
                sum += cardPoints[m];
                m--;
            } else {
                int t1 = l, t2 = m, ts1 = cardPoints[l], ts2 = cardPoints[m], cnt = 0;
                bool change = true;
                while(t1 < k && t2 > n - k && cnt != k - i) {
                    t1++;
                    t2--;
                    cnt++;
                    if(cardPoints[t1] > cardPoints[t2]) {
                        sum += ts1;
                        l = t1;
                        i += cnt - 1;
                        change = false;
                        break;
                    } else if (cardPoints[t1] < cardPoints[t2]) {
                        sum += ts2;
                        m = t2;
                        i += cnt - 1;
                        change = false;
                        break;
                    } else {
                        ts1 += cardPoints[t1];
                        ts2 += cardPoints[t2];
                    }
                }
                if(change) {
                    sum += ts1;
                    i += cnt;
                    l = t1;
                }
            }
        }
        return sum;
    }
};