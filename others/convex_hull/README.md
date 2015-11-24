###凸包问题

####CODING

1. 重载`输出运算符(<<)`时必须声明为**友元函数**！

    在Point类中要重载输出运算符，然而按照网上定义为：
    
    ```C++
    ostream& operator<< (ostream &out , const Point &p)
    ```
    总是报错，提示:` ‘std::ostream& P::operator<<(std::ostream&, const P&)’带且仅带 1 个实参`

    后来终于找到了解释： 一般的重载操作符，默认第一个参数就是类本身（进一步说，成员函数都应该有这样的性质，即包含隐含的this指针），在这种情况下，重载只能有一个参数！且为外部的变量。可是输出重载就不同了！

    因为要遵循 标准库的iostream的规则，即第一个变量不是类本身，而是输出流对象！ 所以就**不能将输出重载作为 成员函数**。

    应该作为友元函数。

    ```C++
    friend ostream& operator<< (ostream &out , const Point &p)
    ```

2. 将vector<Point *> 作为常量引用传入，创建迭代器时出错：

    开始是这样的：
    
    ```C++
    void print_pnts(const vector<Point *> & pnts)
    {
        ...
        for(vector<Point *>::iterator ite = pnts.begin() + 1; ite != pnts.end() ; ++ite)
        {
            ...
        }
    }

    ```

    总是报 `转换到非标量类型` ， 细看，应该是把 vector中的const* 指针变为了 非常量指针。

    后来在网上终于找到，应该使用`::const_iterator`来定义该迭代器！

    即：

    ```C++
    for(vector<Point *>::const_iterator ite = pnts.begin() + 1; ite != pnts.end() ; ++ite)

    ```
    
    所以： 参数vector使用const在头部修饰时，表示*内部元素*为const不可变。所以，应该使用`const_iterator`类型来表示不能通过iterator改变内部元素的值。







