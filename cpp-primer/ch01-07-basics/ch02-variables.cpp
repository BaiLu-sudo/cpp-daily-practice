#include<iostream>


//p35
#if 0
void ex2_3(){
    unsigned u-10 , u2 - 42
    std::cout<< u2 - u << std:: endl
    std:: cout<< u-u2 < < std:: endl
    int 1 = 10 , 12 = 42
    std:: cout<< i2 -i<< std::endl
    std::cout<< i-i2<< std::endl
    std::cout<< i-u<< std:: endl;
    std:: cout<< u-i<< std:: endl;
}

int main(){
    ex2_3();
    return 0;
}

#endif

//p38
#if 0
int month = 9, day = 7;    // 合法，日常十进制赋值
int month = 09, day = 07;  // 八进制的数字只有 0 ~ 7
#endif

//p42
#if 0
(a) extern int ix = 1024; 定义
(b) int iy; 定义
(c) extern int iz; 声明

同一个变量，可以声明很多次，但只能定义一次。
，代码会分成多个文件（比如 a.cpp 和 b.cpp）。b.cpp 想用 a.cpp 里的变量，就需要在 b.cpp 里写个声明 extern int ix;
#endif


//p43
/*
(a) int double = 3.14;  非法
原因：double 是 C++ 内置的关键字（代表双精度浮点数类型）。你不能拿类型名字当变量名，就像你不能给宠物狗起名叫“狗”。
(b) int _; 合法（但极不建议这样写）
原因：下划线 _ 是允许作为变量名的。
在 C++ 里，_ 作为变量名在函数内部是合法的，但在全局作用域下，或者连续两个下划线（__），或者下划线加大写字母（_A）是留给编译器或系统库用的。你以后看别人的代码，几乎不会有人写 int _;，容易引发冲突。
(c) int catch-22; 非法
原因：包含了减号 -。编译器会把 catch 和 22 分开看，并且 catch 还是个 C++ 关键字（异常处理用的）。
(d) int 1_or_2 = 1; 非法
原因：以数字 1 开头了。变量名不能以数字开头，这样编译器很难区分它是变量还是数字字面值。必须写成 _1_or_2 或者 one_or_two。
(e) double Double = 3.14;  合法
原因：C++ 是区分大小写的！double（小写）是关键字，但 Double（首字母大写）仅仅是普通名字，编译器觉得它们完全不同
*/


//p46
#if 0
int &rval2 = ival rval2指向ival （ 是ival的另一个名字 ）
引用 （reference） 为对象起了另外一个名字， 引用类型引用 （refers to） 另外一种类型。
通过将声明符写成&d 的形式来定义引用类型， 其中 d是声明的变量名：
(a) int ival = 1.01; 合法。（但存在窄化转换，1.01 会被截断为 1，赋值给 ival）。

(b) int &rval1 = 1.01;  不合法！ 原因有两个：第一，引用必须绑定到对象（变量），不能绑定到字面值（1.01 是常量）；第二，类型不匹配（int& 不能绑定到 double 类型的值）。

(c) int &rval2 = ival;  合法。类型完全匹配，rval2 成了 ival 的别名。

(d) int &rval3; 不合法！引用必须在定义时立即初始化。你不能先定义一个空的引用，然后再给它赋值。
#endif


//p51（指针基本用法示例）
#if 0
#include <iostream>

int main() {
    int a = 10, b = 20;
    int *p = &a; // p 指向 a（p 的值是 a 的地址）

    // 1. 更改指针所指对象的值（改变 a 里的数字）
    *p = 30; 
    std::cout << "a = " << a << std::endl; // a 变成了 30

    // 2. 更改指针的值（让 p 指向 b）
    p = &b; 
    *p = 40;
    std::cout << "b = " << b << std::endl; // b 变成了 40
    std::cout << "a 还是 = " << a << std::endl; // a 还是 30
    return 0;
}
#endif

//p54(const)
#if 0
 const int buf;  不合法 因为 buf 是一个常量（const），常量一旦诞生就必须有个固定值const int buf = 0;
 int cnt = 0;  合法
 const int sz = cnt; 合法
 ++cnt; ++sz; 不合法++cnt 是没问题的，cnt 是普通变量。但是 ++sz 是绝对不允许的！ 因为 sz 是 const（常量）

#endif

//p57
#if 0
引用必须绑定到对象，const 变量和 const 指针必须初始化
int i = -1, &r = 0; 不合法 r 是普通引用（int&），必须绑定到变量（左值）。而 0 是字面量（右值），普通引用绑不了。
int *const p2 = &i2;合法
const int i = -1, &r = 0;  合法
const int *const p3 = &i2;  合法
const int i2 = i, &r = i;  合法


int i, *const cp; 不合法 必须在定义时初始
i = ic;  合法 i 是普通 int，ic 是 const int。把只读的值赋给可写变量

#endif


//p57  2.4.3
#if 0
顶层 const 是锁住自己（指针本身），底层 const 是锁住目标（指向的值）。
const int v2 = 0;  顶层 const
const int *p2 = &v2  底层 const。
const int &r2 = v2; 底层 const。引用的const永远是底层。r2 只是个别名，不能改变绑定关系，但它绑定的对象 v2 是 const 的。
*const p3 = &i 顶层 const。p3 本身是常量指针，但它指向的 i 是普通的 int

int null = 0, *p = null;指针只能存地址，不能存整数

#endif


//p65  自定义数据类型（结构体 / 类）
#if 0

#include <string>
struct sale_data{
    std::string bookno;
    double price=0.0;
    unsigned units_sold =0;

    double total_revenue()const{
        return price* units_sold;
    }
};

int main(){
    sale_data item1;
    item1.bookno = "978-7-121-15535-2";
    item1.price = 59.90;
    item1.units_sold = 5;

    std::cout << "书籍编号: " << item1.bookNo << std::endl;
    std::cout << "单价: " << item1.price << " 元" << std::endl;
    std::cout << "销量: " << item1.units_sold << " 本" << std::endl;
    std::cout << "总销售额: " << item1.total_revenue() << " 元" << std::endl;

    return 0;
}

#endif


//auto decltype
#if 0

int main(){
    int a =10;
    int &r =a;
    auto x=r;// auto 只拿值，x 是全新的 int
    x=99;
    std::cout<<"xiugai x hou,a de zhi shi:"<<a<<ensl;
    // 输出 10，a 没变


    decltype(r)y=a; // decltype(r) 是 int&，所以 y 也是 a 的别名
    y=88;// 修改 y（也就是修改 a）
    std::cout<<a<<std::endl;
    return 0;// 输出 88，a 变了！


}

#endif