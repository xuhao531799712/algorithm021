/* 动态规划
dp数组定义
dp[i][k][z] 其中 i 表示第 i 天的状态。k 表示最大进行的操作数(买入股票次数)， z 的值为 0 和 1 分别代表未持有股票和持有一支股票
初始条件定义
dp[-1][.][0] = 0; dp[-1][.][1] = -INF
dp[.][0][0] = 0; dp[.][0][1] = -INF
递推公式
dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1]+prices[i])
dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0]-prices[i])
*/
  class Solution {
  public:
      int maxProfit(vector<int>& prices) {
          int kmax = 2;
          vector<vector<vector<int>>> dp(prices.size() + 1, vector<vector<int>>(kmax + 1, vector<int>(2, 0)));
          for (int k = 0; k <= kmax; ++k) {
              dp[0][k][0] = 0;
              dp[0][k][1] = INT_MIN;
          }
          for (int i = 0; i <= prices.size(); ++i) {
              dp[i][0][0] = 0;
              dp[i][0][1] = INT_MIN;
          }
          for (int i = 1; i <= prices.size(); ++i) {
              for (int k = 1; k <= kmax; ++k) {
                  dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1]+prices[i - 1]);
                  dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0]-prices[i - 1]);
              }
          }
          return dp[prices.size()][kmax][0];
      }
  };

// 优化内存
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int kmax = 2;
        vector<vector<int>> dp(kmax + 1, vector<int>(2, 0));
        for (int k = 0; k <= kmax; ++k) {
            dp[k][0] = 0;
            dp[k][1] = INT_MIN;
        }
        for (int i = 1; i <= prices.size(); ++i) {
            for (int k = 1; k <= kmax; ++k) {
                dp[k][0] = max(dp[k][0], dp[k][1]+prices[i - 1]);
                dp[k][1] = max(dp[k][1], dp[k-1][0]-prices[i - 1]);
            }
        }
        return dp[kmax][0];
    }
};