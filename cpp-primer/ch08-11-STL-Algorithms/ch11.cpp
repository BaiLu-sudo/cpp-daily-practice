//p376
#if 0
ector、list 都是顺序容器（按位置排队），而 map 和 set 是关联容器（按值/键找东西）
什么是 map 和 set？
map（字典）：它是一堆键值对（Key-Value）。就像你查英语字典，你要找的是“apple（Key）”，得到的是“苹果（Value）”。它的最大绝招是：找东西极快，自带去重和排序。
set（集合）：它就是一个只存 Key、没有 Value 的 map。就像去办个门禁卡，系统只关心“你在不在名单里”，不关心你叫什么别的属性。它同样自带去重和排序。

map 和 vector 的不同
vector：底层是数组，靠位置（下标/索引）访问数据。v[0] 找第一个元素。
map：底层是红黑树，靠键（Key）访问数据。m["apple"] 直接找到 apple 对应的值，你根本不用管它排在哪个位置。

list：频繁在中间插入/删除（比如：待办事项列表，今天插一个，明天删一个）。
vector：频繁随机访问，只在尾部添加（比如：排行榜、历史浏览记录）。
deque：频繁在头尾两头操作（比如：消息队列、撤销/重做）。
map：通过名字找东西（比如：电话簿、单词计数、学号查成绩）。
set：需要去重并判断是否存在（比如：黑名单、敏感词过滤）。

单词计数程序
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cctype>   // 用于 ispunct 和 tolower

using namespace std;

int main() {
    // 货架：标签是 string，值是 int
    map<string, int> word_count; 
    
    // 我们手动塞入两个单词
    string w1 = "apple";
    string w2 = "banana";
    string w3 = "apple";

    cout << "=== 刚开始货架是空的 ===" << endl;

    // 第一次遇到 apple
    ++word_count[w1]; 
    // 拆解：word_count["apple"] 发现没有 -> 创建默认值 0 -> 返回 0 -> ++ 变成 1
    // 第一次遇到 banana
    ++word_count[w2];
    // 第二次遇到 apple
    ++word_count[w3];
    // 拆解：word_count["apple"] 发现已经有了，值是 1 -> 返回 1 -> ++ 变成 
    cout << "\n=== 现在货架上的内容 ===" << endl;
    // 遍历打印（注意：map 会自动按字母顺序排序）
    for (const auto& pair : word_count) {
        // pair.first 是标签（单词）
        // pair.second 是数字（次数）
        cout << "单词: " << pair.first << " , 出现了: " << pair.second << " 次" << endl;
    }

    return 0;
}


map<string, size_t> word_count; 是个啥？
在 vector<int> 里，一个 int 就是一个格子。但在 map 里，一个格子是一对数据。
<string, size_t> 的意思是：这个货架上的每一层，左边贴着一个标签（string），右边放着一个数字（size_t）。
左边叫 key（键）：比如单词 "apple"。
右边叫 value（值）：比如单词出现的次数 1。
word_count 就是这个货架的名字。

word_count[word] 到底干了啥？
你平时用 vector 的时候，v[0] 就是找第 0 个格子。如果你找 v[100]，但数组只有 10 个元素，程序直接崩溃（越界）。
但 map 的 [] 简直就是个“保姆”，它会做以下判断：
假设你读入了一个单词 word = "apple"。
情况 A：货架上已经有 "apple" 了
你写 word_count["apple"]。
保姆直接把 "apple" 对应的那个次数（比如当前是 2）拿给你。
情况 B：货架上根本没有 "apple" （新手最容易懵的地方！）
你写 word_count["apple"]。
保姆发现货架上没这个东西，它不会报错，而是自动创建一个！
它会凭空建一个新的格子：左边贴上 "apple"，右边放个默认值 0（因为 size_t 是整数，默认初始值是0）。
然后，它把那个 0 拿给你。

++word_count[word]; 发生了什么？
有了上面的铺垫，这行代码简直绝妙。我们慢慢推演：
你读入了一个单词 word（假设它是 "apple"）。
你执行 word_count[word]。如果货架上有，它返回次数；如果没有，它自动创建一个次数为 0 的新格子，并返回 0。
前面的 ++ 符号，就是把这个返回的数字加 1。
如果原来返回的是 0（说明第一次见），加 1 变成 1，货架里的值更新为 1。
如果原来返回的是 2（说明见过了），加 1 变成 3，货架里的值更新为 3。

#endif


//p378
#if 0
set 和 list 的区别？
set = 排好队且拒绝重复的名单。你随便塞进去，它自动按字母顺序排好，且同一个人只能出现一次。
list = 谁都能进的大通铺。你按什么顺序放进去，它就是什么顺序，而且允许同名同姓的人出现多次。

家庭姓氏与孩子名字
题目要求：key 是姓（string），value 是孩子名字（vector<string>）。
核心难点：怎么往已有或新建的 vector 里塞孩子名字？
解法：依然利用 map 的 [] 魔法！family[last_name] 会返回那个 vector 的引用，你可以直接对它 push_back

