// class Solution {
// public:
//     int coinChange(vector<int>& coins, int amount) {
//         vector<int> dp(amount + 1, -1);
//         dp[0] = 0;
//         for (int i = 1; i <= amount; ++i) {
//             for (int j = 0; j < coins.size(); ++j) {
//                 if (i < coins[j] || dp[i - coins[j]] < 0) continue;
//                 if(dp[i] >= 0) dp[i] = min(dp[i], dp[i - coins[j]] + 1);
//                 else dp[i] = dp[i - coins[j]] + 1;
//             }
//         }
//         return dp[amount];
//     }
// };

// 本质是棵决策树
// 1. 暴力解(dfs) + 剪枝， 并按贪心的算法。来进行剪枝
// 2. bfs，查找到第一次兑换成功的
// 3. dfs + memo
// 4. 动态规划

// 交换一下里外循环，则 i 就可以直接从 符合要求的地方开始，节省时间
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> counts(amount+1,-1);
        counts[0]=0;
        for(auto coin:coins)
        {
            for(int i=coin;i<=amount;i++)
            {
                if(counts[i-coin]==-1) continue;
                if(counts[i]==-1) counts[i]=counts[i-coin]+1;
                else counts[i]=min(counts[i-coin]+1,counts[i]);
            }
        }
        return counts[amount];
    }
};