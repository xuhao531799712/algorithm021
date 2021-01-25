class Solution {
public:
    int myAtoi(string s) {
        int index = 0;
        int signe = 1;
        long res = 0;
        while (s[index] == ' ') ++index;
        if (s[index] == '+' || s[index] == '-') {
            signe = (s[index] == '+'? 1 : -1);
            ++index;
        } else {
            signe = 1;
        }
        for ( ; index < s.size(); ++index) {
            int x = s[index] - '0';
            if (x > 9 || x < 0) break;
            res = res * 10 + x;
            if (res * signe > 2147483647) return 2147483647;
            else if (res * signe < -2147483648) return -2147483648;
        }
        return res * signe;
    }
};