#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;
int main() {
    cout << "=== 练习 11.7 ===" << endl;
    // 定义 map：键是 string，值是 vector<string>
    map<string, vector<string>> family;

    // 1. 添加新家庭，并直接添加孩子
    // 拆解：family["Smith"] 发现没这个姓，自动建一个空 vector。然后 push_back("Tom")
    family["Smith"].push_back("Tom"); 
    family["Smith"].push_back("Jerry");

    // 2. 给已有家庭添加新孩子
    // 拆解：family["Smith"] 找到了已有的 vector，继续 push_back("Alice")
    family["Smith"].push_back("Alice");

    // 3. 给另一个家庭添加孩子
    family["Johnson"].push_back("Bob");

    // 4. 遍历打印
    for (const auto& pair : family) {
        cout << "姓氏: " << pair.first << " | 孩子: ";
        for (const string& child : pair.second) { // pair.second 是一个 vector
            cout << child << " ";
        }
        cout << endl;
    }
    return 0;
}

姓氏: Johnson | 孩子: Bob 
姓氏: Smith | 孩子: Tom Jerry Alice 
自动按姓氏排好了序，而且孩子都塞进了对应的 vector 

为什么保存不重复单词要用 set 而不是 vector？
在 vector 里保不重复（极其痛苦）：
每次来一个新词，你必须遍历整个 vector，看看这个词是不是已经存在了。如果单词有 1 万个，每查一次都要比对 1 万次，速度极慢。
在 set 里保不重复（降维打击）：
set 底层是红黑树，自带“去重”属性，而且查找速度是 极快）。你无脑 insert 进去，它自动帮你搞定一切


#endif


//p381
#if 0
pair 想象成“一副手铐”或者“买一送一的套餐”。它永远只能装两个数据，不管这两个数据是什么类型（比如一个是 string，一个是 int）

#include <iostream>
#include <string>
#include <vector>
#include <utility> //  pair 定义在这个头文件里

int main() {
    cout << "=== 练习 11.12 & 11.13 ===" << endl;
    vector<pair<string, int>> vp;
    
    // 假设我们读到了一组数据
    string s1 = "apple", s2 = "banana", s3 = "cherry";
    int i1 = 10, i2 = 20, i3 = 30;

    // 方法一：使用花括号直接初始化（C++11 引入，最简单、最直观）
    vp.push_back({"apple", i1});

    // 方法二：使用标准库的 make_pair 函数（最老牌，无需写类型名）
    vp.push_back(make_pair(s2, i2));

    // 方法三：显式调用 pair 的构造函数（最啰嗦）
    vp.push_back(pair<string, int>(s3, i3));

    // 遍历打印看看
    for (const auto& p : vp) {
        cout << "单词: " << p.first << ", 数字: " << p.second << endl;
    }

    return 0;
}

vector<pair<string, int>> vp;
pair<string, int>
这是 C++ 标准库里自带的一个“小结构体”，它里面只有两个成员：
first：类型是 string
second：类型是 int
struct MyPair {
    string first;
    int second;
};
ector<pair<string, int>> vp; 就是定义了一个叫 vp 的数组（vector），数组里的每一个元素，都长这样：{"一个字符串", 一个整数}。

 vp 是个空数组，我们要往里面塞数据。vector 添加元素用 push_back，但 push_back 里面填什么？必须填一个 pair<string, int>。
：用花括号 {}（最简单、最推荐）
C++ 看到 push_back 的括号里是个 {...}，就知道你要造一个 pair。
vp.push_back({"apple", 10}); 


怎么把存进去的数据拿出来？
pair 里面有两个成员：first 和 second。
for (const auto& p : vp) {
    // p 是一个 pair
    cout << p.first << " 对应的数字是 " << p.second << endl;
}
#endif



//p383
#if 0
map<int, vector<int>> m;
key_type：钥匙的类型。也就是 int。（因为是 map<int, ...>）
mapped_type：值的类型。也就是 vector<int>。（因为是 map<..., vector<int>>）
value_type：整个元素的类型。也就是 pair<const int, vector<int>>。
为啥有个 const？ 因为 map 的钥匙是神圣不可修改的，一旦你把 int 放进去，它的值就锁死了，所以你只能修改里面的 vector<int>，不能修改那个 int。

map 的迭代器指向的是 pair 对象。因为 key 是 const 的，所以你只能改 .second。
map<string, int> m = {{"apple", 1}};
auto it = m.begin();
it->second = 100; //  合法，把 apple 的值改成 100

map 本质上是“自动帮你套上 pair 的机器”
当你写 map<string, int> m; 时，编译器在底层其实偷偷把它的元素类型规定死成了：
pair<const string, int>
map<string, int> m = {{"apple", 1}};
如果你不按 {"key": value} 这种 pair 的格式写，比如写成 m = {"apple"}，编译器直接报错，因为 map 认死理：“我只收 pair 格式的数据！”

为什么还要单独弄出个 vector<pair<string, int>>？
map 已经自动处理了 pair，为什么还要学 pair？
因为 vector 不是 map。vector 是个“大通铺”，它不知道你塞进去的数据是单个的，还是成对的。如果你想让 vector 存成对的数据，你必须手动告诉它：
“我的 vector 里装的不是 int，而是 pair<string, int> 这样的双人床。”

 如果不定义 pair，值到底存在什么地方？
 值就存在那个 pair 里面。

在 map 里，每一个元素都是一个 pair 对象。pair 有两个成员：
.first：存放键（如 "apple"）
.second：存放值（如 1）

#endif

//p386
#if 0




#endif

























































































































































































