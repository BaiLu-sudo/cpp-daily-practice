#include <iostream>
#include <string>


#if 1
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



































