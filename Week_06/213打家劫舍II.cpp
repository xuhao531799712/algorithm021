class Solution {
public:
    int rob(vector<int>& nums) {
        if (!nums.size()) return 0;
        if (nums.size() == 1) return nums[0];
        if (nums.size() == 2) return max(nums[0], nums[1]);

        vector<int> dp1(nums.size(), 0), dp2(nums.size(), 0);
        
        dp1[0] = nums[0];
        dp1[1] = max(nums[0], nums[1]);
        dp2[1] = nums[1];
        dp2[2] = max(nums[1], nums[2]);
        for (int i = 2; i < nums.size(); ++i) {
            if(i < nums.size() - 1) dp1[i] = max(dp1[i - 1], dp1[i - 2] + nums[i]);
            if(i > 2) dp2[i] = max(dp2[i - 1], dp2[i - 2] + nums[i]);
        }

        return max(dp2[nums.size() - 1], dp1[nums.size() - 2]);
    }
};

//优化内存
class Solution {
public:
    int rob(vector<int>& nums) {
        if (!nums.size()) return 0;
        if (nums.size() == 1) return nums[0];
        if (nums.size() == 2) return max(nums[0], nums[1]);

        int dp10 = nums[0], dp11 = max(nums[0], nums[1]), dp20 = nums[1], dp21 = max(nums[1], nums[2]);

        for (int i = 2; i < nums.size(); ++i) {
            int tmp1 = dp11, tmp2 = dp21;
            if(i < nums.size() - 1) {
                dp11 = max(dp11, dp10 + nums[i]);
                dp10 = tmp1;
            } 
            if(i > 2) {
                dp21 = max(dp21, dp20 + nums[i]);
                dp20 = tmp2;
            }
        }

        return max(dp21, dp11);
    }
};