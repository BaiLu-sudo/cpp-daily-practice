#include<iostream>

//p8
#if 0
void ex1_3(){
    std::cout<<"hello world"<<std::endl;
}

void ex1_4(){
    std::cout<<"enter two number:"<<std::endl;
    int v1 =0 , v2=0;
    std:: cin >> v1 >>v2;
    std::cout <<"the product is"<<v1 * v2<< std::endl;
}

int main(){
    ex1_3();
    return 0;
}
#endif
 
//p11

#if 0

void ex1_9(){
    int sum =0;
    int val=50;

    while(val <= 100){
        sum +=val;
        val ++;
    }
    std::cout << "total:" <<sum<< std::endl;
}

void ex1_10(){
    int val =10;
    while(val >= 0){
      std::cout<<val<<"";
      --val;
    }

    std::cout<<std::endl;
}

void ex1_11(){
    std::cout<< "shu ru liang ge zhengshu:";
    int v1=0,v2=0;
    std::cin >> v1>>v2;
    if(v1>v2){
        int temp =v1;
        v1 =v2;
        v2 =temp;
    }
    std::cout <<"suo you zhengs shu";
    while(v1<=v2){
        std::cout<<v1<<"";
        ++v1;
    }
    std::cout <<std::endl;


}

int mian(){
    ex1_11;
    return 0;
}


#endif

#if 1

void ex1_13_9(){
    int sum=0;
    for(int val=50;val <=100;val++){
        sum +=val;
    }
    std::cout<<"50到100:"<<sum<<std::endl;
}


void ex1_13_10(){
    for(int val=10;val>=0;val --){
        std::cout<<val<<"";
    }
    std::cout<<std::endl;
}

void ext1_13_11(){
    std::cout<<"lianggezhengshuwei:";
    int v1=0,v2=0;
    if(v1>v2){
        int temp=v1;
        v1=v2;
        v2=temp;
    }

    std::cout<<"zhengshu:";
    for(int i=v1;i<v2;i++){
        std::cout<<i;
    }
     std::cout<<std::endl; 
}


int main(){
    ex1_13_9();
}

#endif


