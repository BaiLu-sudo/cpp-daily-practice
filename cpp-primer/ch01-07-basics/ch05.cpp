//p155
#if 0
空语句就是一个孤零零的分号 ;
故意制造延迟（在嵌入式开发中常见）
for (int i = 0; i < 1000000; ++i) 
    ; // 循环空转，只是为了浪费时间

坑点：写 if 或 while 时，千万不要在条件后面不小心多打一个分号
while (i < 10); // ⚠️ 灾难！这个分号意味着循环体是空的，死循环！
{
    cout << i << endl; // 这段代码根本不属于 while，只会执行一次
}

用逗号运算符重写后（把循环体里的两条语句用逗号连成一条，从而去掉花括号）：
int sum=100,val=50;
while(val<=100)
 sum +=val,++val;

#endif


//p156
#if 0
while (string::iterator iter != s.end())\
语法错误：while 的条件部分（括号里）只能放表达式，不能用来定义变量。你不能写 while (类型 变量名 != ...)。
逻辑错误：就算你写成 while (string::iterator iter = s.begin())，它每次循环都会重新定义 iter 并初始化，你永远别想走到 s.end()（死循环）。

string::iterator iter =s.begin();
while(iter !=s.end()){
    ++iter;
}
#endif

//p159
#if 0
if-else 实现数字成绩转字母成绩
if(grate >=90) cout<<"a";
else if (grate >=80) cout<<"b";
else if (grate >=70) cout<<"c";
else if (grate >=60) coutL<<"d";
else  cout<<"f";


用条件运算符重写
string letter = (grade >= 90) ? "A" :
                (grade >= 80) ? "B" :
                (grade >= 70) ? "C" :
                (grade >= 60) ? "D" : "F";


if (int ival = get_value())
    cout << "ival = " << ival << endl;
if (!ival) // 报错：ival 未定义
    cout << "ival = 0\n";
 ival 是在第一个 if 里面定义的，它的生命周期只在第一个 if 内部。第二个 if 找不到它。   
    


if (ival = 0) //  这是赋值 把 0 塞给 ival，条件永远是 false
    ival = get_value();
#endif

//p164
#if 0
//统计元音字母
#include <iostream>
#include<cctype>

using std::cin; using std ::cin; using std ::endl;
int main(){ 
    unsigned aCnt = 0, eCnt = 0, iCnt = 0, oCnt = 0, uCnt = 0;
    unsigned spaceCnt = 0, tabCnt = 0, newlineCnt = 0;
    unsigned ffCnt = 0, flCnt = 0, fiCnt = 0;
    
     char c;
    char prev = '\0'; // 用于记录前一个字符，判断 ff / fl / fi

        while (cin.get(c)) {
        // 5.10: 统计元音（大小写都算）
        // 利用 tolower 转成小写再判断，兼容性最好
        char lower_c = std::tolower(c);
        if (lower_c == 'a') ++aCnt;
        else if (lower_c == 'e') ++eCnt;
        else if (lower_c == 'i') ++iCnt;
        else if (lower_c == 'o') ++oCnt;
        else if (lower_c == 'u') ++uCnt;

        // 5.11: 统计空白字符
        if (c == ' ') ++spaceCnt;
        else if (c == '\t') ++tabCnt;
        else if (c == '\n') ++newlineCnt;

        // 5.12: 统计双字符序列
        if (prev == 'f') {
            if (c == 'f') ++ffCnt;
            else if (c == 'l') ++flCnt;
            else if (c == 'i') ++fiCnt;
        }
        
        prev = c; //  别忘了把当前字符变成“前一个字符”
    }
}


switch (ch) {
    case 'a': aCnt++;
    case 'e': eCnt++;
    default: iouCnt++;
}漏写 break 导致的“贯穿”
错误：如果输入 'a'，aCnt 加 1 后，代码不会停，会继续往下执行 eCnt++ 和 iouCnt++，导致所有计数器都加了一遍。
修正：每个 case 后面都加上 break;

