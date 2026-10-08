#if 0
#define bai 0
#if bai
形参（Parameter）：是函数定义时括号里写的“占位符”。就像停车位，只是个空架子，等着别人把车停进来。
实参（Argument）：是调用函数时，括号里传入的“真实数据”。就像真正停进停车位的车

int f() { string s; /*...*/ return s; }
错误：函数返回值类型是 int，但里面返回的是 string 类型，类型不匹配。
修正：把返回类型改成 string（即 string f() { ... }
#endif

#include<iostream>
#include<string>

using std::cin; using std::cout; using std::endl;
// 练习 6.3：编写阶乘函数
int fact(int val){
    int ret=1;
    while(val>1){
        ret *=val--;
    }
    return ret;
}

// 练习 6.4：与用户交互，计算阶乘
voi interactive_fact(){
    int val;
    if(cin<<val){
         cout << val << " 的阶乘是: " << fact(val) << endl;
    }
}

// 练习 6.5：求绝对值
double absolute(double x){
    return(x<0)?-x:x;
}

int main(){
    return 0;
}
#endif

//p186 局部静态变量
#if 0
void test_variables(int param) { // param 是形参
    int local_var = 0;              // 局部变量（每次调用都重新初始化为 0）
    static int static_var = 0;      // 局部静态变量（只在第一次调用时初始化为 0）

    local_var++;
    static_var++;

    cout << "形参: " << param 
         << ", 局部变量: " << local_var 
         << ", 静态变量: " << static_var << endl;
}

// 练习 6.7：第一次调用返回 0，之后每次返回值加 1
int counter() {
    static int count = 0; //  静态变量，只初始化一次
    return count++;       // 先返回 count 的当前值，再把 count 加 1
}

// 使用指针形参交換两个整数的值。 在代码中调用该函数并输
//出交换后的结果
#include <iostream>
using std::cout;using std::endl;
void swap(int *p1,int *p2){
    int temp=*p1;
    *p1=*p2;
     *p2=temp;
}
int main(){
    int a=10,b=20;
     swap(&a, &b);
     return 0;
}

/*
不加 &（值传递）：就像你把文件复印了一份交给前台。前台拿着复印件，在上面乱写乱画（i = 0）。你手里的原件毫发无损。
加 &（引用传递）：就像你直接把原件交给了前台。前台拿起笔，直接在原件上划掉，写上了 0。你拿回来的时候，原件已经被改了。
*/
void reset(int &i) { // ⭐ 形参加 &，代表这是引用传参
    i = 0;
}

// 练习 6.12：用引用交换两个整数（对比上一节的指针版本）
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}
引用版本（int &）更好用
对比指针版本，你不需要在调用时写 swap(&x, &y)，也不需要在函数内部到处写 *p1、*p2。代码看起来就像普通传值一样清爽，但底层依然在操作真实的内存地址，兼顾了“简单”和“高效”。


void f(T) 和 void f(T&) 的区别
void f(T)：值传递（复印机）。把外面的数据复印一份传进去。你在函数里怎么改，都不会影响外面原来的数据。
void f(T&)：引用传递（别名）。把外面数据的外号告诉函数。函数里对 T 的任何修改，都会直接改变外面原来的数据

#include <iostream>
using std::cout; using std::endl;

// 版本 1：不加 &
void reset_without_ref(int i) {
    i = 0; // 改的是副本
}
// 版本 2：加 &
void reset_with_ref(int &i) {
    i = 0; // 改的是本体
}
int main() {
    int a = 42;
    int b = 42;

    cout << "=== 不加 & 的版本 ===" << endl;
    cout << "调用前 a = " << a << endl;
    reset_without_ref(a); // 传入的是 a 的值（42）
    cout << "调用后 a = " << a << " (没变！)" << endl;

    cout << "\n=== 加 & 的版本 ===" << endl;
    cout << "调用前 b = " << b << endl;
    reset_with_ref(b); // 传入的是 b 本身
    cout << "调用后 b = " << b << " (变成 0 了！)" << endl;

    return 0;
}
引用还有一个巨大的作用：省内存、省时间。

#endif



//p193
#if 0
判断和改小写
判断是否含大写：只是读取，不修改原字符串，必须用 const string&（常量引用），避免拷贝，且承诺安全。
改成小写：必须修改原字符串，必须用 string&（普通引用），否则改的是副本，原字符串不变。

#include <iostream>
#include <string>
#include <cctype> // 用于 isupper 和 tolower
using std::cout; using std::endl; using std::string;

bool has_upper(const string &s){
    for(auto:s){
        if(isupper(c))return ture;
    }
    return false;
}
void to_lower(string &s){
    for(auto&c : s){
        c=tolower(c);
    }
}


什么时候用 const 引用？
不需要修改参数时。
参数类型比较大（如 string、vector），避免值拷贝带来的性能损耗。
希望函数能接收字面量或常量对象（比如 "hello"）
#endif

