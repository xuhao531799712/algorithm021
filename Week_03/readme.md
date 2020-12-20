## 第四课笔记
### 递归的逻辑与伪代码
```cpp
 void recursion(int level, int param) {
     // 1. 设定递归终止条件
    if (level > MAX_LEVEL) {
        // 执行终止逻辑
        return ;
    }

    // 2.本层处理逻辑
    process(level, param);

    // 3.递归至下一层
    recursion(level + 1, param);

    // 4.清理本层状态(可选)
    // 特别应用在回溯中

 }
```
递归是一种编程元素。而分治和回溯是编程算法，其使用的元素或者说手段是递归。
### 回溯
回溯使用的就是上面的标准递归模板。
其思想是采用试错的思想，去一步一步地尝试各个解法方法，在某一个方法失败后会回退（就需要清理状态）后继续尝试其他算法，知道找到解决方法或者遍历完所有可能的途径。
注意，在最坏的情况下，回溯法会导致一次复杂度为指数时间的计算。

## 分治
而分治使用的是稍微复杂的递归模板。
和最简单的递归模板不同之处在于，在其模板里有一个步骤是拆分问题成子问题，再对子问题进行分别调用递归，然后将子结果组合成最后问题的结果。
也就是多了一步拆分和组合的步骤。
```cpp
 int divide_conquer(Problem *problem, int params) {
     // 1. 设定递归终止条件
    if (problem == nullptr) {
        // 执行终止逻辑
        process_sult
        return return_result;
    }

    // 2.本层处理逻辑 + 3. 递归至下一层
    subproblems = split_problem(problem, data);
    subresult1 = divide_conquer(subproblems[0], p1);
    subresult2 = divide_conquer(subproblems[1], p2);
    subresult3 = divide_conquer(subproblems[2], p3);
    ...

    // 合并结果
    result = process_result(subresult1, subresult2, subresult3, ...);

    // 4.清理本层状态(可选)
    
    return 0 or result;

 }
```

# 本课总结
使用递归、回溯、分治的最核心思想是找问题的重复性。
找最近的重复性或者最优的重复性（即动态规划）。
找到问题的重复性后就可以把重复性的事情交给计算机去做。

## 注意事项补充
递归会不断进行压栈和出栈操作，每次进行函数跳转都会有各种寄存器的切换，这在当前的计算机中不算什么问题。
不过面试过程中面试官很有可能会提出用迭代代替递归来人为控制递归多出的一点代价，那么这时候要使用队列或者栈手动的进行循环操作来完成任务。
任何用到递归的地方都可以想一下如何用迭代实现。

另外，dfs是靠栈实现，bfs是靠队列实现，不过在实现dfs的时候使用函数栈编程更加方便，手动用栈编程会稍微麻烦一些。