/// 239滑动窗口最大值
class Solution {
 public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    //使用双端队列，队列总是单调递减的，也就是当前窗口的最大值在队列最左边，队列中存数组的下标
    deque<int> deq;
    vector<int> res(nums.size() - k + 1);
    for (int i = 0; i < k; i++) {
      while (!deq.empty() && nums[i] > nums[deq.back()]) {
        deq.pop_back();
      }
      deq.push_back(i);
      res[0] = nums[deq.front()];
    }
    for (int i = k; i < nums.size(); i++) {
      if (i - deq.front() == k) deq.pop_front();
      while (!deq.empty() && nums[i] > nums[deq.back()]) {
        deq.pop_back();
      }
      deq.push_back(i);
      res[i - k + 1] = nums[deq.front()];
    }
    return res;
  }
};
// 上述方法可以合为一个for循环
class Solution {
 public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    //使用双端队列，队列总是单调递减的，也就是当前窗口的最大值在队列最左边，队列中存数组的下标
    deque<int> deq;
    vector<int> res(nums.size() - k + 1);
    for (int i = 0; i < nums.size(); i++) {
      if (!deq.empty() && i - deq.front() >= k) deq.pop_front();
      while (!deq.empty() && nums[i] > nums[deq.back()]) {
        deq.pop_back();
      }
      deq.push_back(i);
      if (i >= k - 1) res[i - k + 1] = nums[deq.front()];
    }
    return res;
  }
};
// 动态规划解法
class Solution {
 public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    //第一步建立 left 和 right 数组
    int wins = nums.size() - k + 1;
    vector<int> left(nums.size()), right(nums.size()), res(wins);
    for (int i = 0; i < nums.size(); i++) {
      left[i] = nums[i];
      if (i % k != 0) left[i] = max(left[i], left[i - 1]);
    }
    right[nums.size() - 1] = nums[nums.size() - 1];
    // 注意下面 i 的位置从 n - 2 开始，因为最后一个窗口可能是不完整的
    for (int i = nums.size() - 2; i >= 0; i--) {
      right[i] = nums[i];
      if (i % k != k - 1) right[i] = max(right[i], right[i + 1]);
    }
    for (int i = 0; i < wins; i++) {
      res[i] = max(left[i + k - 1], right[i]);
    }
    return res;
  }
};