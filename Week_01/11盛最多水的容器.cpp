// 11题盛最多水的容器
class Solution {
 public:
  int maxArea(vector<int>& height) {
    int maxarea = 0;
    for (int left = 0, right = height.size() - 1; left < right;) {
      int minheight =
          height[left] > height[right] ? height[right--] : height[left++];
      maxarea = max(maxarea, minheight * (right - left + 1));
    }
    return maxarea;
  }
};