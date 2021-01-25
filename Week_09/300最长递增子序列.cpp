// 动态规划 时间复杂度O(n) 空间复杂度O(n)
// 状态定义 dp[i] 表示以 nums[i] 结尾的最长严格递增子序列的长度
 class Solution {
 public:
     int lengthOfLIS(vector<int>& nums) {
         int n = nums.size();
         int res = 0;
         vector<int> dp(n, 1);
         for (int i = 0; i < n; ++i) {
             for (int j = i - 1; j >= 0; --j) {
                 if (nums[j] < nums[i]) dp[i] = max(dp[j] + 1, dp[i]);
             }
             res = max(res, dp[i]);
         }
         return res;
     }
 };

// 要使时间复杂度为 O(n log(n))，首先外层遍历一定是 O(n)，这时候需要把动态规划处理每个元素时的 O(n) 改为 O(log(n))
// 这样想到要用二分法
// 维护一个数组 dp[i]，表示长度为 i 的最长上升子序列的末尾元素的最小值
// dp[i]是一个单调递增的数组，证明：
//      因为如果 dp[j]  dp[i]≥dp[i] 且 j < i，考虑从长度为 i 的最长上升子序列的末尾删除 i-j 个元素，那么这个序列长度变为 j ，且第 j 个元素 x（末尾元素）必然小于 dp[i]，也就小于 dp[j]。
//      那么我们就找到了一个长度为 j 的最长上升子序列，并且末尾元素比 dp[j] 小，从而产生了矛盾。因此数组 dp[] 的单调性得证。
// 外层遍历数组的每个元素，在内部进行二分查找，找到dp[i] < nums[j] 的情况下的最大 i，然后判断 dp[i+1] 与 nums[j] 的大小并更新 res 和 dp[i+1]
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        int res = 0;
        vector<int> dp(n, INT_MAX);
        dp[0] = nums[0]; // dp[0] 表示长度为 1 的子序列
        for (int i = 0; i < n; ++i) {
            int left = 0, right = res;
            if (dp[left] >= nums[i]) {
                // dp[] 内没有小于 nums[i] 的值。直接修改 dp[0]
                dp[left] = nums[i];
                continue;
            }
            while (left < right) {
                // 找到小于 nums[i] 的最大值
                int mid = left + ((right - left + 1) >> 1); // 此处尤其注意，使用 >> 写法时，一定要套括号，因为 >> 优先级很低
                if (dp[mid] >= nums[i]) right = mid - 1;
                else left = mid;
            }
            // 此时 left + 1 为要进行判断的位置
            dp[left + 1] = min(dp[left + 1], nums[i]);
            res = max(res, left + 1);
        }
        return res + 1;
    }
};