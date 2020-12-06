// 19旋转数组
// 现在想到的两个原地算法，一个是整体翻转再分段翻转，一个是从第一个开始挨个移动元素，原来还有另外一个就是暴力，每次往后移动一位，移动k轮

// 方法一：暴力法，超时，时间复杂度 O(n*k)
class Solution {
 public:
  void rotate(vector<int>& nums, int k) {
    k = k % nums.size();
    for (int i = 0; i < k; ++i) {
      int lastvalue = nums[nums.size() - 1];
      for (int j = nums.size() - 1; j > 0; --j) {
        nums[j] = nums[j - 1];
      }
      nums[0] = lastvalue;
    }
  }
};

// 方法二： 分段翻转
// 里面的helper函数可用库函数reverse代替
class Solution {
 public:
  void rotate(vector<int>& nums, int k) {
    k = k % nums.size();
    helper(nums, 0, nums.size() - 1);
    helper(nums, 0, k - 1);
    helper(nums, k, nums.size() - 1);
  }
  void helper(vector<int>& nums, int start, int end) {
    int times = (end - start + 1) / 2;
    for (int i = 0; i < times; ++i) {
      swap(nums[start++], nums[end--]);
    }
  }
};

// 方法三：逐元素移动
class Solution {
 public:
  void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    k = k % n;
    for (int start = 0, steps = 0; steps < n; ++start) {
      int index = start;
      int tmp = nums[start];
      do {
        int next = (index + k) % n;
        int tmp2 = nums[next];
        nums[next] = tmp;
        index = next;
        tmp = tmp2;
        ++steps;
      } while (index != start);
    }
  }
};
