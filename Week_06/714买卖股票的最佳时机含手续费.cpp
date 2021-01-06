/* 动态规划
dp数组定义
dp[i][k][z] 其中 i 表示第 i 天的状态。k 表示最大进行的操作数(买入股票次数)， z 的值为 0 和 1 分别代表未持有股票和持有一支股票
初始条件定义
dp[-1][.][0] = 0; dp[-1][.][1] = -INF
dp[.][0][0] = 0; dp[.][0][1] = -INF
有手续费递推公式
dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1]+prices[i]-fee)
dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0]-prices[i])
本题中 k 最大为 无穷 ，即 dp[i-1][k-1][0] = dp[i-1][k][0]，以及 dp[i-1][k-1][1] = dp[i-1][k][1]
本题递推公式化简为
dp[i][0] = max(dp[i-1][0], dp[i-1][1]+prices[i]-fee)
dp[i][1] = max(dp[i-1][1], dp[i-1][0]-prices[i])
初始条件化简为
dp[-1][0] = 0; dp[-1][1] = -INF
*/
  class Solution {
  public:
      int maxProfit(vector<int>& prices, int fee) {
          vector<vector<int>> dp(prices.size() + 1, vector<int>(2, 0));
          dp[0][0] = 0;
          dp[0][1] = INT_MIN + fee; // 此处 + fee 防止迭代时 int 型溢出
          for (int i = 1; i <= prices.size(); ++i) {
              dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i - 1] - fee);
              dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i - 1]);
          }
          return dp[prices.size()][0];
      }
  };

// 优化内存
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int dp0 = 0, dp1 = INT_MIN + fee;
        for (int i = 0; i < prices.size(); ++i) {
            dp0 = max(dp0, dp1 + prices[i] - fee);
            dp1 = max(dp1, dp0 - prices[i]);
        }
        return dp0;
    }
};