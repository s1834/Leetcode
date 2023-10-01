class ParkingSystem {
private:
    int b, m, s;
public:
    ParkingSystem(int big, int medium, int small) {
        b = big;
        m = medium;
        s = small;
    }
    
    bool addCar(int carType) {
        if (carType == 1 && b) {
            b--;
            return true;
        } else if (carType == 2 && m) {
            m--;
            return true;
        } else if (carType == 3 && s) {
            s--;
            return true;
        } else {
            return false;
        }
    }
};

/**
 * Your ParkingSystem object will be instantiated and called as such:
 * ParkingSystem* obj = new ParkingSystem(big, medium, small);
 * bool param_1 = obj->addCar(carType);
 */