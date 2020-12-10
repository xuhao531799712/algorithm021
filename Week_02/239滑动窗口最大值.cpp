// 239滑动窗口最大值
// 大顶堆实现
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        // 大顶堆
        int count = nums.size() - k + 1;
        vector<int> res(count);
        priority_queue<pair<int, int>, vector<pair<int, int>>, less<pair<int, int>>> q; // first放值的大小，second放index

        for (int i = 0; i < nums.size(); ++i) {
            q.push(make_pair(nums[i], i));
            while (i - q.top().second >= k) q.pop();
            if (i >= k - 1) res[i - k + 1] = q.top().first;  
        }
        return res;
    }
};