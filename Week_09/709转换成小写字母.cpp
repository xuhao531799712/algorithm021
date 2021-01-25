class Solution {
public:
    string toLowerCase(string str) {
        int dif = 'A' - 'a';
        for (auto &c : str) {
            if (c >= 'A' && c <= 'Z') {
                c -= dif;
            }
        }
        return str;
    }
};