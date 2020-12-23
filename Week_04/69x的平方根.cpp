// 正常二分查找
// 满足三个条件：单调性、有界性、可索引访问
class Solution {
public:
    int mySqrt(int x) {
        long left = 0, right = x;
        while (left < right) {
            long mid = left + (right - left + 1) / 2; // 因为下面是 right = mid - 1，所以这里 mid 要取偏右值来保证每次区间不一样
            if (mid * mid > x) { // 本题中是只保留整数部分，所以这个地方判定条件是 >，然后下面是 right = mid - 1;
                right = mid - 1;  
            } else {
                left = mid;
            }
        }
        return (int)left;
    }
};
// 二分查找的核心是，保证每次迭代左右区间中一定包括了目标值，然后再保证每次迭代一定会缩小区间长度，这样当 left < right 不再满足时
// left == right 就是目标值了

// 牛顿迭代法
class Solution {
public:
    int mySqrt(int x) {
        if (x == 0) {
            return 0;
        }

        double x0 = x;
        while (true) {
            double xi = (x0 + x / x0) / 2;
            if (fabs(x0 - xi) < 1e-7) {
                break;
            }
            x0 = xi;
        }
        return int(x0);
    }
};