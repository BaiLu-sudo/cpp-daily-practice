//p443
#if 0
什么是拷贝构造函数？
Point p1;         // 普通构造
Point p2 = p1;    //  拷贝构造：拿 p1 复印一份给 p2
Point p3(p1);     //  拷贝构造：同上

为什么下面的声明非法？
Sales_data::Sales_data(Sales_data rhs);
原因：参数名 rhs 前面少了一个 &（引用）。如果按值传参，把实参传给 rhs 这个形参时，就会触发一次拷贝。
死循环：为了拷贝形参，编译器又得去调拷贝构造函数，结果又产生了一个新的形参……无限套娃，直接死循环报错。拷贝构造函数的参数必须是引用（const 类名&）。

StrBlob 和 StrBlobPtr 的拷贝
拷贝 StrBlob 时：它的底层是一个 shared_ptr<vector<string>>。拷贝它时，只是拷贝了智能指针，底层数据的引用计数加 1。两个 StrBlob 共享同一个底层 vector。
拷贝 StrBlobPtr 时：它底层是一个 weak_ptr 和一个 size_t curr。拷贝它时，weak_ptr 被拷贝（不会增加底层数据的引用计数），curr 也被拷贝。两个迭代器指向同一位置。

数一数用了几次拷贝构造
Point foo_bar(Point arg) //  1. 按值传参：实参拷给形参 arg
{
    Point local = arg, *heap = new Point(global); 
    //  2. local = arg (拷贝构造)
    //  3. new Point(global) (拷贝构造，把 global 拷给新分配的对象)

    *heap = local; // 这是赋值，不是拷贝构造！(因为 heap 指向的对象已存在)
    
    Point pa[ 4 ] = { local, *heap }; 
    // 4. 数组初始化，把 local 拷给 pa[0]
    // 5. 把 *heap 拷给 pa[1]
    
    return *heap; //  6. 返回对象，拷贝给返回值临时对象
}

编写 HasPtr 的拷贝构造函数（深拷贝起点）
class HasPtr {
public:
    HasPtr(const std::string &s = std::string()):
        ps(new std::string(s)), i(0) { }
private:
    std::string *ps;
    int i;
};
HasPtr 里有一个 string* ps。如果直接拷贝指针，两个对象会指向同一块内存，销毁时直接崩溃。所以我们要进行深拷贝（Deep Copy）：在堆上重新 new 一块内存，把原来的字符串内容复制过去。

#include <iostream>
#include <string>

using namespace std;

class HasPatr{
    public:
     HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) { }

}

#endif

//析构函数
#if 0
当对象的生命周期结束（比如出了大括号，或者被 delete），系统会自动调用它，帮你清理残局（主要是释放内存）。

是什么？ 名字是 ~类名()，没有参数，没有返回值。
干什么？ 释放对象在生命周期内占用的资源（比如 new 出来的内存、关闭文件句柄）。
何时生成合成版？ 如果你没自己写，编译器会自动生成一个。合成的析构函数会按成员逆序销毁它们。但如果类里有裸指针，合成版不会帮你 delete 指针

智能指针的销毁
销毁 StrBlob 时：因为它底层是 shared_ptr。销毁它时，底层数据的引用计数减 1。如果计数变成 0，底层那个 vector<string> 才会被真正销毁。
销毁 StrBlobPtr 时：它底层是 weak_ptr。销毁它时，什么都不会发生，底层数据的引用计数不变。它只是静静地从旁边消失。

给 HasPtr 加析构函数
calss HasPtr{
   public:
    HasPtr(const string& s = string()) : ps(new string(s)), i(0) { }
    HasPtr(const HasPtr& hp) : ps(new string(*hp.ps)), i(hp.i) { }
    
    //  练习 13.11：析构函数，负责释放内存
    ~HasPtr() {
        delete ps; 
        cout << "析构函数被调用，内存被释放！" << endl;
    }
private:
    string* ps;
    int i;
};

#endif

#if 0




#endif















































































































