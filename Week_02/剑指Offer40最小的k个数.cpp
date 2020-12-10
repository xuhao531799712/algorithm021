// 剑指Offer40最小的k个数
class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        priority_queue<int, vector<int>,less<int>> q;
        vector<int> res;
        if (!k) return res;
        for (int i = 0; i < arr.size(); ++i) {
            if (i >= k) {
                if (q.top() > arr[i]) {
                    q.pop();
                    q.push(arr[i]);
                }
            } else {
                q.push(arr[i]);
            }
        }
        while (!q.empty()) {
            res.push_back(q.top());
            q.pop();
        }
        return res;
    }
};