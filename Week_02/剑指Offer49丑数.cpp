// 剑指Offer49丑数
class Solution {
public:
    int nthUglyNumber(int n) {
        // 丑数可以不断入队，但是每次入队要进行排序，小根堆排序
        // 注意int范围不够大，下面的小顶堆和res都要定义成long类型
        priority_queue<long, vector<long>, greater<long>> q;  
        int count = 0;
        vector<int> factor = {2, 3, 5};
        q.push(1);
        long res = 1;
        while (count < n) {
            res = q.top();
            while (!q.empty() && q.top() == res) q.pop(); //不在入队时判断重复，而在出队时判断重复
            ++count;
            for (auto x : factor) {
                q.push(res * x);
            }
        }
        return res;
    }
};