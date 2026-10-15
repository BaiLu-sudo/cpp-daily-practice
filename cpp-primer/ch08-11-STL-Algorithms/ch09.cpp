//p294
#if 0
vector（动态数组）：排成一排的停车位。车都挨着停。
优点：找车位快（随机访问 v[i]），在末尾停车快（push_back）。
缺点：如果要在中间或者头部插队，后面的车全都要往后挪，费老鼻子劲了。
deque（双端队列）：两头都能进出的长管子。
优点：头部和尾部都能快速塞东西、快速取东西（push_front、pop_front、push_back 都很快）。
缺点：在正中间插入依然比较慢。
list（双向链表）：用一根线串起来的珠子。
在任何位置插入或删除，只要把线解开，把新珠子串上去就行（O(1)复杂度）

频繁在中间插入/删除 用 list
频繁在两端插入/删除 用 deque。
需要随机访问（用下标 [i]）、排序、节省内存 用 vector。
初学者日常写代码，无脑首选 vector，除非明显发现它在头部/中间插入很慢

#endif


//p269
#if 0
//定义一个 list 对象，其元素类型是 int 的 deque。
内层：是一个 deque<int>（一个两头都能进出的“整数排队管子”）。
外层：是一个 list< ... >（一个用链子串起来的容器）。
合起来：这个 list 里装的不是普通的整数，而是装着一整根“整数 deque”的管子

std::list<std::deque<int>>mylist;
#endif

//p297
#if 0
构成迭代器范围的迭代器有何限制？
同一个容器：begin 和 end 必须指向同一个容器（你不能拿 v1.begin() 和 v2.end() 去凑一对）。
顺序正确：begin 必须指向 end 所指向位置之前（或者相等，此时范围为空）。
可达性：从 begin 开始不断执行 ++ 操作，必须能到达 end。如果越过了 end，就是非法范围。

编写查找函数
#include<iostream>
#include<vector>

using std::cout;using std::endl;using std::vector;
bool find_val(vector<int>::iterator begin,vector<int>::iterator end,int val){
    for(auto it ==begin;it !=end;++it){
        if(*it ==val)return true;
    }
    return false;
}

返回迭代器
vector<int>::interator find_val_iter(vector<int>::iterator begin,vector<int>::iterator end,int val){
    for(atuo it =begin;it !=end;++it){
        if(*it ==val)return it;
    }
    return end;
}

找出程序错误
list<int> lst1;
list<int>::iterator iter1 = lst1.begin(),
                     iter2 = lst1.end();
while (iter1 < iter2) /* ... */
list（双向链表）的迭代器不支持 < 运算符！只有 vector 和 deque 的迭代器（随机访问迭代器）才支持比较大小。
修正方法：把 < 改成 !=

返回值类型：vector<int>::iterator
人话：这个函数如果找到了，会返回一个检票员（指向那个元素的迭代器）。
参数 1：vector<int>::iterator begin
人话：告诉我从哪个检票员开始找。
参数 2：vector<int>::iterator end
人话：告诉我找到哪个检票员为止（找到他之前，就停下）。
参数 3：int val
人话：我要找的那个 int 是什么。

#include <iostream>
#include <vector>

using std::cout; using std::endl; using std::vector;

// ⭐ 按标准写法定义函数
vector<int>::iterator find_val_iter(vector<int>::iterator begin, vector<int>::iterator end, int val) {
    for (auto it = begin; it != end; ++it) {
        if (*it == val) return it;
    }
    return end; 
}

int main() {
    vector<int> v = {10, 20, 30, 40, 50};

    // 1. 查整个容器
    auto it1 = find_val_iter(v.begin(), v.end(), 30);
    if (it1 != v.end()) {
        cout << "在整辆车里找到了 30，下标是: " << (it1 - v.begin()) << endl;
    }

    // 2. ⭐ 只查一部分（只查从下标 3 开始到末尾）
    auto it2 = find_val_iter(v.begin() + 3, v.end(), 30);
    if (it2 == v.end()) {
        cout << "在下标 3 之后的范围里，没找到 30" << endl;
    }
    
    return 0;
}


