class Solution {
private:
    int count(int numBottles, int extraBottles, int numExchange) {
    return numExchange > numBottles + extraBottles ? numBottles : numBottles + count((numBottles + extraBottles) / numExchange, (numBottles + extraBottles) % numExchange, numExchange);
    }

public:
    int numWaterBottles(int numBottles, int numExchange) {
        return count(numBottles, 0, numExchange);
    }
};