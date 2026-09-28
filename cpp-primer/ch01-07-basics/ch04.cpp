#include <iostream>
//p128   &&和||
#if 1
#define bai 0
#if bai
&&：先算左边，如果左边是 假（false），整个表达式直接判定为假，右边根本不会去算。
||：先算左边，如果左边是 真（true），整个表达式直接判定为真，右边根本不会去算。

const char *cp = "Hello World";
if (cp && *cp)
防崩溃写法:直接写 *cp，当 cp 是空指针（nullptr）时，你去解引用它（*cp）会导致程序直接崩溃。加上 cp && 后，利用短路特性，如果 cp 真的是空指针，右边 *cp 根本不会被计算，程序安全退出
#endif

//while 循环读入整数，遇到 42 停止
int main(){
    int x;
    while(std::cin>> x && x!=42){
        std::cout<<x<<std::endl;
    }
    return 0;
}

// 书写一条表达式用于测试4个值 a、 b、 c、 d的关系， 确保a大于 b、 b 大
//于 、 大于 d
//a > b && b > c && c > d

#endif


//131
#if 0
int i; double d;
 d = i = 3.5;
 i = d = 3.5;
赋值运算符 = 是从右向左结合的 d = i = 3.5 先算 i = 3.5

if (42 = i)  // ...编译直接报错
if (i = 42)  // ...能编译通过，但逻辑全错条件永远成立
和原本想要的 if (i == 42)（判断 i 是否等于 42）意思差了十万八千里

double dval; int ival; int *pi;
dval = ival = pi = 0;
类型不匹配！ ival 是 int，pi 是 int*。你不能把指针直接塞进 int 变量里，编译器会报错。

#endif

//p133
#if o
前置先加再用，后置先用再加
前置递增（++i）：先把 i 的值加 1，然后返回 加完之后的新值。
比喻：你先迈步，然后踩到新位置。
后置递增（i++）：先返回 i 的当前值（旧值），然后再把 i 的值加 1。
比喻：你先踩在当前位置，然后再迈步。

int *ptr;
vector<int> vec;
int ival;

ptr != 0 && *ptr++
合法性：合法。这也是一道经典的“防御性编程”面试题。如果直接用 *ptr++，当 ptr 是空指针时会崩溃。加了一层 && 利用短路求值，完美避免了空指针解引用。

ival++ && ival
先计算 ival++。因为它是后置递增，所以 ival 会先作为布尔值参与逻辑与 && 的判断，然后 ival 自增 1。接着再判断自增后的 ival 是否为真。

#endif

//p134
#if 0
迭代器 iter 的 -> 和 . 优先级高于 * 和 ++（除了后缀 ++，后缀 ++ 优先级最高，但它是右结合的）
*iter 拿到的是一个 string 对象，而不是迭代器

 假设 iter的类型是 vector<string> ：：iterator，说明下面的表达式
是否合法。 如果合法， 表达式的含义是什么？ 如果不合法， 错在何处？
*iter++; 合法 后缀 ++ 高于前缀 *。所以等价于 *(iter++)

(*iter)++; 非法 (*iter) 拿到了一个 string 对象，然后试图对这个 string 执行 ++ 操作
std::string 没有 ++ 运算符（你不能对一个字符串做自增）

*iter.empty(); 非法. 高于 *。所以等价于 *(iter.empty())
iter 是一个迭代器，迭代器没有 empty() 这个成员函数（只有 string 或 vector 才有）

iter->empty();  合法 -> 是解引用并访问成员的简写，等价于 (*iter).empty()

++*iter; 非法
前缀 ++ 和 * 同优先级，但右结合，所以等价于 ++(*iter)
和 (b) 一样，*iter 拿到的是 string，对 string 执行前缀 ++ 是非法的

智能指针：以后你在第 12 章学 shared_ptr 或 unique_ptr 时，它们也是“指针”，访问成员也全部用 ->（比如 sp->age）。
写代码的习惯：看到 ->，脑子里立刻浮现出“这是一个指针”；看到 .，脑子里立刻浮现出“这是一个对象实体”。
优先级陷阱：如果一定要用 * 和 . 配合（比如 (*ptr).name），一定要加括号！写了括号，走遍天下都不怕。

#endif

//p135
#if 0

#include <vector>

using std::cout; using std::endl; using std::vector;

int main(){
    vector<int>v={1,2,3,4,5,6};

    for(auto &x :v){
        x = (x % 2 != 0) ? x * 2 : x; 
    }
    for (int x : v) cout << x << " ";
     return 0;
}


string result;
if (grade > 90)       result = "high pass";
else if (grade > 75)  result = "pass";
else if (grade > 60)  result = "low pass";
else                  result = "fail";

在 C++ 里，? 不能单独用，必须和 : 搭配，格式是：
条件 ? 条件为真时选这个 : 条件为假时选那个
如果问号前面的条件成立，结果就是冒号左边的；否则，结果就是冒号右边的。

int a=10,b=20;
int max;
if(a>b){
    max=a;
}else{
    max=b;
}

int a=10,b=20;
int max=(a>b)?a:b;


x = (x % 2 != 0) ? x * 2 : x;
if (x % 2 != 0) { // 如果 x 是奇数
    x = x * 2;    // 问号左边
} else {
    x = x;        // 冒号右边（保持原样）
}


 ul1 & ul 2  按位与
ull && ul2   逻辑与
#endif 

//p140
#if 0
#include <iostream>
using std::cout; using std::cin;

int main(){
    cout<<sizeof(char)<<endl;
    cout<<sizeof(short)<<endl;
}

int x[10]; int *p = x;
cout << sizeof(x)/sizeof(*x) << endl;
cout << sizeof(p)/sizeof(*p) << endl;

sizeof(x)：x 是一个包含 10 个 int 的数组。它的大小 = 10 * 4 = 40 字节。
sizeof(*x)：*x 是数组的第一个元素（int）。它的大小 = 4 字节。
sizeof(p)：p 是一个指针。指针存的是地址，在 64 位系统上，指针的大小固定是 8 字
sizeof(*p)：*p 是 int。它的大小 = 4 字节。


#endif



//141
#if 0
为什么要用前置（++ix）而不是后置（ix++

性能：前置版直接加 1 返回，效率高。后置版要先复制一份旧值保存，再加 1 返回旧值。对于迭代器或复杂类类型，后置版会带来额外的拷贝开销。
习惯：在 for 循环的递增部分，其实用哪个结果都一样，但 C++ 程序员习惯性地写前置，这是从 C 语言继承来的高效习惯

解释 someValue ? ++x, ++y : --x, --y 的含义
优先级：逗号运算符 , 的优先级低于条件运算符 ? :。所以这行代码实际上被解析为：
(someValue ? ++x, ++y : --x), --y;
看到最后的 , --y; 了吗？它永远会被执行，不管 someValue 是真还是假！

someValue ? (++x, ++y) : (--x, --y); 

#endif



//p143
#if 0


#endif