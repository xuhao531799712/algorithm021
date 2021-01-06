// 此题未发现动态规划解法，下满使用的贪心算法
// https://leetcode-cn.com/problems/task-scheduler/solution/tong-zi-by-popopop/
// 参照以上题解链接
// 自己还需多温习加深理解
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        int len = tasks.size();
        vector<int> nn(26, 0);
        for(char task : tasks) nn[task - 'A']++;
        sort(nn.begin(), nn.end(), [](int &a, int &b) -> bool {return a > b;});//降序排列
        int firstmax = nn[0];
        int time = (n + 1) * (firstmax - 1);
        for(int x  : nn) {
            if(x - firstmax + 1 > 0) time++;
            else break;
        }
        return time > len ? time : len;
    }
};

//基本信息中的姓名拼音内容错误.;中/英文封面没做书签,请参见“常见问题解答”.;给目录页做一个书签,请参见“常见问题解答”.