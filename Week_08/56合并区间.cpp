class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> ans;
        cout<<1<<endl;
        if (intervals.size() == 0) return ans;
        sort(intervals.begin(), intervals.end(), [&](vector<int>& a, vector<int>& b) {
            return a[0] < b[0]; // 此处必须是 < 不能是 <= 不然会出错 原因未知
        });
        cout<<1<<endl;
        int left = intervals[0][0], right = intervals[0][1];
        for (auto interval : intervals) {
            if (right >= interval[0]) {
                // 有重叠
                right = max(right, interval[1]);
            } else {
                ans.push_back({left, right});
                left = interval[0];
                right = interval[1];
            }
        }
        ans.push_back({left, right});
        return ans;
    }
};