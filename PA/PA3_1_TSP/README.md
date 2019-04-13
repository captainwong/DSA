# [旅行商(TSP)](https://dsa.cs.tsinghua.edu.cn/oj/problem.shtml?id=1147)

## Description

Shrek is a postman working in the mountain, whose routine work is sending mail to n villages. Unfortunately, road between villages is out of repair for long time, such that some road is one-way road. There are even some villages that can’t be reached from any other village. In such a case, we only hope as many villages can receive mails as possible.

Shrek hopes to choose a village A as starting point (He will be air-dropped to this location), then pass by as many villages as possible. Finally, Shrek will arrived at village B. In the travelling process, each villages is only passed by once. You should help Shrek to design the travel route.

## Input

There are 2 integers, n and m, in first line. Stand for number of village and number of road respectively.

In the following m line, m road is given by identity of villages on two terminals. From v1 to v2. The identity of village is in range [1, n].

## Output

Output maximum number of villages Shrek can pass by.

## Example

### Input

```
4 3
1 4
2 4
4 3
```

### Output

```
3
```

## Restrictions

1 <= n <= 1,000,000

0 <= m <= 1,000,000

These is no loop road in the input.

Time: 2 sec

Memory: 256 MB

## Hints

Topological sorting

## 描述

Shrek是一个大山里的邮递员，每天负责给所在地区的n个村庄派发信件。但杯具的是，由于道路狭窄，年久失修，村庄间的道路都只能单向通过，甚至有些村庄无法从任意一个村庄到达。这样我们只能希望尽可能多的村庄可以收到投递的信件。

Shrek希望知道如何选定一个村庄A作为起点（我们将他空投到该村庄），依次经过尽可能多的村庄，路途中的每个村庄都经过仅一次，最终到达终点村庄B，完成整个送信过程。这个任务交给你来完成。

## 输入

第一行包括两个整数n，m，分别表示村庄的个数以及可以通行的道路的数目。

以下共m行，每行用两个整数v1和v2表示一条道路，两个整数分别为道路连接的村庄号，道路的方向为从v1至v2，n个村庄编号为[1, n]。

## 输出

输出一个数字，表示符合条件的最长道路经过的村庄数。

## 样例

见英文题面

## 限制

1 ≤ n ≤ 1,000,000

0 ≤ m ≤ 1,000,000

输入保证道路之间没有形成环

时间：2 sec

空间：256 MB

## 提示

拓扑排序

---

## 解答

目前毫无思路。。。


1. 第一版

    使用数组分别表示上下游的村庄列表，建立道路时，沿着上游追溯，逐代更新上游的长度，并更新最长下游支链，且记录下当前拥有最长支链的村庄。

    但是只能35ac。。。

    Case No. |	Result | Time(ms) | Memory(KB)
    ---------|---------|----------|------------
    1        | Accepted	|84	|121868
    2 | 	Accepted	 | 84	 | 121868
    3	 | Accepted	 | 84	 | 121868
    4	 | Accepted	 | 84 | 	121868
    5	 | Accepted	 | 84 | 	121868
    6	 | Accepted	 | 84 | 	121868
    7	 | Accepted	 | 84 | 	121868
    8	 | Runtime Error (signal 11) | 	80 | 	≥121860
    9	 | Runtime Error (signal 11) | 	76 | 	≥121860
    10	 | Runtime Error (signal 11) | 	76 | 	≥121860
    11	 | Runtime Error (signal 11) | 	76 | 	≥121860
    12	 | Runtime Error (signal 11) | 	76 | 	≥121860
    13	 | Runtime Error (signal 11) | 	76 | 	≥121860
    14	 | Time Limit Exceeded | 	≥2988 | 	121860
    15	 | Runtime Error (signal 11) | 	80 | 	≥121860
    16	 | Runtime Error (signal 11) | 	80 | 	≥121860
    17 | 	Runtime Error (signal 11) | 	76 | 	≥121860
    18	 | Runtime Error (signal 11) | 	76 | 	≥121860
    19	 | Runtime Error (signal 11) | 	80 | 	≥121860
    20	 | Time Limit Exceeded | 	≥2988 | 	121860


2. 第二版

    智商实在捉急啊，没思路啊，郁闷啊，我一绺一绺薅头发啊。。。
    
    参考了[清华OJ：PA2-3 旅行商(TSP)最简解决方案](https://blog.csdn.net/qq_37729102/article/details/83177125)的思路，手写代码，总算100ac。。。

    Case No. |	Result | Time(ms) | Memory(KB)
    ---------|---------|----------|------------
    1 | 	Accepted | 	8 | 	47588
    2 | 	Accepted | 	8 | 	47588
    3 | 	Accepted | 	8 | 	47588
    4 | 	Accepted | 	8 | 	47588
    5 | 	Accepted | 	8 | 	47588
    6 | 	Accepted | 	8 | 	47588
    7 | 	Accepted | 	12 | 	47588
    8 | 	Accepted | 	8 | 	47588
    9 | 	Accepted | 	12 | 	47588
    10 | 	Accepted | 	12 | 	47588
    11 | 	Accepted | 	16 | 	47588
    12 | 	Accepted | 	28 | 	47588
    13 | 	Accepted | 	112 | 	47588
    14 | 	Accepted | 	24 | 	47588
    15 | 	Accepted | 	108 | 	47588
    16 | 	Accepted | 	180 | 	47588
    17 | 	Accepted | 	224 | 	47588
    18 | 	Accepted | 	120 | 	47588
    19 | 	Accepted | 	224 | 	47588
    20 | 	Accepted | 	24 | 	47588

    等有时间了再优化第一版，我感觉还可以抢救一下。。。