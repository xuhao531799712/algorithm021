# 第九周笔记

## 不同路径2 题目的状态转移方程

>状态转移方程:
> 1. 如果 obstacleGrid[i, j] = 0, 那么 dp[i, j] = 0
> 2. 如果 obstacleGrid[i, j] != 0, 那么 dp[i, j] = dp[i - 1, j] + dp[i, j - 1]