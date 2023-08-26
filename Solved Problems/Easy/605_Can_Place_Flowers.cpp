class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int size = flowerbed.size();
        if (size < 3) {
            if(n == 0) {
                return true;
            } else if(n == 1 && flowerbed[0] == 0) {
                if (size > 1) {
                    if (flowerbed[1] == 0) {
                        return true;
                    } else {
                        return false;
                    }
                }
                return true;
            } else {
                return false;
            }
        }

        for (int i = 0; i < size; i++) {
            if (i == 0 && flowerbed[i] != 1 && flowerbed[i + 1] != 1) {
                n--;
                flowerbed[i] = 1;
            } else if (i == size - 1 && flowerbed[i] != 1 && flowerbed[i - 1] != 1) {
                n--;
                flowerbed[i] = 1;
            } else if (flowerbed[i] != 1 && flowerbed[i + 1] != 1 && flowerbed[i - 1] != 1) {
                n--;
                flowerbed[i] = 1;
            }
        }

        if (n) {
            return false;
        }
        return true;
    }
};