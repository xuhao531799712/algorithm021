// 155 最小栈
class MinStack {
 public:
  /** initialize your data structure here. */
  MinStack() {
    while (!stc.empty()) stc.pop();
    while (!minstc.empty()) minstc.pop();
  }

  void push(int x) {
    stc.push(x);
    // 此处注意需要判断 minstc.empty() 否则会报运行时错误
    if (minstc.empty() || x <= minstc.top()) minstc.push(x);
  }

  void pop() {
    int x = stc.top();
    stc.pop();
    if (minstc.top() == x) minstc.pop();
  }

  int top() { return stc.top(); }

  int getMin() { return minstc.top(); }
  stack<int> stc;
  stack<int> minstc;
};
// 方法二：使用一个栈来实现，可以一次入栈两个值，也可以一次入栈一个pair
class MinStack {
 public:
  /** initialize your data structure here. */
  MinStack() {
    while (!stc.empty()) stc.pop();
  }

  void push(int x) {
    if (stc.empty()) {
      stc.push(make_pair(x, x));
      return;
    }
    int minv = stc.top().second;
    if (x <= minv)
      stc.push(make_pair(x, x));
    else
      stc.push(make_pair(x, minv));
  }

  void pop() { stc.pop(); }

  int top() { return stc.top().first; }

  int getMin() { return stc.top().second; }
  stack<pair<int, int>> stc;
};