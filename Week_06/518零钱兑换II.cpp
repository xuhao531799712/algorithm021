// class Solution {
// public:
//     int change(int amount, vector<int>& coins) {
//         vector<int> dp(amount + 1, 0);
//         dp[0] = 1;
//         for (int i = 1; i <= amount; ++i) {
//             for (auto coin : coins) {
//                 if (i >= coin) dp[i] += dp[i - coin];
//             }
//         }
//         return dp[amount];
//     }
// };

// 以上的做法是错误的，是因为包含了重复举例，比如 1 2 2 的序列在计算 amount=5 的时候中会算做多次, 1 2 2 , 2 1 2， 2 2 1 等
// 把硬币放在外循环，就相当于给序列中硬币的出现次数排了序，先 1 后 2 那么序列中所有的 1 都会出现在 2 前面。

// 定义状态 dp[i] 表示可以用硬币凑成总金额为 i 的方式数目
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;
        for (auto coin : coins) {
            for (int i = 1; i <= amount; ++i) {
                if (i >= coin) dp[i] += dp[i - coin];
            }
        }
        return dp[amount];
    }
};