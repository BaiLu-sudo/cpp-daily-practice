//p407
#if 0
shared_ptr 到底是什么？
以前的做法（手动挡，容易车毁人亡）：用 new 申请内存，必须时刻记得用 delete 释放。如果忘了，就是内存泄漏；如果释放早了还在用，就是野指针。
现在的做法（自动挡）：shared_ptr（共享智能指针）。
它内部有一个“引用计数器”。
有 1 个 shared_ptr 指向这份数据，计数器就是 1。
又来了 1 个 shared_ptr 指向它，计数器变 2。
当一个 shared_ptr 死掉时，计数器减 1。只有当计数器减到 0 的时候，它才会自动把底层数据销毁！

#include <iostream>
#include <string>
#include <vector>
#include <memory>      //  shared_ptr 在这里
#include <stdexcept>   // 异常

using namespace std;
typedef vector<string>::size_type size_type;

typedef 的意思是：“以后我在这个类里写 size_type，你就把它当成 vector<string>::size_type”





class：默认所有成员都是 private（私有） 的。
struct：默认所有成员都是 public（公开） 的。
使用习惯上的区别（潜规则）：
struct：通常用来做纯数据打包（比如只装几个变量的结构体，不需要复杂的函数和隐藏逻辑）。你一眼就能看穿它。
class：通常用来做封装好的对象（有复杂的内部逻辑，需要隐藏数据，对外提供接口）。就像 StrBlob，必须用 class，因为要保护里面的 data 不被随便修改。

用 : 初始化列表）：定制精装房。你在房子建好的那一刻，里面的家具就已经按你的要求摆好了。（直接初始化）
为什么不用 {}，非要用 :？ 因为对于像 shared_ptr、vector 这样的复杂对象，直接一步到位初始化，比先建空壳再赋值效率高得多，而且有些成员（比如 const 变量）只能用 : 初始化。
StrBlob() : data(make_shared<vector<string>>()) { }
// 等价于（但下面这种写法效率低，不推荐）：
StrBlob() { data = make_shared<vector<string>>(); }

智能指针 shared_ptr 到底怎么用？
// 造一个 int，值是 42，用智能指针 p 指向它
shared_ptr<int> p = make_shared<int>(42); 
// 造一个装字符串的 vector，里面有两个词，用智能指针 data 指向它
shared_ptr<vector<string>> data = make_shared<vector<string>>(initializer_list<string>{"a", "b"});

为什么叫“共享”（shared）？（引用计数）
当你拷贝一个 shared_ptr 时（比如 b1 = b2），底层的数据不会复制，只是引用计数 +1。
当你把其中一个指针销毁时，引用计数 -1。
只有当计数变成 0 的时候，底层数据才会被真正销毁！

shared_ptr<int> p1 = make_shared<int>(100);
cout << p1.use_count(); // 输出 1（只有 p1 指着它）
shared_ptr<int> p2 = p1; //  拷贝！
cout << p1.use_count(); // 输出 2（p1 和 p2 共同指着那个 100）

这就解释了为什么在 12.1 题里，b1 = b2 后，b2.push_back 会让 b1 也改变——因为它们共享了同一份底层数据。

为什么用 -> 而不是 .？
data 是一个智能指针，它存的是地址。

如果直接写 data.size()，编译器会认为你在找“指针对象”本身的大小。
写 data->size()，意思是：“顺着指针找到它指向的那个 vector，然后调用 vector 的 size 方法”。

: 后面跟着的，是在对象出生前就准备好的初始状态。
shared_ptr 本质上是一个带计数器的指针，多个指针可以指向同一个数据，全都不用了才会自动清理。
make_shared 是创建它的标准动作，-> 是访问它指向数据的动作。

#endif


//p412
#if 0
原生指针 vs 智能指针
动态分配一个 vector<int>。
传给另一个函数读入数据。
传给另一个函数打印。
记得 delete。

原生指针
#include <iostream>
#include <vector>

using namespace std;
// 读数据
void read_vector(vector<int>* v) {
    int num;
    while (cin >> num) {
        v->push_back(num);
    }
}

