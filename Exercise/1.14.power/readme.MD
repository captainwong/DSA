# [1.14] 


## 2^n 迭代版理解

教材上给出的推导过程，看了n久看不懂，我这个智力就到这了。。。

一直看一直看一直看，终于有一天5环TMD修到了7环！懂了。。。

```c++
__int64 power2_I(int n)
{
	__int64 pow = 1;
	__int64 p = 2;

	while (n) {
		if (n & 1) { pow *= p; }
		n >>= 1;
		p *= p;
	}

	return pow;
}
```

代码如是，理解起来可真要我老命。

以 `2^10` 为例，

    10 = b(1010)

    2^10 = (2^(2^3))^1 * (2^(2^2))^0 * (2^(2^1))^1 * (2^(2^0))^0

    假设计算 2^n， n有k个比特位，f(k)表示数字n的第k个字节的值（1或0），对本例n=10, k=4，则

    2^n = (2^(2^k))^f(k) * (2^(2^(k-1)))^f(k-1) * ... * (2^(2^0))^f(0)

    设 g(k)=2^(2^k)，则：

    2^n = g(k)^f(k) * g(k-1)^f(k-1) * ... * g(0)^f(0)

    可见 g(k) = g(k-1) ^ 2

    因此：

```c++
__int64 power2_I(int n)
{
    __int64 pow = 1; // 结果
    __int64 p = 2; // 累乘项初始化为2，即g(k)

    while (n) { // 迭代 log(n)轮
        if (n & 1) { pow *= p; } // 当f(k)为1时，将g(k)计入结果
        n >>= 1;
        p *= p; // g(k) = g(k-1) ^ 2
    }

    return pow;
}
```

嗯，我这个智力也就到这了。。。

## a^n

扩展到 a^n，同样有：

    a^n = g(k)^f(k) * g(k-1)^f(k-1) * ... * g(0)^f(0)，其中，g(k) = a^(a^k)

因此：

```c
__int64 power(__int64 a, int n)
{
	__int64 pow = 1;
	__int64 p = a;
	while (n) {
		if (n & 1) { pow *= p; }
		n >>= 1;
		p *= p;
	}
	return pow;
}
```

## 快速幂取模 a^n % m

由于 `(a * b) % c = ((a % c) * (b % c)) % c`

因此：

    a^n % m = (g(k)^f(k) * g(k-1)^f(k-1) * ... * g(0)^f(0)) % m
            = (g(k)^f(k) % m) * (g(k-1)^f(k-1) % m) * ... * (g(0)^f(0) % m)

依然是f(k)=0时忽略掉（乘1）。

因此：

```c++
__int64 modular_exponentiation(__int64 a, __int64 n, __int64 m)
{
	__int64 mod = 1;
	__int64 p = a % m;

	while (n) {
		if (n & 1) { mod = (mod * p) % m; }
		p = (p * p) % m;
		n >>= 1;
	}

	return mod;
}
```

## 平方运算测试

10000000个随机数，范围为2^[32, 63]，结果下来还是有点小惊讶：

```
assertion test begin...
assertion test elapsed 1.000000 ms, avg 0.000000 ms

performance test for power2BF_I begin...
performance test for power2BF_I elapsed 2768.000000 ms, avg 0.000277 ms

performance test for power2BF_R begin...
performance test for power2BF_R elapsed 21490.000000 ms, avg 0.002149 ms

performance test for power2 begin...
performance test for power2 elapsed 5262.000000 ms, avg 0.000526 ms

performance test for power2_I begin...
performance test for power2_I elapsed 1093.000000 ms, avg 0.000109 ms
```

最快的算法是 `power2_I` 毋庸置疑，但 `power2BF_I` 的表现居然比 `power2` 要好，可见以后设计算法时尽量用迭代，少用递归。