//p337
#if 0
什么是泛型算法？
在之前的章节里，你想在一个 vector 里找元素，得自己写一个 for 循环遍历。
但在 C++ 里，<algorithm>（算法头文件）提供了一套通用工具。
为什么叫“泛型”？
因为标准库里的算法根本不关心你用的是 vector、list 还是数组。它们只认一样东西：迭代器（Iterator）。
只要你能提供一对迭代器表示范围，它就能在这个范围里干活。
std::count 是什么
它专门用来数数。语法是：count(起始迭代器, 结束迭代器, 你要找的值)。它返回那个值出现的次数。

用 count 统计次数
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

using namespace std;
int main(){
     cout << "=== 练习 10.1：vector<int> ===" << endl;
     vector<int> ivec;
    int num;
    cout << "请输入一组整数（Ctrl+D 结束）：" << endl;
    while (cin >> num) {
        ivec.push_back(num);
    }
     int targetInt = 3; // 假设我们要找数字 3
     auto intCount = count(ivec.begin(), ivec.end(), targetInt);
     cout << "数字 " << targetInt << " 出现了 " << intCount << " 次。" << endl;
  
     cout << "\n=== 练习 10.2：list<string> ===" << endl;
      cin.clear(); 
        list<string> slist = {"apple", "banana", "apple", "orange", "apple"};
    
    string targetStr = "apple"; // 假设我们要找 "apple"
    auto strCount = count(slist.begin(), slist.end(), targetStr);
    cout << "字符串 \"" << targetStr << "\" 出现了 " << strCount << " 次。" << endl;

    return 0;
}

#endif



//340
#if 0
accumulate(起, 止, 初始值)：“求和器”。它从初始值开始，把范围内的元素挨个加起来。 注意：它定义在 <numeric> 头文件里，而不是 <algorithm>。
equal(起1, 止1, 起2)：“比对器”。判断两个序列是否一模一样。它假定第二个序列至少和第一个序列一样长

用 accumulate 求和
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;
int main(){
     vector<int> v = {1, 2, 3, 4, 5};
     int sum = accumulate(v.cbegin(), v.cend(), 0); 
     cout << "元素之和: " << sum << endl; // 输出 15
     return 0;
}


vector<double> v; accumulate(v.cbegin(), v.cend(), 0);
有什么错误？
答案：不会报错，但会发生精度丢失（bug）
accumulate 的第三个参数（初始值）决定了整个加法的类型。
因为你传的是 0（int 类型），所以 accumulate 内部在进行 0 + 1.5 时，会把 1.5 截断成 1，最终算出来的和是一个整数。这完全违背了你要算 double 的初衷


equal(起1, 止1, 起2)：“比对器”。如果名册里装的是 C 风格字符串，会怎样？
答案：程序会一直返回 false（判定不相等），即使内容完全一样。
为什么？
equal 算法内部是用 == 来比较元素的。
如果存的是 std::string，== 被重载过，比的是字符串的内容。
如果存的是 const char*（C 风格字符串），== 比较的其实是指针的地址！
所以，即使两个名册里的名字都是 "Alice"，它们指向的也是内存里两块不同的地方，== 判定为 false

#endif


//p343
#if 0
 fill（填充）、fill_n（填充 n 个）、copy（拷贝）。它们统称为写算法。
致命警告：标准库算法不会检查目标容器的大小。如果你往一个只有 3 个元素的空间里写 10 个数据，程序会直接踩坏内存崩溃（段错误）。
为了解决这个问题，C++ 提供了两种方案：
先扩容：用 resize() 把容器真正变大。
插入迭代器：用 back_inserter(vec)，它相当于在背后帮你自动调用 push_back，往里面塞一个就自动加一个，永远不会越界。

用 fill_n 把序列置为 0
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    vector<int> v = {1, 2, 3, 4, 5};
    
    //  从 v.begin() 开始，连续把 5 个元素改成 0
    fill_n(v.begin(), 5, 0); 
    
    for (int x : v) cout << x << " "; // 输出 0 0 0 0 0
    return 0;
}

找错并修正
vector<int> vec; list<int> lst; int i;
while (cin >> i) lst.push_back(i);
copy(lst.cbegin(), lst.cend(), vec.begin());
错误原因：vec 是一个空容器（size = 0）。vec.begin() 等于 vec.end()。copy 算法试图把 lst 里的数据写进 vec 里，但 vec 根本没有分配内存，直接越界踩踏内存（崩溃）
copy(lst.cbegin(), lst.cend(), back_inserter(vec));

