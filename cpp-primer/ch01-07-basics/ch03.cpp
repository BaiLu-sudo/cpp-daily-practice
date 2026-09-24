#include <iostream>
#include <string>


#if 0
using std::cin;
using std::cout;
using std::endl;
using std::string;

void ex3_2(){
    string line;

    if(getline(cin,line)){
      cout << "读入一整行的结果: [" << line << "]" << endl;
    }

    string word;
    if(cin >>word){
        cout << "读入一个词的结果: [" << word << "]" << endl;
    }
}

void ex3_4(){
    string s1,s2;
    cin>>s1>>s2;
    if(s1==s2){
        cout<<"xiangdeng"<<endl;
    }else{
        if(s1>s2){
            cout<<"da:"<<s1<<endl;
        }else{
            cout<<"da:"<<s2<<endl;
        }
    }

        if (s1.size() == s2.size()) {
        cout << "两个字符串长度相等" << endl;
    } else {
        if (s1.size() > s2.size()) {
            cout << "长度较大的字符串是: " << s1 << endl;
        } else {
            cout << "长度较大的字符串是: " << s2 << endl;
        }
    }

}

void ex3_5(){
    string result;
    string word;

    while(cin>>word){
        result +=word;
    }
    cout<<result<<endl;
}

int main(){

}

#endif


//p90  vector
#if 0
圆括号 ()：表示“数量”。(n, val) 意思是“我要 n 个值为 val 的元素”
花括号 {}：表示“列表”。里面的数字就是你想要的具体内容。

vector<int> v1;元素个数：0（空 vector）
vector<int> v2(10);元素个数：10。元素的值：全部是 0
vector<int> v3(10, 42);元素个数：10。元素的值：全部是 42。
vector<int> v5{10, 42};元素个数：2。元素的值：10 和 42。
vector<string> v6{10}; 元素个数：10。元素的值：10 个空字符串 ""。因为 {} 想把你给的 10 当作“列表里的元素”，但 10 是个 int，无法装进 vector<string> 里。于是编译器退而求其次，把 {10} 解释成了 (10)，变成了“10 个默认初始化的元素”。

int n;
cin >> n;           // 用户输入 100
vector<int> v(n);   // 完美！直接创建 100 个元素的 vector

#endif


//p94 vector use
#if 0
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

void ex3_14(){
    vector<int> v;
    int x;
    
    while(cin>>x){
        v.push_back(x);
    }
    cout << "ni shu ru de zheng shu";
    for(auto i : v){
        cout << i << " ";
    }
    cout <<endl;
}

int main(){
    ex3_14();
    return 0;
}

#endif


//p94 3.3.3
#if 1
#define duicuo  0
#if duicuo
vector<int> ivec; 
ivec[0] = 42;   不合法
vector<int> ivec; 创建的是一个空 vector 
vector<int> ivec(10); ivec[0] = 42;（先创建 10 个元素，再修改第 1 个）
#endif

#include <vector>
#include <string>
#include <cctype>

using std::cin; using std::cout; using std::endl;
using std::vector; using std::string;

void ex3_17(){
    vector<string>words;
    string word;
    while(cin>>word){
        words.push_back(word);//把读到的字符串塞进 vector 的末尾
    }

    cout<<"gai wei da xie"<<endl;
       for (auto &w : words) {     
            for (auto &c : w) {     
            c = toupper(c);     
        }
        cout << w << endl;
    }
}

#endif


//p99 迭代器的标准遍历代码
#if 1

#define zhushi 0
#if zhushi
for(int i=0;i<v.size();++i){
    cout <<v[i]<<endl;
}
for(auto it=v.begin();it !=v.end();++it){
    cout<<*it<<endl;
}
#endif


//打印 vector 大小和内容
void ex3_21(){
    vector<int>v5{10,42};
    vector<string>v6{10};
    vector<string>v7{10,"hi"};

    cout<<"v5 neirong;";
    for(auto it =v5.begin();it !=v5.end();++it){
        cout << *it << " ";
    }
    cout <<endl;

    cout<<"v7 neirong:";
     for (auto it = v7.begin(); it != v7.end(); ++it) {
        cout << "\"" << *it << "\" ";
    }
    cout << endl;
}

#endif

//p101 
#if 1

#include <vector>
#include <string>

using std::cin; using std::cout; using std::endl;
using std::vector; using std::string;
//相邻元素求和 & 首尾配对求和
void ex3_24(){
    vector<int>v;
    int x;
    while(cin>>x){
        v.push_back(x);
    }
    for(auto it=v.begin(); it != v.end() - 1; ++it){
         cout << *it + *(it + 1) << " ";
    }
    cout << endl;

//首尾配对求和
  auto beg=v.begin();
  auto end=v.end() = v.end() - 1;
  while (beg < end) {
    cout << *beg + *end << " ";
    ++beg; 
    --end;
    if (beg == end) {
         cout << *beg << " ";
    }  
      cout << endl;
}
#endif


//p103 数组
#if 0
unsigned buf_size = 1024;
int ia[buf_size]; 非法buf_size 是一个普通的 unsigned 变量编译器不允许一个数组的大小是可变
char st[11] = "fundamental"; 非法 看起来 st[11] 刚好放下。但是，C++ 的字符串末尾隐藏了一个结束符 \0


 假定 p1 和 p2 指向同一个数组中的元素， 则下面程序的功能是什么？ 什么
情况下该程序是非法的？

p1 在第 1 格，p2 在第 5 格。p2 - p1 算出来是 4 格。
让 p1 往前走 4 格，到达第 5 格。
最后 p1 = p2


两个指针相加为什么没意义？
指针存的不是数字，而是内存地址（门牌号）


#endif


//p113
#if 0
#include <vector>
#include <iterator>

using std::cout;using std::cin; using std::endl;
using std::vector;

void ex3_41(){
    int arr[]={1,2,3,4,5};
    vector<int>v(std::begin(arr),std::end(arr));
    for(int x : arr)cout<<x<<"";
    cout<<endl;

    for(int x :v)cout<<x<<"";
    cout<<endl;
}


// 练习 3.42：将含有整数元素的 vector 拷贝给一个整型数组
/*
decltype(v.size()) 的意思就是：“编译器老兄，你去看看 v.size() 是什么类型，
然后把我括号里的 i 定义成一模一样的类型。”
*/

void ex3_42(){
    vector<int>v={10,20,30,40,50};
    int arr[5];
 for (decltype(v.size()) i = 0; i < v.size(); ++i) {
        arr[i] = v[i];
    }
    for (int x : v) cout << x << " ";
    cout << endl;
     for (int x : arr) cout << x << " ";
    cout << endl;
}

int main() {
    ex3_41();
    ex3_42();
    return 0;
}
#endif

















































