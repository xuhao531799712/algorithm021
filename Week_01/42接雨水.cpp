// 42接雨水
// 方法1:使用栈
class Solution {
 public:
  int trap(vector<int>& height) {
    // 用一个栈，递减，遇到大于尾结点的，就弹栈进行计算
    stack<int> stc;
    int cap = 0;
    for (int i = 0; i < height.size(); ++i) {
      while (!stc.empty() &&
             height[stc.top()] <= height[i]) {  // 此处使用 < 和 <= 都可以
        int top = stc.top();
        stc.pop();
        if (stc.empty()) break;
        cap += (min(height[stc.top()], height[i]) - height[top]) *
               (i - stc.top() - 1);
      }
      stc.push(i);
    }
    return cap;
  }
};