vector<int> vec;
vec.reserve(10); 
fill_n(vec.begin(), 10, 0);
错误原因：这是最坑的一个点！reserve(10) 只是把 capacity（容量）变成了 10，但 size（真实元素个数）依然是 0。fill_n 面对 0 个元素的空间强行写 10 个，依然越界崩溃。
修正方法：改成 resize(10)。resize 才是真的把元素填进去了（默认初始化为0），这时候再 fill 就是安全的。
vec.resize(10);
fill_n(vec.begin(), 10, 0);


reserve 不等于 resize：reserve 只建房间（改容量），resize 才真的住人（改大小）。写算法之前，永远检查 size()，而不是 capacity()。
解决写入越界的终极方案：遇到目标容器不够大，第一时间想到 #include <iterator> 和 back_inserter(容器)。
写算法不检查边界：这是 C++ 性能的代价，把安全的检查交给了你。

unique 的实际操作是“覆盖”：
它把不重复的元素全挪到前面，把重复的“垃圾”踢到后面。最后返回一个迭代器，指向“垃圾区”的起点。
要想真的把垃圾扔掉，必须手动调用容器的 erase 成员函数。 这就是大名鼎鼎的 “erase-remove 惯用法”。

为什么算法不改变容器大小？
因为算法操作的是迭代器，它不知道底层容器是什么（vector 还是 list），它没法调用容器的 push_back 或 erase，自然也就无法改变容器的大小。

手写 elimDups 并打印
题目要求分三步打印：读取输入后、unique 后、erase 后。
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 去重函数
void elimDups(vector<string>& words) {
    // 1. 排序，让重复元素挨在一起
    sort(words.begin(), words.end());

    // 2. 把不重复的移到前面，返回“垃圾区”的起点
    auto end_unique = unique(words.begin(), words.end());

    // 打印 unique 之后的情况
    cout << "unique 之后，容器大小: " << words.size() << "，内容: ";
    for (const auto& s : words) cout << "\"" << s << "\" ";
    cout << endl;

    // 3. 真正删除垃圾区的元素
    words.erase(end_unique, words.end());
    
    // 打印 erase 之后的情况
    cout << "erase 之后，容器大小: " << words.size() << "，内容: ";
    for (const auto& s : words) cout << "\"" << s << "\" ";
    cout << endl;
}

int main() {
    vector<string> words;
    string word;

    cout << "请输入单词（Ctrl+D 结束）：" << endl;
    while (cin >> word) {
        words.push_back(word);
    }

    cout << "\n=== 读取输入后，容器大小: " << words.size() << "，内容: " << endl;
    for (const auto& s : words) cout << "\"" << s << "\" ";
    cout << "\n\n";

    elimDups(words);

    return 0;
}


#endif


//345
#if 0
谓词就是“一个返回 true 或 false 的判断函数”。

谓词与排序
stable_sort（稳定排序）：和普通的 sort 类似，但它有一个神奇的属性：如果两个元素“相等”（比如两个单词长度一样），它们原本的先后顺序会被保留。而 sort 可能会打乱它们的原本顺序。
partition（划分）：它拿着你的“谓词”，把容器重新洗牌。让谓词返回 true 的排在前面，返回 false 的排在后面。它返回一个迭代器，指向第一个“返回 false”的元素。

使用 stable_sort 和 isShorter
写一个 isShorter 函数，比较两个字符串长度。然后用 stable_sort 对去重后的 words 排序

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
// 谓词：判断 s1 是否比 s2 短
bool isShorter(const string& s1, const string& s2) {
    return s1.size() < s2.size();
}
// 去重函数（复用上一节的）
void elimDups(vector<string>& words) {
    sort(words.begin(), words.end());
    auto end_unique = unique(words.begin(), words.end());
    words.erase(end_unique, words.end());
}
int main() {
    vector<string> words = {"fox", "jumps", "over", "quick", "red", "slow", "the", "turtle"};
    
    elimDups(words); // 先按字典序去重

    cout << "=== 练习 10.11 ===" << endl;
    // 用 stable_sort 按长度排序，长度相同的保持字典序
    stable_sort(words.begin(), words.end(), isShorter);
    
    for (const auto& s : words) cout << "\"" << s << "\" ";
    cout << endl;
    return 0;
}

