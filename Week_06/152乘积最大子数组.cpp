class Solution {
public:
    int maxProduct(vector<int>& nums) {
        // 得出以每个元素为结尾的子数组的最大积和最小积，然后再留存全局最大
        // 也是采用升维的思想，来保存更多信息
        // dp[n][0] = max(dp[n - 1][0]* nums[n], dp[n - 1][1]* nums[n], nums[n]) // 存大值
        // dp[n][1] = min(dp[n - 1][0]* nums[n], dp[n - 1][1]* nums[n], nums[n]) // 存小值
        vector<vector<int>> dp(nums.size(), vector<int>(2,0));
        int maxValue = dp[0][0] = dp[0][1] = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            dp[i][0] = max(max(dp[i - 1][0] * nums[i], dp[i - 1][1] * nums[i]), nums[i]);
            dp[i][1] = min(min(dp[i - 1][0] * nums[i], dp[i - 1][1] * nums[i]), nums[i]);
            maxValue = max(maxValue, dp[i][0]);
        }
        return maxValue;
    }
};