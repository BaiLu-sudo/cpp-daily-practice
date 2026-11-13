#if 0
什么是模板（Template）？
你之前写函数：int add(int a, int b)，你只能算 int。想算 double 就得重写一个。
有了模板：你写一个 template <typename T> T add(T a, T b)。编译器看到这行，就像拿到了一台万能复印机，你以后传什么类型，它就自动帮你复印出一份对应类型的函数。
函数模板：就是给函数做模具。
类模板：就是给类做模具。你看 vector<int>，其实就是 vector 这个类模板，套上了 int 这个材料。



// 1. 定义模板（造模具）
template <typename T> 
class Box {
public:
    T value; // 这坑叫 T，目前不知道塞什么
};

int main() {
    // 使用模板（真往坑里填馅）
    Box<int> b1;    // 编译器把所有的 T 替换成 int。生成了第一个真实的类。
    b1.value = 100; 

    Box<string> b2; // 编译器把所有的 T 替换成 string。生成了第二个真实的类。
    b2.value = "hello";
}
当你写下 Box<int> b1; 的时候，编译器比你还累，它会自动把上面的代码复制一份，并把所有的 T 替换成 int。它替换出来的代码长这样：
// 编译器偷偷生成的代码（你看不到）
class Box {
public:
    int value; // T 被替换成了 int
};



找出模板定义中的错误
template <typename elemType> class ListItem;
template <typename elemType> class List {
public:
    List<elemType>(); // 错误 1
    List<elemType>(const List<elemType> &); // 错误 2
    List<elemType>& operator=(const List<elemType> &); //  错误 3
    ~List();
    void insert(ListItem *ptr, elemType value); // 错误 4 (ListItem 少写了 <elemType>)
};
在类模板的内部，类名 List 就等同于 List<elemType>。所以，构造函数和析构函数不需要再写尖括号！
同时，ListItem 也是个模板，必须加上类型。

template <typename elemType> class ListItem;
template <typename elemType> class List {
public:
    List(); // 正确写法
    List(const List&); // 正确写法
    List& operator=(const List&); //正确写法
    ~List();
    void insert(ListItem<elemType> *ptr, elemType value); // 正确写法
};



非类型模板参数 & 友元
template <unsigned H, unsigned W> class Screen; （H 是高，W 是宽）。这叫非类型参数。
#include <iostream>
using namespace std;

template <using H,unsigned W>
calss Screen{
    friend ostream& operator<<(ostream& os, const Screen<H, W>& s) {
}







#endif

























































