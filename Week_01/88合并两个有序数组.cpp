// 88合并两个有序数组
class Solution {
 public:
  void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    // 从最后开始，避免覆盖
    int end = m + n - 1;
    int index1 = m - 1, index2 = n - 1;
    while (index1 >= 0 && index2 >= 0) {
      if (nums2[index2] > nums1[index1])
        nums1[end--] = nums2[index2--];
      else
        nums1[end--] = nums1[index1--];
    }
    if (index1 < 0) {
      while (index2 >= 0) nums1[end--] = nums2[index2--];
    }
  }
};

// 对以上进行优化
class Solution {
 public:
  void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    // 从最后开始，避免覆盖
    for (int end = m + n - 1, index1 = m - 1, index2 = n - 1; index2 >= 0;
         --end) {
      if (index1 >= 0 && nums2[index2] <= nums1[index1])
        nums1[end] = nums1[index1--];
      else
        nums1[end] = nums2[index2--];
    }
  }
};