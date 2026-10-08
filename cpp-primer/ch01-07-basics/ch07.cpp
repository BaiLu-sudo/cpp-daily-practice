//p230
#if 0
#include <iostream>
#include <string>
#include "ch07.h"

using std::cin; using std::cout; using std::endl; using std::string;
int main(){
    Salas_data total;
    if(cin >> total.bookNo >> total.units_sold >> total.revenue){
         Sales_data trans;
          while (cin >> trans.bookNo >> trans.units_sold >> trans.revenue) {
            // 3. 判断新读到的书和当前书是不是同一本
            if (total.isbn() == trans.isbn()) {
                // 是同一本，累加销量和收入
                total.units_sold += trans.units_sold;
                total.revenue += trans.revenue;
            } else {
                // 不是同一本，打印上一本书的统计结果
                cout << total.isbn() << " " << total.units_sold << " "
                     << total.revenue << " " << total.avg_price() << endl;
                // 更新当前处理的书，变成新读到的那本
                total = trans;
            }
    }
    cout << total.isbn() << " " << total.units_sold << " "
             << total.revenue << " " << total.avg_price() << endl;
    } else {
        std::cerr << "没有输入任何数据！" << endl;
        return -1;
    }

    return 0;
}

#endif

//p239
#if 0
什么是构造函数？
名字必须和类名一模一样。
没有返回值（连 void 都不写）。
可以重载（可以有多个不同参数的构造函数）。
最常用的写法是初始化列表（: 成员(值)），它比在函数体里赋值更高效。

#endif

//p241
#if 0
class 和 struct 有区别吗？
有区别，但只差一个默认权限。 这也是 C++ 里最反直觉的细节之一。
class：默认权限是 private。如果你不写 public:，里面的所有成员都是私有的，外部完全无法访问。
struct：默认权限是 public。如果你不写 private:，里面所有成员都是公开的，外部可以直接修改。

什么是封装？有什么用？
封装（Encapsulation）：就是把数据和操作数据的函数打包在一起，并且隐藏内部实现细节（用 private），只暴露必要的接口（用 public）。
有什么用？
安全：防止外部代码“乱改”内部数据。比如银行账户的余额，你不能随便 account.balance = 999999;，必须通过 deposit() 函数来操作。
灵活：以后你可以随意修改内部的实现（比如把 double revenue 改成 int total_cents），只要对外接口（avg_price()）不变，调用你代码的人根本不需要修改他们写的代码。这大大降低了维护成本。

给 Person 类分 public 和 private
结合上面说的原则，我们来改造 Person：
应该声明为 public 的成员：
get_name()：让外部能读名字。
get_address()：让外部能读地址。
构造函数（如果有）：让外部能创建对象。
修改姓名的 set_name() 或 set_address()（如果你提供的话）。
应该声明为 private 的成员：
name 和 address 数据本身。
原因：如果 name 和 address 设为 public，别人就可以写 p.name = "恶意修改";，你无法阻止。设为 private 后，别人必须通过 p.set_name("张三"); 来修改，你可以在 set_name 里加各种校验（比如名字不能超过50个字）



//内连函数
inline 只是“建议”，不是“命令”：你写了 inline，编译器不一定照做。如果函数很复杂（包含递归、循环），编译器会觉得“这泡面太复杂了，你还是去餐厅吃吧”，从而拒绝内联。
内联函数的定义必须放在头文件里！ 因为编译器需要看到完整的函数体才能“复制粘贴”。如果你把内联函数的定义放在了 .cpp 里，其他 .cpp 文件只看到声明，编译器就没法粘贴了，会导致链接错误。
省去函数调用的开销。做法：就是在函数定义的最前面加上 inline 关键字
inline int add(int a, int b) {
    return a + b;
}
int main() {
    int x = add(3, 5); // 调用
}

直接转换成
int main() {
    int x = 3 + 5; //  函数调用不见了，直接变成了算术表达式！
}

#endif


//p246
#if 0
Screen& 和 Screen 到底差了啥？
Screen&（带&，返回引用）：“原件”。你在 myScreen 这张纸上画画，画完还是这张纸。
Screen（不带&，返回值）：“复印件”。你在复印出来的纸上画画，画完复印件被扔了，你原来的 myScreen 还是白纸一张！

#include <iostream>
#include <string>
using std::cout; using std::endl; using std::string;

class Screen {
public:
    // 构造函数
    Screen(unsigned w, unsigned h, char c) : 
        width(w), height(h), contents(w * h, c), cursor(0) {}

    // 移动光标到 (r, c) 处
    Screen& move(unsigned r, unsigned c) {
        cursor = r * width + c;
        return *this; // 返回当前对象本身
    }

    // 在当前光标处设置字符
    Screen& set(char ch) {
        contents[cursor] = ch;
        return *this; //  返回当前对象本身
    }

    // 打印屏幕
    Screen& display(std::ostream &os) {
        os << "屏幕尺寸: " << width << "x" << height << endl;
        for (unsigned i = 0; i < height; ++i) {
            for (unsigned j = 0; j < width; ++j) {
                os << contents[i * width + j];
            }
            os << endl;
        }
        return *this; // 返回当前对象本身
    }

private:
    unsigned width = 0;
    unsigned height = 0;
    string contents;
    unsigned cursor = 0; // 新增：记录光标位置
};

执行返回语句：return *this;。*this 解引用，拿到的是myScreen 这个对象本身（包含了新的 cursor，还有之前的 width、height、contents）。
返回给谁？ 返回给了调用者。所以 myScreen.move(4,0) 这个表达式执行完，结果就是 myScreen 本身（带着新坐标）
#endif










































































































