// 使用两个哈希表对 s 和 t 中的字符建立一一映射关系
class Solution{
        public:
        bool isIsomorphic(string s, string t) {
            unordered_map<char, char> smap, tmap;
            int n = s.size();
            for (int i = 0; i < n; ++i) {
                if (!smap.count(s[i])) {
                    smap[s[i]] = t[i];
                } else if (smap[s[i]] != t[i]) return false;

                if (!tmap.count(t[i])) {
                    tmap[t[i]] = s[i];
                } else if (tmap[t[i]] != s[i]) return false;
            }
            return true;
        }
};

// 使用数组代替哈希表来优化速度与内存
class Solution{
        public:
        bool isIsomorphic(string s, string t) {
            vector<char>
            smap(128, -1), tmap(128, -1);
            int n = s.size();
            for (int i = 0; i < n; ++i) {
                if (smap[s[i]] == -1) {
                    smap[s[i]] = t[i];
                } else if (smap[s[i]] != t[i]) return false;

                if (tmap[t[i]] == -1) {
                    tmap[t[i]] = s[i];
                } else if (tmap[t[i]] != s[i]) return false;
            }
            return true;
        }
};