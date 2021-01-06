// 动态规划，定义状态 dp[i] 表示组成正整数 i 的完全平方数最少个数
// 递推方程：
//     dp[i] = min(dp[j] + dp[i-j]); for 循环遍历，但如此遍历复杂度是 O(n^2)，超出时间限制

class Solution {
public:
    int numSquares(int n) {
        if (n <= 1) return n;
        vector<int> dp(n + 1, INT_MAX);
        for (int i = 1; i * i <= n; ++i) {
            dp[i * i] = 1;
        }
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j <= i/2; ++j) {
                dp[i] = min(dp[i], dp[j] + dp[i - j]);
            }
        }
        return dp[n];
    }
};

// 可通过直接减完全平方数来加快
class Solution {
public:
    int numSquares(int n) {
        if (n <= 1) return n;
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j * j <= n; ++j) {
                if(i-j*j < 0) break;
                dp[i] = min(dp[i], dp[i - j * j] + 1);
            }
        }
        return dp[n];
    }
};