vector<int>::size_type
int 是有符号整数（最高约 21 亿），而 vector 的大小可能非常大，甚至超过 int 的上限。
为了绝对安全，C++ 规定 vector 的大小和索引必须用一个专门的无符号整型，叫做 size_type。
在 Ubuntu 64 位系统上，它通常等价于 unsigned long。
你平时写 int i 之所以没报错，只是因为你的 vector 没装满过。




// 初学者写法（容易触发警告）
for (int i = 0; i < v.size(); ++i) { ... } 
// 标准写法（推荐，安全）
for (vector<int>::size_type i = 0; i < v.size(); ++i) { ... }
// 现代 C++ 最推荐写法（用 auto 偷懒，编译期自动推导）
for (auto i = 0; i < v.size(); ++i) { ... }


#endif



//p299
#if 0
begin 和 cbegin 有什么区别？
begin()：普通检票员。如果这个容器本身是可以修改的（非 const），那他拿到的就是普通的迭代器，你可以通过他修改车里的数据。
cbegin()：只读检票员（c 代表 const）。不管容器本身是不是只读的，他拿到的都是 const_iterator（常量迭代器）。你只能看，不能改。

这 4 个对象分别是什么类型？
it1：vector<int>::iterator（普通迭代器，可读可写）
it2：vector<int>::const_iterator（常量迭代器，只读）
it3：vector<int>::const_iterator（常量迭代器，只读）
it4：vector<int>::const_iterator（常量迭代器，只读）

v1 是普通 vector<int>，所以 v1.begin() 返回 iterator，v1.cbegin() 返回 const_iterator。
v2 是 const vector<int>（常量对象），所以无论调用 begin 还是 cbegin，它返回的都必须是 const_iterator（因为你是只读对象，我不能给你一个能改数据的权限）

6 种创建和初始化 vector 的方法
空的 vector：vector<int> v1;

值：空的，size() 为 0。

拷贝构造（复制另一个 vector）：vector<int> v2(v1);（或 = v1）

值：和 v1 一模一样。

列表初始化（C++11）：vector<int> v3 = {1, 2, 3, 4, 5};

值：包含 1, 2, 3, 4, 5。这是最直观的写法。
指定数量和初值：vector<int> v4(5, 42);（⚠️ 注意是圆括号）
值：包含 5 个元素，每个都是 42。
只指定数量（默认初始化）：vector<int> v5(5);
值：包含 5 个元素，每个都是 0（int 的默认值）。
迭代器范围初始化：vector<int> v6(v3.begin(), v3.end());
值：把 v3 里的所有元素拷贝一份给 v6。

两种拷贝构造的区别
接受一个容器（vector<int> v2(v1)）：要求 v2 和 v1 的类型完全相同（都是 vector<int>）。它直接把底层数据拷贝一份。
接受两个迭代器（vector<int> v2(v1.begin(), v1.end())）：不要求容器类型完全一致！ 只要元素类型能转换就行。比如，它可以把 list<int> 变成 vector<double>，或者把 vector<char> 变成 vector<int>。它通过迭代器逐个取元素，然后逐个构造新元素。



list<int> 和 vector<int> 转 vector<double>
list<int> myList = {1, 2, 3};
vector<int> myVec = {4, 5, 6};
// 从 list<int> 初始化 vector<double>
vector<double> vd1(myList.begin(), myList.end());
// 从 vector<int> 初始化 vector<double>
vector<double> vd2(myVec.begin(), myVec.end());


