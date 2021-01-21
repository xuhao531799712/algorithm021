# 第八周笔记

## 位运算

在位运算部分，要记住几个常用公式，它们是位运算进行加速的关键：

```cpp
// 按位与
x & (x-1) // 清零最低位的1
x & -x  // 获得最低位的1,补码是取反后再加1
x & ~x == 0
// 按位异或
x ^ 0 = x
x ^ 1s = ~x
x ^ (~x) = 1s
x ^ x = 0
c = a ^ b => a ^ c = b, b ^ c = a
a ^ b ^ c = a ^ (b ^ c) = (a ^ b) ^ c
// 造一个低n位为 1 高位全为 0 
(1 << n) - 1
```

另外还有几个 c++ 内建的快速位运算的函数：

```cpp
/*
•int __builtin_ffs (unsigned int x)
返回x的最后一位1的是从后向前第几位，比如7368（1110011001000）返回4。
•int __builtin_clz (unsigned int x)
返回前导的0的个数。
•int __builtin_ctz (unsigned int x)
返回后面的0的个数，和__builtin_clz相对。
•int __builtin_popcount (unsigned int x)
返回二进制表示中1的个数。
•int __builtin_parity (unsigned int x)
返回x的奇偶校验位，也就是x的1的个数模2的结果。

此外，这些函数都有相应的usigned long和usigned long long版本，只需要在函数名后面加上l或ll就可以了，比如int __builtin_clzll。
 */
```

## 布隆过滤器

原始数据经过哈希函数的映射后称为了一个个的哈希编码，数据得到压缩。哈希函数是实现哈希表和布隆过滤器的基础。

### 布隆过滤器介绍

    1. 一个很长的二进制向量 （位数组）
    2. 一系列随机函数 (哈希)
    3. 空间效率和查询效率高
    4. 有一定的误判率（而哈希表是精确匹配）

### 原理

假设集合里面有3个元素{x, y, z}，哈希函数的个数为 n。首先将位数组进行初始化，将里面每个位都设置位0。对于集合里面的每一个元素，将元素依次通过 n 个哈希函数进行映射，每次映射都会产生一个哈希值，这个值对应位数组上面的一个点，然后将位数组对应的位置标记为1。查询W元素是否存在集合中的时候，同样的方法将W通过哈希映射到位数组上的 n 个点。如果 n 个点的其中有一个点不为1，则可以判断该元素一定不存在集合中。反之，如果 n 个点都为1，则该元素**可能**存在集合中。

### 布隆过滤器添加元素

- 将要添加的元素给k个哈希函数

- 得到对应于位数组上的k个位置

- 将这k个位置设为1

### 布隆过滤器查询元素

- 将要查询的元素给k个哈希函数

- 得到对应于位数组上的k个位置

- 如果k个位置有一个为0，则肯定不在集合中

- 如果k个位置全部为1，则可能在集合中

### 布隆过滤器应用

- 网页爬虫对URL的去重，避免爬取相同的URL地址；

- 反垃圾邮件，从数十亿个垃圾邮件列表中判断某邮箱是否垃圾邮箱（同理，垃圾短信）；

- 缓存击穿，将已存在的缓存放到布隆中，当黑客访问不存在的缓存时迅速返回避免缓存及DB挂掉。 
  此处是将所有的key放在布隆过滤器中，也就是代表了本布隆过滤器可以直接判断DB中有没有请求的value；
  而缓存中是需要存key-value对的，而且正常的缓存数据是有过期时间的，不全。

- 在 leveldb 中有应用，提升查询未命中的效率。在从磁盘加载数据前，先从布隆过滤器中判断数据是否存在。如果不存在，就直接返回。这样可以减少磁盘访问，提升响应速度。

### 布隆过滤器 C++ 实现

