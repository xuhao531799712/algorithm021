// 左右指针
class Solution {
public:
    bool isPalindrome(string s) {
        for (int left = 0, right = s.size() - 1; left < right; left++, right--) {
            while (left < right && !(isalpha(s[left]) || isdigit(s[left]))) left++;
            while (left < right && !(isalpha(s[right]) || isdigit(s[right]))) right--;
            if (left == right) break;
            if (tolower(s[left]) != tolower(s[right])) return false;
        }
        return true;
    }
};