// 打印数据
void print_vector(vector<int>* v) {
    for (int x : *v) {
        cout << x << " ";
    }
    cout << endl;
}
int main() {
    // 1. 动态分配
    vector<int>* vp = new vector<int>();
    
    // 2. 读入
    cout << "请输入整数（Ctrl+D 结束）：" << endl;
    read_vector(vp);
    
    // 3. 打印
    print_vector(vp);

    // 4. 必须手动 delete！如果忘了，就是内存泄漏
    delete vp; 
    return 0;
}


智能指针
#include <iostream>
#include <vector>
#include <memory> //智能指针头文件

using namespace std;

void read_vector(vector<int>* v) {
    int num;
    while (cin >> num) v->push_back(num);
}
void print_vector(vector<int>* v) {
    for (int x : *v) cout << x << " ";
    cout << endl;
}
// 传参的时候依然传原生指针，因为智能指针可以通过 .get() 拿到原生指针
// 或者直接传 shared_ptr 也可以（但没必要拷贝一份）
int main() {
    // 用 make_shared 代替 new，自动管理内存
    shared_ptr<vector<int>> vp = make_shared<vector<int>>();
    cout << "请输入整数（Ctrl+D 结束）：" << endl;
    // 注意：get() 返回内置指针（即真实的地址）
    read_vector(vp.get()); 
    print_vector(vp.get());
    // 完全不需要 delete！出了 main 函数，vp 销毁，底层内存自动释放
    return 0;
}

bool b() {
    int* p = new int;
    // ...
    return p;
}
类型不匹配：函数返回类型是 bool，但你试图 return p;（返回一个 int* 指针）。编译器会直接报错。
内存泄漏：就算你强行 return true;，用 new 申请的 p 也永远没有机会被 delete。每次调用这个函数，就会漏掉 4 个字节。



int *q = new int(42), *r = new int(100);
r = q;
auto q2 = make_shared<int>(42), r2 = make_shared<int>(100);
r2 = q2;
第一组（原生指针，疯狂漏内存）：

你买了 42（q）和 100（r）。

r = q; 只是让指针 r 指向了 42。原来那个 100 现在已经没有任何指针指着它了，它变成了真正的“孤魂野鬼”，永远无法被释放（内存泄漏）。 并且 q 和 r 现在指向同一块内存。

第二组（智能指针，自动清理）：

你买了 42（q2，计数为1）和 100（r2，计数为1）。

r2 = q2;。此时 r2 不再指向 100，而是指向了 42。

⭐ 智能的魔法发生了：由于没有指针再指向那个 100，它的引用计数变成了 0。智能指针自动帮你把那个 100 的 delete 掉了！ 现在 q2 和 r2 共同指向 42（计数变为 2）。

💻 一键验证代码（亲自跑跑 12.6、12.7、12.9）
你可以把这段代码跑一遍（记得分批次输入数据测试）：

cpp
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

int main() {
    // ================= 验证 12.9 =================
    cout << "=== 练习 12.9 ===" << endl;
    // 1. 原生指针
    int *q = new int(42), *r = new int(100);
    r = q; // 此时 100 的内存泄漏了
    cout << "原生指针 r 指向的值: " << *r << endl; // 输出 42
    delete q; // 释放掉 42 的内存
    // ⚠️ 此时千万不能 delete r; 因为 r 和 q 指向同一块内存，会重复释放导致崩溃

    // 2. 智能指针
    auto q2 = make_shared<int>(42), r2 = make_shared<int>(100);
    cout << "赋值前 r2 的值: " << *r2 << "，q2 引用计数: " << q2.use_count() << endl; 
    
    r2 = q2; // ⭐ 赋值！原来的 100 自动释放
    cout << "赋值后 r2 的值: " << *r2 << "，q2 引用计数: " << q2.use_count() << "，r2 引用计数: " << r2.use_count() << endl;
    // 输出: r2 变为 42，q2 和 r2 的计数都是 2

    return 0;
}
🛡️ 终极避坑总结（刻在脑子里）
忘掉 new 和 delete：除非你在写极底层的代码，否则现代 C++ 强烈建议用 make_shared 来创建对象。
原生指针的赋值极其危险：r = q 会直接导致 r 原本指的内存永久丢失（内存泄漏）。
智能指针会自己“擦屁股”：r2 = q2 会让原本指向 100 的引用计数归零，底层自动调用 delete。
去把 12.9 的代码跑一遍，看到 r2 = q2 后，100 被清理得干干净净，同时 q2 和 r2 共享 42，你就完全理解智能指针的核心优势了。
下一节（12.1.3）会讲 shared_ptr 和 new 结合使用时的坑，比如不要用同一个裸指针初始化两个智能指针，会遇到新的问题。有卡壳随时发我！

