class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // 得出以每个元素为结尾的子数组的最大和，然后再留存全局最大
        // dp[n] = max(dp[n - 1], 0) + nums[n]
        int maxValue = nums[0];
        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            dp[i] = max(dp[i - 1], 0) + nums[i];
            maxValue = max(maxValue, dp[i]);
        } 
        return maxValue;
    }
};