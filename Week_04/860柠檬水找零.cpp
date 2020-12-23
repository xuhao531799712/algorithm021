class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int five = 0, ten = 0;
        for (auto bill : bills) {
            if (bill == 5) ++five;
            else if (bill == 10) {
                if (five < 1) return false;
                ++ten;
                --five;
            } else {
                if (ten > 0 && five > 0) {
                    --ten;
                    --five;
                } else if (five > 2) {
                    five -= 3;
                } else {
                    return false;
                }
            }
        }
        return true;
    }
};