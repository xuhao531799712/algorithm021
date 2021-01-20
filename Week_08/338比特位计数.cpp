// 方法一
// 举例，比如 5 : 0b101 这个数 它就是 2 : 0b10 左移一位加了一个1
//          4 : 0b100 这个数 它就是 2 : 0b10 左移一位加了一个0
// 所以每个数的比特位中 1 的个数可以由其右移一位的数的个数推得出来
// 递推方程为 dp[i] = dp[i>>1] + (i & 1)
class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> res(num + 1, 0);
        for (int i = 1; i <= num; ++i) {
            res[i] = res[i >> 1] + (i & 1);
        }
        return res;
    }
};

// 方法二
// 举例，比如 5 : 0b101 这个数 它相当于去掉最后一个 1 后的 4 : 0b100 加 1 的结果
// 所以每个数的比特位中 1 的个数可以由其去掉最后一个一后的数的个数 +1 推得出来
// 递推方程为 dp[i] = dp[i&(i-1)] + 1
class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> res(num + 1, 0);
        for (int i = 1; i <= num; ++i) {
            res[i] = res[i & (i - 1)] + 1;
        }
        return res;
    }
};