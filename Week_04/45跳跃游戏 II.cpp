// 方法一： 超时做法，动态规划
class Solution {
public:
    int jump(vector<int>& nums) {
        vector<int> dp(nums.size(), INT_MAX);
        dp[0] = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (dp[i] == INT_MAX) continue; // 本位置不可达
            for (int j = 1; j <= nums[i]; ++j) {
                if (i + j >= nums.size()) break;
                dp[i + j] = min(dp[i + j], dp[i] + 1);
            }
        }
        return dp[nums.size() - 1];
    }
};
// 时间复杂度 O(n^2) 空间复杂度 O(n)
// 以上的dp做法就像课程说的那样，记录了过程中每一个步骤的值，实际上计算出了到达所有位置的最小步数
// 但本题只需要计算最后一个位置，所以使用此dp做法复杂度偏高
// 用贪心算法，每次只记录一个对跳到最后位置最快的值就可以了，这样就只得到了跳到最后位置的最短路径中的各个途经点它们分别的最短路径长度，省略了其他无关点

// 贪心做法
class Solution {
public:
    int jump(vector<int>& nums) {
        int farest = 0;
        int count = 0;
        int end = 0, start = 0;
        while (end < nums.size() - 1) {
            for (int i = start; i <= end; ++i) {
                farest = max(farest, i + nums[i]);
            }
            start = end + 1;
            end = farest;
            count++;
        }
        return count;
    }
};
// 时间复杂度 O(n) 空间复杂度 O(1)
// 将代码优化一下变得更简洁
class Solution {
public:
    int jump(vector<int>& nums) {
        int farest = 0, count = 0, end = 0;
        for (int i = 0; i < nums.size() - 1; ++i) {
            farest = max(farest, i + nums[i]);
            if (i == end) {
                end = farest;
                count++;
            }
        }
        return count;
    }
};