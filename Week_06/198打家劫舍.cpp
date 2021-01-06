class Solution {
public:
    int rob(vector<int>& nums) {
        if (!nums.size()) return 0;
        if (nums.size() == 1) return nums[0];
        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < nums.size(); ++i) {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        return dp[nums.size() - 1];
    }
};

//优化内存
class Solution {
public:
    int rob(vector<int>& nums) {
        if (!nums.size()) return 0;
        if (nums.size() == 1) return nums[0];
        int dp0 = nums[0], dp1 = max(nums[0], nums[1]);
        for (int i = 2; i < nums.size(); ++i) {
            int tmp = dp1;
            dp1 = max(dp1, dp0 + nums[i]);
            dp0 = tmp;
        }
        return dp1;
    }
};