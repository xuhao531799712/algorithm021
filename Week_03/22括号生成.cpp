// 22括号生成
class Solution {
 public:
  vector<string> generateParenthesis(int n) {
    vector<string> res;
    string str = "";
    int left = n, right = n;
    helper(res, left, right, str);
    return res;
  }

  void helper(vector<string> &res, int left, int right, string &str) {
    if (right == 0) {
      res.push_back(str);
      return;
    }

    if (left > 0) {
      str += "(";
      helper(res, left - 1, right, str);
      str.pop_back();
    }

    if (right > left) {
      str += ")";
      helper(res, left, right - 1, str);
      str.pop_back();
    }
  }
};

// 以上还可以再优化一下速度和内存，因为 str 的长度从一开始就是固定的 2*n，
// 那么就不用再使用 += 和 pop_back 来使效率降低了 可以直接使用索引来加速

class Solution {
 public:
  vector<string> generateParenthesis(int n) {
    vector<string> res;
    string str(2 * n, ' ');
    int left = n, right = n;
    helper(res, left, right, str, n);
    return res;
  }

  void helper(vector<string> &res, int left, int right, string &str, int &n) {
    if (right == 0) {
      res.push_back(str);
      return;
    }

    if (left > 0) {
      str[2 * n - left - right] = '(';
      helper(res, left - 1, right, str, n);
    }

    if (right > left) {
      str[2 * n - left - right] = ')';
      helper(res, left, right - 1, str, n);
    }
  }
};