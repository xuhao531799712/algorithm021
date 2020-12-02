// 66.加一
class Solution {
 public:
  vector<int> plusOne(vector<int>& digits) {
    bool carry = true;
    for (int i = digits.size() - 1; i >= 0; i--) {
      if (carry) {
        if (digits[i] == 9) {
          digits[i] = 0;
          carry = true;
        } else {
          digits[i]++;
          carry = false;
        }
      } else {
        break;
      }
    }
    if (carry) {
      vector<int> res(digits.size() + 1, 0);
      res[0] = 1;
      return res;
    }
    return digits;
  }
};
// 实际可以不通过carry来判断是否继续，判断末尾位就可以
class Solution {
 public:
  vector<int> plusOne(vector<int>& digits) {
    for (int i = digits.size() - 1; i >= 0; i--) {
      digits[i]++;
      if (digits[i] == 10) {
        digits[i] = 0;
      } else {
        return digits;
      }
    }
    vector<int> res(digits.size() + 1, 0);
    res[0] = 1;
    return res;
  }
};