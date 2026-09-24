 第二章节
 如何选择类型：
    1、在算术表达式中不要使用 char或 boo1，机器识别不一样。用 sianed char或者 unsigned cbar

    2、执行浮点数运算选用 doub1e，这是因为 float通常精度不能而日双精度浮点数和单精度浮占数的计算代价相差无几。
    
无符号类型和带符号类型的区别易错：无符号类型能表示的正数上限是带符号类型的两倍。如果你给无符号变量赋一个负数（比如 unsigned int u = -1;），它会被转换为一个极其庞大的正数，初学者极易在此处踩坑导致死循环。    


const:引用必须绑定到对象，const 变量和 const 指针必须初始化
const int *p;  不能改 *p 的值   顶层 
int *const p;  可以修改 *p 的值 但是却不能修改地址& 底层
const int *const p 双重锁死：既不能改指向，也不能改值。

易错：std::string isbn() const{return bookNo; }    
不加const：const Sales_data，
data2;  // 这是一个常量对象，只读！
data2.isbn();  // 编译报错！
解析：
data2 是 const 的，它生怕 isbn() 这个函数会在背地里偷偷修改 data2 的数据。但是 isbn() 后面没有加 const 做出“不修改”的承诺，所以编译器直接拦下来，保护了 data2。


第三章节
头文件不应包含 using声明.
如果头文件里有某个 using声明，
那么每个使用了该头文件的文件就都会有这个声明。对于某些程序来说，由于不经意间包
含了一些名字， 反而可能产生始料未及的名字冲突

优先用 vector，忘掉原本的 int arr[]