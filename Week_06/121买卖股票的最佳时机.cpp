// 动态规划
// 状态定义，dp[i] 为第i天卖出股票获得的最大值，注意是一定在 i 天卖出
// 递推方程：dp[i] = dp[i-1] + (prices[i] - prices[i-1])  计算过后 if (dp[i] < 0) dp[i] = 0;
// 递推方程解释， dp[i-1] 为 i-1 天卖出股票获得的最大值，则计算 dp[i] 要先把 i-1 天卖股票的差值先补上，才能再卖
// 递推方程解释，如果经过计算得到 dp[i] < 0，则说明 prices[i] 值小于之前的购入值，则不管怎么卖，今天卖出都会亏本，今天只能购入

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int maxpro = 0;
        vector<int> dp(prices.size(), 0);
        for (int i = 1; i < prices.size(); ++i) {
            dp[i] = dp[i - 1] + prices[i] - prices[i - 1];
            if (dp[i] < 0) dp[i] = 0;
            maxpro = max(maxpro, dp[i]);
        }
        return maxpro;
    }
};

// 优化内存
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int maxpro = 0;
        int dp = 0;
        for (int i = 1; i < prices.size(); ++i) {
            dp = dp + prices[i] - prices[i - 1];
            if (dp < 0) dp = 0;
            maxpro = max(maxpro, dp);
        }
        return maxpro;
    }
};

// 贪心思想：在第 i 天前的最小值和今天的值做运算可以得到今天的最大收益
// 维护遍历过程中的最小值，以及当前最小值后面的最大差值
// 得到的代码和优化内存后的动态规划相似
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int min = INT_MAX;
        int res = 0;
        for (auto price : prices) {
            if (price < min) min = price;
            else res = max(res, price - min);
        }
        return res;
    }
};


/* 接下来按照股票问题的通性进行重新动态规划设计和解题
dp数组定义
dp[i][k][z] 其中 i 表示第 i 天的状态。k 表示最大进行的操作数(买入股票次数)， z 的值为 0 和 1 分别代表未持有股票和持有一支股票
初始条件定义
dp[-1][.][0] = 0; dp[-1][.][1] = -INF
dp[.][0][0] = 0; dp[.][0][1] = -INF
递推公式
dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1]+prices[i])
dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0]-prices[i])
本题中 k 最大为 1 ，即 dp[i-1][k-1][0] = 0 为常值
本题递推公式化简为
dp[i][0] = max(dp[i-1][0], dp[i-1][1]+prices[i])
dp[i][1] = max(dp[i-1][1], -prices[i])
初始条件化简为
dp[-1][0] = 0; dp[-1][1] = -INF
*/


 class Solution {
 public:
     int maxProfit(vector<int>& prices) {
         vector<vector<int>> dp(prices.size() + 1, vector<int>(2, 0));
         dp[0][0] = 0;
         dp[0][1] = INT_MIN;
         for (int i = 1; i <= prices.size(); ++i) {
             dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i - 1]);
             dp[i][1] = max(dp[i - 1][1], -prices[i - 1]);
         }
         return dp[prices.size()][0];
     }
 };


// 进行内存优化
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int dp0 = 0, dp1 = INT_MIN;
        for (int i = 0; i < prices.size(); ++i) {
            dp0 = max(dp0, dp1 + prices[i]);
            dp1 = max(dp1, -prices[i]);
        }
        return dp0;
    }
};