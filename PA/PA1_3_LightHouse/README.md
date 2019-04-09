# 灯塔(LightHouse)

## Description

As shown in the following figure, If another lighthouse is in gray area, they can beacon each other.

![img](https://github.com/captainwong/DSA/blob/master/PA/PA1_3_LightHouse/1.png?raw=true)

For example, in following figure, (B, R) is a pair of lighthouse which can beacon each other, while (B, G), (R, G) are NOT.

![img](https://github.com/captainwong/DSA/blob/master/PA/PA1_3_LightHouse/2.png?raw=true)

## Input

1st line: N

2nd ~ (N + 1)th line: each line is X Y, means a lighthouse is on the point (X, Y).

## Output

How many pairs of lighthourses can beacon each other

( For every lighthouses, X coordinates won't be the same , Y coordinates won't be the same )

## Example

### Input

```
3
2 2
4 3
5 1
```

### Output

```
1
```

## Restrictions

For 90% test cases: 1 <= n <= 3 * 10^5

For 95% test cases: 1 <= n <= 10^6

For all test cases: 1 <= n <= 4 * 10^6

For every lighthouses, X coordinates won't be the same , Y coordinates won't be the same.

1 <= x, y <= 10^8

Time: 2 sec

Memory: 256 MB

## Hints

The range of int is usually [-2^31, 2^31 - 1], it may be too small.

## 描述
海上有许多灯塔，为过路船只照明。

![img](https://github.com/captainwong/DSA/blob/master/PA/PA1_3_LightHouse/1.png?raw=true)

（图一）

如图一所示，每个灯塔都配有一盏探照灯，照亮其东北、西南两个对顶的直角区域。探照灯的功率之大，足以覆盖任何距离。灯塔本身是如此之小，可以假定它们不会彼此遮挡。

![img](https://github.com/captainwong/DSA/blob/master/PA/PA1_3_LightHouse/2.png?raw=true)

（图二）

若灯塔A、B均在对方的照亮范围内，则称它们能够照亮彼此。比如在图二的实例中，蓝、红灯塔可照亮彼此，蓝、绿灯塔则不是，红、绿灯塔也不是。

现在，对于任何一组给定的灯塔，请计算出其中有多少对灯塔能够照亮彼此。

## 输入

共n+1行。

第1行为1个整数n，表示灯塔的总数。

第2到n+1行每行包含2个整数x, y，分别表示各灯塔的横、纵坐标。

## 输出

1个整数，表示可照亮彼此的灯塔对的数量。

## 样例

见英文题面

## 限制

对于90%的测例：1 ≤ n ≤ 3×10^5

对于95%的测例：1 ≤ n ≤ 10^6

全部测例：1 ≤ n ≤ 4×10^6

灯塔的坐标x, y是整数，且不同灯塔的x, y坐标均互异

1 ≤ x, y ≤ 10^8

时间：2 sec

内存：256 MB

## 提示

注意机器中整型变量的范围，C/C++中的int类型通常被编译成32位整数，其范围为[-2^31, 2^31 - 1]，不一定足够容纳本题的输出。