```c++
#include <iostream>
#include <bitset>
#include <cmath>

using namespace std;

typedef unsigned int uint;
const int DEFAULT_SIZE = 1 << 20;
const int seed[] = { 5, 7, 11, 13, 31, 37, 61 };

class BloomFilter {
public:	
    BloomFilter() : hash_func_count(3) {}
    BloomFilter(int bitsize, int str_count) {
        hash_func_count = ceil((bitsize / str_count) * log(2));	
    }
    ~BloomFilter() {}		
    
    uint RSHash(const char *str, int seed);	
    void Add(const char *str);	
    bool LookUp(const char *str);
private:	
    int hash_func_count;	
    bitset<DEFAULT_SIZE> bits;
};

    uint BloomFilter::RSHash(const char *str, int seed) {
        uint base = 63689;
        uint hash = 0;
        
        while (*str) {
            hash = hash * base + (*str++);
            base *= seed;
        }
        
        return (hash & 0x7FFFFFFF);
    }
    
    void BloomFilter::Add(const char* str) {	
        int index = 0;	
        for(int i = 0; i < hash_func_count; ++i) {		
            index = static_cast<int>(RSHash(str, seed[i])) % DEFAULT_SIZE;		
            bits[index] = 1;	
        }		
        return ;
    }
    
    bool BloomFilter::LookUp(const char* str) {	
        int index = 0;	
        for(int i = 0; i < hash_func_count; ++i) {		
            index = static_cast<int>(RSHash(str, seed[i])) % DEFAULT_SIZE;		
            if (!bits[index]) return false;
            return true;
        }
```

### 补充缓存击穿内容

#### 什么是缓存击穿

![avatar](E:\传送\算法训练营笔记\算法训练营作业\第八周\缓存处理流程.png)

在高并发场景下，如果某一个key被高并发访问，没有被命中，出于对容错性考虑，会尝试去从后端数据库中获取，从而导致了大量请求达到数据库，而当该key对应的数据本身就是空的情况下，这就导致数据库中并发的去执行了很多不必要的查询操作，从而导致巨大冲击和压力。

在高并发的场景下，缓存相当于数据库的防火墙，如果用一个肯定不存在的key去访问系统，每次都会绕过缓存去访问数据库，缓存则失去了作用。

#### 解决方法

  1. 缓存空值
     之所以会发生穿透，就是因为缓存中没有存储这些空数据的key。从而导致每次查询都到数据库去。 那么可以为这些key对应的值设置为 null 丢到缓存里面去。后面再出现查询这个key 的请求的时候，直接返回null 。 
     这样，就不用在到数据库中去走一圈了，但是要记得设置过期时间，过期时间可以设置得比其他数据时间短，主要为了抵御短时密集攻击。
     
      缺点：攻击带过来的大量 key 是不存在的，那么这一种方案就会缓存大量不存在key的数据。适用于空数据的key有限的，重复率比较高的场景。
  
  2. 布隆过滤器

## LRU Cache

LRU Cache 的实现一般是用一个**哈希表**加一个**双向链表**来实现，这样可以达到O(1)的查询和修改更新的时间复杂度。

Cache当然越大越好，但是容量不够的情况下就需要进行替换，把不重要的数据从Cache中拿出来空出空间，此处的替换算法有很多
LRU、 LFU、 FIFO、 LIFO等等

### LRU C++ 模板

