class DisjointSetUnion {
public:
    DisjointSetUnion(int size) {
        vec.resize(size);
        for (int i = 0; i < size; ++i) vec[i] = i;
    }

    void unionpair(int i, int j) {
        int fa_i = findfather(i);
        int fa_j = findfather(j);
        vec[fa_j] = fa_i;
    }

    int findfather (int i) {
        while (vec[i] != i) {
            vec[i] = vec[vec[i]];
            i = vec[i];
        }
        return i;
    }

private:
    vector<int> vec;
};


class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int n = s.size();
        DisjointSetUnion uni(n);
        for (auto pair : pairs) {
            uni.unionpair(pair[0], pair[1]);
        }
        unordered_map<int, vector<int>> mm;
        for (int i = 0; i < n; ++i) {
            mm[uni.findfather(i)].push_back(s[i]);
        }
        for (auto& pair : mm) { // 注意此处一定要用引用传递，不然没法改变源数组
            sort(pair.second.begin(), pair.second.end(), greater<int>()); // 降序排列，方便从尾部进行弹出
        }
        for (int i = 0; i < n; ++i) {
            int x = uni.findfather(i);
            s[i] = mm[x].back();
            mm[x].pop_back();
        }
        return s;
    }
};