//p196
#if 0
比较 int 和指针指向的值
因为我们只是去“读取”指针指向的值，不需要修改它。加上 const 更安全，也能接收更多类型的实参
int compare(int val,const int *ptr)
{
    return (val>*ptr)?val:*ptr;
}

交换两个 int 指针
如果你写成 void swapPtr(int *p1, int *p2)，这只是交换了函数内部的指针副本，外面的指针根本没变
要想交换外面的指针，必须传指针的引用（int *&）或者指向指针的指针（int **）。推荐用引用，写法清爽很多。
void swapPtr(int *&p1, int *&p2){
    int *temp=p1
    p1=p2;
    p2=temp;
}



指出 print 函数的问题并改正
void print(const int ia[10]) {
    for (size_t i = 0; i != 10; ++i)
        cout << ia[i] << endl;
}
数组退化：形参 const int ia[10] 里的那个 [10] 是骗人的！编译器会自动把它当成 const int *ia
越界访问（程序崩溃）：因为函数内部写死了循环 10 次，如果你传入的数组只有 3 个元素，程序就会强行去读 ia[10]
void print(const int ia[], size_t size) {
    for (size_t i = 0; i != size; ++i)
        cout << ia[i] << endl;
}
void print(const int (&ia)[10]) { // 明确要求数组必须是 10 个元素
    for (int x : ia) cout << x << endl;
}

#endif

//p197
#if 0
#include <iostream>
#include <string>

using std::cout; using std::endl; using std::string;

int main(int argc,char *argv[]){
        for (int i = 0; i < argc; ++i) {
        cout << "argv[" << i << "] = " << argv[i] << endl;
    }
        if (argc < 3) {
        cout << "错误：需要至少两个参数！例如：./main hello world" << endl;
        return 1;
    }
    string result = string(argv[1]) + " " + string(argv[2]);
    cout << "连接结果: " << result << endl;

    return 0;
}



#endif

//p199
#if 0
#include <iostream>
#include <initializer_list>

using std::cout; using std::endl; using std::initializer_list;
int sum(initializer_list<int> il) {
    int total = 0;
    for (const auto &num : il) { // 使用范围 for 遍历列表
        total += num;
    }
    return total;
}

int main(){
    cout << "求和结果: " << sum({1, 2, 3, 4, 5}) << endl; // 输出 15
    cout << "求和结果: " << sum({10, 20}) << endl;         // 输出 30
    return 0;
}

练习 6.29：应该声明成引用吗？为什么？
答案：应该声明成引用，但不是普通引用，而是常量引用（const auto&）。

为什么？
避免拷贝：如果 initializer_list 里的元素是很大的对象（比如一个大 string 或复杂结构体），如果不加 &，每次循环都会拷贝一份出来，效率极低。加上 & 就是直接拿别名，毫无开销。
为什么必须是 const 引用？ 因为 initializer_list 本身的设计就是“只读”的，它里面的元素全都是 const 的，所以你用普通引用（auto&）去接，编译器会直接报错。
#endif


//p205
#if 0
阶乘停止条件是 if (val != 0) 会发生什么？
原因：阶乘的正常递归是 val * factorial(val - 1)。如果条件是 val != 0，当 val 变成负数（例如 -1）时，-1 != 0 成立，递归继续；然后 -2 继续……永远也碰不到 0，最终导致内存耗尽，程序崩溃。
修正：必须写成 if (val > 1) 或者 if (val == 1) 等能确保递归结束的条件。

为什么传 val - 1 而不是 val--？
// 正确写法
return val * factorial(val - 1); // val - 1 只是计算出一个新值传给下一层，不改变当前层的 val
// 错误写法（极度危险！）
return val * factorial(val--); // ❌ 严重问题
val-- 是后置递减。它的执行逻辑是：先返回 val 的旧值（作为参数传给递归函数），然后再把当前的 val 减 1。
但 C++ 标准规定，在同一个表达式中，对同一个变量既读取又修改，属于未定义行为（Undefined Behavior）。也就是说，编译器不知道是该先读取 val 去乘，还是先自减。不同编译器会给出不同结果，甚至直接崩溃。

#endif

//p210
#if 0
函数重载
#include <iostream>
using std::cout; using std::endl;

// (a) 错误示范，取消注释就会报错
// int calc(int, int);
// int calc(const int, const int); //  报错：重定义

// (b) 错误示范，取消注释就会报错
// int get();
// double get(); // 报错：返回值不同不能重载

// (c) 正确示范（可以正常编译运行）
int *reset(int *p) {
    cout << "调用了 int* 版本的 reset" << endl;
    return p;
}
double *reset(double *p) {
    cout << "调用了 double* 版本的 reset" << endl;
    return p;
}

int main() {
    // 验证 (c) 的重载
    int a = 10;
    double b = 3.14;
    
    reset(&a); // 自动匹配 int* 版本
    reset(&b); // 自动匹配 double* 版本

    return 0;
}


#endif



























































