赋值 vs assign
在 C++ 里，给容器“换血”有两种方式：
赋值运算符 =：要求两边类型必须完全一样。
vector<int> v1; vector<int> v2; v1 = v2; （合法，都是 vector<int>）。
如果是 list<int> 直接 = 给 vector<int>，编译器会直接报错，因为它们类型不兼容。
成员函数 assign：这是一个万能换血器。它接受两个迭代器（表示一段范围）。
语法：目标容器.assign(源.begin(), 源.end());
它的威力在于：它会把目标容器清空，然后依据两个迭代器开始遍历，把元素逐个塞进来。只要元素类型能转换（比如 const char* 转 string），它就能工作！



把一个 list 中的 char * 指针（C风格字符串）赋值给一个 vector 中的 string
#include <iosteam>
#include <list>
#include <string>
#include<vector>
using std::cout; using std::endl; using std::list; using std::vector; using std::string;

int main(){
    list<const char*> charList = {"hello", "world", "c++"};
    vector<string> stringVec;

    stringVec.assign(charList.begin(), charList.end());
   cout << "=== 练习 9.14 验证 ===" << endl;
    cout << "vector 的元素个数: " << stringVec.size() << endl;
    cout << "vector 的内容: ";
    for (const auto& s : stringVec) {
        cout << s << " ";
    }
    cout << endl;

    return 0;

}
#endif



//p305
#if 0
比较两个 vector<int>
规则：C++ 里的容器重载了 == 运算符。两个 vector 相等，必须同时满足两个条件：

#include <iostream>
#include <vector>
using std::cout; using std::endl; using std::vector;

int main(){
    vector<int> v1 = {1, 2, 3};
    vector<int> v2 = {1, 2, 3};
    vector<int> v3 = {1, 2, 4};
    vector<int> v4 = {1, 2};

    cout << "v1 == v2: " << (v1 == v2) << endl; // 1 (真)
    cout << "v1 == v3: " << (v1 == v3) << endl; // 0 (假，元素不同)
    cout << "v1 == v4: " << (v1 == v4) << endl; // 0 (假，长度不同)
    return 0;
}


比较 list<int> 和 vector<int>
绝对不能用 == 直接比较！ 因为它们类型不同（一个是 list，一个是 vector）。编译器会直接报错：no match for 'operator=='。
人话思路：必须自己写一个函数，先用 size() 比长度，长度相同的话，再用迭代器逐个元素比对

#include <iostream>
#include <vector>
#include <list>
using std::cout; using std::endl; using std::vector; using std::list;

bool compare_list_and_vector(const list<int>&lst,const vector<int>&vec){
    if(lst.size()!=vec.size())return false;
    auto it1=lst.begin();
    auto it2 =vec.begin();
    while(it1 !=lst.end()){
        if(*it1 !=*it2)return false;
         ++it1;
        ++it2;
    }
    return true;
}
int main() {
    list<int> lst = {1, 2, 3};
    vector<int> vec1 = {1, 2, 3};
    vector<int> vec2 = {1, 2, 4};

    cout << "lst == vec1: " << (compare_list_and_vector(lst, vec1) ? "相等" : "不相等") << endl;
    cout << "lst == vec2: " << (compare_list_and_vector(lst, vec2) ? "相等" : "不相等") << endl;
    return 0;
}



if (c1 < c2) 有何限制？
容器类型必须完全相同：c1 和 c2 必须都是 vector<int>，或者都是 list<int>。不能拿 vector<int> 和 list<int> 去比 <。
元素类型必须支持 < 比较：如果容器里装的是自定义对象（比如 struct Person），而你没给 Person 重载 < 运算符，那么 c1 < c2 也会报错。
比较规则是“字典序（Lexicographical Comparison）”：就像查英语字典。
先比第一个元素，谁的第一个元素小，谁就小。
如果第一个元素相等，就比第二个元素，以此类推。
如果某个容器提前耗尽了元素，那么短的那个容器更小。
vector<int> a = {1, 2, 3};
vector<int> b = {1, 2, 4};
cout << "a < b: " << (a < b) << endl; // 1（真，因为 3 < 4）
vector<int> c = {1, 2};
cout << "c < a: " << (c < a) << endl; // 1（真，因为 c 是 a 的前缀，短的更小）

