// 84柱状图中最大的矩形
// 超时做法：时间复杂度 O(n^2)，优化后的暴力解法
class Solution {
 public:
  int largestRectangleArea(vector<int>& heights) {
    int maxarea = 0;
    for (int i = 0; i < heights.size(); i++) {
      int left = 0, right = 0;
      for (int j = i - 1; j >= 0; j--) {
        if (heights[j] >= heights[i])
          left++;
        else
          break;
      }
      for (int j = i + 1; j < heights.size(); j++) {
        if (heights[j] >= heights[i])
          right++;
        else
          break;
      }
      maxarea = max(maxarea, heights[i] * (left + right + 1));
    }
    return maxarea;
  }
};
// 使用栈，算法复杂度 O(n)
class Solution {
 public:
  int largestRectangleArea(vector<int>& heights) {
    int maxarea = 0;
    stack<int> stc;  //存放下标值
    for (int i = 0; i < heights.size(); i++) {
      while (!stc.empty() && (heights[i] < heights[stc.top()])) {
        // 相等时不需要管，统计任意一个就可以
        int index = stc.top();
        stc.pop();
        int length = i - 1 - (stc.empty() ? -1 : stc.top());
        maxarea = max(maxarea, heights[index] * length);
      }
      stc.push(i);
    }
    while (!stc.empty()) {
      int index = stc.top();
      stc.pop();
      int length = heights.size() - 1 - (stc.empty() ? -1 : stc.top());
      maxarea = max(maxarea, heights[index] * length);
    }
    return maxarea;
  }
};