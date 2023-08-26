class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        // int size = flowerbed.size(), count = 0;
        // for(int i = 0; i < size; i++) {
        //     if(flowerbed[i] == 0) {
        //         count++;
        //     }
        // }

        // if (count == 2 * n + 2) {
        //     return true;
        // } else {
        //     return false;
        // }

        int size = flowerbed.size(), flag = (flowerbed[0] == 1) ? 0 : 1;
        for (int i = 0; i < size; i++) {
            if (flowerbed[i] != 1 && flowerbed[i + 1] != 1 && !flag) {
                n--;
                flag = 1;
            } else {
                flag = 0;
            }
        }

        if (n) {
            return false;
        }
        return true;
    }
};