#endif

//p309

#if 0

尾部（push_back）：
vector：非常快（如果没满，直接放；满了就扩容搬一次家）。
deque：非常快。
list：非常快。
头部（push_front）：
vector：完全不支持（因为数组头部没预留空间，硬塞要全体后移，C++ 直接禁用）。
deque：非常快（这是 deque 的看家本领）
list：非常快
中间（insert）：
vector：极慢（因为要腾位置，后面的元素全部往后挪，平均耗时 O(n)）。
deque：比较慢。
list：非常快（改个指针就行）。


从标准输入读取 string 存入 deque，并用迭代器打印
#include <iostream>
#include <deque>
#include <string>
using namespace std;

int main(){
    deque<string>dq;
    string word;
    cout << "请输入字符串（Ctrl+D 结束）：" << endl;
    
    while (cin >> word) {
        dq.push_back(word);
    }

    cout << "deque 中的内容: ";
    for (auto it = dq.begin(); it != dq.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}

用 list 替代 deque，要改什么？
只需要把声明从 deque<string> 改成 list<string> 

从 list<int> 拷贝到两个 deque
人话思路：遍历 list，如果是偶数，就丢到偶数 deque 尾部；奇数就丢到奇数 deque 尾部。这里用 push_back 或者 push_front 都可以，但 push_back 更符合直觉。
#include <iostream>
#include <list>
#include <deque>
using namespace std;

int main(){
    list<int>lst= {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
     deque<int> evenDeque, oddDeque;

     for (int num : lst) {
        if (num % 2 == 0) {
            evenDeque.push_back(num); // 偶数放这里
        } else {
            oddDeque.push_back(num);  // 奇数放这里
        }
    }

      cout << "偶数 deque: "; for (int x : evenDeque) cout << x << " "; cout << endl;
    cout << "奇数 deque: "; for (int x : oddDeque) cout << x << " "; cout << endl;
    return 0;
}

#endif

//312
#if 0
// 删除 [elem1, elem2) 范围内的元素
auto it = c.erase(elem1, elem2);
如果 elem1 与 elem2 相等：
[elem1, elem2) 是空区间。
结果：什么都不删，返回 elem1。
如果 elem2 是尾后迭代器（end()）：
删除从 elem1 开始，一直到容器末尾的所有元素。
结果：elem1 之后（包括它）的所有元素都被删掉，返回 end()。
如果 elem1 和 elem2 皆为尾后迭代器：
也就是 [end(), end())。
结果：同样是空区间，什么都不删，返回 end()。


从 list 删奇数，从 vector 删偶数
用数组 ia = {0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89} 拷贝到 list 和 vector，然后使用单迭代器版本的 erase 分别删除奇数和偶数。

#include <iostream>
#include <vector>
#include <list>
using std::cout; using std::endl; using std::vector; using std::list;

int main() {
    int ia[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};
    
    // 用数组范围初始化 list 和 vector
    list<int> lst(ia, ia + 11);
    vector<int> vec(ia, ia + 11);

    // 1. 从 list 中删除奇数
    auto it1 = lst.begin();
    while (it1 != lst.end()) {
        if (*it1 % 2 != 0) { // 是奇数
            it1 = lst.erase(it1); // ⭐ 删除后，it1 已经自动指向下一个元素
        } else {
            ++it1; // 不是奇数，手动往后走
        }
    }
    // 2. 从 vector 中删除偶数
    auto it2 = vec.begin();
    while (it2 != vec.end()) {
        if (*it2 % 2 == 0) { // 是偶数
            it2 = vec.erase(it2); // ⭐ 同理，必须重新接收迭代器
        } else {
            ++it2;
        }
    }
      // 3. 打印验证
    cout << "list (删掉奇数后): ";
    for (int x : lst) cout << x << " ";
    cout << endl;

    cout << "vector (删掉偶数后): ";
    for (int x : vec) cout << x << " ";
    cout << endl;

    return 0;
}
#endif


//p322
#if 0
string 也是容器：它有迭代器，有 push_back，也能用范围构造函数。
reserve() 是性能利器：如果你能预知大概需要多少字符，务必用 reserve() 提前预留。这在读取大文件或处理海量字符串时，能把速度提升几十倍。
reserve 和 resize 的区别
reserve(100)：只扩展容量（房间建好了，但没住人），size 还是 0。
resize(100)：真的住进去了 100 个元素，多出来的会被默认初始化为 '\0'，size 变成 100。

从 vector<char> 初始化 string
人话思路：string 有一个“范围构造函数”，就像 vector 一样。只要给它两个迭代器，它就会把范围内的字符全抄过来。
#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main() {
    vector<char> vc = {'H', 'e', 'l', 'l', 'o'};
    
    //核心写法：用 vector 的迭代器范围初始化 string
    string s(vc.begin(), vc.end());
    
    cout << "从 vector<char> 得到的 string: " << s << endl; // 输出 Hello
    return 0;
}

已知要读 100 个字符，如何提高性能？
如果在读入之前，你明确知道“至少要 100 个字符”，那就应该提前一次性把空间准备好。否则，随着字符不断加入，string 会像 vector 一样反复“搬家”（扩容），每次搬家都要拷贝一遍旧数据，非常浪费时间。
调用 reserve(100)

#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    s.reserve(100); // 关键：提前预留 100 个字符的空间，避免频繁扩容

    char c;
    int count = 0;
    cout << "请输入字符（Ctrl+D 结束）：" << endl;
    while (cin >> c && count < 100) {
        s += c; // 追加字符
        ++count;
    }

    cout << "读取到的字符串: " << s << endl;
    cout << "当前 size: " << s.size() << ", capacity: " << s.capacity() << endl;
    return 0;
}

