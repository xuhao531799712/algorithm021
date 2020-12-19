// // 方法一：采用递归
class Solution {
public:
    double myPow(double x, int n) {
        long nn = n;
        return nn < 0? 1.0 / quickPow(x, -nn) : quickPow(x, nn);
    }

    double quickPow(double x, long n) {
        if (x == 1 || x == 0) return x;
        if (n == 0) return 1;

        return n % 2 == 0 ? myPow(x * x, n / 2) : myPow(x * x, n / 2) * x;
    }
};

// 方法一：采用迭代
class Solution {
public:
    double myPow(double x, int n) {
        long nn = n;
        return nn < 0? 1.0 / quickPow(x, -nn) : quickPow(x, nn);
    }

    double quickPow(double x, long n) {
        if (x == 1 || x == 0) return x;
        if (n == 0) return 1;

        // contr 相当于存下了过程中的奇数时的单独的数
        // 然后再和累乘后的 x 相乘得到最后结果
        double contr = 1.0;
        while (n) {
            if (n % 2 == 1) {
                contr *= x;
            }
            n /= 2;
            x *= x;
        }

        return contr;
    }
};