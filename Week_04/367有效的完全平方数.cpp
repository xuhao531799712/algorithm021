// 二分法
class Solution {
public:
    bool isPerfectSquare(int num) {
        long left = 0, right = num;
        while (left < right) {
            long mid = left + (right - left + 1) / 2;
            if (mid * mid > num) {
                right = mid - 1;
            } else {
                left = mid;
            }
        }
        return left * left == num;
    }
};
// 牛顿迭代法
class Solution {
public:
    bool isPerfectSquare(int x) {
        double x0 = x;
        while (true) {
            double xi = (x0 + x / x0) / 2;
            if (fabs(x0 - xi) < 1e-7) {
                break;
            }
            x0 = xi;
        }
        return int(x0) * int(x0) == x;
    }
};