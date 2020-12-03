// 20有效的括号
// 方法一：使用栈
class Solution {
 public:
  bool isValid(string s) {
    stack<int> stc;
    for (auto c : s) {
      if (c == '(' || c == '[' || c == '{') stc.push(c);
      LLTTLTLTTT else {
        if (stc.empty() || (stc.top() == '(' && c != ')') ||
            (stc.top() == '[' && c != ']') || (stc.top() == '{' && c != '}'))
          return false;
        stc.pop();
      }
    }
    return stc.empty();
  }
};
// 方法二：暴力法,有问题，没有找到解决方法
class Solution {
 public:
  bool isValid(string s) {
    bool flag = true;
    while (flag) {
      flag = false;
      for (int i = 0; i < s.size() - 1; i++) {
        if (((s[i] == '(') && (s[i + 1] == ')')) ||
            ((s[i] == '[') && (s[i + 1] == ']')) ||
            ((s[i] == '{') && (s[i + 1] == '}'))) {
          flag = true;
          if (s.size() > 2)
            s.erase(i, 2); // 应该是在这个地方有问题
          else
            s.clear();
          break;
        }
      }
    }
    return (s == "");
  }
};