#endif


//p324
#if 0
find 和 replace 是什么？
find(oldVal, pos)：从 pos 下标开始，往后找 oldVal。找到了，返回第一次出现的下标；找不到，返回 string::npos（一个非常巨大的无符号数，代表“找不到”）。
replace(pos, len, newVal)：从 pos 开始，把长度为 len 的一段字符，替换成 newVal。
s.erase(iter1, iter2)：把迭代器范围 [iter1, iter2) 内的字符全删掉。
s.insert(iter, val)：在迭代器 iter 指向的位置之前，插入 val，返回插入的第一个字符的迭代器。
s.append(str)：在字符串末尾追加 str。

接受 s、oldVal、newVal，把 s 里所有的 oldVal 替换成 newVal
#include <iostream>
#include <string>
using namespace std;

void replace_with_iter(string& s, const string& oldVal, const string& newVal) {
    auto it = s.begin();
    while (it != s.end()) {
        // 判断从当前迭代器开始的字符是否和 oldVal 匹配
        if (string(it, it + oldVal.size()) == oldVal) { 
            // 1. 先删掉旧词 (erase 返回删除后的下一个位置)
            it = s.erase(it, it + oldVal.size());
            // 2. 插入新词 (insert 返回插入的第一个字符位置)
            it = s.insert(it, newVal.begin(), newVal.end());
            // 3. ⭐ 跳过新插入的词，防止死循环
            it += newVal.size();
        } else {
            ++it; // 不匹配，往后走一步
        }
    }
}

int main() {
    string s = "tho thru tho";
    replace_with_iter(s, "tho", "though");
    replace_with_iter(s, "thru", "through");
    cout << "9.43 结果: " << s << endl; // 输出: though through though
    return 0;
}

用下标 + replace 替换
#include <iostream>
#include <string>
using namespace std;

void replace_with_index(string& s, const string& oldVal, const string& newVal) {
    size_t pos = 0;
    while ((pos = s.find(oldVal, pos)) != string::npos) {
        // 找到后，直接用 replace 一步到位
        s.replace(pos, oldVal.size(), newVal);
        // ⭐ 跳过新替换的字符串，防止无限替换
        pos += newVal.size();
    }
}



