class Solution {
private:
    int count(int numBottles, int extraBottles, int numExchange) {
    return numExchange > numBottles + extraBottles ? numBottles : numBottles + count(1, numBottles + extraBottles - numExchange, numExchange + 1);
    }

public:
    int maxBottlesDrunk(int numBottles, int numExchange) {
        return count(numBottles, 0, numExchange);
    }
};