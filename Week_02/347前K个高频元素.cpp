// 347前K个高频元素
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // 使用小顶堆实现
        unordered_map<int, int> m;
        for (auto num : nums) ++m[num];

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
        for (auto mm :m) {
            q.push(make_pair(mm.second, mm.first));
            if (q.size() > k) q.pop();
        }

        vector<int> res;
        // 优先队列没有定义顺序访问方法，所有不可以用for auto来遍历
        while (!q.empty()) {
            res.push_back(q.top().second);
            q.pop();
        }
        return res;
    }
};