find 找不到会返回 string::npos（不是 -1，是一个很大的无符号数）。判断条件必须写 != string::npos。
防止死循环：如果替换后的 newVal 里面包含了 oldVal（比如把 "a" 替换成 "aa"），find 会一直找下去。必须在替换后跳过去：pos += newVal.size();。
迭代器 vs 下标：
用迭代器删除插入，需要小心更新迭代器 it = s.erase(...); 和 it = s.insert(...);。
用下标的话，replace 和 insert 接受下标版本，逻辑更直观，推荐初学者用下标。
erase + insert 与 replace 的选择：
用 replace(pos, len, newVal) 一行搞定，代码短，语义明确。
用 erase + insert，要分两步，但能更灵活地处理迭代器。
#endif


//p328
#if 0
find_first_of(目标字符集)：“找第一个属于目标字符集的字符”。
比如：s.find_first_of("0123456789")，就是找 s 中第一个数字的位置。
find_first_not_of(目标字符集)：“找第一个不属于目标字符集的字符”。
比如：s.find_first_not_of("0123456789")，就是找 s 中第一个非数字的位置（也就是字母）。
这两个函数用来做“提取数字”或“提取字母”这类任务非常方便

numbers.find(name) 返回什么？
name = "r2d2"，numbers = "0123456789"。
numbers.find(name) 的意思是：在 "0123456789" 这个字符串里，找 "r2d2" 这个子串。
因为 numbers 里根本没有字母 r，也没有 "r2d2" 这个连续的序列。
所以，它找不到，返回 string::npos。





对字符串 "ab2c3d7R4E6"，分别查找数字和字母。
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s = "ab2c3d7R4E6";
    string numbers = "0123456789";
    string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    cout << "=== 版本一：find_first_of ===" << endl;
    cout << "所有数字: ";
    for (size_t pos = 0; (pos = s.find_first_of(numbers, pos)) != string::npos; ++pos) {
        cout << s[pos] << " ";
    }
    cout << endl;

    cout << "所有字母: ";
    for (size_t pos = 0; (pos = s.find_first_of(letters, pos)) != string::npos; ++pos) {
        cout << s[pos] << " ";
    }
    cout << endl;




stack（栈）和 queue（队列）不是全新的容器，而是容器适配器。它们底层是用 deque 或 list 实现的，但对外隐藏了大部分功能，只提供特定的操作：
stack（栈）：“一摞盘子”。后进先出（LIFO）。只能从顶部 push（放盘子）和 pop（拿盘子）。
queue（队列）：“排队买奶茶”。先进先出（FIFO）。从尾部 push（新人排队），从头部 pop（前面的人买完走人）

#include <iostream>
#include <stack>
#include <string>

using namespace std;
int main() {
    // 模拟一个输入表达式
    string expr = "(1 + (2 * 3))";
    stack<string> st;
     for (char c : expr) {
        if (c == '(') {
            st.push("("); // 左括号入栈
            cout << "遇到 '('，入栈" << endl;
        } 
        else if (c == ')') {
            cout << "遇到 ')'，开始弹出直到左括号：" << endl;
            // 1. 弹出所有内容，直到遇到左括号
            while (!st.empty() && st.top() != "(") {
                cout << "  弹出: " << st.top() << endl;
                st.pop();
            }
            // 2. 把左括号也弹出去
            if (!st.empty()) {
                st.pop(); // 弹出 "("
                cout << "  弹出: (" << endl;
            }
            // 3. 将一个值（代表运算结果）压入栈中
            st.push("res"); // 用 "res" 代表括号内算完的结果
            cout << "  压入结果: res" << endl;
        } 
        else if (c != ' ') {
            // 如果是数字或运算符，也入栈
            st.push(string(1, c));
            cout << "遇到字符 '" << c << "'，入栈" << endl;
        }
    }


#endif






























