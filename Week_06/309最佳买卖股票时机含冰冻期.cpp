/* 动态规划
dp数组定义
dp[i][k][z] 其中 i 表示第 i 天的状态。k 表示最大进行的操作数(买入股票次数)， z 的值为 0 和 1 分别代表未持有股票和持有一支股票
初始条件定义
dp[-1][.][0] = 0; dp[-1][.][1] = -INF
dp[.][0][0] = 0; dp[.][0][1] = -INF
无冷却期递推公式
dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1]+prices[i])
dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0]-prices[i])
本题有冷却期，所以递推公式改为
dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1]+prices[i])
dp[i][k][1] = max(dp[i-1][k][1], dp[i-2][k-1][0]-prices[i]) // 后一项改为 i-2, 因为此时 i-1 天必须为冷却期无操作
本题中 k 最大为 无穷 ，即 dp[i-1][k-1][0] = dp[i-1][k][0]，以及 dp[i-1][k-1][1] = dp[i-1][k][1]
本题递推公式化简为
dp[i][0] = max(dp[i-1][0], dp[i-1][1]+prices[i])
dp[i][1] = max(dp[i-1][1], dp[i-2][0]-prices[i])
初始条件化简为
dp[-1][0] = 0; dp[-1][1] = -INF
*/
  class Solution {
  public:
      int maxProfit(vector<int>& prices) {
          if (prices.size() <= 0) return 0;
          vector<vector<int>> dp(prices.size() + 1, vector<int>(2, 0));
          dp[0][0] = 0;
          dp[0][1] = INT_MIN;
          dp[1][0] = 0;
          dp[1][1] = -prices[0];
          for (int i = 2; i <= prices.size(); ++i) {
              // 循环从2开始
              dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i - 1]);
              dp[i][1] = max(dp[i - 1][1], dp[i - 2][0] - prices[i - 1]);
          }
          return dp[prices.size()][0];
      }
  };

// 优化内存
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() <= 0) return 0;
        vector<vector<int>> dp(3, vector<int>(2, 0));
        dp[0][0] = 0;
        dp[0][1] = INT_MIN;
        dp[1][0] = 0;
        dp[1][1] = -prices[0];
        for (int i = 0; i < prices.size(); ++i) {
            dp[2][0] = max(dp[1][0], dp[1][1] + prices[i]);
            dp[2][1] = max(dp[1][1], dp[0][0] - prices[i]);
            dp[0][0] = dp[1][0];
            dp[0][1] = dp[1][1];
            dp[1][0] = dp[2][0];
            dp[1][1] = dp[2][1];
        }
        return dp[2][0];
    }
};