compareIsbn 比较 Sales_data
写一个谓词，比较两个 Sales_data 对象的 isbn()。

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
struct Sales_data {
    string bookNo;
    // ... 其他成员
    string isbn() const { return bookNo; }
};
// 谓词：比较 ISBN
bool compareIsbn(const Sales_data& lhs, const Sales_data& rhs) {
    return lhs.isbn() < rhs.isbn();
}

void test_10_12() {
    vector<Sales_data> books = {{"ISBN-2"}, {"ISBN-1"}, {"ISBN-3"}};
    
    // 用 compareIsbn 对 books 排序
    sort(books.begin(), books.end(), compareIsbn);
    
    cout << "\n=== 练习 10.12 ===" << endl;
    for (const auto& book : books) {
        cout << book.isbn() << " ";
    }
    cout << endl;
}

partition 划分长度 >= 5 的单词
调用 partition，它会返回一个边界。边界前面全是 true，后面全是 false
遍历从 begin() 到边界的前面，打印出来

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 谓词：判断字符串长度是否 >= 5
bool lengthIs5OrMore(const string& s) {
    return s.size() >= 5;
}

void test_10_13() {
    vector<string> words = {"fox", "jumps", "over", "quick", "red", "slow", "the", "turtle"};
auto bound = partition(words.begin(), words.end(), lengthIs5OrMore);

 cout << "\n=== 练习 10.13 ===" << endl;
    cout << "长度 >= 5 的单词: ";
    // 从开头遍历到 boundary
    for (auto it = words.begin(); it != bound; ++it) {
        cout << *it << " ";
    }
    cout << endl;
}
stable_sort 保平安：如果你希望长度相同的单词，不要被排得乱七八糟，那就用 stable_sort。它比你想象中慢不了多少，但能保证结果稳定。
partition 返回的是边界：它不返回 true 的个数，返回的是迭代器。指向了划分后的分界线（第一个返回 false 的元素）。
给谓词取个好名字：名字要能体现“判断”的意思，比如 isShorter、lengthIs5OrMore。
#endif


//349    lambda 表达式
#if 0
lambda 就是“原地手写、用完即弃的匿名小函数”。
基本语法是：[捕获列表] (参数列表) -> 返回类型 { 函数体 }
[]：捕获列表（最重要！）。如果 lambda 里面想用外面的变量，必须在这里把变量“抓”进来。
()：参数列表。和普通函数一样。
{}：函数体。写你要干的事

接受两个 int，返回和。
auto add = [](int a, int b) { return a + b; };

捕获所在函数的一个 int，然后跟参数相加。
int local_i = 10;
//  [local_i] 就是把外面的 local_i 捕获进来
auto add_capture = [local_i](int a) { return local_i + a; };

大综合（biggies 函数）
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
// 去重函数（帮你准备干净的数据）
void elimDups(vector<string>& words) {
    sort(words.begin(), words.end());
    auto end_unique = unique(words.begin(), words.end());
    words.erase(end_unique, words.end());
}

