// 283.爬梯子题目
class Solution {
 public:
  void moveZeroes(vector<int>& nums) {
    // mothed 1: 重新复制一个数组，将非零元素复制进去
    // vector<int> res(nums.size(), 0);
    // int index = 0;
    // for(auto x:nums) {
    //     if (x != 0) res[index++] = x;
    // }
    // nums = res;

    // mothed 2: 移动交换
    // int left = 0, right = 0;
    // while(right < nums.size()) {
    //     if(nums[right] != 0) {
    //         swap(nums[right], nums[left]);
    //         left++;
    //     }
    //     right++;
    // }
    // 对以上进行优化和化简,使用for替换while，并用后缀++来合并其他操作与++操作
    for (int right = 0, left = 0; right < nums.size(); right++) {
      if (nums[right]) {
        swap(nums[right], nums[left++]);
      }
    }
  }
};