```c++
struct listnode {
    int key;
    int value;
    listnode* pre;
    listnode* next;
    listnode(int k, int v) : key(k), value(v) {
        pre = next = nullptr;
    }
    listnode(int k, int v, listnode* p, listnode* n) : key(k), value(v), pre(p), next(n) {}
};

class LRUCache {
public:
    LRUCache(int capacity) : cap(capacity), count(0) {
        head->next = tail;
        tail->pre = head;
    }
    
    int get(int key) {
        if (!mm.count(key)) return -1;
        listnode* ptr = mm[key];
        // 移动到头部
        movetohead(ptr);

        return ptr->value;
    }
    
    void put(int key, int value) {
        if (mm.count(key)) {
            listnode* ptr = mm[key];
            ptr->value = value;
            movetohead(ptr);
        } 
        else {
            listnode* cur = new listnode(key, value, head, head->next);
            mm[key] = cur;
            head->next = cur;
            cur->next->pre = cur;
            ++count;

            if (count <= cap) return;
            // 开始删除最后一个结点
            deletelast();
            --count;
        }
    }

private:
    void movetohead(listnode* ptr) {
        ptr->pre->next = ptr->next;
        ptr->next->pre = ptr->pre;
        ptr->next = head->next;
        ptr->next->pre = ptr;
        ptr->pre = head;
        head->next = ptr;
    }

    void deletelast() {
        listnode* last = tail->pre;
        if (last == head) return;
        tail->pre = last->pre;
        last->pre->next = tail;
        mm.erase(last->key);
        delete last;
    }


    int cap;
    int count;
    listnode *head = new listnode(-1, -1); // 存近期刚访问的元素
    listnode *tail = new listnode(-1, -1); // 存最久没访问的元素
    unordered_map<int, listnode*> mm;
};
```

## 排序

### 排序分类

![avatar](E:\传送\算法训练营笔记\算法训练营作业\第八周\排序算法分类.png)

![avatar](E:\传送\算法训练营笔记\算法训练营作业\第八周\排序算法复杂度.png)

_建议阅读：https://www.cnblogs.com/onepixel/p/7674659.html_

十种常见排序算法可以分为两大类：

1. 比较类排序：通过比较来决定元素间的相对次序，由于其时间复杂度不能突破O(nlogn)，因此也称为非线性时间比较类排序。

    包括：冒泡排序、选择排序、插入排序——O(n^2) + O(1)；希尔排序O(n^1.3) + O(1)；归并排序 + O(n)、快速排序 O(logn)递归栈空间、堆排序 + O(1) —— O(nlogn)；

2. 非比较类排序：不通过比较来决定元素间的相对次序，它可以突破基于比较排序的时间下界，以线性时间运行，因此也称为线性时间非比较类排序。

    包括：桶排序、基数排序、计数排序；

非比较类排序的缺点：

1. 只能用于整型的数据类型，不能用于其他数据类型

2. 需要额外的内存空间

稳定概念：

    稳定：如果a原本在b前面，而a=b，排序之后a仍然在b的前面。
    
    不稳定：如果a原本在b的前面，而a=b，排序之后 a 可能会出现在 b 的后面。

### 重点

在排序部分的考察中，时间复杂度为 O(logn) 的几个排序——堆排序、快速排序、归并排序 是考察的重点，要熟悉它们的实现和优缺点。

### 归并排序与快速排序对比

归并排序和快速排序具有相似性但步骤顺序相反：
    
    归并排序先排序左右子数组然后合并两个有序子数组；
    
    快速排序先调配出左右子数组然后对左右子数组进行排序。

### C++ 代码实现

**先总结优先级最高的三个排序算法的代码实现**

#### 归并排序

```cpp
void mergesort(vector<int>& nums, int left = 0, int right = nums.size() - 1) {
    if (right == left) return;
    int mid = left + (right - left) >> 1;
    mergesort(nums, left, mid);
    mergesort(nums, mid + 1, right);
    
    merge(nums, left, mid, right);
}

void merge(vector<int>& nums, int left, int mid, int right) {
    vector<int> tmp(right - left + 1);
    int i = left, j = mid + 1, index = 0;
    while (i <= mid && j <= right) {
        tmp[index++] = nums[i] < nums[j] ? nums[i++] : nums[j++];
    }
    while (i <= mid) tmp[index++] = nums[i++];
    while (j <= right) tmp[index++] = nums[j++];

    for (i = left, index = 0; i <= right;) nums[i++] = tmp[index++];
}
```

注意点：归并排序是三个 O(logn) 排序算法中唯一一个稳定算法，但是代价是每次合并两个有序数组都需要创建相同大小的临时数组，所以空间复杂度最高，为 O(n)

#### 快速排序

