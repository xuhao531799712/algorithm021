// 26删除排序数组中的重复项
class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    int size = 1;
    for (int pt1 = 1, pt2 = 1; pt2 < nums.size(); ++pt2) {
      if (nums[pt2] != nums[pt2 - 1]) {
        nums[pt1++] = nums[pt2];
        ++size;
      }
    }
    return size;
  }
};