void biggies(vector<string>& words, vector<string>::size_type sz) {
    elimDups(words); // 1. 去重并按字典排序

 //  10.17：用 lambda 替换 compareIsbn/isShorter
    // 按长度排序，长度相同的保持字典序
    stable_sort(words.begin(), words.end(),
        [](const string& a, const string& b) { return a.size() < b.size(); });

// 10.16：使用 lambda 和 find_if 找到第一个长度 >= sz 的元素
    // [sz] 捕获外面的参数 sz
    auto wc = find_if(words.begin(), words.end(),
        [sz](const string& s) { return s.size() >= sz; });

    // 计算满足条件的单词数量
    auto count = words.end() - wc;
    cout << count << " 个单词长度大于等于 " << sz << "。" << endl;

 // 10.18：重写 biggies，用 partition 替代 find_if
    auto bound = partition(words.begin(), words.end(),
        [sz](const string& s) { return s.size() >= sz; });
    
    cout << "（partition 版本）: ";
    for (auto it = words.begin(); it != bound; ++it) {
        cout << *it << " ";
    }
    cout << endl;

    //  10.19：用 stable_partition 重写，保证划分后原顺序不变
    // 重新打乱一下数据测试稳定划分
    elimDups(words); 
    auto bound2 = stable_partition(words.begin(), words.end(),
        [sz](const string& s) { return s.size() >= sz; });
    
    cout << "（stable_partition 版本）: ";
    for (auto it = words.begin(); it != bound2; ++it) {
        cout << *it << " ";
    }
    cout << endl;



获列表 [] 是灵魂：
[]：空，什么外面的变量都不用。
[sz]：值捕获，把外部的 sz 拷贝一份进来，只能读不能改。
[&sz]：引用捕获，直接操作外面的 sz;

#endif


//p354
#if 0
count_if（带条件的计数器）：
你之前学过 count，它是找“等于某个值”的个数。而 count_if 是找“满足某个条件（谓词）”的个数。只要你的谓词返回 true，它就加 1。
mutable（解封咒语）：
默认情况下，lambda 的值捕获（就是直接写 [val]）是只读的！你在 lambda 内部不能修改捕获的变量（编译器会认为它加了 const）。如果你想在 lambda 内部修改它，必须在参数列表后面加上 mutable 关键字。

用 count_if 统计长度超过 6 的单词
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
void test_10_20() {
    vector<string> words = {"hello", "world", "cppprimer", "good", "longword"};
    
    //  核心：谓词 lambda 判断长度是否大于 6
    auto count = count_if(words.begin(), words.end(), 
        [](const string& s) { return s.size() > 6; });

    cout << "=== 练习 10.20 ===" << endl;
    cout << "长度超过 6 的单词有 " << count << " 个。" << endl;
}

递减直到为 0 的 lambda
捕获一个局部变量，写个 lambda，每次调用它，它就减 1。减到 0 以后，返回 true，不再继续减。
#include <iostream>
using namespace std;
void test_10_21() {
    int val = 5;
    
    // 必须加 mutable，否则修改 val 会报错！
    auto decreaseToZero = [val]() mutable -> bool {
        if (val > 0) {
            --val; // 因为加了 mutable，这里才能修改 val
        }
        return val == 0;
    };

    cout << "\n=== 练习 10.21 ===" << endl;
    for (int i = 0; i < 7; ++i) {
        bool isZero = decreaseToZero();
        cout << "第 " << i + 1 << " 次调用，返回: " << (isZero ? "true" : "false") << endl;
    }


mutable 是什么？ 它是 lambda 的“解封咒语”。没有它，你在 {} 里修改 val 会直接报错：cannot assign to a variable captured by copy in a non-mutable lambda。
值捕获的本质是“拷贝”：你在 lambda 里面把 val 从 5 减到 0，但外面的 val 依然是 5。lambda 修改的只是它自己保存的一份副本。
lambda 的返回值：如果你用 -> bool 指定了返回值，记得一定要有 return 语句。如果只有一个 return 语句，-> bool 其实也可以省略，编译器会自动推导。
#endif

//p357  bind 
#if 0
假设你有一个函数 bool check(int a, int b)。你每次只想传 b，a 固定为 10。
bind 就可以帮你把 a 焊死成 10，留下 b 变成一个“坑（占位符 _1）”。
生成的新函数，只要传 1 个参数就行了。

语法：auto new_func = bind(原函数, 固定的参数, 占位符_1, ...);

使用函数代替 lambda



#endif


//p359
#if 0
之前我们说“标准库算法不能改变容器大小”，如果你要把数据写到空容器里，直接写 copy(v.begin(), v.end(), empty.begin()) 会直接崩溃。
插入迭代器的存在，就是为了解决这个“容器不够大”的问题。

back_inserter（尾部插入器）：
动作：永远把元素塞到容器的最后面。
底层：调用容器的 push_back()。

front_inserter（头部插入器）：
动作：永远把元素塞到容器的最前面。
底层：调用容器的 push_front()。

inserter（通用插入器）：
动作：塞到你指定的位置（通过传入一个迭代器作为第二个参数）。
底层：调用容器的 insert()。

使用 unique_copy 将去重后的元素拷贝到空 list
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator> //  必须包含这个头文件

using namespace std;

void test_10_27() {
    vector<int> vi = {1, 2, 2, 3, 4, 4, 4, 5, 6, 6, 7};
    list<int> li; // 初始为空的 list

    // 拷贝时，遇到重复的只拷贝第一个。存到 li 的尾部
    unique_copy(vi.begin(), vi.end(), back_inserter(li));

    cout << "=== 练习 10.27 ===" << endl;
    cout << "去重后的 list 内容: ";
    for (int x : li) cout << x << " ";
    cout << endl;
}


将 vector 中的 1 到 9 拷贝到三个容器，分别用 inserter、back_inserter、front_inserter。估计输出并验证。
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
using namespace std;

void test_10_28() {
    vector<int> vi = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    list<int> lst1, lst2;
    vector<int> vec;

    // 1. 使用 back_inserter，追加到尾部
    copy(vi.begin(), vi.end(), back_inserter(lst1));

    // 2. 使用 front_inserter，每次插入到头部
    copy(vi.begin(), vi.end(), front_inserter(lst2));

    // 3. 使用 inserter，指定插入到 vec 的尾部
    copy(vi.begin(), vi.end(), inserter(vec, vec.end()));

    cout << "\n=== 练习 10.28 ===" << endl;
    
    cout << "back_inserter (尾部插入): ";
    for (int x : lst1) cout << x << " ";
    cout << endl;

    cout << "front_inserter (头部插入): ";
    for (int x : lst2) cout << x << " ";
    cout << endl;

    cout << "inserter (在末尾插入): ";
    for (int x : vec) cout << x << " ";
    cout << endl;
}

#endif


//p363
#if 0
流迭代器（Stream Iterators）。
以前我们要读数据，得写 while(cin >> x) v.push_back(x);；要写数据，得写 for (int x : v) cout << x << " ";。现在，有了流迭代器，你可以把 cin 和 cout 直接当成容器来用，

istream_iterator<T> in(cin);：“吸管”。它把键盘输入（或文件）当成一个源源不断产生 T 类型数据的容器。in 指向当前读到的元素。当读到文件末尾时，它会等于 istream_iterator<T>()（
ostream_iterator<T> out(cout, "分隔符");：“漏斗”。你往里面扔一个元素，它就会把元素和分隔符一起输出到屏幕上（或文件里）

流迭代器读文本文件
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <fstream>

using namespace std;

void test_10_29() {
    cout << "=== 练习 10.29 ===" << endl;
    // 模拟文件内容
    istringstream fileContent("hello world cpp primer");
    // 两个流迭代器，一个指开头，一个指文件末尾(默认构造)
    istream_iterator<string> in_iter(fileContent), eof;
    // 用流迭代器范围直接初始化 vector
    vector<string> words(in_iter, eof);
    cout << "读取到 " << words.size() << " 个单词" << endl;
}

istringstream fileContent("...");
istream_iterator<string> in_iter(fileContent), eof;
这行代码其实定义了两个迭代器！中间有个逗号 ,。
这是一个字符串输入流。它把 "hello world cpp primer" 这句话装进了一根水管里。你可以把它当成一个虚拟的 cin，只不过里面的内容是你手写死的。
第一个：in_iter(fileContent)。它绑定到了刚才那根水管上。它代表水管里的“当前”位置。 只要你对它进行 ++ 操作，它就会从水管里吸出下一个单词（以空格为界）。因为模板是 <string>，所以它每次吸出来的是一个字符串。
第二个：eof。它没有传任何参数。 在 C++ 里，不传参数的流迭代器（默认构造函数）专门代表“水流干了（文件末尾/EOF）”。它就是个路标，告诉你“到这儿就没水了”。
vector<string> words(in_iter, eof);

这是 vector 的范围构造函数（你之前在 9.2 节学过）。
它拿着 in_iter（起点，刚开始水管里第一个词是 "hello"）和 eof（终点），开始疯狂循环：
把 "hello" 放进 vector。
in_iter 自动 ++，吸出下一个词 "world"，放进 vector。
in_iter 自动 ++，吸出 "cpp"，放进 vector。
in_iter 自动 ++，吸出 "primer"。
再 ++ 的时候，水管空了！in_iter 发现了终点，变成了和 eof 一样的状态。
循环结束！vector 里完美装进了 4 个单词



读入、排序、去重并输出
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;
void test_10_30_31() {
    cout << "\n=== 练习 10.30 & 10.31 ===" << endl;
    cout << "请输入几个整数（Ctrl+D 结束）：" << endl;
    
    // 1. 读取（吸管）
    istream_iterator<int> in(cin), eof;
    vector<int> v(in, eof);
     // 2. 排序
    sort(v.begin(), v.end());
    
    // 3. 输出（漏斗，用空格分隔）
    ostream_iterator<int> out(cout, " ");
    
    // 10.30 直接输出：
    cout << "排序后: ";
    copy(v.begin(), v.end(), out);
    cout << endl;

    // 10.31 去重输出 (unique_copy 需要先排序)
    cout << "去重后: ";
    unique_copy(v.begin(), v.end(), out);
    cout << endl;
}
构造了一个输出迭代器 out。
第一个参数 cout：指定流向哪里（流向屏幕）。
第二个参数 " "：这是一个分隔符。每次你往 out 里扔一个数据，它会自动在末尾加上这个分隔符
copy(v.begin(), v.end(), out); 的时候，copy 会挨个把 v 里的元素赋给 *out，屏幕就会自动输出带空格的一组数字



重写书店程序（vector + 算法版）
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

// 简易版 Sales_data
struct Sales_data {
    string bookNo;
    double revenue = 0.0;
    string isbn() const { return bookNo; }
};

// compareIsbn 谓词
bool compareIsbn(const Sales_data& a, const Sales_data& b) {
    return a.isbn() < b.isbn();
}

void test_10_32() {
    cout << "\n=== 练习 10.32 ===" << endl;
    vector<Sales_data> books = {
        {"ISBN-2", 100.0}, {"ISBN-1", 50.0}, 
        {"ISBN-2", 150.0}, {"ISBN-3", 200.0}
    };

    // 1. 排序，让相同的 ISBN 挨在一起
    sort(books.begin(), books.end(), compareIsbn);

    // 2. 遍历并累加
    auto it = books.begin();
    while (it != books.end()) {
        // find_if 找到下一个不同的 ISBN
        auto next_it = find_if(it, books.end(), 
            [it](const Sales_data& b) { return b.isbn() != it->isbn(); }
        );
        
        // accumulate 累加当前 ISBN 的收入
        double total_rev = accumulate(it, next_it, 0.0, 
            [](double sum, const Sales_data& b) { return sum + b.revenue; }
        );
        
        cout << it->isbn() << " 总收入: " << total_rev << endl;
        it = next_it; // 移动到下一个 ISBN
    }
}

输入文件，输出两个文件（奇偶分离）
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>

using namespace std;

void test_10_33() {
    cout << "\n=== 练习 10.33 ===" << endl;
    
    ifstream in("input.txt");
    ofstream out_odd("odd.txt");
    ofstream out_even("even.txt");

    if (!in) {
        cout << "错误：找不到 input.txt" << endl;
        return;
    }

    // 输入迭代器
    istream_iterator<int> in_iter(in), eof;
    // 输出迭代器：奇数后跟空格，偶数后跟换行
    ostream_iterator<int> out_odd_iter(out_odd, " ");
    ostream_iterator<int> out_even_iter(out_even, "\n");

    // 核心逻辑：遍历输入流，判断奇偶，分配到两个输出流
    for (auto it = in_iter; it != eof; ++it) {
        if (*it % 2 != 0) {
            *out_odd_iter++ = *it; // 奇数
        } else {
            *out_even_iter++ = *it; // 偶数
        }
    }
    cout << "处理完成！请查看 odd.txt 和 even.txt" << endl;
}

ifstream in("input.txt");：打开你电脑硬盘上的 input.txt 文件，把里面的数据当成水管的源头。接下来的 in 就可以当 cin 一样用。
ofstream out_odd("odd.txt");：在硬盘上创建/打开 odd.txt 文件。接下来的 out_odd 就可以当 cout 一样用，只不过它不在屏幕上打印，而是把字写进这个文件里。

如果你用 cin 读数据，必须先用 while 循环把数据存进 vector，然后再去调 sort。
有了流迭代器，一步到位：
从键盘读数字，直接排序，直接打到屏幕上！
sort(istream_iterator<int>(cin), istream_iterator<int>(), ostream_iterator<int>(cout, " "));
#endif


//p367
#if 0
反向迭代器（reverse_iterator）倒着走的指针
反向迭代器反过来，从最后一个元素往前走（rbegin() 到 rend()）。

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

using namespace std;
int main() {
    // ================= 练习 10.34 =================
    cout << "=== 练习 10.34: 反向迭代器 ===" << endl;
    vector<int> v1 = {1, 2, 3, 4, 5};
    
    // rbegin() 指向最后一个元素(5)，rend() 指向第一个元素之前
    for (auto rit = v1.rbegin(); rit != v1.rend(); ++rit) {
        cout << *rit << " ";
    }
    cout << endl;
    
rbegin() 和 rend() 的本质：
rbegin() 指向最后一个元素。
rend() 指向第一个元素之前的位置（它不是 begin()，而是 begin() 的前一个位置）。


#endif






































