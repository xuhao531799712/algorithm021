// 剑指Offer49丑数

// 优先队列做法
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

//先想到的就是下面这个方法，跟我本科时候做的一个题差不多，但这种做法超时了
class Solution {
public:
    int nthUglyNumber(int n) {
        unordered_map<int, bool> uglynum;
        uglynum[1]=true;
        int count=0;
        for(int i=1;i>0;i++)
        {
            if(uglynum.find(i)!=uglynum.end())
            {
                count++;
                if(count==n) return i;
                uglynum[i*2]=true;
                uglynum[i*3]=true;
                uglynum[i*5]=true;
            }
        }
        return 0;
    }
};
//之所以用一个从一开始的for循环就是想保持从小到达的排列，但这样浪费了大量的时间在不是丑数的数上面
//而要只用现有的丑数推出下一个最小的丑数是问题的关键，可以实现这一步就可以一直只由当前最小丑数推出下一个最小丑数
//题解里的三指针方法就是完成这一步。设定三个指针，一个指向要做×2的数，一个指向要做×3的数，最后一个指向要做×5的数
//三个指针的移动速度是不一样的，很明显×2的会移动得最快，×5的移动得最慢
class Solution {
public:
    int nthUglyNumber(int n) {
        int uglynum[n];
        uglynum[0]=1;
        int mul2=0,mul3=0,mul5=0;
        for(int i=1;i<n;i++)
        {
            uglynum[i]=min(min(uglynum[mul2]*2, uglynum[mul3]*3), uglynum[mul5]*5);
            if(uglynum[i]==uglynum[mul2]*2) mul2++;
            if(uglynum[i]==uglynum[mul3]*3) mul3++;
            if(uglynum[i]==uglynum[mul5]*5) mul5++; //此处可能有重复的地方，比如2*3等于3*2,如果用if-else的语句，6会算作两次
        }
        return uglynum[n-1];
    }
};