case 1:
    int ix = get_value(); //  编译报错或逻辑大坑！
    ivec[ix] = index;
    break;
错误：C++ 规定，switch 内的变量作用域会跨越所有 case。如果在 case 1 里定义了 ix，而在 case 2 里跳过了 case 1 直接执行，ix 就会处于“未初始化”的诡异状态。
修正：把变量定义放到 switch 外面，或者用花括号 {} 把 case 括起来：

case 1, 3, 5, 7, 9: // 严重语法错误
    oddcnt++;
    break;
错误：case 标签后面只能跟一个常量表达式。1, 3, 5, 7, 9 会被解析成逗号表达式，最终只等价于 case 9:，前面的数字全被忽略。
修正：必须拆开写
case 1: case 3: case 5: case 7: case 9:
    oddcnt++;
    break;

 unsigned ival = 512, jval = 1024, kval = 4096;
// ... 省略 ...
switch(swt) {
    case ival: //  编译报错！
        // ...
}  
错误：case 标签必须是编译时常量。ival 是变量，它的值在程序运行时才确定，不能作为 case 标签。 
const unsigned ival = 512;
switch(swt) {
    case ival: //  合法
        break;
}

#endif

//p166
#if 0

#include<iostream>
#include<string>
using std::cin; using std::cout; using std::endl; using std::string;
int main() {
    string currWord, prevWord, maxWord;
    unsigned currCnt = 0, maxCnt = 0;

    cout << "请输入一段文本（按 Ctrl+D 结束输入）：" << endl;

    // cin >> 会自动跳过空格和换行，完美适合读单词
    while (cin >> currWord) {
        if (currWord == prevWord) {
            // 如果新来的单词和上一个一样，计数加 1
            ++currCnt;
        } else {
            // 如果不一样，说明连续中断了，重置计数器为 1
            currCnt = 1;
            prevWord = currWord; // 更新记忆
        }

        // 核心：每读一个单词，都去挑战一下最高记录
        if (currCnt > maxCnt) {
            maxCnt = currCnt;
            maxWord = currWord;
        }
    }

#endif 


//p168
#if 0
for (int ix = 0; ix != sz; ++ix) { /* ... */ }
错误：如果 sz 是负数，ix 从 0 开始递增，ix != sz 永远为真，导致死循环。
修正：换成 < 判断更安全。for (int ix = 0; ix < sz; ++ix)



编写一段程序，从标准输入中读取 string对象的序列直到连续出现两个相
同的单词或者所有单词都读完为止。 使用 whi1e 循环一次读取一个单词， 当一个单词
连续出现两次时使用 break语句终止循环。 输出连续重复出现的单词， 或者输出一个
消息说明没有任何单词是连续重复出现的

你要对比当前单词和前一个单词。
如果它们一样，立刻大喊一声“找到了！”，然后使用 break 拍下急停按钮，跳出循环。
如果不一样，就把当前单词记到脑子里（更新 prevWord），然后继续读下一个。
如果一直读到结束都没找到，就标记一下“没找到”。

#include<iostream>
#include<string>

using std::cin; using std::cout; using std::endl;
using std::string;

int main(){
    sting word,preWord;
    bool found =false;
     cout << "请输入一组单词（按 Ctrl+D 结束输入）：" << endl;

     while(cin<<word){
        if(woed==prevWord){
             found = true;
              break; //  找到连续重复的，立刻跳出 while 循环
        }
         prevWord = word; // 如果没有重复，把当前单词存为“前一个单词”
     }
     if (found) {
        cout << "连续重复出现的单词是: " << word << endl;
    } else {
        cout << "没有任何单词是连续重复出现的。" << endl;
    }
    return 0;
}

#endif

//p171 continue
#if 0
continue 的作用：它会直接中止当前这一轮循环剩下的代码，跳回到 while (cin >> word) 去读下一个单词。所以下面的 if (word == prevWord) 根本不会被执行。



#endif

















































































































































































