#endif


//p415
#if 0
process 函数的参数是值传递。传进去的时候，智能指针的“引用计数”会加 1；函数结束时，“引用计数”会减 1，如果减到 0，房子（内存）就会自动炸毁（释放）。

shared_ptr<int> p(new int(42)); process(shared_ptr<int>(p));
推演：p 是个管家，手里有 42 号房子的钥匙。你拿 p 复制了一个临时管家，丢进 process。这时有两个人管 42 号。
结局：process 执行完，临时管家死了，人数减到 1。p 依然安全地活着，房子没被拆。合法，但多此一举（直接 process(p) 就行）。

process(shared_ptr<int>(p.get()));直接崩溃
推演：p.get() 是什么？是管家 p 偷偷把房子的原始裸钥匙交了出来！然后你居然用这把原始钥匙，凭空又造了一个新的管家，丢进了 process。此时，旧管家 p 和新管家，都以为自己是房子的唯一主人（各自计数为 1）。
结局：process 执行完，新管家死掉，它顺手把房子炸了。此时 p 还傻乎乎地以为自己有房子。等 p 死的时候，它再去炸一次已经没了的房子，程序当场爆炸（Segmentation fault）。

auto p = new int();（p 是毫无保护的裸指针）；auto sp = make_shared<int>();（sp 是智能管家）。
(a) process(sp); 合法。正常交接，安全。
(b) process(new int());  合法。买了个新房子，派个临时管家带去 process，用完后管家带着房子一起死，干净利落。
(c) process(p);  编译报错。process 要的是智能指针，你 p 是个裸指针。C++ 编译器怕你瞎搞，绝对禁止把裸指针隐式转成智能指针。
(d) process(shared_ptr<int>(p));  合法，但极其危险。你把裸指针 p 强行塞给了临时管家。process 结束时，临时管家把房子炸了。此时外面的裸指针 p 指向的是一堆废墟。如果你后续敢 delete p;，直接原地爆炸。

delete p; （其中 p 是 sp.get() 拿出来的裸指针）
推演：sp 这个管家好好地在管着房子，引用计数是 1。你通过 get() 拿到了原始钥匙 p，结果你反手一个 delete p;，直接把房子炸了。
结局：管家 sp 根本不知道房子已经被你炸了。等 sp 离开作用域（或重置）时，它按规矩去拆房，发现房子没了，程序直接崩溃。

终极保命口诀（一定要背下来）：
get() 出来的裸指针，只能看，绝对不能拿来 delete，也绝对不能拿去 new 智能指针！
一个 new 出来的对象，只能交给一个独立的智能指针去管。 绝对不能像 12.11 那样，让两个智能指针同时管一个裸指针。
如果你要创建一个智能指针，永远优先使用 make_shared，不要用 new。

#endif



//p417
#if 0
shared_ptr 只能帮你自动 delete 内存。但现实世界里，很多东西不能只靠 delete。
比如：一个网络连接，你不能直接把它的内存删了，你必须先调用 disconnect() 断开连接，然后再释放内存。
自定义删除器”就是一份遗嘱：告诉智能指针，“等你死的时候，别光顾着 delete，请帮我把这个指定的清理动作（比如断开连接）给执行了。”

