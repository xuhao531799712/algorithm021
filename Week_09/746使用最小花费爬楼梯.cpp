// 动态规划状态定义 dp[i] 表示到达 i 消耗的最小体力值
// dp[i] = min(dp[i - 2], dp[i - 1]) + cost[i];
// 时间复杂度 O(n) 空间复杂度 O(n)
class Solution {
 public:
     int minCostClimbingStairs(vector<int>& cost) {
         int n = cost.size();
         if (n < 2) return 0;
         vector<int> dp(n);
         dp[0] = cost[0];
         dp[1] = cost[1];
         for (int i = 2; i < n; ++i) {
             dp[i] = min(dp[i - 2], dp[i - 1]) + cost[i];
         }
         return min(dp[n - 2], dp[n - 1]);
     }
 };

// 内存优化
// 时间复杂度 O(n) 空间复杂度 O(1)
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        if (n < 2) return 0;
        int dp0 = cost[0], dp1 = cost[1];
        for (int i = 2; i < n; ++i) {
            swap(dp0, dp1);
            dp1 = min(dp1, dp0) + cost[i];
        }
        return min(dp0, dp1);
    }
};