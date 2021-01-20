// 方法一：常规排序
class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        unordered_map<int, int> mm;
        for (int i = 0; i < arr2.size(); ++i) {
            mm[arr2[i]] = i;
        }
        sort(arr1.begin(), arr1.end(), [&](int &x, int &y) {
            if (mm.count(x) && mm.count(y)) {
                return mm[x] <= mm[y];
            } else if (mm.count(x)) {
                return true;
            } else if (mm.count(y)) {
                return false;
            } else return x <= y;
        });
        return arr1;
    }
};


// 方法二：基数排序
class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        vector<int> fre(1001, 0);
        vector<int> ans(arr1.size());
        for (int i = 0; i < arr1.size(); ++i) {
            ++fre[arr1[i]];
        }
        int ansIndex = 0;
        for (int i = 0; i < arr2.size(); ++i) {
            int inx = arr2[i];
            while (fre[inx] > 0) {
                ans[ansIndex++] = inx;
                --fre[inx];
            }
        }
        for (int i = 0; i <= 1000; ++i) {
            while (fre[i] > 0) {
                ans[ansIndex++] = i;
                --fre[i];
            }
        }
        return ans;
    }
};