connect() 函数负责建立连接，返回一个对象。
disconnect(connection) 函数负责断开连接。
我们要用 shared_ptr 来管理这个连接，而且需要在智能指针销毁时，自动调用 disconnect()。
核心语法：shared_ptr<类型> 指针名(裸指针, 自定义删除器函数);

#include <iostream>
#include <string>
#include <memory> // shared_ptr 需要

using namespace std;

// 1. 定义连接的数据结构
struct connection {
    string ip;
    int port;
    // 构造函数：创建对象时，把 i 和 p 存进 ip 和 port 里
    connection(string i, int p) : ip(i), port(p) { 
        cout << "  [建立连接] " << ip << ":" << port << endl; 
    }
};

// 2. 模拟建立连接（返回 new 出来的裸指针）
connection* connect(string ip, int port) {
    return new connection(ip, port);
}

// 3. 模拟断开连接（清理业务，并真正释放内存）
void disconnect(connection* ptr) {
    cout << "  [断开连接] " << ptr->ip << ":" << ptr->port << endl;
    delete ptr; // 释放 new 出来的内存
}

int main() {
    cout << "=== 开始测试 ===" << endl;
    
    // 4. 调用 connect 建立连接，用裸指针 raw_p 接住
    connection* raw_p = connect("192.168.1.1", 8080);
    
    // 5. 用智能指针接管 raw_p，并给它贴上“遗嘱”
    shared_ptr<connection> p(raw_p, [](connection* ptr) {
        disconnect(ptr); // 当 p 死的时候，会执行这段代码
    });
    
    cout << "  [正在使用连接执行各种操作...]" << endl;
    
    cout << "=== 马上要离开大括号了，p 即将销毁 ===" << endl;
    return 0;
}
 //开始测试 ===
  //[建立连接] 192.168.1.1:8080
  //[正在使用连接执行各种操作...]
 //马上要离开大括号了，p 即将销毁 ===
  //[断开连接] 192.168.1.1:8080//

#endif

 
//p420
#if 0
unique_ptr 是“绝对自私”的指针。 它霸占着某块内存，绝对不允许别人拷贝它，因为一旦拷贝，就有两个人以为自己拥有这块内存，最后就会发生双重释放（程序崩溃）。

拷贝 unique_ptr 会怎样？
unique_ptr<int> p1(new int(42));
unique_ptr<int> p2 = p1; // 编译报错：试图使用已删除的拷贝构造函数

int ix = 1024, *pi = &ix, *pi2 = new int(2048);
typedef unique_ptr<int> IntP; // 给类型起个短名
IntP p0(ix);  编译报错。
原因：ix 是个 int，不是指针。智能指针只能接管地址。
(b) IntP p1(pi); 合法，但极度危险！
原因：pi 是裸指针，指向 ix。编译能过，但 unique_ptr 在销毁时，会调用 delete pi; 去释放内存。
后果：ix 是个局部变量（在栈上），栈上的内存不能 delete！ 程序运行到这里会直接崩溃。unique_ptr 只能接管 new 出来的堆内存。
(c) IntP p2(pi2;  合法，且安全。
原因：pi2 是 new 出来的，在堆上。p2 接管了它，并在销毁时自动 delete，非常完美。
(d) IntP p3(&ix);  合法，但极度危险
原因：和 (b) 一样，&ix 是栈上的地址，交给 unique_ptr 会引发对栈内存的 delete，导致崩溃。
(e) IntP p4(new int(2048));  合法，且安全。
原因：最标准、最推荐的做法。直接接管 new 出来的内存。
(f) IntP p5(p2.get());  极其危险（虽然语法上能编译，但会导致崩溃）。
原因：p2.get() 拿到了 p2 内部保存的裸指针。你拿这个裸指针去初始化 p5。现在 p2 和 p5 都以为自己是这块内存的唯一主人！
后果：等它们俩死的时候，会各自 delete 一次，导致 Double Free（双重释放），程序当场暴毙。

#endif


//423
#if 0


#endif






































































































































