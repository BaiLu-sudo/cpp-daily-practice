#ifndef SALES_DATA_H
#define SALES_DATA_H

#if 0
#include <string>
struct Sales_data{
    std::string bookNo;
    unsigned units_sold =0;
    double revenue =0.0;
    
     std::string isbn() const { return bookNo; }
      
    double avg_price() const {
        if (units_sold != 0)
            return revenue / units_sold;
        else
            return 0.0;
    }

    Sales_data& combine(const Sales_data& rhs){
        units_sold +=rhs.units_sold;
        revenue +=rhs.revenue;
        return *this;
    }

        double avg_price() const {
        return (units_sold != 0) ? revenue / units_sold : 0.0;
    }


};

struct Person{
    std::string name;
    std::string address;

    std::string get_name() const { return name; }
    std::string get_address() const { return address; }
/*
// 你写的：
std::string isbn() const { return bookNo; }
// 编译器眼里的真相：
std::string isbn(const Sales_data *this) { return this->bookNo; }

不加 const
定义了一个“只读对象”（也就是常量对象）
const Sales_data data2; // 这是一个常量对象，它的数据是神圣不可修改的
data2.isbn(); // 编译器直接报错！
*/



};
    
/*
&代表引用。这意味着 rhs 是传进来的那个对象的“别名”，不会复制一整个对象。如果不用 &，每次调用 combine 都要复印一份 trans，如果书本很多，效率极低。
const：代表常量。这就给函数立了个规矩：“你拿着 rhs 的引用，但是只准读，不准改。”

如果返回类型写成 void，那就没有返回值了。如果写成 Sales_data（不加 &），那么返回的是 *this 的一个副本（拷贝）。
而写成 Sales_data&，意思是返回当前对象本身的引用
*/

//数据流
std::ostream& print(std::ostream& os, const Person& p) {
    os << p.get_name() << p.get_address();
    return os;
}
#endif







#if 0
//构造函数
#include <string>
#include <iostream>

struct Sales_data {
    // 1. 默认构造函数（必须显式写，不然有了别的构造函数，编译器就不给了）
    Sales_data() = default;

    // 2. 带参数的构造函数（练习 7.14：用类内初始值显式初始化）
    Sales_data(const std::string &s, unsigned n, double p) :
        bookNo(s), units_sold(n), revenue(p) { }
/*
性能：冒号直接“初始化”，花括号里是“先初始化再赋值”。对于复杂对象（比如 string），直接初始化比先建空再赋值快得多。
规矩（极其重要）：如果类里有 const 成员（只读）或者引用成员（别名），它们只能在冒号后面初始化，绝对不能在花括号里赋值！

*/
    // 3. 从 istream 读取的构造函数（练习 7.12：定义移到类内部）
    Sales_data(std::istream &is) {
        read(is, *this); // 调用下面的 read 函数
    }

    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;

    std::string isbn() const { return bookNo; }
    Sales_data& combine(const Sales_data& rhs) {
        units_sold += rhs.units_sold;
        revenue += rhs.revenue;
        return *this;
    }
    double avg_price() const {
        return (units_sold != 0) ? revenue / units_sold : 0.0;
    }

    // 把 read 和 print 声明为友元（或直接作为普通函数放在头文件里）
    friend std::istream& read(std::istream&, Sales_data&);
    friend std::ostream& print(std::ostream&, const Sales_data&);
};

// 定义 read 函数（练习 7.12 里说的“只接受 istream”的构造函数需要用到它）
inline std::istream& read(std::istream& is, Sales_data& item) {
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = item.units_sold * price;
    return is;
}

inline std::ostream& print(std::ostream& os, const Sales_data& item) {
    os << item.isbn() << " " << item.units_sold << " " 
       << item.revenue << " " << item.avg_price();
    return os;
}
#endif





//封装的强制保护  class 来演示封装
#if 1
#include <iostream>
#include <string>

using std::cout;using std::endl;using std::string;
class Person{
private:
   string name;
   string address;
   
public:
   Person()   =default;

   Person(const string &n, const string &a) : name(n), address(a) {}
   string get_name() const { return name; }
   string get_address() const { return address; }
   void set_name(const string &n) { 
        if (!n.empty()) name = n; // 加一层校验，保护数据安全
    }

};


#endif

#endif