```cpp
void quicksort(vector<int>& nums, int left = 0, int right = nums.size() - 1) {
    if (right <= left) return;
    int pivot = nums[left], index = left + 1;
    // index 指向前面出现的最早的一个大于 pivot 的位置，用于交换
    for (int i = left + 1; i <= right; ++i) {
        if (nums[i] < pivot) {
            swap(nums[i], nums[index]);
            ++index;
        }
    }
    swap(nums[left], nums[index - 1]);
    // index - 1 为当前 pivot 在的位置，也就是 partion_position
    
    quicksort(nums, left, index - 2);
    quicksort(nums, index, right);
}
```

快速排序的空间复杂度来源于递归栈，由于递归深度是 logn，所以空间复杂度为 O(logn).

中间的 for 循环部分也常作为一个单独的 partion() 函数单独写出来。

#### 堆排序

```cpp
void heapify(vector<int> &array, int length, int i) {
    // 维护以 i 为 root 的树
    // length 为有效堆长度，i 为当前要处理的索引值 index
    int left = 2 * i + 1, right = 2 * i + 2;
    int largest = i;
    
    if (left < length && array[left] > array[largest]) {
        largest = left;
    }
    if (right < length && array[right] > array[largest]) {
        largest = right;
    }
    
    if (largest != i) {
        swap(array[i], array[largest]);
        heapify(array, length, largest);
    }
}
void heapSort(vector<int> &array) {
    if (array.empty()) return ;
    
    int length = array.size();
    
    // 建堆从底向上
    for (int i = length / 2 - 1; i >= 0; i--)
        heapify(array, length, i);
    
    // 维护从顶向下
    for (int i = length - 1; i >= 0; i--) {
        swap(array[0], array[i]);
        heapify(array, i, 0);
    }
}
```

方法就是建立一个大顶堆，每次从堆顶弹出最大值放到数组最后。

当面试时如果面试官不要求手写建堆代码，则可以直接调用 STL 库中的容器。

```cpp
void heapSort(vector<int> &array) {
    if (array.empty()) return ;
    
    int length = array.size();
    
    priority_queue<int, vector<int>, greater<int> > q;
    
    for (int i = 0; i < length; ++i) q.push(array[i]); 
    // 注意此处是小顶堆，因为 STL 的实现中堆顶在数组尾部
    
    for (int i = 0; i < length; ++i) {
        array[i] = q.top();
        q.pop();
    }
}
```

缺点是空间复杂度变成了 O(n).

**再补充一下另外三个简单排序算法**

#### 冒泡排序

```cpp
void bubbleSort(vector<int> &array) {
    int len = array.size();
    for (int i = 0; i < len; ++i) {
        for (int j = 1; j < len - i; ++j) {
            if (array[j] < array[j - 1]) swap(array[j], array[j - 1]);
        }
    }
}
```

    比较相邻的元素。如果第一个比第二个大，就交换它们两个；
    对每一对相邻元素作同样的工作，从开始第一对到结尾的最后一对，这样在最后的元素应该会是最大的数；

#### 插入排序

```cpp
void insertSort(vector<int> &array) {
    int len = array.size();
    for (int i = 0; i < len; ++i) {
        // i 表示前面的有序部分的 index
        for (int j = i + 1; j > 0; --j) {
            if (array[j - 1] > array[j]) swap(array[j], array[j - 1]);
            else break;
        }
    }
}
```

    它的工作原理是通过构建有序序列，对于未排序数据，在已排序序列中从后向前扫描，找到相应位置并插入。

#### 选择排序

```cpp
void selectSort(vector<int> &array) {
    int len = array.size();
    for (int i = 0; i < len; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < len; ++j) {
            if (array[j] < array[minIndex]) minIndex = j;
        }
        swap(array[i], array[minIndex]);
    }
}
```

    首先在未排序序列中找到最小（大）元素，存放到排序序列的起始位置，然后，再从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾。以此类推，直到所有元素均排序完毕。 

