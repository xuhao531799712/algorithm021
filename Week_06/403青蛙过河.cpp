 class Solution {
 public:
     bool canCross(vector<int>& stones) {
         // 存 跳到本个石头时，跳了几步，dp[i]是一个vector,即二维dp
         int n = stones.size();
         unordered_map<int, int> mm; // 存石头在的索引以及其在stones中的Index值
         for (int i = 0; i < n; ++i) mm.insert(make_pair(stones[i], i)); // 将
         vector<vector<int>> dp(stones.size(), vector<int>());
         dp[0].push_back(0); // 初始化第一个石头
         for (int i = 0; i < n; ++i) {
             if (dp[i].size() == 0) continue; // 本处石头不可达不代表后面的石头不可以到达
             sort(dp[i].begin(), dp[i].end());
             for (int j = 0; j < dp[i].size(); ++j) {
                 if (j > 0 && dp[i][j] == dp[i][j - 1]) continue;
                 int step = dp[i][j], pos = stones[i];
                 if (mm.count(pos + step - 1)) dp[mm[pos + step - 1]].push_back(step - 1);
                 if (mm.count(pos + step)) dp[mm[pos + step]].push_back(step);
                 if (mm.count(pos + step + 1)) dp[mm[pos + step + 1]].push_back(step + 1);
             }
         }

         return dp[n - 1].size();
     }
 };

class Solution {
public:
    bool canCross(vector<int>& stones) {
        // 存 跳到本个石头时，跳了几步，dp[i]是一个vector,即二维dp
        int n = stones.size();
        unordered_map<int, int> mm; // 存石头在的索引以及其在stones中的Index值
        for (int i = 0; i < n; ++i) mm.insert(make_pair(stones[i], i)); // 将
        vector<set<int>> dp(stones.size(), set<int>());
        dp[0].insert(0); // 初始化第一个石头
        for (int i = 0; i < n; ++i) {
            if (dp[i].size() == 0) continue; // 本处石头不可达不代表后面的石头不可以到达
            for (auto it = dp[i].begin(); it != dp[i].end(); ++it) {
                int step = *it, pos = stones[i];
                if (mm.count(pos + step - 1)) dp[mm[pos + step - 1]].insert(step - 1);
                if (mm.count(pos + step)) dp[mm[pos + step]].insert(step);
                if (mm.count(pos + step + 1)) dp[mm[pos + step + 1]].insert(step + 1);
            }
        }

        return dp[n - 1].size();
    }
};