// 70.爬楼梯
class Solution {
 public:
  int climbStairs(int n) {
    if (n <= 2) return n;
    int fn1 = 2, fn2 = 1, res;
    for (int i = 3; i <= n; i++) {
      res = fn1 + fn2;
      fn2 = fn1;
      fn1 = res;
    }
    return res;
  }
};