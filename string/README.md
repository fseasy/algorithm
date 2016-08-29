# string algorithm

## 1. find

1. brute force 

2. Rabin-Karp algorithm

    使用将字符串编码为数字的方法，来达到快速匹配的目的。在编码字符串时，滑动窗口间的两个数字是有关联的，只需要使用：

    ```C++
    ( encoding_val - out_slide * h ) * alphabet_size + in_slide
    ```

    即可，然而问题是，因为数字实在太大了，所以我们需要加入模运算。这导致了一些问题，首先算法层次上，有原来的精确匹配变为了非精确（与Hash相似），其次，计算上需要注意一些问题。

    最关键的就是上面的公式，我们加入模运算后，直观上应该如下：

    ```C++
    ( ( encoding_val - out_slide * h ) * alphabet_size + in_slide ) % M
    ```

    然而，这里有个问题，即`encoding_val - out_slide * h`可能为负数！这是可能的，因为这两个值没法确定大小。如果是`signed`,那么我们其实问题不大的，但是如果我们用的signed, 那么结果就会有问题了( 相当于加了 2^32 , 这就导致模运算结果错了。)

    处理这种情况，我们有两种思路： 一种，所有都使用`signed`，最后判断是否为负，如果为负，则加上 `M` , 这是在`GeeksforGeeks`上的看到的方法，应该没有问题，因为变为负数并不会影响模结果的正确性（仍然是取模啊，只是最后需要保证为正，因为C/C++中模结果正负与被除数相关）。这种方法的弊端是：因为这一个问题我们就不得不全部使用`signed`，这个代价太大了。因为很明显我们期望使用`unsigned`，这样由`alphabet_size * M < LIMIT`只，`LIMIT`越大，`M`越大，冲突的可能越低。

    第二种方法是，将上述公式再变化一下：

    ```C++
    ( ( M - (out_slide * h)%M  + encoding_val) * alphabet_size + in_slide ) % M
    ```
    
    变化之后结果是一致的，这需要用到模运算的性质： `(a +/- b) % M = (a%M +/- b%M) %M` 以及 `a % a = 0` 。利用这两个性质，显然我们可以得到：

    ```C++
    ( encoding_val *alphabet_size % M + in_slide % M - (out_slide * h) * alphabet_size % M ) % M 
    ```

    没有问题。

    最后，还有一个问题需要注意。因为string的每个位置类型是`char`，如果直接与`unsigned`相加，那么如果char值大于128，那么char会按照`char -> int -> unsigned`扩展，结果变成一个非常大的正数。

    我们有两种方法解决，一种是给它与上`0xff`， 即`(signed_char & 0xff)` , 或者强制转为`unsigned char`(一定是unsinged char , 而不是unsigned!)



