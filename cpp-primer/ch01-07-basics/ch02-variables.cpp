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


